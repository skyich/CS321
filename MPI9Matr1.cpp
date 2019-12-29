#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // количество процессов
int r;              // ранг текущего процесса

int m, p, q;        // размеры исходных матриц

int *a_, *b_, *c_;  // массивы для хранения исходных матриц в главном процессе

void Solve()
{
    Task("MPI9Matr1");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;

	if (rank == 0) {
		pt >> m >> p >> q;
		a_ = new int[m * p];
		b_ = new int[p * q];
		c_ = new int[m * q];

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < p; ++j)
				pt >> a_[i * p + j];

		for (int i = 0; i < p; ++i)
			for (int j = 0; j < q; ++j)
				pt >> b_[i * q + j];

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < q; ++j) {
				c_[i * q + j] = 0;
				for (int k = 0; k < p; ++k)
					c_[i * q + j] += a_[i * p + k] * b_[k * q + j];
			}

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < q; ++j)
				pt << c_[i * q + j];
	}
}
