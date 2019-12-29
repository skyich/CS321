#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send3");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank != 0) {
		int x[4];
		for (int i = 0; i < 4; ++i)
			pt >> x[i];
		MPI_Send(&x, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		for (int i = 1; i < size; ++i) {
			int x[4];
			MPI_Recv(&x, 4, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (int j = 0; j < 4; ++j)
				pt << x[j];
		}
	}
}
