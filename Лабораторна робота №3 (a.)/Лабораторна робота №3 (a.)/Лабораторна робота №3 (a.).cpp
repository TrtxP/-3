#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX 10000

void counting_sort(int arr[], int size) {

	if (size <= 0) return;

	int maxValue = arr[0];

	for (int i = 1; i < size; i++) {
		if (arr[i] > maxValue) maxValue = arr[i];
	}

	int* count = (int*)calloc(maxValue + 1, sizeof(int));
	if (count == NULL) {
		fprintf(stderr, "Помилка виділення пам'яті\n");
		return;
	}

	for (int i = 0; i < size; i++) {
		count[arr[i]]++;
	}

	int index = 0;
	for (int i = 0; i <= maxValue; i++) {
		while (count[i]-- > 0) {
			arr[index++] = i;
		}
	}

	free(count);
}

int* generate_random_array(int size) {

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

void test_time_sorting(void (*sort_func)(int[], int), const char* sort_name) {

	printf("-----------------------------------------------------\n");
	printf("Алгоритм сортування масиву: %s\n", sort_name);
	printf("-----------------------------------------------------\n");
	printf("Розмір масиву: | Час виконання:\n");
	printf("               |               \n");

	srand((unsigned)time(NULL));

	for (int size = 100; size <= MAX; size *= 10) {
		int* arr = generate_random_array(size);

		LARGE_INTEGER frequency, start, end;
		QueryPerformanceFrequency(&frequency);

		QueryPerformanceCounter(&start);
		sort_func(arr, size);
		QueryPerformanceCounter(&end);
		double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

		printf("%14d | %12.18f\n", size, elapsed);
		free(arr);
	}
	printf("-----------------------------------------------------");
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	test_time_sorting(counting_sort, "Сортування підрахунком");

	return 0;
}