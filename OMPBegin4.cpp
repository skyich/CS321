#include "pt4.h"
#include "omp.h"

double nonparallel_f(double x, int n) {
	double res = 0;
	for (int i = 1; i <= n; ++i) {
		double t = 0;
		for (int j = i; j <= 2 * n; ++j) {
			t += (j + pow(x + j, 1. / 3)) / (2 * i * j - 1);
		}
		res += 1 / t;
	}
	return res;
}

double parallel_f(double x, int n) {
	double res = 0;
	#pragma omp parallel num_threads(2)
	{
		int num = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		int num_procs = omp_get_num_procs();
		int count = 0;
		if (num == 0) {
			Show("\nnum_procs: ");
			Show(num_procs);
			Show("\nnum_threads: ");
			Show(num_threads);
		}
		double time = omp_get_wtime();
		for (int i = num; i <= n; i += 2) {
			double t = 0;
			for (int j = i; j <= 2 * n; ++j) {
				t += (j + pow(x + j, 1. / 3)) / (2 * i * j - 1);
				count += 1;
			}
			res += 1 / t;
		}
		Show("\nthread_num:");
		Show(num);
		Show("Count:");
		Show(count);
		Show("Thread time:");
		Show(omp_get_wtime() - time);
	}
	return res;
}

void Solve()
{
    Task("OMPBegin4");
	double x;
	int n;
	pt >> x >> n;
	double start = omp_get_wtime();
	double res = nonparallel_f(x, n);
	Show("Non-parallel time:");
	double np_time = omp_get_wtime() - start;
	Show(np_time);
	pt << res;
	pt >> x >> n;
	start = omp_get_wtime();
	res = parallel_f(x, n);
	double p_time = omp_get_wtime() - start;
	Show("\nTotal parallel time:");
	Show(p_time);
	pt << res;
	Show("\nRate:");
	Show(np_time / p_time);
}
