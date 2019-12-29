#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int nsize = sizeof(double) + sizeof(int) * (size - 1);
	char* buff = new char[nsize];
	int position;
	double x;
	int* numbers = new int[size - 1];
	std::fill(numbers, numbers + size - 1, 0);
	
	if (rank != 0) {
		pt >> x;
		for (int i = 0; i < rank; ++i)
			pt >> numbers[i];
		position = 0;
		MPI_Pack(&x, 1, MPI_DOUBLE, buff, nsize, &position, MPI_COMM_WORLD);
		MPI_Pack(numbers, size - 1, MPI_INT, buff, nsize, &position, MPI_COMM_WORLD);
	}

	
	int allsize = nsize * (size - 1);
	char* rec = new char[allsize];
	MPI_Gather(buff, nsize, MPI_PACKED, rec, nsize, MPI_PACKED, 0, MPI_COMM_WORLD);

	
	if (rank == 0) {
		position = nsize;
		for (int i = 1; i < size; ++i) {
			MPI_Unpack(rec, nsize, &position, &x, 1, MPI_DOUBLE, MPI_COMM_WORLD);
			MPI_Unpack(rec, nsize, &position, numbers, size - 1, MPI_INT, MPI_COMM_WORLD);
			pt << x;
			for (int j = 0; j < i; ++j)
				pt << numbers[j];
		}
	}
}
