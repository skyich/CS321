#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int i = 1; i < size; ++i) {
			double x;
			MPI_Status status;
			MPI_Recv(&x, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, &status);
			pt << x;
		}
	}
	else {
		int n;
		double a;
		pt >> a;
		pt >> n;
		MPI_Send(&a, 1, MPI_DOUBLE, 0, n, MPI_COMM_WORLD);
	}
}
