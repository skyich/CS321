#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;
	pt >> n;

	if (rank != 0) {
		int* block = new int[n * n];
		for (int i = 0; i < n * n; ++i) {
			pt >> block[i];
		}
		MPI_Send(block, n * n, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Datatype newtype;

		MPI_Type_vector(n, n, n * 3, MPI_INT, &newtype);
		MPI_Type_commit(&newtype);

		int* A = new int[n * n * (size - 1)];

		for (int i = 1; i < size; ++i){
			int t = (i - 1) / 3;
			int tm = (i - 1) % 3;
			MPI_Recv(A + (t * (n * n * 3) + tm * n), 1, newtype, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}

		for (int i = 0; i < n * n * (size - 1); ++i) {
			pt << A[i];
		}
	}
}
