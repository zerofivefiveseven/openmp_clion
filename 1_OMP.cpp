#include <omp.h>
#include <iostream>
#include <unistd.h>
//1
int main(int argc, char* argv[]) 
{
	int M = 0, N = 0;
	std::cout << "Enter N\n";
	std::cin >> N;
#pragma omp parallel private(M) num_threads(N)
	{
		M = omp_get_thread_num();
		printf("Hello, World! I'm thread %d from %d threads\n", M, N);
		sleep(1000); //sleep(1); для мака
		if ((M & 1) == 0)
			printf("I'm thread %d. I'm even.\n", M);
	}
	return 0;
}

