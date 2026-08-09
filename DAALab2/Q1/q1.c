/* ============================================================
   Design and Analysis of Algorithms - Lab 02, Q1
   Empirical validation of Dictionary ADT running times across:
     1. Unsorted array
     2. Sorted array
     3. Singly linked unsorted list
     4. Singly linked sorted list
     5. Doubly linked unsorted list
     6. Doubly linked sorted list
   Operations: Search, Insert, Delete, Max, Min, Predecessor, Successor
   Output: results.csv  (structure,operation,n,time_us)
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REPEATS 25

/* ---------- timing helper (portable: Windows + Linux/Mac) ---------- */
#if defined(_WIN32)
    #include <windows.h>
    static double now_us(void) {
        static LARGE_INTEGER freq;
        static int init = 0;
        LARGE_INTEGER counter;
        if (!init) { QueryPerformanceFrequency(&freq); init = 1; }
        QueryPerformanceCounter(&counter);
        return (double)counter.QuadPart * 1e6 / (double)freq.QuadPart;
    }
#else
    #include <time.h>
    static double now_us(void) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
    }
#endif

FILE *out;
static void log_result(const char *structure, const char *op, int n, double us) {
    fprintf(out, "%s,%s,%d,%.4f\n", structure, op, n, us);
}

/* ============================================================
   1. UNSORTED ARRAY
   ============================================================ */
typedef struct { int *a; int n; int cap; } ArrU;

ArrU arrU_build(int n, int extra) {
    ArrU s; s.cap = n + extra; s.n = n;
    s.a = malloc(sizeof(int) * s.cap);
    for (int i = 0; i < n; i++) s.a[i] = 2 * i;   /* even values */
    return s;
}
void arrU_free(ArrU *s) { free(s->a); }

void bench_arrU(int n) {
    ArrU s = arrU_build(n, REPEATS);
    double t0, t1;

    /* Search: absent key (odd, out of range) -> forces full scan */
    t0 = now_us();
    volatile int found;
    for (int r = 0; r < REPEATS; r++) {
        found = -1;
        for (int i = 0; i < s.n; i++) if (s.a[i] == 2*n + 1) { found = i; break; }
    }
    t1 = now_us();
    log_result("UnsortedArray", "Search", n, (t1 - t0) / REPEATS);

    /* Insert: append at end -> O(1) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) s.a[s.n++] = 999999;
    t1 = now_us();
    log_result("UnsortedArray", "Insert", n, (t1 - t0) / REPEATS);

    /* Delete: swap-with-last trick -> O(1) (order doesn't matter) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        int idx = 0; /* delete "first" element each time via swap trick */
        s.a[idx] = s.a[s.n - 1];
        s.n--;
    }
    t1 = now_us();
    log_result("UnsortedArray", "Delete", n, (t1 - t0) / REPEATS);

    /* Max / Min: full scan -> O(n) */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) {
        mx = s.a[0];
        for (int i = 1; i < s.n; i++) if (s.a[i] > mx) mx = s.a[i];
    }
    t1 = now_us();
    log_result("UnsortedArray", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) {
        mn = s.a[0];
        for (int i = 1; i < s.n; i++) if (s.a[i] < mn) mn = s.a[i];
    }
    t1 = now_us();
    log_result("UnsortedArray", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor / Successor of an existing key: full scan -> O(n) */
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) {
        int target = 2 * (n - 1); /* value that requires scanning far */
        pred = -1; int best = -1;
        for (int i = 0; i < s.n; i++)
            if (s.a[i] < target && s.a[i] > best) best = s.a[i];
        pred = best;
    }
    t1 = now_us();
    log_result("UnsortedArray", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    for (int r = 0; r < REPEATS; r++) {
        int target = 0;
        succ = -1; int best = 1 << 30;
        for (int i = 0; i < s.n; i++)
            if (s.a[i] > target && s.a[i] < best) best = s.a[i];
        succ = best;
    }
    t1 = now_us();
    log_result("UnsortedArray", "Successor", n, (t1 - t0) / REPEATS);

    arrU_free(&s);
}

/* ============================================================
   2. SORTED ARRAY
   ============================================================ */
typedef struct { int *a; int n; int cap; } ArrS;

ArrS arrS_build(int n, int extra) {
    ArrS s; s.cap = n + extra; s.n = n;
    s.a = malloc(sizeof(int) * s.cap);
    for (int i = 0; i < n; i++) s.a[i] = 2 * i;
    return s;
}
void arrS_free(ArrS *s) { free(s->a); }

