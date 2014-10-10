#include "parallel_main.h"

int main(int argc, char* argv []) {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
        int rank, numProcs;
        MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

        if (numProcs > 1) {
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);

            Process p(numProcs, rank);

            if (rank == 0) {
                p.processMaster();
            }
            else {
                p.processSlave(rank);
            }
        }
        else {
            std::cerr << "This program requires more than one process!" << std::endl;
        }
        MPI_Finalize();
    }
    return 0;
}

