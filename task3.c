#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 500000

int comparisons = 0;

int cmp(const void* a, const void* b){
	comparisons++;
	int ai = *(int*)a;
	int bi = *(int*)b;
	return (ai > bi) - ( ai < bi);

}

void generate_ascending(int* arr, int n){
	for(int i = 0; i < n; ++i){
		arr[i] = i;
	}
}

void generate_descending(int* arr, int n){
	for(int i = 0; i < n; ++i){
		arr[i] = n - i;
	}
}

void generate_equal(int* arr, int n){
	for(int i =0; i < n; ++i){
		arr[i] = 42;
	}
}

void generate_random(int* arr, int n){
	for(int i = 0 ; i < n; ++i){
		arr[i] = rand() % 1000;
	}
}

void test_case(const char* name, void (*generator)(int*, int), int n){
	int* arr = malloc(n * sizeof(int));
	generator(arr, n);

	comparisons = 0;
	clock_t start = clock();
	qsort(arr, n, sizeof(int), cmp);
	clock_t end = clock();

	printf("%s:\n", name);
	printf(" Comparisons: %d\n", comparisons);
	printf(" Time: %.3f sec\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(arr);
}

void assert_sorted(int* arr, int n){
	for(int i = 1; i < n; ++i){
		if(arr[i-1] > arr[i]){
			printf("Assertion failed: array not sorted at index %d\n", i);
			exit(1);
		}
	}
}


void test_correctness(){
	int data1[] = {5, 2, 8, 1, 3};
	int data2[] = {10, 9, 8, 7, 6};
	int data3[] = {1, 1, 1, 1, 1};
	int data4[] = {};
	int data5[] = {42};

	int sizes[] = {5, 5, 5, 0, 1};
	int* arrays[] = {data1, data2, data3, data4, data5};

	for(int i =0; i < 5; ++i){
		qsort(arrays[i], sizes[i], sizeof(int), cmp);
		assert_sorted(arrays[i], sizes[i]);
	}

	printf("All correctness tests passed.\n");

}

int main(){
	srand(time(NULL));
	int n = MAX_N;

	test_correctness();

	test_case("Ascending", generate_ascending, n);
	test_case("Descending", generate_descending, n);
	test_case("All equal", generate_equal, n);
	test_case("Random", generate_random, n);

	return 0;

}

