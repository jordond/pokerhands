#include <iostream>
#include <fstream>
#include <string>
#include "parallel_main.h"
#include "mpi.h"
using namespace std;


const int MAX_MSG_SIZE = 100;
const int TAG_DATA = 0, TAG_QUIT = 1;

void dispatchSins(int numProcs, int& totalHands, ifstream& in)
{
	int msgBuff[MAX_MSG_SIZE];

	// Dispatch a "wave" of SINs to the slaves
	int numToSend = MAX_MSG_SIZE;
	for (int p = 1; p < numProcs; ++p)
	{
		// Fill the message buffer
		for (int i = 0; i < MAX_MSG_SIZE; ++i)
		{
			if (!(in >> msgBuff[i]))
			{
				numToSend = i;
				break;
			}
		}

		// Update the SINs counter
		totalHands += numToSend;

		// Send
		MPI_Send(msgBuff, numToSend, MPI_INT, p, TAG_DATA, MPI_COMM_WORLD);
	}

}

void terminateSlaves(int numProcs)
{
	int msgBuff = 0;
	for (int p = 1; p < numProcs; ++p)
		MPI_Send(&msgBuff, 1, MPI_INT, p, TAG_QUIT, MPI_COMM_WORLD);
}

void checkMessagesFromSlaves(int& activeCount)
{
	static int msgBuff, recvFlag;
	MPI_Status status;
	static MPI_Request request;

	if (request)
	{
		// Already listening for a message

		// Test to see of a message has "come in"
		MPI_Test(&request, &recvFlag, &status);

		if (recvFlag)
		{
			// Message has "come in"
			if (status.MPI_TAG == TAG_DATA)
				// Invalid SIN
				cout << "\t** Invalid Hand: " << msgBuff << " found by process "
				<< status.MPI_SOURCE << endl;
			else
				// Slave is quitting
				--activeCount;

			// Reset the request handle to "false"
			request = 0;
		}
	}

	// TO DO: Test to see if it's time to start listening (again)

}


void processMaster(int numProcs)
{
	Stats s;
	Deck d;

	cout << "using " << numProcs
		<< " processes..." << endl << endl;

	// Declare counters
	int totalHands = 0;
	int activeCount = numProcs - 1;

	//start the master process timer
	double masterTimer = MPI_Wtime();
		

	// main loop while there are any slaves still "active"
	bool deadSlaves = false;

	//loop needs work. probably wrong
	while (activeCount > 0)
	{
		// IF there are more Hands
		if (!s.allHandsFound()){
			do {
				Hand h = d.dealHand();

				//Increment the stats object with the found hand
				s.increment(h.type());
			} while (!s.allHandsFound());
		}
		else{
			// ELSE Sends a TERMINATE message to each slave
			terminateSlaves(numProcs);
			deadSlaves = true;
		}

		// Checks for a message from any slave(NON - BLOCKING)
		checkMessagesFromSlaves(activeCount);
	}
}

void processSlave(int rank){
	// Message passing variables
	int msgBuff[MAX_MSG_SIZE];
	MPI_Status status;
	MPI_Request request;
	int numRecv;

	// Validation variables
	//CSin sinVal;

	// main loop until a TERMINATE message is received
	do
	{
		// Receive a message from the master
		MPI_Recv(msgBuff, MAX_MSG_SIZE, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		// IF it's a DATA message
		if (status.MPI_TAG == TAG_DATA)
		{
			MPI_Get_count(&status, MPI_INT, &numRecv);

			// Validate the SINs in the message buffer
			for (int i = 0; i < numRecv; ++i)
			{
				// For each invalid SIN... 
				//if (!sinVal.set(msgBuff[i]))
					// ... Send a message to the master
				//	MPI_Isend(&msgBuff[i], 1, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD, &request);
			}

		}
		//ELSE
		else
			// Sends a DONE message to the master
			MPI_Send(&msgBuff[0], 1, MPI_INT, 0, TAG_QUIT, MPI_COMM_WORLD);

	} while (status.MPI_TAG != TAG_QUIT);
}




int main(int argc, char* argv[]) {

	if (MPI_Init(&argc, &argv) == MPI_SUCCESS){

		//Create stat counting object, and the deck
		Stats s;
		Deck d;
		
		int rank, numProcs;

		MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

		//continue if there is at least one slave process
		if (numProcs > 1){
			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			if (rank == 0)
				processMaster(numProcs);
			else
				processSlave(rank);
		}

		//Print message to user
		s.printHeader();

		//Start the timer 
		s.start();

		//Perform dealing hand until all hands are found
		//do {
		//	Hand h = d.dealHand();

		//	//Increment the stats object with the found hand
		//	s.increment(h.type());
		//} while (!s.allHandsFound());

		//Stop the timer and print the information
		s.stop();
		s.printHands();
		s.printFooter();
	}
	else
		cerr << "Error: invalid input." << endl;

	MPI_Finalize();
	

    //debugHandType(); // deprecated see Hand.cpp line 5
    //debugVariableHands();
    //debug250000Hands();
    //debugFindAllHands();
    return 0;
}


void debugHandType() {
    ////DEBUG
    Deck d;
    Stats s;
    int hands_ = 0;
   
    std::string cards;
    do {
        std::cout << "Suit: Diamond0, Hearts1, Club2, Spade3" << std::endl;
        std::cout << "Rank: Ace0/a, 1-10, Jack11/j, Queen12/q, King13/k, Ace14/a" << std::endl;
        std::cout << "Enter hand (" << Card::HAND_SIZE << ") cards - 0 to quit:";
        std::cin >> cards;

        Hand h = cards;

        if (h.type() != Hand::None) {
            std::cout << "Hand entered: " << cards;
            std::cout << "Hand parsed: " << h.readable();
            std::cout << "Hand type: " << h.type();
        }
    } while (cards != "0");
    
    std::cout << "Hands Drawn: " << hands_ << " Decks drawn: " << d.getDecks() << std::endl;
}
void debugVariableHands() {
    int count = 0;
    do {
        count = 0;
        std::cout << "Enter number of hands (0 to quit): ";
        std::cin >> count;
        std::vector<double> t;

        Deck d;
        Stats s;
        for (int i = 0; i <= count; ++i) {
            s.start();
            Hand h = d.dealHand();
            s.increment(h.type());
            s.stop();
            t.push_back(s.getClock());
        }
        s.printHands();

        double totaltime = 0.0;
        for (std::vector<double>::iterator it = t.begin(); it != t.end(); ++it) {
            totaltime += *it;
        }
        std::cout << "Average time per hand:\t" << totaltime / t.size() << std::endl;
        std::cout << "Total time:\t" << totaltime << std::endl;

        if (s.allHandsFound())
            std::cout << "All hands have been found.\n" << std::endl;
        else
            std::cout << "Missing some hands, luck is not in your favor.\n" << std::endl;
    } while (count > 0);
}
void debug250000Hands() {
    Deck d;
    Stats s;
    std::cout << "Drawing 250k hands..." << std::endl;
    for (int i = 0; i <= 250000; ++i) {
        Hand h = d.dealHand();
        s.increment(h.type());
    }
    s.printHands();
    if (s.allHandsFound())
        std::cout << "All hands have been found." << std::endl;
    else
        std::cout << "Missing some hands, luck is not in your favor." << std::endl;
}
void debugFindAllHands() {
    Deck d;
    Stats s;
    int count = 0;
    s.printHeader();
    s.start();
    do {
        Hand h = d.dealHand();
        s.increment(h.type());
        count++;
    } while (!s.allHandsFound());
    s.stop();
    s.printHands();
    s.printFooter();
}