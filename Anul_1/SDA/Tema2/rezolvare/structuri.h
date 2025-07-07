/* MICU Francesca-Maria - 313CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  macro-uri
#define FAIL -1
#define MAX_LEN 250

//  structuri implementate

//  structura pentru informatile din satelit
typedef struct satelit {
    int frecv;
    char *nume;
}TSatelit;

typedef int (*TFCmp)(TSatelit, TSatelit);

//  structura pentru heap
typedef struct Heap {
    int nrMax, nrElem;
    TSatelit *info;
    TFCmp comp;
} THeap;

//  structura pentru arbore binar
typedef struct nod {
    TSatelit info;
    struct nod *st, *dr;
} TNod, *TArb;

//  structura pentru lista simplu inlantuita
typedef struct celula { 
    TArb info;
    struct celula *urm;
} TCelula, *TLista;

//  structura pentru coada
typedef struct coada {
    TLista inc, sf;
} TCoada;

//  functiile folosite in implementarea temei
int RelMinHeap(TSatelit a, TSatelit b);
TArb ImplemArb(FILE *inp_file);
void Task1(TArb arb, FILE *out_file);
void Task2(FILE *inp_file, FILE *out_file, TArb arb);
void Task3(FILE *inp_file, FILE *out_file, TArb arb);
void Task4(FILE *inp_file, FILE *out_file, TArb arb);

//  functii folosite pentru prelucrarea heap-ului
void InserHeap(THeap *heap, TSatelit val);
TSatelit ExtrHeap(THeap *h);

//  functii pentru prelucrarea arborelui
TArb CautaSat(TArb arb, TSatelit sat);
int CautaNumeSat(TArb arb, char *sat);
TArb ConstrArb(THeap *min_heap, int nr_sateliti);
char *CodifArb(TArb arb, char *codif, char *nume_sat, int idx_codif);
char *CautaSatComun(char **nume_sat, int nr_sat_caut, TArb arb);

//  functii pentru prelucrarea cozii
TArb ExtrCoada(TCoada *c);
void InserCoada(TCoada *c, TArb arb);
int NumarNodCoada(TCoada *c);

//  functii alocare si eliberare de memorie
THeap *AlocHeap(int nrMax, TFCmp comp);
TArb ConstrNod(TSatelit sat);
void ELibArb(TArb *a);
void ElibNodArb(TArb arb);
void ElibHeap(THeap **heap);
void ElibCoada(TCoada **c);