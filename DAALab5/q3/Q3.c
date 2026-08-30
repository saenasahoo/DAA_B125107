/*
 * DAA LAB-5, QUESTION 3
 * Implement Quick Sort of N random elements stored in a file.
 * Steps: generate N random ints -> input.txt
 *        read input.txt into memory
 *        quick sort in memory
 *        write sorted result -> output.txt
 * Time  : O(N log N) average, O(N^2) worst case
 * Space : O(N) for the array, O(log N) average recursion stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* Step 1: generate N random integers and write them to a file */
void generateFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Could not create %s\n", filename); exit(1); }
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", rand() % 100000);
    fclose(fp);
}

/* Step 2: read all integers from a file into a dynamically allocated array */
int *readFile(const char *filename, int *outN) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("Could not open %s\n", filename); exit(1); }

    int capacity = 16, count = 0;
    int *arr = malloc(capacity * sizeof(int));
    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        if (count == capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(int));
        }
        arr[count++] = value;
    }
    fclose(fp);
    *outN = count;
    return arr;
}

/* Step 3: Quick Sort (Lomuto partition scheme) */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotPos = partition(arr, low, high);
        quickSort(arr, low, pivotPos - 1);
        quickSort(arr, pivotPos + 1, high);
    }
}

/* Step 4: write the sorted array to a file */
void writeFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Could not create %s\n", filename); exit(1); }
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", arr[i]);
    fclose(fp);
}

int main(void) {
    int n;
    srand((unsigned) time(NULL));

    printf("Enter the number of random elements N to generate: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid N.\n");
        return 1;
    }

    const char *inputFile  = "input.txt";
    const char *outputFile = "output.txt";

    generateFile(inputFile, n);
    printf("Generated %d random elements into %s\n", n, inputFile);

    int count;
    int *arr = readFile(inputFile, &count);
    printf("Read %d elements from %s\n", count, inputFile);

    printf("\nUnsorted (input) elements:\n");
    for (int i = 0; i < count; i++) printf("%d ", arr[i]);
    printf("\n");

    quickSort(arr, 0, count - 1);

    writeFile(outputFile, arr, count);
    printf("\nSorted elements written to %s\n", outputFile);

    printf("\nSorted (output) elements:\n");
    for (int i = 0; i < count; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
