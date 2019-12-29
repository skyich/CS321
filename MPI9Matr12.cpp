#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // количество процессов
int r;              // ранг текущего процесса

int m, p, q;        // размеры исходных матриц
int na, nb;         // размеры полос матриц

int *a_, *b_, *c_;  // массивы для хранения исходных матриц в главном процессе
int *a, *b, *c;     // массивы для хранения полос матриц в каждом процессе

MPI_Datatype MPI_BAND_B; // тип данных для полосы матрицы B
MPI_Datatype MPI_BAND_C; // тип данных для полосы матрицы C

void Matr2CreateTypeBand(int p, int n, int q, MPI_Datatype& t) {
	MPI_Type_vector(p, n, q, MPI_INT, &t);
	MPI_Type_commit(&t);
}

void Matr2ScatterData() {
	int* bsend = new int[3];
	if (r == 0) {
		pt >> m >> p >> q;
		na = m * p;
		int size_a = m * p;
		int size_b = p * q;
		a_ = new int[size_a];
		b_ = new int[size_b];
		for (int i = 0; i < size_a; ++i)
			pt >> a_[i];
		for (int i = 0; i < size_b; ++i)
			pt >> b_[i];

		na = ceil((double)m / k);
		nb = ceil((double)q / k);
		bsend[0] = na;
		bsend[1] = nb;
		bsend[2] = p;
	}
	MPI_Bcast(bsend, 3, MPI_INT, 0, MPI_COMM_WORLD);
	na = bsend[0];
	nb = bsend[1];
	p = bsend[2];

	int size_a = na * p;
	int size_b = p * nb;
	int size_c = na * k * nb;
	a = new int[size_a];
	b = new int[size_b];
	c = new int[size_c];
	std::fill(c, c + size_c, 0);

	int size_temp_a = na * p * k;
	int size_temp_b = p * nb * k;
	int* temp_a = new int[size_temp_a];
	std::fill(temp_a, temp_a + size_temp_a, 0);
	int* temp_b = new int[size_temp_b];
	std::fill(temp_b, temp_b + size_temp_b, 0);
	Matr2CreateTypeBand(p, nb, nb * k, MPI_BAND_B);

	if (r == 0) {
		for (int i = 0; i < size_temp_a; ++i)
			if (i < m * p)
				temp_a[i] = a_[i];
		int t = 0;
		for (int i = 0; i < size_temp_b; ++i)
			if (i % (nb * k) < q)
				temp_b[i] = b_[t++];
	}

	MPI_Scatter(temp_a, na * p, MPI_INT, a, na * p, MPI_INT, 0, MPI_COMM_WORLD);

	if (r == 0) {
		MPI_Sendrecv(temp_b, 1, MPI_BAND_B, 0, 0, b, size_b, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		for (int i = 1; i < k; ++i)
			MPI_Send(temp_b + nb * i, 1, MPI_BAND_B, i, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(b, size_b, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	}
}

void Solve()
{
    Task("MPI9Matr12");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;

	Matr2ScatterData();
	
	pt << na << p << nb;
	int size_a = na * p;
	int size_b = p * nb;
	int size_c = na * k * nb;
	for (int i = 0; i < size_a; ++i)
		pt << a[i];
	for (int i = 0; i < size_b; ++i)
		pt << b[i];
	for (int i = 0; i < size_c; ++i)
		pt << c[i];
}
