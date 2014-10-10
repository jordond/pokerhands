#include "process.h"

Process::Process() {}

Process::Process(int p, int r) : rank_(r), procs_(p) {
}

Process::~Process() {}

void Process::processMaster() {
    stats_ = Stats();
    Deck d;
    active_ = procs_ - 1;

    stats_.printHeader();
    stats_.start();

    while (!stats_.allHandsFound()) {
        Hand h = d.dealHand();
        stats_.increment(h.type());

        checkMessages();
    }
    terminateSlaves();

    while (active_ > 0) {
        checkMessages();
    }

    stats_.stop();
    stats_.printHands();
    stats_.printFooter(procs_);
}

void Process::processSlave(int r) {
    Stats s;
    Deck d;

    static int flag = 0;
    MPI_Status status;
    MPI_Request request;

    while (!s.allHandsFound() && !flag) {
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);

        Hand h = d.dealHand();
        int type = h.type();
        s.increment(type);

        if (s.getTypeCount(h.type()) == 1) { //is new hand
            MPI_Isend(&type, 1, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD, &request);
        }
    }
    int test = 0;
    MPI_Send(&test, 1, MPI_INT, 0, TAG_QUIT, MPI_COMM_WORLD);

    int hands[10];
    for (int i = 0; i < 10; ++i) {
        hands[i] = s.getTypeCount(i);
    }
    MPI_Isend(&hands, 10, MPI_INT, 0, TAG_FREQS, MPI_COMM_WORLD, &request);
}

void Process::checkMessages() {
    static int hand, recievedFlag;
    MPI_Status status;
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recievedFlag, &status);

    if (recievedFlag) {
        MPI_Recv(&hand, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == TAG_DATA) {
            std::cout << "Process " << status.MPI_SOURCE << " found Hand: " << hand << std::endl;
            stats_.increment(hand);
        }
        else if (status.MPI_TAG == TAG_QUIT) {
            --active_;
            std::cout << "Process " << status.MPI_SOURCE << " is exiting." << std::endl;
            recieveStats(status.MPI_SOURCE);
        }
        else {
            std::cout << "checkMessages() : else {} - Hand: " << hand << " Process: " << status.MPI_SOURCE << std::endl;
        }
    }
}

void Process::recieveStats(int s) {
    MPI_Status status;
    int hands[10];
    MPI_Recv(hands, 10, MPI_INT, s, TAG_FREQS, MPI_COMM_WORLD, &status);

    for (int i = 0; i < 10; ++i) {        
        if (hands[i] != -1) {
            std::cout << "Increment handtype: " << i << ", with value = " << hands[i] << std::endl;
            stats_.increment(i, hands[i]);
        }
    }
}

void Process::terminateSlaves() {
    int msg = 0;
    for (int i = 1; i < procs_; ++i)
        MPI_Send(&msg, 1, MPI_INT, i, TAG_QUIT, MPI_COMM_WORLD);
}