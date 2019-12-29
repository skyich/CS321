#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int new_size = 3 * size;
	int* numbers = new int[new_size];
	for (int i = 0; i < new_size; ++i)
		pt >> numbers[i];

	int* result = new int[new_size];
	MPI_Alltoall(numbers, 3, MPI_INT, result, 3, MPI_INT, MPI_COMM_WORLD);
	for (int i = 0; i < new_size; ++i)
		pt << result[i];
}
