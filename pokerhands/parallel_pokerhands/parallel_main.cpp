#include "parallel_main.h"

int main(int argc, char* argv []) {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
        int rank, numProcs;
        MPI_Comm_size(MPI_COMM_WORLD, &numProcs);


		//should be able to run with just 1 process
       // if (numProcs > 1) {
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);

            Process p(numProcs, rank);

            if (rank == 0) {
                p.processMaster();
            }
            else {
                p.processSlave(rank);
            }
       // }
        
    }
	else {
		std::cerr << "Invalid input..." << std::endl;
	}
	MPI_Finalize();
    return 0;
}

