#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int k, n;
	if (rank == 0) {
		pt >> k;
		n = 1;
	}
	else
		pt >> n;
	MPI_Comm comm;
	int color = n;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm);

	if (n == 1) {
		double* numbers = new double[1];
		int* sendCounts = new int[1];
		int* displs = new int[1];
		double x;

		if (rank == 0) {
			numbers = new double[k + 1];
			for (int i = 1; i < k + 1; ++i)
				pt >> numbers[i];
			sendCounts = new int[k + 1];
			std::fill(sendCounts, sendCounts + k + 1, 1);
			sendCounts[0] = 0;
			displs = new int[k + 1];
			for (int i = 0; i < k + 1; ++i)
				displs[i] = i * 1;
			displs[0] = 0;
		}

		MPI_Scatterv(numbers, sendCounts, displs, MPI_DOUBLE, &x, 1, MPI_DOUBLE, 0, comm);
		if (rank != 0)
			pt << x;
	}
}
