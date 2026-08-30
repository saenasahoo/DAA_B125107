/*
 * DAA LAB-5, QUESTION 2
 * Find the K'th smallest element in a list of N numbers WITHOUT sorting.
 * Method   : Randomized Quickselect
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

/* returns element at 0-indexed rank k */
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

int kthSmallest(int arr[], int n, int k) {
    return quickSelect(arr, 0, n - 1, k - 1); /* convert to 0-indexed rank */
}

int main(void) {
    int n, k;
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

    printf("Enter K (1 <= K <= %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("K is out of range.\n");
        free(arr);
        return 1;
    }

    int result = kthSmallest(arr, n, k);
    printf("The %d%s smallest element is %d\n", k,
           (k % 10 == 1 && k % 100 != 11) ? "st" :
           (k % 10 == 2 && k % 100 != 12) ? "nd" :
           (k % 10 == 3 && k % 100 != 13) ? "rd" : "th",
           result);

    free(arr);
    return 0;
}
