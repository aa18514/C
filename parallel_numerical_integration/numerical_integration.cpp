#include <iostream>
#include <algorithm>
#include <chrono> 
#include <numeric>
#include <sys/time.h> 
#include <math.h>
#include <omp.h> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std; 

double naive_implementation(long double num_steps, int experiments);
double multi_core_implementation(long double num_steps, double scaling_factor, float total_experiments, int C); 
void reduce(double* output, double* input, int iterations);
void bring_data_in_block(double* output, int64_t block_number, int iterations, double step); 

int main(int argc, char* argv[])
{
	double multi_core_answer, naive_answer; 
	if(argc < 6){
		cout << "incorrect number of parameters, please try again!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		naive_answer = naive_implementation(strtod(argv[1], NULL), atoi(argv[2])); 
		multi_core_answer = multi_core_implementation(strtod(argv[3], NULL), atof(argv[4]), atoi(argv[5]), atoi(argv[6])); 
		printf("evaluated answer on multi-core: %f\t\t", float(multi_core_answer));
		printf("expected answer: %f\n", float(naive_answer));
	}
	return 0; 
}

double naive_implementation(long double num_steps, int experiments){
	long double average_time = 0.0; 
	double pi = 0.0;
	for(int j = 0; j < experiments; j++){
		struct timeval tv, tb; 
		gettimeofday(&tv, NULL);
		double sum = 0.0; 
		long double step = 1.0/(long double) num_steps;
		for(int64_t i = 0; i < num_steps; i = i + 1)
		{
			double x = (i + 0.5) * step; 
			double s = (4.0/(1 + x * x)); 
			sum = sum + s;
		}
		pi = sum * step; 
		gettimeofday(&tb, NULL); 
		long double t = (((((unsigned long long)tb.tv_sec) - (unsigned long long)tv.tv_sec))) + (((tb.tv_usec - tv.tv_usec)/1e6));
		average_time += t; 
	}
	printf("steps: %.9e\t\t\t", float(num_steps));
	printf("mean for naive implementation: %fs\t\t\t",  float(average_time)/float(experiments));
	return pi;
}