int bsearch_idx(int *a, int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] == key) return mid;
        else if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -(lo + 1); /* insertion point encoded */
}

void bench_arrS(int n) {
    ArrS s = arrS_build(n, REPEATS);
    double t0, t1;

    /* Search: binary search for absent key -> O(log n) */
    t0 = now_us();
    volatile int idx;
    for (int r = 0; r < REPEATS; r++) idx = bsearch_idx(s.a, s.n, 2*n + 1);
    t1 = now_us();
    log_result("SortedArray", "Search", n, (t1 - t0) / REPEATS);

    /* Insert: find position (binary search) then shift -> O(n) worst case (insert at front) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        for (int i = s.n; i > 0; i--) s.a[i] = s.a[i - 1];
        s.a[0] = -1 - r;
        s.n++;
    }
    t1 = now_us();
    log_result("SortedArray", "Insert", n, (t1 - t0) / REPEATS);

    /* Delete: remove front element, shift -> O(n) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        for (int i = 0; i < s.n - 1; i++) s.a[i] = s.a[i + 1];
        s.n--;
    }
    t1 = now_us();
    log_result("SortedArray", "Delete", n, (t1 - t0) / REPEATS);

    /* Max / Min: ends of array -> O(1) */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) mx = s.a[s.n - 1];
    t1 = now_us();
    log_result("SortedArray", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) mn = s.a[0];
    t1 = now_us();
    log_result("SortedArray", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor / Successor given key: binary search then index +-1 -> O(log n) */
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) {
        int i = bsearch_idx(s.a, s.n, s.a[s.n - 1]);
        pred = (i > 0) ? s.a[i - 1] : -1;
    }
    t1 = now_us();
    log_result("SortedArray", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    for (int r = 0; r < REPEATS; r++) {
        int i = bsearch_idx(s.a, s.n, s.a[0]);
        succ = (i < s.n - 1) ? s.a[i + 1] : -1;
    }
    t1 = now_us();
    log_result("SortedArray", "Successor", n, (t1 - t0) / REPEATS);

    arrS_free(&s);
}

/* ============================================================
   3. SINGLY LINKED UNSORTED LIST
   ============================================================ */
typedef struct SNode { int val; struct SNode *next; } SNode;

SNode* sll_build(int n) {
    SNode *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        SNode *nd = malloc(sizeof(SNode));
        nd->val = 2 * i; nd->next = NULL;
        if (!head) head = tail = nd; else { tail->next = nd; tail = nd; }
    }
    return head;
}
void sll_free(SNode *h) { while (h) { SNode *t = h->next; free(h); h = t; } }

