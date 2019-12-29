#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // ���������� ���������
int r;              // ���� �������� ��������

int m, p, q;        // ������� �������� ������
int m0, p0, q0;     // ������� ������ ������
int k0;             // ������� ���������� �������, ������ sqrt(k)

int *a_, *b_, *c_;  // ������� ��� �������� �������� ������ � ������� ��������
int *a, *b, *c;     // ������� ��� �������� ������ ������ � ������ ��������

MPI_Datatype MPI_BLOCK_A; // ��� ������ ��� ����� ������� A
MPI_Datatype MPI_BLOCK_B; // ��� ������ ��� ����� ������� B
MPI_Datatype MPI_BLOCK_C; // ��� ������ ��� ����� ������� C

MPI_Comm MPI_COMM_GRID = MPI_COMM_NULL;
                // ������������, ��������� � ��������� ���������� ��������

void Matr3CreateTypeBlock(int m0, int p0, int p, MPI_Datatype& t) {
	MPI_Type_vector(m0, p0, p, MPI_INT, &t);
	MPI_Type_commit(&t);
}

void Solve()
{
    Task("MPI9Matr21");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
    k0 = (int)floor(sqrt((double)k) + 0.1);

	pt >> m >> p;
	int m0 = m / k0;
	int p0 = p / k0;
	a = new int[m0 * p0];

	if (rank == 0) {
		a_ = new int[m * p];
		for (int i = 0; i < m * p; ++i)
				pt >> a_[i];
		Matr3CreateTypeBlock(m0, p0, p, MPI_BLOCK_A);
		int t = 0;
		for (int i = 1; i < k; ++i) {
			MPI_Send(&a_[t + p0 * (i % k0)], 1, MPI_BLOCK_A, i, 0, MPI_COMM_WORLD);
			if ((i + 1) % k0 == 0)
				t += p * m0;
		}
		MPI_Sendrecv(a_, 1, MPI_BLOCK_A, 0, 0, a, m0 * p0, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		for (int i = 0; i < m0 * p0; ++i) {
			pt << a[i];
		}
	}
	else {
		MPI_Recv(a, m0 * p0, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		for (int i = 0; i < m0 * p0; ++i)
			pt << a[i];
	}
}
