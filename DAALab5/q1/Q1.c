/*
 * DAA LAB-5, QUESTION 1
 * Find the median of a list of N numbers WITHOUT sorting the list.
 * Method   : Randomized Quickselect (finds the k-th smallest element
 *            without fully sorting the array)
 * Time     : O(N) average, O(N^2) worst case
 * Space    : O(1) auxiliary, O(log N) average recursion stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* Lomuto partition with a random pivot */
int partition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
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

/* Returns the element that would be at index k (0-indexed) if arr were sorted */
int quickSelect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];

    int pivotPos = partition(arr, low, high);

    if (k == pivotPos)
        return arr[pivotPos];
    else if (k < pivotPos)
        return quickSelect(arr, low, pivotPos - 1, k);
    else
        return quickSelect(arr, pivotPos + 1, high, k);
}

double findMedian(int arr[], int n) {
    if (n % 2 == 1) {
        return (double) quickSelect(arr, 0, n - 1, n / 2);
    } else {
        int left  = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int right = quickSelect(arr, 0, n - 1, n / 2);
        return (left + right) / 2.0;
    }
}

int main(void) {
    int n;
    srand((unsigned) time(NULL));

    printf("Enter the number of elements N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid N.\n");
        return 1;
    }

    int *arr = (int *) malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    double median = findMedian(arr, n);
    printf("Median = %.2f\n", median);

    free(arr);
    return 0;
}
