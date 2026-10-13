
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef struct { ll w; int root; } Item;

int *parent, *sz;
ll *sum;
Item *heap;
int hs = 0;

int find(int x) {
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}

void push(ll w, int r) {
    int i = hs++;
    heap[i].w = w; heap[i].root = r;
    while (i > 0 && heap[(i - 1) / 2].w < heap[i].w) {
        Item t = heap[i]; heap[i] = heap[(i - 1) / 2]; heap[(i - 1) / 2] = t;
        i = (i - 1) / 2;
    }
}

void pop(void) {
    heap[0] = heap[--hs];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < hs && heap[l].w > heap[m].w) m = l;
        if (r < hs && heap[r].w > heap[m].w) m = r;
        if (m == i) break;
        Item t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
}

/* discard stale entries; return best valid weight or 0 */
ll best(int K) {
    while (hs > 0) {
        int r = heap[0].root;
        if (parent[r] == r && sum[r] == heap[0].w && sz[r] <= K) return heap[0].w;
        pop();
    }
    return 0;
}

int main(void) {
    int V, K, E;
    scanf("%d %d", &V, &K);
    parent = malloc(V * sizeof(int));
    sz = malloc(V * sizeof(int));
    sum = malloc(V * sizeof(ll));
    for (int i = 0; i < V; i++) {
        scanf("%lld", &sum[i]);
        parent[i] = i; sz[i] = 1;
    }
    scanf("%d", &E);
    heap = malloc((size_t)(V + E + 1) * sizeof(Item));
    if (K >= 1)
        for (int i = 0; i < V; i++) push(sum[i], i);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int a = find(u), b = find(v);
        if (a != b) {
            if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
            parent[b] = a;
            sz[a] += sz[b];
            sum[a] += sum[b];
            if (sz[a] <= K) push(sum[a], a);
        }
        printf("After edge (%d,%d): max weight = %lld\n", u, v, best(K));
    }
    free(parent); free(sz); free(sum); free(heap);
    return 0;
}
