#include "pt4.h"
#include "mpi.h"
#include <stddef.h>

struct custom
{
	int a;
	int b;
	double c;
};

void Solve()
{
    Task("MPI4Type8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Datatype newtype;
	MPI_Datatype old_types[] = { MPI_INT, MPI_INT, MPI_DOUBLE };
	int count = 3;
	int blocklens[] = { 1,1,1 };
	MPI_Aint disp[3];
	disp[0] = (MPI_Aint)offsetof(struct custom, a);
	disp[1] = (MPI_Aint)offsetof(struct custom, b);
	disp[2] = (MPI_Aint)offsetof(struct custom, c);
	MPI_Type_struct(count, blocklens, disp, old_types, &newtype);
	MPI_Type_commit(&newtype);

	if (rank != 0) {
		custom* s = new custom[rank];
		for (int i = 0; i < rank; ++i)
			pt >> s[i].a >> s[i].b >> s[i].c;
		MPI_Send(s, rank, newtype, 0, 0, MPI_COMM_WORLD);
	}
	else {
		custom* s;
		for (int i = 1; i < size; ++i) {
			s = new custom[i];
			MPI_Recv(s, i, newtype, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			for (int j = 0; j < i; ++j)
				pt << s[j].a << s[j].b << s[j].c;
		}
	}
}
