#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;
	pt >> n;

	int* dims = new int[3];
	dims[0] = 2;
	dims[1] = 2;
	dims[2] = size / 4;

	int* periods = new int[3];
	periods[0] = 0;
	periods[1] = 0;
	periods[2] = 0;

	MPI_Comm dcomm;
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, false, &dcomm);

	MPI_Comm ncomm;
	int remain_dims[3] = { 1, 1, 0};
	MPI_Cart_sub(dcomm, remain_dims, &ncomm);

	int numbers[4];
	MPI_Gather(&n, 1, MPI_INT, numbers, 1, MPI_INT, 0, ncomm);
	
	int nrank;
	MPI_Comm_rank(ncomm, &nrank);
	if (nrank == 0)
		for (int i = 0; i < 4; ++i)
			pt << numbers[i];
}
