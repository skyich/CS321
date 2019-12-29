#include "pt4.h"
#include "mpi.h"
#include <stddef.h>

struct custom
{
	double a;
	int b;
	int c;
};

void Solve()
{
    Task("MPI4Type6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Datatype newtype;
	MPI_Datatype old_types[] = { MPI_DOUBLE, MPI_INT, MPI_INT };
	int count = 3;
	int blocklens[] = { 1,1,1 };
	MPI_Aint disp[3];
	disp[0] = (MPI_Aint)offsetof(struct custom, a);
	disp[1] = (MPI_Aint)offsetof(struct custom, b);
	disp[2] = (MPI_Aint)offsetof(struct custom, c);
	MPI_Type_struct(count, blocklens, disp, old_types, &newtype);
	MPI_Type_commit(&newtype);

	if (rank != 0) {
		custom s;
		pt >> s.a >> s.b >> s.c;
		MPI_Send(&s, 1, newtype, 0, 0, MPI_COMM_WORLD);
	}
	else {
		custom s;
		for (int i = 1; i < size; ++i) {
			MPI_Recv(&s, 1, newtype, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			pt << s.a << s.b << s.c;
		}
	}
}
