
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz, *par; /* par[x]: parity of x w.r.t. parent[x] */

int find(int x, int *p) { /* returns root, *p = parity of x w.r.t. root */
    if (parent[x] == x) { *p = 0; return x; }
    int pp;
    int r = find(parent[x], &pp);
    par[x] ^= pp;       /* path compression: x now points to root */
    parent[x] = r;
    *p = par[x];
    return r;
}

int main(void) {
    int V, E;
    scanf("%d %d", &V, &E);
    parent = malloc(V * sizeof(int));
    sz = malloc(V * sizeof(int));
    par = calloc(V, sizeof(int));
    for (int i = 0; i < V; i++) { parent[i] = i; sz[i] = 1; }

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int pu, pv;
        int ru = find(u, &pu), rv = find(v, &pv);
        if (ru == rv) {
            if (pu == pv) { printf("Edge (%d,%d): violates bipartiteness (skipped)\n", u, v); continue; }
            printf("Edge (%d,%d): added, graph still bipartite\n", u, v);
        } else {
            if (sz[ru] < sz[rv]) { int t = ru; ru = rv; rv = t; }
            parent[rv] = ru;
            par[rv] = pu ^ pv ^ 1; /* force u and v onto different sides */
            sz[ru] += sz[rv];
            printf("Edge (%d,%d): added, graph still bipartite\n", u, v);
        }
    }
    free(parent); free(sz); free(par);
    return 0;
}
