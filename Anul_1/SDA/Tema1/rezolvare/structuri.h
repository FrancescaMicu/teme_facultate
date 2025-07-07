/* MICU Francesca-Maria - 313CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  macro-uri 
#define MAX_LEN 50
#define FAIL -1

//  structuri implementate
typedef struct page {
    int id;
    char url[MAX_LEN];
    char *description;
}TPage;

typedef struct stack {
    TPage *info;
    struct stack *urm;
} TCelulaStiva, *TStiva;

typedef struct tab {
    int id;
    TPage *currentPage;
    TStiva backwardStack;
    TStiva forwardStack;
}TTab;

typedef struct tabsList {
    TTab *info;
    struct tabsList *pre, *urm;
}TCelTab, *TListTab;

typedef struct browser {
    TTab *current;
    TListTab list_2_inl;
}TBrow;

//  functii auxiliare
TPage *AlocPag(int id, char* url, char* descr);
TTab *AlocTab(int id, TPage *curr_page);
TPage *CreatePag_0();
TTab *CreateTab_0(TPage *pag_0);
TBrow *AlocBrowser(TPage *pag_0);
TListTab AlocLista();
TListTab AlocNodLista(TTab *tab, TListTab list);
int ALocNodStiva(TStiva *stiva, TPage *pag);
void AfisStivaInv(TStiva stiva, FILE *out_file);
int ExtragNodStiva(TStiva *stiva, TPage **pag);
void ElibStiva(TStiva *stiva);
void ElibLista(TListTab *lista);
void ElibPag(TPage **pag);
void ElibTab(TTab **tab);
void ElibBrow(TBrow **brow);

//  functii task-uri
void NEW_TAB(TBrow *brow, int *tab_id_curr, TPage *pag_0);
void PRINT(TBrow *brow, FILE *out_file);
void CLOSE(TBrow *brow, FILE *out_file);
void OPEN(TBrow *brow, char *id, FILE *out_file);
void NEXT(TBrow *brow);
void PREV(TBrow *brow);
void PAGE(TBrow *brow, char *id, TPage **pag, int nr_pag, FILE *out_file);
void PRINT_HISTORY(TBrow *brow, FILE *out_file, char *id);
void BACKWARD(TBrow *brow, FILE *out_file);
void FORWARD(TBrow *brow, FILE *out_file);
