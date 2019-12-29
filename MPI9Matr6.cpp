#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // количество процессов
int r;              // ранг текущего процесса

int m, p, q;        // размеры исходных матриц
int na, nb;         // размеры полос матриц

int *a_, *b_, *c_;  // массивы для хранения исходных матриц в главном процессе
int *a, *b, *c;     // массивы для хранения полос матриц в каждом процессе

void Matr1GatherData() {
	int sizec =  m * q;
	c_ = new int[sizec];
	MPI_Gather(c, na * q, MPI_INT, c_, na * q, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (r == 0) {
		for (int i = 0; i < sizec; ++i)
			pt << c_[i];
	}
}

void Solve()
{
    Task("MPI9Matr6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;

	if (r == 0)
		pt >> m;
	pt >> na >> q;
	int size_c = na * q;
	c = new int[size_c];
	for (int i = 0; i < size_c; ++i)
		pt >> c[i];
	Matr1GatherData();
}
