#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm1");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int nsize = size / 2 + 1;

	MPI_Group MPI_GROUP_WORLD;
	MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
	
	MPI_Group even;
	int* ranks = new int[nsize];
	for (int i = 0, j = 0; i < nsize; ++i, j += 2)
		ranks[i] = j;
	MPI_Group_incl(MPI_GROUP_WORLD, nsize, ranks, &even);

	MPI_Comm even_comm;
	MPI_Comm_create(MPI_COMM_WORLD, even, &even_comm);

	int* numbers = new int[nsize];
	int x;
	if (rank == 0)
		for (int i = 0; i < nsize; ++i)
			pt >> numbers[i];
	
	MPI_Scatter(numbers, 1, MPI_INT, &x, 1, MPI_INT, 0, even_comm);

	if (rank % 2 == 0)
		pt << x;
}
