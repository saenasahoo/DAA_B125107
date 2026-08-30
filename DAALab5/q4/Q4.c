/*
 * DAA LAB-5, QUESTION 4
 * Implement Heap Sort to sort N randomly generated elements stored in a file.
 * Steps: generate N random ints -> input.txt
 *        read input.txt into memory
 *        heap sort (build max-heap, repeated extract-max) in memory
 *        write sorted result -> output.txt
 * Time  : O(N log N) in ALL cases (best/average/worst) - guaranteed
 * Space : O(N) for the array, O(log N) recursion stack (recursive heapify)
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

/* Step 3: Heap Sort */
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);
    for (int end = n - 1; end > 0; end--) {
        swap(&arr[0], &arr[end]);
        maxHeapify(arr, end, 0);
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

    heapSort(arr, count);

    writeFile(outputFile, arr, count);
    printf("\nSorted elements written to %s\n", outputFile);

    printf("\nSorted (output) elements:\n");
    for (int i = 0; i < count; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
