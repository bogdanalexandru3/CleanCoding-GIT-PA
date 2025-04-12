/* Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf */

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim int-uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa
NODE;

typedef struct g {
    int v;
    int *vis;
    struct Node **alst;
}
GPH;

typedef struct s {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;

    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("adauga %d muchii (de la 0 la %d)\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int check_direct_connection(GPH *g, int src, int dest) {
    NODE *aux = g->alst[src];
    while (aux != NULL) {
        if (aux->data == dest) {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int main() {

    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    printf("introduceti cele doua noduri pentru verificare: ");
    scanf("%d %d", &vortex_1, &virtex_2);

    ans = check_direct_connection(g, vortex_1, virtex_2);

    if (ans) {
        printf("Exista drum direct intre %d si %d.\n", vortex_1, virtex_2);
    } else {
        printf("Nu exista drum direct intre %d si %d.\n", vortex_1, virtex_2);
    }

    for (int i = 0; i < nrv; i++) {
        NODE *temp = g->alst[i];
        while (temp != NULL) {
            NODE *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(g->alst);
    free(g->vis);
    free(g);
    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);

    return 0;
}
