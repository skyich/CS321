#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm27");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double n;
	pt >> n;

	int* dims = new int[3];
	dims[0] = 2;
	dims[1] = 2;
	dims[2] = size / 4;

	int* periods = new int[3];
	periods[0] = 0;
	periods[1] = 0;
	periods[2] = 1;

	MPI_Comm dcomm;
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, false, &dcomm);

	int rank_s, rank_d;
	MPI_Cart_shift(dcomm, 2, 1, &rank_s, &rank_d);

	MPI_Sendrecv_replace(&n, 1, MPI_DOUBLE, rank_d, 0, rank_s, 0, dcomm, MPI_STATUSES_IGNORE);
	pt << n;
}
