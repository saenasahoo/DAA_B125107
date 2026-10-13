
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;

int find(int x) {
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    sz[a] += sz[b];
}

int main(void) {
    int n, m;
    scanf("%d", &n);
    int *A = malloc((n + 1) * sizeof(int)), *pos = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) { scanf("%d", &A[i]); pos[A[i]] = i; }
    parent = malloc((n + 1) * sizeof(int));
    sz = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) { parent[i] = i; sz[i] = 1; }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    /* offset of each component's block inside vals[] */
    int *off = calloc(n + 2, sizeof(int)), *fill = calloc(n + 1, sizeof(int)), *ptr = calloc(n + 1, sizeof(int));
    int run = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i) { off[i] = run; run += sz[i]; }

    int *vals = malloc(n * sizeof(int));
    for (int v = 1; v <= n; v++) {          /* ascending values -> already sorted per component */
        int r = find(pos[v]);
        vals[off[r] + fill[r]++] = v;
    }

    printf("Smallest permutation:");
    for (int i = 1; i <= n; i++) {          /* ascending positions */
        int r = find(i);
        printf(" %d", vals[off[r] + ptr[r]++]);
    }
    printf("\n");

    free(A); free(pos); free(parent); free(sz); free(off); free(fill); free(ptr); free(vals);
    return 0;
}
