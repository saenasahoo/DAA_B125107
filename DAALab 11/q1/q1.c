
   #include <stdio.h>
#include <stdlib.h>
#define INF 1000000000

int main() {
    int n, m, s; long long C;
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (m): ");
    scanf("%d", &m);
    printf("Enter source vertex S (1-%d): ", n);
    scanf("%d", &s);
    printf("Enter penalty cost C: ");
    scanf("%lld", &C);

    int *head = malloc((n + 1) * sizeof(int));
    int *nxt = malloc(m * sizeof(int)), *to = malloc(m * sizeof(int)), *wt = malloc(m * sizeof(int));
    for (int i = 0; i <= n; i++) head[i] = -1;

    printf("Enter %d directed edges as: u v w (w must be 0 or 1)\n", m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &w);
        to[i] = v; wt[i] = w; nxt[i] = head[u]; head[u] = i;
    }

    int *d = malloc(2 * (n + 1) * sizeof(int));
    for (int i = 0; i < 2 * (n + 1); i++) d[i] = INF;

    int cap = 4 * n + 2 * m + 10;
    int *dq = malloc(2 * cap * sizeof(int));
    int l = cap, r = cap;
    d[s * 2] = 0;
    dq[r++] = s * 2;

    while (l < r) {
        int x = dq[l++], u = x / 2, p = x % 2;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e], w = wt[e];
            int y = v * 2 + (p ^ w);
            if (d[x] + w < d[y]) {
                d[y] = d[x] + w;
                if (w == 0) dq[--l] = y; else dq[r++] = y;
            }
        }
    }

    printf("\nMinimum effective cost from source %d:\n", s);
    for (int v = 1; v <= n; v++) {
        long long best = INF;
        if (d[v * 2] < INF) best = d[v * 2];
        if (d[v * 2 + 1] < INF && d[v * 2 + 1] + C < best) best = d[v * 2 + 1] + C;
        if (best >= INF) printf("Vertex %d: unreachable\n", v);
        else printf("Vertex %d: %lld\n", v, best);
    }
    return 0;
}