#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI1Proc3");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double x;
	if (rank == 0) {
		pt >> x;
		pt << -x;
		Show("-X=", -x);
	}
	else {
		pt << rank;
		Show("rank=", rank);
	}
}
