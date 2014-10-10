#include "process.h"

Process::Process() {}

//Assign the rank and total number of processes
Process::Process(int p, int r) : rank_(r), procs_(p) {}

Process::~Process() {}

void Process::processMaster() {

    //Create data members
    stats_ = Stats();
    Deck d;
    active_ = procs_ - 1;

    //Print header information and start timer
    stats_.printHeader();
    stats_.start();

    //Loop through until the master and all the slaves have found all of the hands
    while (!stats_.allHandsFound()) {

        //Draw hand and increment it in the stats object
        Hand h = d.dealHand();
        stats_.increment(h.type());

        //Check for any messages from the slaves ie. hand types
        checkMessages();
    }

    //All hands found so terminate the other processes
    terminateSlaves();

    //While there is any active slave process keep checking for the termination signal
    while (active_ > 0) {
        checkMessages();
    }

    //Stop the timer and print the footer and hand frequencies
    stats_.stop();
    stats_.printHands();
    stats_.printFooter(procs_);
}

void Process::processSlave(int r) {

    //Create stats and deck object
    Stats s;
    Deck d;

    //MPI related variables
    static int flag = 0;    //Recieved message from master
    MPI_Status status;
    MPI_Request request;

    //Loop until either all the hands were found, or the master told to terminate
    while (!s.allHandsFound() && !flag) {

        //Check the channel for any messages
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);

        //Deal a hand and increment the local stats object
        Hand h = d.dealHand();
        int type = h.type();
        s.increment(type);

        //If it is a new hand, inform the master that a new hand type has been found
        if (s.getTypeCount(h.type()) == 1) { 
            MPI_Isend(&type, 1, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD, &request);
        }
    }

    //Inform the master that slave is quitting, so it can wait for the frequencies
    int hand = s.getHands(); // not really needed
    MPI_Send(&hand, 1, MPI_INT, 0, TAG_QUIT, MPI_COMM_WORLD);

    //Gather the total number of hands drawn for each type into an array
    int hands[10];
    for (int i = 0; i < 10; ++i) {
        hands[i] = s.getTypeCount(i);
    }

    //Send array of all hands to the master
    MPI_Isend(&hands, 10, MPI_INT, 0, TAG_FREQS, MPI_COMM_WORLD, &request);
}

void Process::checkMessages() {

    //MPI related variables
    static int hand, recievedFlag;
    MPI_Status status;

    //Check the channel for any messages
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recievedFlag, &status);

    //If message was found do some work
    if (recievedFlag) {
        MPI_Recv(&hand, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        //If slave found a new hand type increment the master stats object
        if (status.MPI_TAG == TAG_DATA) {
            stats_.increment(hand);
        }
        //If slave is quitting decrement the active count and listen for the array of frequencies
        else if (status.MPI_TAG == TAG_QUIT) {
            --active_;
            recieveStats(status.MPI_SOURCE);
        }
        //catch all error handling
        else {
            std::cout << "checkMessages() : else {} - Hand: " << hand << " Process: " << status.MPI_SOURCE << std::endl;
        }
    }
}

//Recieve the array of hands from the slave processes
//Accepts slave rank
void Process::recieveStats(int s) {
    MPI_Status status;
    int hands[10];
    MPI_Recv(hands, 10, MPI_INT, s, TAG_FREQS, MPI_COMM_WORLD, &status);

    //Use the stats() second increment method to increment multiple hands at once
    for (int i = 0; i < 10; ++i) {        
        if (hands[i] != -1) {
            stats_.increment(i, hands[i]);
        }
    }
}

//Send the terminate signal to all the slave processes
void Process::terminateSlaves() {
    int msg = 0;
    for (int i = 1; i < procs_; ++i)
        MPI_Send(&msg, 1, MPI_INT, i, TAG_QUIT, MPI_COMM_WORLD);
}