inline double multi_core_implementation(long double num_steps, double scale_factor, float total_experiments, int C){
	double step = 1.0/(long double) num_steps; 
	long double average_time = 0.0;
	double pi;
	for(int experiments = 0; experiments < int(total_experiments); experiments++){
		long double sum = 0.0;
		struct timeval tv, tb; 
		gettimeofday(&tv, NULL); 
		int iterations = int(double(scale_factor) * double(num_steps));
		int size = (1.0/double(scale_factor));
		double* level_up_sums = new double[size];
		vector<double*> partial_sum;
		double* level_two_up_sums = NULL;
		double* level_three_up_sums = NULL; 
		double* level_four_up = NULL;
		double*	level_five_up = NULL; 
		double* level_six_up = NULL;
		int index; 
		int i = 0; 
		for(i = 0; i < 6; i++){
			index = (i == 0) ? 2 : i + 2; 
			partial_sum.push_back(new double[iterations >> index]);
		}
	
		for(int64_t j = 0; j < size; j++)
		{
			bring_data_in_block(partial_sum[0], j * iterations, iterations, step);
			for(int i = 0; i < 5; i++){
				int index = (i == 0) ? 0 : i + 2; 
				level_up_sums[j] += ((iterations >> index) % 2 == 0) ? 0 : partial_sum[i][(iterations >> index) - 1]; 
				reduce(partial_sum[i + 1], partial_sum[i], iterations >> (i + 1)); 
			}
			level_up_sums[j] += ((iterations >> 6) > 1) ? accumulate(partial_sum[5], partial_sum[5] + ((iterations >> 7)), double(0)) : 
					    ((iterations >> 5) > 1) ? partial_sum[4][0] : 
					    ((iterations >> 4) > 1) ? partial_sum[3][0] :
					    ((iterations >> 3) > 1) ? partial_sum[2][0] : 
					    ((iterations >> 2) > 1) ? partial_sum[1][0] : 
					    partial_sum[0][0];
	
		}
		
		
		sum = (size == 1) ? level_up_sums[0] : 
			((size % 2) == 0) ? 0 : level_up_sums[size - 1];
		if(size > 1){
			level_two_up_sums = new double[size >> 1];
			#pragma omp parallel for
			for(int i = 0; i < size; i = i + 2){
				level_two_up_sums[i >> 1] = level_up_sums[i] + level_up_sums[i + 1];
			}
			
			int size_level_two_up = size >> 1; 
			sum = (size_level_two_up == 1) ? sum + level_two_up_sums[0] : 
				((size_level_two_up % 2) == 0) ? sum : level_two_up_sums[size_level_two_up - 1];
			size_level_two_up = ((size_level_two_up % 2) == 0) ? size_level_two_up : size_level_two_up - 1;
			if(size_level_two_up > 1){
				level_three_up_sums = new double[size_level_two_up >> 1];
				#pragma omp parallel for
				for(int i = 0; i < size_level_two_up; i = i + 2){
					level_three_up_sums[i >> 1] = level_two_up_sums[i] + level_two_up_sums[i + 1];
				}		
			}
			
			int size_level_three_up = size_level_two_up >> 1; 
			sum = (size_level_three_up == 1) ? sum + level_three_up_sums[0]: 
				((size_level_three_up % 2) == 0) ? sum : level_three_up_sums[size_level_three_up - 1];
			size_level_three_up = ((size_level_three_up % 2) == 0) ? size_level_three_up : size_level_three_up - 1;
			if(size_level_three_up > 1){
				level_four_up = new double[size_level_three_up >> 1];
				#pragma omp parallel for 
				for(int i = 0; i < size_level_three_up; i = i + 2){
					level_four_up[i >> 1] = level_three_up_sums[i] + level_three_up_sums[i + 1];
				}
			}
			
			int size_level_four_up = size_level_three_up >> 1;
			sum = (size_level_four_up == 1) ? sum + level_four_up[0] : 
				((size_level_four_up % 2) == 0) ? sum : level_four_up[size_level_four_up - 1];
			size_level_four_up = ((size_level_four_up % 2) == 0) ? size_level_four_up : size_level_four_up - 1;
			if(size_level_four_up > 1){
				level_five_up = new double[size_level_four_up >> 1]; 
				#pragma omp parallel for 
				for(int i = 0; i < size_level_four_up; i = i + 2){
					level_five_up[i >> 1] = level_four_up[i] + level_four_up[i + 1]; 
				}
			}
			
			int size_level_five_up = size_level_four_up >> 1; 
			sum = (size_level_five_up == 1) ? sum + level_five_up[0] : 
				((size_level_five_up % 2) == 0) ? sum : level_five_up[size_level_five_up - 1];
			size_level_five_up = ((size_level_five_up % 2) == 0) ? size_level_five_up : size_level_five_up - 1;
			if(size_level_five_up > 1){
				level_six_up = new double[size_level_five_up >> 1];
				#pragma omp parrallel for
				for(int i = 0; i < size_level_five_up; i = i + 2){
					level_six_up[i >> 1] = level_five_up[i] + level_five_up[i + 1];
				}
				for(i = 0; i < (size_level_five_up >> 1); i++){
					sum = sum + level_six_up[i];
				}
			}
		}
		pi = sum * step;
		gettimeofday(&tb, NULL);
		long double t = (((((unsigned long long)tb.tv_sec) - (unsigned long long)tv.tv_sec))) + (((tb.tv_usec - tv.tv_usec)/1e6)); 
		average_time += t; 
	}
	cout << "mean for multicore implementation: " << average_time/(total_experiments) << "s" << endl;
	return pi; 
} 

inline void reduce(double* output, double* input, int iterations){
	int Iterations = (iterations % 2 == 0) ? iterations : iterations - 1;
	if(Iterations > 1){
		#pragma omp parallel for
		for(int i = 0; i < (Iterations >> 1); i = i + 2){
			//cout << input[i] << endl;
			output[i >> 1] = input[i] + input[i + 1];
		}
	}
}

inline void bring_data_in_block(double* output, int64_t block_number, int iterations, double step){
	#pragma omp parallel for
	for(int64_t i = 0; i < iterations; i = i + 4){
		long double x = (block_number + i + 0.5) * step; 
		double s = 0.0; 
		for(int p = 0; p < 4; p++){
			s += 4.0/(1 + (x + p * step) * (x + p * step)); 
		}
		output[i >> 2] = s; 
	}
}
