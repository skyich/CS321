#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm12");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;
	double a;
	pt >> n >> a;
	if (n == 1)
		a *= -1;
	
	MPI_Comm comm;
	int color = n;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm);

	double res;
	MPI_Allreduce(&a, &res, 1, MPI_DOUBLE, MPI_MAX, comm);
	if (n == 1)
		res *= -1;
	pt << res;
}
