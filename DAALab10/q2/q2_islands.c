
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int unite(int a, int b) { /* returns 1 if merged */
    a = find(a); b = find(b);
    if (a == b) return 0;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main(void) {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);
    int N = R * C;
    parent = malloc(N * sizeof(int));
    sz = malloc(N * sizeof(int));
    char *land = calloc(N, 1);
    for (int i = 0; i < N; i++) { parent[i] = i; sz[i] = 1; }

    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    int count = 0;
    for (int k = 0; k < K; k++) {
        int r, c;
        scanf("%d %d", &r, &c);
        int id = r * C + c;
        if (!land[id]) {
            land[id] = 1;
            count++;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int nid = nr * C + nc;
                if (land[nid] && unite(id, nid)) count--;
            }
        }
        printf("After (%d,%d): %d island(s)\n", r, c, count);
    }
    free(parent); free(sz); free(land);
    return 0;
}
