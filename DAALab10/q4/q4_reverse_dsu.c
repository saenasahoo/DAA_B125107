
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int *parent, *sz;
ll *sum;

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
    sum[a] += sum[b];
}

int main(void) {
    int V, E;
    scanf("%d %d", &V, &E);
    ll *w = malloc(V * sizeof(ll));
    for (int i = 0; i < V; i++) scanf("%lld", &w[i]);

    int *eu = malloc(E * sizeof(int)), *ev = malloc(E * sizeof(int));
    int *deg = calloc(V + 1, sizeof(int));
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &eu[i], &ev[i]);
        deg[eu[i]]++; deg[ev[i]]++;
    }
    /* CSR adjacency list */
    int *start = calloc(V + 1, sizeof(int));
    for (int i = 0; i < V; i++) start[i + 1] = start[i] + deg[i];
    int *adj = malloc((size_t)2 * E * sizeof(int)), *fill = calloc(V, sizeof(int));
    for (int i = 0; i < E; i++) {
        adj[start[eu[i]] + fill[eu[i]]++] = ev[i];
        adj[start[ev[i]] + fill[ev[i]]++] = eu[i];
    }

    int *p = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) scanf("%d", &p[i]);

    parent = malloc(V * sizeof(int));
    sz = malloc(V * sizeof(int));
    sum = malloc(V * sizeof(ll));
    char *present = calloc(V, 1);
    for (int i = 0; i < V; i++) { parent[i] = i; sz[i] = 1; sum[i] = w[i]; }

    ll *ans = malloc(V * sizeof(ll));
    ll bestSum = 0;
    ans[V - 1] = 0;                      /* everything deleted */
    for (int i = V - 1; i >= 1; i--) {   /* add p[i], giving state after deleting p[0..i-1] */
        int x = p[i];
        present[x] = 1;
        for (int j = start[x]; j < start[x + 1]; j++)
            if (present[adj[j]]) unite(x, adj[j]);
        ll s = sum[find(x)];
        if (s > bestSum) bestSum = s;
        ans[i - 1] = bestSum;
    }
    for (int i = 0; i < V; i++)
        printf("After deleting vertex %d: max component sum = %lld\n", p[i], ans[i]);

    free(w); free(eu); free(ev); free(deg); free(start); free(adj); free(fill);
    free(p); free(parent); free(sz); free(sum); free(present); free(ans);
    return 0;
}
