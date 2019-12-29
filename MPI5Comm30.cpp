#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI5Comm30");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int a;
	pt >> a;

	int* index = new int[size];
	std::vector<int> edges;
	index[0] = (size - 1) / 3;

	for (int i = 1; i < size; ++i)
		if (i % 3 == 0)
			index[i] = index[i - 1] + 3;
		else
			index[i] = index[i - 1] + 2;
	
	for (int i = 3; i < size; i += 3) // соседи корня
		edges.push_back(i);

	for (int i = 1; i < size; ++i)
		if (i % 3 == 0) {
			edges.push_back(0);
			edges.push_back(i - 2);
			edges.push_back(i - 1);
		}
		else if ((i + 1) % 3 == 0){
			edges.push_back(i - 1);
			edges.push_back(i + 1);
		}
		else {
			edges.push_back(i + 1);
			edges.push_back(i + 2);
		}

	MPI_Comm comm_graph;
	MPI_Graph_create(MPI_COMM_WORLD, size, index, &edges[0], false, &comm_graph);

	int ncount;
	MPI_Graph_neighbors_count(comm_graph, rank, &ncount);
	int* neighbors = new int[ncount];
	MPI_Graph_neighbors(comm_graph, rank, ncount, neighbors);

	int x;
	std::vector<int> rec;
	for (int i = 0; i < ncount; ++i) {
		MPI_Sendrecv(&a, 1, MPI_INT, neighbors[i], 0, &x, 1, MPI_INT, neighbors[i], 0, comm_graph, MPI_STATUSES_IGNORE);
		rec.push_back(x);
	}
	for (auto x : rec)
		pt << x;
}
