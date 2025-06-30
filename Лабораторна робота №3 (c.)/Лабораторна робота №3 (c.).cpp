#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define MAX 10000

void insertion_sort(int arr[], int size) {

	for (int i = 1; i < size; i++) {
		int c = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > c) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = c;
	}
}

int* generate_array_items(int size) {
	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "Помилка виділення пам'яті\n");
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 1001;
	}
	return arr;
}

void testing_time_sort(void (*sort_func)(int[], int), const char* sort_name) {
	printf("-----------------------------------------------------\n");
	printf("Алгоритм сортування масиву: %s\n", sort_name);
	printf("-----------------------------------------------------\n");
	printf("Розмір масиву: | Час виконання:\n");
	printf("               |               \n");

	srand((unsigned)time(NULL));

	for (int size = 100; size <= MAX; size *= 10) {
		int* arr = generate_array_items(size);

		LARGE_INTEGER frequency, start, end;

		QueryPerformanceFrequency(&frequency);

		QueryPerformanceCounter(&start);
		sort_func(arr, size);
		QueryPerformanceCounter(&end);

		double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

		printf("%14d | %12.18f\n", size, elapsed);
		free(arr);
	}

	printf("-----------------------------------------------------\n");
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	testing_time_sort(insertion_sort, "Сортування вставками");

	return 0;
}