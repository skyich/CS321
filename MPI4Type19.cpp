#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;
	pt >> n;
	int nsize = n * 2 + n - 2;
	if (rank != 0) {
		int p;
		pt >> p;
		int* Z = new int[nsize];
		for (int i = 0; i < nsize; ++i) {
			pt >> Z[i];
		}
		MPI_Send(Z, nsize, MPI_INT, 0, p, MPI_COMM_WORLD);
	}
	else {
		int* displs = new int[n];
		std::fill(displs, displs + n, 0);
		for (int i = 1; i < n; ++i) {
			displs[i] = i * n * 3 + (n - i - 1);
		}
		
		int* array_of_blocklengths = new int[n];
		std::fill(array_of_blocklengths, array_of_blocklengths + n, 1);
		array_of_blocklengths[0] = n;
		array_of_blocklengths[n - 1] = n;
		
		MPI_Datatype newtype;
		MPI_Type_indexed(n, array_of_blocklengths, displs, MPI_INT, &newtype);
		MPI_Type_commit(&newtype);

		int* res = new int[n * n * (size - 1)];
		std::fill(res, res + n * n * (size - 1), 0);

		for (int i = 1; i < size; ++i) {
			MPI_Status status;
			MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Recv(res + status.MPI_TAG, 1, newtype, i, status.MPI_TAG, MPI_COMM_WORLD, &status);
		}

		for (int i = 0; i < n * n * (size - 1); ++i)
			pt << res[i];
	}
}
