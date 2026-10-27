#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, K, R;
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (m): ");
    scanf("%d", &m);
    printf("Enter number of hubs (K): ");
    scanf("%d", &K);
    printf("Enter radius threshold (R): ");
    scanf("%d", &R);

    int *hub = malloc(K * sizeof(int));
    printf("Enter %d hub vertices (h1 to hK, space separated): ", K);
    for (int i = 0; i < K; i++) scanf("%d", &hub[i]);

    int *head = malloc((n + 1) * sizeof(int));
    int *nxt = malloc(2 * m * sizeof(int)), *to = malloc(2 * m * sizeof(int));
    for (int i = 0; i <= n; i++) head[i] = -1;
    int ec = 0;

    printf("Enter %d undirected edges as: u v\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);
        to[ec] = v; nxt[ec] = head[u]; head[u] = ec++;
        to[ec] = u; nxt[ec] = head[v]; head[v] = ec++;
    }

    int *dist = malloc((n + 1) * sizeof(int));
    int *owner = malloc((n + 1) * sizeof(int));
    int *q = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) { dist[i] = -1; owner[i] = -1; }

    int qh = 0, qt = 0;
    for (int i = 0; i < K; i++) {
        int h = hub[i];
        if (dist[h] == -1) { dist[h] = 0; owner[h] = i + 1; q[qt++] = h; }
    }
    while (qh < qt) {
        int u = q[qh++];
        if (dist[u] == R) continue;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1; owner[v] = owner[u]; q[qt++] = v;
            } else if (dist[v] == dist[u] + 1 && owner[u] < owner[v]) {
                owner[v] = owner[u];
            }
        }
    }

    printf("\nVertex assignments:\n");
    for (int v = 1; v <= n; v++) {
        if (owner[v] == -1) printf("Vertex %d: owner = -1 (outside coverage), distance = -\n", v);
        else printf("Vertex %d: owner = hub %d, distance = %d\n", v, owner[v], dist[v]);
    }
    return 0;
}