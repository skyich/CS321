#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank != 0) {
		int x;
		pt >> x;
		if (x != 0)
			MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		int x;
		MPI_Status status;
		MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&x, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
		pt << x;
		pt << status.MPI_SOURCE;
	}
}
