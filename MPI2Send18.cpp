#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;
	double buf[5];
	pt >> n;
	for (int i = 0; i < n; ++i)
		pt >> buf[i];

	int next_rank;
	if (rank % 2 == 0 || rank == 0)
		next_rank = rank + 1;
	else
		next_rank = rank - 1;

	MPI_Status status;
	MPI_Sendrecv_replace(&n, 1, MPI_INT, next_rank, 0, next_rank, 0, MPI_COMM_WORLD, &status);
	MPI_Sendrecv_replace(&buf, 5, MPI_DOUBLE, next_rank, 0, next_rank, 0, MPI_COMM_WORLD, &status);

	int i = 0;
	for (int i = 0; i < n; ++i)
		pt << buf[i];
}