void bench_sllU(int n) {
    SNode *head = sll_build(n);
    double t0, t1;

    /* Search absent key -> O(n) */
    t0 = now_us();
    volatile int found;
    for (int r = 0; r < REPEATS; r++) {
        found = 0;
        for (SNode *p = head; p; p = p->next) if (p->val == 2*n+1) { found = 1; break; }
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Search", n, (t1 - t0) / REPEATS);

    /* Insert at head -> O(1) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        SNode *nd = malloc(sizeof(SNode));
        nd->val = 999999; nd->next = head; head = nd;
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Insert", n, (t1 - t0) / REPEATS);

    /* Delete: given pointer to LAST node -> must traverse to find predecessor -> O(n) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        if (head->next == NULL) continue;
        SNode *prev = head;
        while (prev->next->next != NULL) prev = prev->next;
        SNode *target = prev->next;
        prev->next = NULL;
        free(target);
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Delete", n, (t1 - t0) / REPEATS);

    /* Max / Min: traverse all -> O(n) */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) {
        mx = head->val;
        for (SNode *p = head; p; p = p->next) if (p->val > mx) mx = p->val;
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) {
        mn = head->val;
        for (SNode *p = head; p; p = p->next) if (p->val < mn) mn = p->val;
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor / Successor -> O(n) (must scan whole list) */
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) {
        int target = 2 * (n - 1), best = -1;
        for (SNode *p = head; p; p = p->next) if (p->val < target && p->val > best) best = p->val;
        pred = best;
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    for (int r = 0; r < REPEATS; r++) {
        int target = 0, best = 1 << 30;
        for (SNode *p = head; p; p = p->next) if (p->val > target && p->val < best) best = p->val;
        succ = best;
    }
    t1 = now_us();
    log_result("SLL_Unsorted", "Successor", n, (t1 - t0) / REPEATS);

    sll_free(head);
}

/* ============================================================
   4. SINGLY LINKED SORTED LIST
   ============================================================ */
void bench_sllS(int n) {
    SNode *head = sll_build(n); /* already sorted ascending */
    double t0, t1;

    /* Search absent key -> O(n) (can early-exit once value exceeds key, still O(n) worst case for large absent key) */
    t0 = now_us();
    volatile int found;
    for (int r = 0; r < REPEATS; r++) {
        found = 0;
        for (SNode *p = head; p; p = p->next) {
            if (p->val == 2*n+1) { found = 1; break; }
            if (p->val > 2*n+1) break;
        }
    }
    t1 = now_us();
    log_result("SLL_Sorted", "Search", n, (t1 - t0) / REPEATS);

    /* Insert maintaining order (insert near the end -> worst case) -> O(n) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        SNode *nd = malloc(sizeof(SNode));
        nd->val = 1000000 + r;
        SNode *p = head;
        while (p->next != NULL) p = p->next;
        nd->next = NULL; p->next = nd;
    }
    t1 = now_us();
    log_result("SLL_Sorted", "Insert", n, (t1 - t0) / REPEATS);

    /* Delete last node (needs predecessor traversal) -> O(n) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        if (head->next == NULL) continue;
        SNode *prev = head;
        while (prev->next->next != NULL) prev = prev->next;
        SNode *target = prev->next;
        prev->next = NULL;
        free(target);
    }
    t1 = now_us();
    log_result("SLL_Sorted", "Delete", n, (t1 - t0) / REPEATS);

    /* Max: traverse to tail -> O(n).  Min: head -> O(1) */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) {
        SNode *p = head; while (p->next) p = p->next; mx = p->val;
    }
    t1 = now_us();
    log_result("SLL_Sorted", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) mn = head->val;
    t1 = now_us();
    log_result("SLL_Sorted", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor: need to traverse from head -> O(n).  Successor: next pointer -> O(1) once node found; here we time given-key lookup + next as O(n)+O(1); classic ADT count for pointer x is O(1), so time the O(1) next-hop given we already hold node pointer */
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) {
        int target = 2*(n-1);
        SNode *p = head, *prev = NULL;
        while (p && p->val < target) { prev = p; p = p->next; }
        pred = prev ? prev->val : -1;
    }
    t1 = now_us();
    log_result("SLL_Sorted", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    SNode *xnode = head; /* pointer we already hold: successor is O(1) */
    for (int r = 0; r < REPEATS; r++) succ = xnode->next ? xnode->next->val : -1;
    t1 = now_us();
    log_result("SLL_Sorted", "Successor", n, (t1 - t0) / REPEATS);

    sll_free(head);
}

/* ============================================================
   5. DOUBLY LINKED UNSORTED LIST
   ============================================================ */
typedef struct DNode { int val; struct DNode *prev, *next; } DNode;

DNode* dll_build(int n) {
    DNode *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        DNode *nd = malloc(sizeof(DNode));
        nd->val = 2 * i; nd->next = NULL; nd->prev = tail;
        if (!head) head = nd; else tail->next = nd;
        tail = nd;
    }
    return head;
}
void dll_free(DNode *h) { while (h) { DNode *t = h->next; free(h); h = t; } }

