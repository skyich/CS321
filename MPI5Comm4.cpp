#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm4");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Group even;
	MPI_Comm even_comm;
	int color = rank % 2;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &even_comm);

	if (rank % 2 == 0) {
		double nums[3];
		for (int i = 0; i < 3; ++i)
			pt >> nums[i];
		double result[3];
		MPI_Reduce(nums, result, 3, MPI_DOUBLE, MPI_MIN, 0, even_comm);
		if (rank == 0) 
			for (int i = 0; i < 3; ++i)
				pt << result[i];
	}
}
