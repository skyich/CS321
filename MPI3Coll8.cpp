#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI3Coll8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double* numbers = new double[size];
	int* displs = new int[size];
	std::vector<int> count(size, 1);

	if (rank == 0) {
		for (int i = 0; i < size; ++i) {
			pt >> numbers[i];
			displs[i] = size - i - 1;
		}
	}

	double x;
	MPI_Scatterv(&numbers[0], &count[0], &displs[0], MPI_DOUBLE, &x, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	pt << x;
}