void bench_dllU(int n) {
    DNode *head = dll_build(n);
    DNode *tail = head; while (tail->next) tail = tail->next;
    double t0, t1;

    /* Search absent -> O(n) */
    t0 = now_us();
    volatile int found;
    for (int r = 0; r < REPEATS; r++) {
        found = 0;
        for (DNode *p = head; p; p = p->next) if (p->val == 2*n+1) { found = 1; break; }
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Search", n, (t1 - t0) / REPEATS);

    /* Insert at head -> O(1) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        DNode *nd = malloc(sizeof(DNode));
        nd->val = 999999; nd->prev = NULL; nd->next = head;
        head->prev = nd; head = nd;
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Insert", n, (t1 - t0) / REPEATS);

    /* Delete given pointer to tail -> O(1) using prev pointer directly */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        DNode *target = tail;
        tail = tail->prev;
        if (tail) tail->next = NULL;
        free(target);
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Delete", n, (t1 - t0) / REPEATS);
    /* rebuild consumed tail nodes for subsequent ops to keep list length ~n */
    dll_free(head);
    head = dll_build(n);
    tail = head; while (tail->next) tail = tail->next;

    /* Max / Min -> O(n) scan */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) {
        mx = head->val;
        for (DNode *p = head; p; p = p->next) if (p->val > mx) mx = p->val;
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) {
        mn = head->val;
        for (DNode *p = head; p; p = p->next) if (p->val < mn) mn = p->val;
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor / Successor -> O(n) scan (unsorted) */
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) {
        int target = 2*(n-1), best = -1;
        for (DNode *p = head; p; p = p->next) if (p->val < target && p->val > best) best = p->val;
        pred = best;
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    for (int r = 0; r < REPEATS; r++) {
        int target = 0, best = 1 << 30;
        for (DNode *p = head; p; p = p->next) if (p->val > target && p->val < best) best = p->val;
        succ = best;
    }
    t1 = now_us();
    log_result("DLL_Unsorted", "Successor", n, (t1 - t0) / REPEATS);

    dll_free(head);
}

/* ============================================================
   6. DOUBLY LINKED SORTED LIST
   ============================================================ */
void bench_dllS(int n) {
    DNode *head = dll_build(n); /* sorted ascending */
    DNode *tail = head; while (tail->next) tail = tail->next;
    double t0, t1;

    /* Search absent -> O(n) */
    t0 = now_us();
    volatile int found;
    for (int r = 0; r < REPEATS; r++) {
        found = 0;
        for (DNode *p = head; p; p = p->next) {
            if (p->val == 2*n+1) { found = 1; break; }
            if (p->val > 2*n+1) break;
        }
    }
    t1 = now_us();
    log_result("DLL_Sorted", "Search", n, (t1 - t0) / REPEATS);

    /* Insert at tail (worst case: still O(n) to find position by walking from head) */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        DNode *nd = malloc(sizeof(DNode));
        nd->val = 1000000 + r;
        DNode *p = head; while (p->next) p = p->next;
        nd->prev = p; nd->next = NULL; p->next = nd;
    }
    t1 = now_us();
    log_result("DLL_Sorted", "Insert", n, (t1 - t0) / REPEATS);
    dll_free(head); head = dll_build(n);
    tail = head; while (tail->next) tail = tail->next;

    /* Delete given pointer to tail -> O(1) via prev pointer */
    t0 = now_us();
    for (int r = 0; r < REPEATS; r++) {
        DNode *target = tail;
        tail = tail->prev;
        if (tail) tail->next = NULL;
        free(target);
    }
    t1 = now_us();
    log_result("DLL_Sorted", "Delete", n, (t1 - t0) / REPEATS);
    dll_free(head); head = dll_build(n);
    tail = head; while (tail->next) tail = tail->next;

    /* Max = tail (O(1) since tail pointer maintained), Min = head (O(1)) */
    t0 = now_us();
    volatile int mx;
    for (int r = 0; r < REPEATS; r++) mx = tail->val;
    t1 = now_us();
    log_result("DLL_Sorted", "Max", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int mn;
    for (int r = 0; r < REPEATS; r++) mn = head->val;
    t1 = now_us();
    log_result("DLL_Sorted", "Min", n, (t1 - t0) / REPEATS);

    /* Predecessor / Successor given pointer x -> O(1) via prev/next */
    DNode *xnode = tail;
    t0 = now_us();
    volatile int pred;
    for (int r = 0; r < REPEATS; r++) pred = xnode->prev ? xnode->prev->val : -1;
    t1 = now_us();
    log_result("DLL_Sorted", "Predecessor", n, (t1 - t0) / REPEATS);

    t0 = now_us();
    volatile int succ;
    for (int r = 0; r < REPEATS; r++) succ = xnode->next ? xnode->next->val : -1;
    t1 = now_us();
    log_result("DLL_Sorted", "Successor", n, (t1 - t0) / REPEATS);

    dll_free(head);
}

/* ============================================================ */
int main(void) {
    out = fopen("results.csv", "w");
    fprintf(out, "structure,operation,n,time_us\n");

    int sizes[] = {500, 1000, 2000, 4000, 8000, 12000, 16000, 20000, 24000, 28000};
    int ns = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < ns; i++) {
        int n = sizes[i];
        bench_arrU(n);
        bench_arrS(n);
        bench_sllU(n);
        bench_sllS(n);
        bench_dllU(n);
        bench_dllS(n);
        fprintf(stderr, "done n=%d\n", n);
    }

    fclose(out);
    printf("Wrote results.csv\n");
    return 0;
}
