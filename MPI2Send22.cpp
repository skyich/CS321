#include "pt4.h"
#include "mpi.h"

template<typename T>
void send(int t, int dest, MPI_Datatype d) {
	T x;
	pt >> x;
	MPI_Send(&x, 1, d, dest, t, MPI_COMM_WORLD);
}

template<typename T>
void recv(MPI_Datatype d, MPI_Status& status) {
	T x;
	MPI_Recv(&x, 1, d, 0, status.MPI_TAG, MPI_COMM_WORLD, &status);
	pt << x;
}

void Solve()
{
    Task("MPI2Send22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int i = 1; i < size; ++i) {
			int t;
			pt >> t;
			if (t == 1)
				send<double>(t, i, MPI_DOUBLE);
			else
				send<int>(t, i, MPI_INT);
		}
	}
	else {
		MPI_Status status;
		MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if (status.MPI_TAG == 1)
			recv<double>(MPI_DOUBLE, status);
		else
			recv<int>(MPI_INT, status);
	}
	

}
