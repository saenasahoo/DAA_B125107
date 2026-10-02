#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int *tails = malloc(n * sizeof(int));
    int len = 0;
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = len;
        while (lo < hi) {                 /* first tail >= a[i] */
            int mid = (lo + hi) / 2;
            if (tails[mid] < a[i]) lo = mid + 1;
            else hi = mid;
        }
        tails[lo] = a[i];
        if (lo == len) len++;
    }
    printf("%d\n", len);
    free(a); free(tails);
    return 0;
}
/* Time: O(n log n), Space: O(n). The plain DP version is O(n^2). */