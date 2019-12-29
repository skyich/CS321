#include "pt4.h"
#include "omp.h"


double parallel_f(double x, int n) {
	double res = 0;
	int k = n * (-2 + sqrt(10)) / 2;
	#pragma omp parallel sections reduction(+:res)
	{
		#pragma omp section
		{
			Show("\nnum_proc:");
			Show(omp_get_num_procs());
			Show("\nnum_threads");
			Show(omp_get_num_threads());

			double time = omp_get_wtime();
			int count = 0;
			double t;
			for (int i = 1; i <= k; ++i) {
				t = 0;
				for (int j = i; j <= n; ++j) {
					t += (j + log(1 + x + j)) / (2 * i * j - 1);
					++count;
				}
				res += 1 / t;
			}
			Show("\nthread_num:");
			Show(omp_get_thread_num());
			Show("Count:");
			Show(count);
			Show("Thread time:");
			Show(omp_get_wtime() - time);
		}

		#pragma omp section
		{
			double time = omp_get_wtime();
			int count = 0;
			double t = 0;
			for (int i = k + 1; i <= n; ++i) {
				t = 0;
				for (int j = i; j <= n; ++j) {
					t += (j + log(1 + x + j)) / (2 * i * j - 1);
					++count;
				}
				res += 1 / t;
			}
			Show("\nthread_num:");
			Show(omp_get_thread_num());
			Show("Count:");
			Show(count);
			Show("Thread time:");
			Show(omp_get_wtime() - time);
		}
	}
	return res;
}

double nonparallel_f(double x, int n) {
	double res = 0;
	for (int i = 1; i <= n; ++i) {
		double t = 0;
		for (int j = i; j <= n; ++j) {
			t += (j + log(1 + x + j)) / (2 * i * j - 1);
		}
		res += 1 / t;
	}
	return res;
}

void Solve()
{
    Task("OMPBegin11");

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
