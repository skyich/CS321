#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int k = size - 1;

	if (rank == 0) {
		MPI_Datatype newtype;
		MPI_Type_vector(k, 1, k, MPI_DOUBLE, &newtype);
		MPI_Type_commit(&newtype);

		double* A = new double[k * k];
		
		for (int i = 0; i < k * k; i++) {
			pt >> A[i];
		}

		for (int i = 0; i < k; ++i) {
			MPI_Send(A + i, 1, newtype, i + 1, 0, MPI_COMM_WORLD);
		}
	}
	else {
		double* rec = new double[k];
		MPI_Recv(rec, k, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		
		for (int i = 0; i < k; ++i) {
			pt << rec[i];
		}
	}
}
