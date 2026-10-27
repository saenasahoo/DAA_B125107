#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 12
#define TS (1 << 18)

char (*W)[MAXL];
int *tab;

unsigned hs(const char *s) {
    unsigned h = 5381;
    while (*s) h = h * 33 + (unsigned char)*s++;
    return h;
}
int find(const char *s) {
    unsigned i = hs(s) & (TS - 1);
    while (tab[i] != -1) {
        if (!strcmp(W[tab[i]], s)) return tab[i];
        i = (i + 1) & (TS - 1);
    }
    return -1;
}
void insert(int idx) {
    unsigned i = hs(W[idx]) & (TS - 1);
    while (tab[i] != -1) i = (i + 1) & (TS - 1);
    tab[i] = idx;
}

int main() {
    int N, L;
    printf("Enter number of dictionary words (N <= 100000): ");
    scanf("%d", &N);
    printf("Enter word length (L <= 10): ");
    scanf("%d", &L);

    W = malloc((N + 2) * sizeof(*W));
    tab = malloc(TS * sizeof(int));
    for (int i = 0; i < TS; i++) tab[i] = -1;

    int cnt = 0;
    printf("Enter %d dictionary words (lowercase, one per line):\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%s", W[cnt]);
        if (find(W[cnt]) == -1) insert(cnt++);
    }

    char A[MAXL], B[MAXL];
    printf("Enter start word A: ");
    scanf("%s", A);
    printf("Enter target word B: ");
    scanf("%s", B);

    int b = find(B);
    if (b == -1) { printf("Result: -1 (target word is not in the dictionary)\n"); return 0; }
    if (!strcmp(A, B)) { printf("Minimum mutations: 0\n"); return 0; }
    int a = find(A);
    if (a == -1) { strcpy(W[cnt], A); a = cnt; insert(cnt++); }

    char *side = calloc(cnt, 1);
    int *dist = calloc(cnt, sizeof(int));
    int *q[3]; int hd[3] = {0}, tl[3] = {0};
    q[1] = malloc(cnt * sizeof(int));
    q[2] = malloc(cnt * sizeof(int));
    side[a] = 1; dist[a] = 0; q[1][tl[1]++] = a;
    side[b] = 2; dist[b] = 0; q[2][tl[2]++] = b;

    while (hd[1] < tl[1] && hd[2] < tl[2]) {
        int me = (tl[1] - hd[1] <= tl[2] - hd[2]) ? 1 : 2;
        int other = 3 - me;
        int end = tl[me], best = 1 << 30;
        while (hd[me] < end) {
            int u = q[me][hd[me]++];
            char buf[MAXL];
            strcpy(buf, W[u]);
            for (int p = 0; p < L; p++) {
                char orig = buf[p];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    buf[p] = c;
                    int v = find(buf);
                    if (v < 0) continue;
                    if (side[v] == other) {
                        int cand = dist[u] + 1 + dist[v];
                        if (cand < best) best = cand;
                    } else if (side[v] == 0) {
                        side[v] = me; dist[v] = dist[u] + 1;
                        q[me][tl[me]++] = v;
                    }
                }
                buf[p] = orig;
            }
        }
        if (best < (1 << 30)) { printf("Minimum mutations: %d\n", best); return 0; }
    }
    printf("Result: -1 (no valid transformation exists)\n");
    return 0;
}