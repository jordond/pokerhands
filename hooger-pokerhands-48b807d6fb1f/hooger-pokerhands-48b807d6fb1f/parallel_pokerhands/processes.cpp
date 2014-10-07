#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
using namespace std;

const int MAX_MSG_SIZE = 100;
const int TAG_DATA = 0, TAG_QUIT = 1;

void dispatchSins(int numProcs, int& totalSins, ifstream& in)
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
		totalSins += numToSend;

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


	// Declare counters
	int activeCount = numProcs - 1;

	// main loop while there are any slaves still "active"
	while (activeCount > 0)
	{
		// IF there are more Hands

		// ELSE Sends a TERMINATE message to each slave
		terminateSlaves(numProcs);


		// Checks for a message from any slave(NON - BLOCKING)
		checkMessagesFromSlaves(activeCount);
	}
}

