#include "pt4.h"
#include "omp.h"

void find_k(int n, int& k1, int& k2, int& k3) {
	int k = 0;
	for (int i = 1; i <= n; ++i)
		k += i;
	int k0 = k / 4;
	int c = 0;
	int d = 0;
	for (int i = 1; i <= n; ++i) {
		c += i;
		if (c > k0) {
			if (d == 0)
				k1 = i;
			else if (d == 1)
				k2 = i;
			else {
				k3 = i;
				return;
			}
			++d;
			c = 0;
		}
	}
}

double parallel_f(double x, int n) {
	double res = 0;
	int k1, k2, k3;
	find_k(n, k1, k2, k3);
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
			double res0 = 0;
			double t;
			for (int i = 1; i <= k1; ++i) {
				t = 0;
				for (int j = 1; j <= i; ++j) {
					t += (j + pow((x + j), 0.25)) / (2 * i * j - 1);
					++count;
				}
				res0 += 1 / t;
			}
			res += res0;
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
			double res1 = 0;
			for (int i = k1 + 1; i <= k2; ++i) {
				t = 0;
				for (int j = 1; j <= i; ++j) {
					t += (j + pow((x + j), 0.25)) / (2 * i * j - 1);
					++count;
				}
				res += 1 / t;
			}
			res += res1;
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
			double res2 = 0;
			for (int i = k2 + 1; i <= k3; ++i) {
				t = 0;
				for (int j = 1; j <= i; ++j) {
					t += (j + pow((x + j), 0.25)) / (2 * i * j - 1);
					++count;
				}
				res2 += 1 / t;
			}
			res += res2;
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
			double res3 = 0;
			for (int i = k3 + 1; i <= n; ++i) {
				t = 0;
				for (int j = 1; j <= i; ++j) {
					t += (j + pow((x + j), 0.25)) / (2 * i * j - 1);
					++count;
				}
				res += 1 / t;
			}
			res += res3;
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
		for (int j = 1; j <= i; ++j) {
			t += (j + pow((x + j), 0.25)) / (2 * i * j - 1);
		}
		res += 1 / t;
	}
	return res;
}

void Solve()
{
    Task("OMPBegin13");

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
