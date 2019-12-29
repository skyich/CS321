#include "pt4.h"
#include "mpi.h"

double minDouble(int n) {
	double min = DBL_MAX;
	double x;
	for (int i = 0; i < n; ++i) {
		pt >> x;
		if (x < min)
			min = x;
	}
	return min;
}

double maxDouble(int n) {
	double max = DBL_MIN;
	double x;
	for (int i = 0; i < n; ++i) {
		pt >> x;
		if (x > max)
			max = x;
	}
	return max;
}

int minInt(int n) {
	int min = INT_MAX;
	int x;
	for (int i = 0; i < n; ++i) {
		pt >> x;
		if (x < min)
			min = x;
	}
	return min;
}


void Solve()
{
    Task("MPI1Proc10");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int n;
	pt >> n;

	if (rank == 0)
		if (size % 2 == 0) {
			double x = minDouble(n);
			pt << x;
		}
		else {
			int x = minInt(n);
			pt << x;
		}
	else if (rank % 2 == 0) {
		int x = minInt(n);
		pt << x;
	}
	else {
		double x = maxDouble(n);
		pt << x;
	}


}


