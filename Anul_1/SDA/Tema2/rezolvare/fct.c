/* MICU Francesca-Maria - 313CB */

#include "structuri.h"

//  functiile folosite in implementarea temei

// functie pentru verificarea relatiei de MinHeap
int RelMinHeap(TSatelit a, TSatelit b) {
    //  verifica daca frecventele sunt egale
    if ( a.frecv != b.frecv ) {
        return a.frecv - b.frecv;
    }
    //  comparare in caz de egalitate a frecventelor
    return strcmp(a.nume, b.nume);
}

//  functie pentru constructia heap-ului si dupa a arborelui
TArb ImplemArb(FILE *inp_file) {
    //  citirea din fisier
    char *lin = (char*)malloc(MAX_LEN * sizeof(char));
    fgets(lin, MAX_LEN, inp_file);
    int nr_sateliti = atoi(lin);
    //  alocare min heap
    THeap *min_heap = AlocHeap(nr_sateliti, RelMinHeap);
    //  verificare in caz de esec
    if ( !min_heap ) {
        free(lin);
        return NULL;
    }
    for ( int i = 0; i < nr_sateliti; i++ ) {
        fgets(lin, MAX_LEN, inp_file);
        //  obtinerea datelor despre sateliti
        char *frecv = strtok(lin, " ");
        char *nume = strtok(NULL, " ");
        //  stergerea newline-ului ramas
        nume[strcspn(nume, "\n")] = '\0';
        //  alocarea satelitului
        TSatelit satelit;
        satelit.frecv = atoi(frecv);
        satelit.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
        //  verificare in caz de esec
        if ( !satelit.nume ) {
            free(lin);
            ElibHeap(&min_heap);
            return NULL;
        }
        strcpy(satelit.nume, nume);
        InserHeap(min_heap, satelit);
    }
    TArb arb = ConstrArb(min_heap, nr_sateliti);
    //  eliberari de memorie
    free(lin);
    ElibHeap(&min_heap);
    return arb;
}

//  implementarea taskului 1
void Task1(TArb arb, FILE *out_file) {
    //  verificare daca arborele este NULL
    if ( !arb ) {
        return;
    }
    //  alocarea cozii
    TCoada *c = (TCoada*)malloc(sizeof(TCoada));
    //  verificare in caz de esec
    if ( !c ) {
        return;
    }
    c->sf = NULL;
    c->inc = NULL;
    //  inserarea in coada 
    InserCoada(c, arb);
    //  parcurgerea cozii
    while ( c->inc != NULL ) {
        //  determinarea numarului de elemente 
        //  pentru afisarea pe nivele
        int nr_coada = NumarNodCoada(c);
        for ( int i = 0; i < nr_coada; i++ ) {
            //  extragerea si afisarea nodului din coada
            TArb nod = ExtrCoada(c);
            fprintf(out_file, "%d-%s", nod->info.frecv, nod->info.nume);
            //  pune spatiu daca nu e ultimul element de pe nivel
            if ( i < nr_coada - 1 ) {
                fprintf(out_file, " ");
            }
            //  inserarea arborelui/nodului stang
            if ( nod->st ) {
                InserCoada(c, nod->st);
            }
            //  inserarea arborelui/nodului drept
            if ( nod->dr ) {
                InserCoada(c, nod->dr);
            }
        }
        fprintf(out_file, "\n");
    }
    //  eliberarea cozii
    ElibCoada(&c);
}

//  implementarea taskului 2
void Task2(FILE *inp_file, FILE *out_file, TArb arb) {
    //  citirea din fisier
    char *lin = (char*)malloc(MAX_LEN * sizeof(char));
    //  verificare in caz de esec
    if ( !lin ) {
        return;
    }
    //  citirea numarului de linii codificate
    fgets(lin, MAX_LEN, inp_file);
    int nr_lin = atoi(lin);
    TArb nod_cautat = arb;
    for ( int i = 0; i < nr_lin; i++ ) {
        fgets(lin, MAX_LEN, inp_file);
        //  eliminarea newline-ului de pe linie
        lin[strcspn(lin, "\n")] = '\0';
        int idx_lin = 0;
        int nr_caract = strlen(lin);
        //  parcurgerea liniei de codificari
        while ( idx_lin < nr_caract ) {
            //  cautarea unei secvente de codificari
            while ( (nod_cautat->st || nod_cautat->dr) && idx_lin < nr_caract ) {
                //  verificarea caracterului din linie
                if ( lin[idx_lin] == '0' && nod_cautat->st ) {
                    nod_cautat = nod_cautat->st;
                } else if ( lin[idx_lin] == '1' && nod_cautat->dr ) {
                    nod_cautat = nod_cautat->dr;
                }
                idx_lin++;
            }
            //  parcurgerea frunzei gasite dupa codificare
            if ( !nod_cautat->st && !nod_cautat->dr ) {
                fprintf(out_file, "%s ", nod_cautat->info.nume);
            }
            //  resetarea pentru cautarea in arbore a urmatorulu nod
            nod_cautat = arb;
        }
        fprintf(out_file, "\n");
    }
    //  eliberare de memorie
    free(lin);
}

//  implementarea taskului 3
void Task3(FILE *inp_file, FILE *out_file, TArb arb) {
    //  citirea din fisier
    char *lin = (char*)malloc(MAX_LEN * sizeof(char));
    //  verificare in caz de esec
    if ( !lin ) {
        return;
    }
    fgets(lin, MAX_LEN, inp_file);
    //  citirea numarului de sateliti din fisier
    int nr_lin = atoi(lin);
    //  parcurgerea satelitilor din fisier
    for ( int i = 0; i < nr_lin; i++ ) {
        fgets(lin, MAX_LEN, inp_file);
        //  eliminarea caracterului newline
        lin[strcspn(lin, "\n")] = '\0';
        //  initializarea variabilei care va retine codificarea
        char *codif = (char*)malloc(MAX_LEN * sizeof(char));
        //  verificare in caz de esec
        if ( !codif ) {
            free(lin);
            return;
        }
        codif[0] = '\0';
        int idx_codif = 0;
        //  apelarea functiei de codificare
        codif = CodifArb(arb, codif, lin, idx_codif);
        if ( codif ) {
            fprintf(out_file, "%s", codif);
            free(codif);
        }
    }
    //  eliberari de memorie
    free(lin);
}

//  implementarea taskului 4
void Task4(FILE *inp_file, FILE *out_file, TArb arb) {
    //  citirea din fisier
    char *lin = (char*)malloc(MAX_LEN * sizeof(char));
    //  verificare in caz de esec
    if ( !lin ) {
        return;
    }
    //  citirea numarului de sateliti din fisier
    fgets(lin, MAX_LEN, inp_file);
    int nr_sat_caut = atoi(lin);
    //  alocarea vectorului de nume de sateliti
    char **nume_sat = (char**)malloc(nr_sat_caut * sizeof(char*));
    //  verificare in caz de esec
    if ( !nume_sat ) {
        free(lin);
        return;
    }
    //  parcurgerea satelitilor din fisier
    for ( int i = 0; i < nr_sat_caut; i++ ) {
        fgets(lin, MAX_LEN, inp_file);
        // eliminarea caracterului newline
        lin[strcspn(lin, "\n")] = '\0';
        //  alocarea numelui respectiv din vector
        nume_sat[i] = (char*)malloc((strlen(lin) + 1) * sizeof(char));
        //  verificare in caz de esec
        if ( !nume_sat[i] ) {
            free(nume_sat);
            free(lin);
            return;
        }
        strcpy(nume_sat[i], lin);
    }
    //  apelarea functiei de cautare a satelitului comun
    fprintf(out_file, "%s", CautaSatComun(nume_sat, nr_sat_caut, arb));
    //  eliberare de memorie
    free(lin);
    for ( int i = 0; i < nr_sat_caut; i++ ) {
        free(nume_sat[i]);
    }
    free(nume_sat);
}

//  functii folosite pentru prelucrarea heap-ului

//  functie pentru inserarea unui element nou in heap
void InserHeap(THeap *heap, TSatelit val) {
    //  realocare daca heapul a depasit nrMax elemente
    if ( heap->nrElem == heap->nrMax ) {
        heap->nrMax++;
        heap->info = realloc(heap->info, heap->nrMax * sizeof(TSatelit));
        //  verificare in caz de esec
        if ( !heap->info ) {
            return;
        }
    }
    //  introducerea noului satelit la finalul vectorului
    heap->info[heap->nrElem++] = val;
    int n = heap->nrElem - 1;
    //  cautarea pozitiei satelitului nou in min heap
    while ( n != 0 && heap->comp(heap->info[(n - 1)/2], heap->info[n]) > 0 ) {
        //  interschimbarea cu noua pozitie
        TSatelit aux = heap->info[(n - 1)/2];
        heap->info[(n - 1)/2] = heap->info[n];
        heap->info[n] = aux;
        n = (n - 1) / 2;
    }
}

//  functie pentru extragerea primului element din heap
TSatelit ExtrHeap(THeap *h) {
    //  pregatirea unui satelit gol in caz de esec
    TSatelit sat_gol;
    sat_gol.frecv = -1;
    sat_gol.nume = NULL;
    //  verificare daca heap-ul e gol
    if ( h == NULL ) {
        return sat_gol;
    }
    //  verificare daca vectorul din heap e gol
    if ( h->info == NULL ) {
        return sat_gol;
    }
    //  verificare daca nu sunt elemente curente in heap
    if ( h->nrElem == 0 ) {
        return sat_gol;
    }
    TSatelit val = h->info[0];
    h->info[0] = h->info[h->nrElem - 1];
    int n = 0;
    h->nrElem--;
    //  parcurgerea heap-ului
    while ( n != h->nrElem - 1 ) {
        int idx = n, st = 2 * n + 1, dr = 2 * n + 2;
        //  cautare la stanga
        if ( st < h->nrElem && h->comp(h->info[st], h->info[idx]) < 0 ) {
            idx = st;
        }
        //  cautare la dreapta
        if ( dr < h->nrElem && h->comp(h->info[dr], h->info[idx]) < 0 ) {
            idx = dr;
        }
        if ( idx == n ) {
            break;
        }
        //  interschimbarea elementelor
        TSatelit aux = h->info[idx];
        h->info[idx] = h->info[n];
        h->info[n] = aux;
        n = idx;
    }
    return val;    
}

//  functii pentru prelucrarea arborelui

//  functie pentru cautarea unui satelit in arbore
TArb CautaSat(TArb arb, TSatelit sat) {
    //  verificare daca arborele este NULL
	if ( !arb ) {
		return NULL;
	}
    //  verificare daca s-a gasit satelitul cautat
	if ( arb->info.frecv == sat.frecv && strcmp(arb->info.nume, sat.nume) == 0 ) {
		return arb;
	}
    //  cautarea in subarborele stang al arborelui
    if ( arb->st ) {
        TArb st = CautaSat(arb->st, sat);
	    if ( st ) {
		    return st;
	    }
    }
    //  cautarea in subarborele drept al arborelui
    if ( arb->dr ) {
        TArb dr = CautaSat(arb->dr, sat);
        if ( dr ) {
            return dr;
        } 
    }
	return NULL;
}

//  functie pentru cautarea unui satelit in arbore cu numele cerut
int CautaNumeSat(TArb arb, char *sat) {
    //  verificare daca arborele este este NULL
	if ( !arb ) {
		return 0;
	}
    //  verificare daca s-a gasit satelitul cu numele cautat
	if ( strcmp(arb->info.nume, sat) == 0 ) {
		return 1;
	}
    //  cautarea in subarborele stang al arborelui
    if ( arb->st ) {
        int st = CautaNumeSat(arb->st, sat);
	    if ( st ) {
		    return st;
	    }
    }
    //  cautarea in subarborele drept al arborelui
    if ( arb->dr ) {
        int dr = CautaNumeSat(arb->dr, sat);
        if ( dr ) {
            return dr;
        }
    }
    return 0;
}

//  functie pentru constructia arborelui din min heap
TArb ConstrArb(THeap *min_heap, int nr_sateliti) {
    TArb arb = NULL;
    //  alocare vector de arbori
    TArb *arb_tmp = (TArb*)malloc(nr_sateliti * sizeof(TArb));
    //  verificare in caz de esec
    if ( !arb_tmp ) {
        return NULL;
    }
    //  initializarea pointerilor din arb_tmp la NULL
    for ( int i = 0; i < nr_sateliti; i++ ) {
        arb_tmp[i] = NULL;
    }
    int idx_arb = 0;
    while ( min_heap->nrElem != 1 ) {
        //  extragerea celor 2 minimuri
        TSatelit min1 = ExtrHeap(min_heap);
        TSatelit min2 = ExtrHeap(min_heap);
        //  verificare in caz de esec
        if ( !min1.nume || !min2.nume ) {
            free(arb_tmp);
            return NULL;
        }
        //  determinarea satelitului de legatura
        TSatelit legat;
        legat.frecv = min1.frecv + min2.frecv;
        //  concatenarea numelui
        legat.nume = (char*)malloc((strlen(min1.nume) + strlen(min2.nume) + 1) * sizeof(char));
        //  verificare in caz de esec
        if ( !legat.nume ) {
            free(min1.nume);
            free(min2.nume);
            free(arb_tmp);
            return NULL;
        }
        strcpy(legat.nume, min1.nume);
        strcat(legat.nume, min2.nume);
        //  inserarea in heap a satelitului de legatura
        InserHeap(min_heap, legat);
        //  adaugarea in arbore a satelitului de legatura
        TArb nod = ConstrNod(legat);
        //  verificare in caz de esec
        if ( !nod ) {
            free(legat.nume);
            free(min1.nume);
            free(min2.nume);
            free(arb_tmp);
            return NULL;
        }
        //  cautarea in arbore a minimelor
        TArb nod_st = CautaSat(arb, min1);
        TArb nod_dr = CautaSat(arb, min2);
        //  daca nu sunt deja adaugate nodurile in arbore
        //  se retin in vectorul de arbori
        if ( nod_st == NULL && nod_dr == NULL && arb ) {
            arb_tmp[idx_arb++] = arb;
        }
        //  construirea nodului daca nu exista
        if ( nod_st == NULL ) {
            nod_st = ConstrNod(min1);
            //  verificare in caz de esec
            if ( !nod_st ) {
                free(legat.nume);
                free(min1.nume);
                free(min2.nume);
                free(arb_tmp);
                return NULL;
            }
        }
        if ( nod_dr == NULL ) {
            nod_dr = ConstrNod(min2);
            //  verificare in caz de esec
            if ( !nod_dr ) {
                ElibNodArb(nod_st);
                free(legat.nume);
                free(min1.nume);
                free(min2.nume);
                free(arb_tmp);
                return NULL;
            }
        }
        //  verificarea existentei satelitilor minimi in vectorul de arbori 
        for ( int i = 0; i < idx_arb; i++ ) {
            if ( arb_tmp[i] != NULL && nod_st->info.frecv == arb_tmp[i]->info.frecv
                && strcmp(nod_st->info.nume, arb_tmp[i]->info.nume) == 0 ) {
                free(nod_st->info.nume);
                free(nod_st);
                nod_st = arb_tmp[i];
            }
            if ( arb_tmp[i] != NULL && nod_dr->info.frecv == arb_tmp[i]->info.frecv
                && strcmp(nod_dr->info.nume, arb_tmp[i]->info.nume) == 0 ) {
                free(nod_dr->info.nume);
                free(nod_dr);
                nod_dr = arb_tmp[i];
            }
        }
        //  legarea nodurilor de parinte
        nod->st = nod_st;
        nod->dr = nod_dr;
        //  resetarea arborelui curent
        arb = nod;
        //  eliberarea memoriei
        free(min1.nume);
        free(min2.nume);
    }
    free(arb_tmp);
    return arb;
}

//  functia de codificare a satelitilor de la taskul 3
char *CodifArb(TArb arb, char *codif, char *nume_sat, int idx_codif) {
    //  verificare daca arborele este NULL
    if ( arb == NULL ) {
        return NULL;
    }
    //  oprirea recursiei daca s-a gasit satelitul cerut
    if ( strcmp(arb->info.nume, nume_sat) == 0 ) {
        codif[idx_codif] = '\0';
        return codif;
    }
    //  cautarea in subarborele stang al arborelui
    if ( arb->st ) {
        codif[idx_codif] = '0';
        char *codif_st = CodifArb(arb->st, codif, nume_sat, idx_codif + 1);
        if ( codif_st ) {
            return codif_st;
        }
    }
    //  cautarea in subarborele stang al arborelui
    if ( arb->dr ) {
        codif[idx_codif] = '1';
        char *codif_dr = CodifArb(arb->dr, codif, nume_sat, idx_codif + 1);
        if ( codif_dr ) {
            return codif_dr;
        }
    }
    return NULL;
}

//  functie de cautare a satelitului comun
char *CautaSatComun(char **nume_sat, int nr_sat_caut, TArb arb) {
    //  verificare daca arborele este NULL
    if ( !arb ) {
        return NULL;
    }
    //  cautarea numelor de sateliti in subarborele respectiv
    int verif_sat = 1;
    for ( int i = 0; i < nr_sat_caut; i++ ) {
        if ( CautaNumeSat(arb, nume_sat[i]) == 0 ) {
            verif_sat = 0;
        }
    }
    //  daca se gasesc, se cauta in urmatorul subarbore
    if ( verif_sat == 1 ) {
        //  cautarea in subarborele stang
        if ( arb->st ) {
            char *sat_st = CautaSatComun(nume_sat, nr_sat_caut, arb->st);
            if ( sat_st ) {
                return sat_st;
            }
        }
        //  cautarea in subarborele drept
        if ( arb->dr ) {
            char *sat_dr = CautaSatComun(nume_sat, nr_sat_caut, arb->dr);
            if ( sat_dr ) {
                return sat_dr;
            }
        }
        return arb->info.nume;
    }
    //  returnare NULL in caz de esec
    return NULL;
}

//  functii pentru prelucrarea cozii

//  functie pentru extragerea unui nod din coada
TArb ExtrCoada(TCoada *c) {
    //  verificare daca coada este goala
    if ( !c->inc ) {
        return NULL;
    }
    //  extragerea primului nod
    TLista aux = c->inc;
    TArb arb = aux->info;
    c->inc = c->inc->urm;
    if ( !c->inc ) {
        c->sf = NULL;
    }
    free(aux);
    return arb;
}

//  functie pentru inserarea unui nod in cod
void InserCoada(TCoada *c, TArb arb) {
    //  alocarea celului noi
    TLista aux = (TLista)malloc(sizeof(TCelula));
    //  verificare in caz de esec
    if ( !aux ) {
        return;
    }
    aux->info = arb;
    aux->urm = NULL;
    //  adaugarea nodului nou in lista
    if ( !c->inc ) {
        c->inc = aux;
        c->sf = aux;
    } else {
        c->sf->urm = aux;
        c->sf = aux;
    }
}

//  functie pentru determinarea numarului de noduri din lista
int NumarNodCoada(TCoada *c) {
    int nr = 0;
    TLista lista = c->inc;
    //  parcurgerea listei
    while ( lista ) {
        nr++;
        lista = lista->urm;
    }
    return nr;
}

//  functii de alocare si eliberare de memorie

//  functie pentru alocare heap
THeap *AlocHeap(int nrMax, TFCmp comp) {
    //  alocare heap
    THeap* heap = (THeap*)malloc(sizeof(THeap));
    //  verificare in caz de esec
    if ( !heap ) {
        return NULL;
    }
    //  alocare vector de sateliti
    heap->info = (TSatelit *)malloc(nrMax * sizeof(TSatelit));
    //  verificare in caz de esec
    if ( !heap->info ) {
		free(heap);
		return NULL;
	}
    heap->nrMax = nrMax;
    heap->nrElem = 0;
    heap->comp = comp;
    return heap;
}

//  functie pentru constructia unui nod in arbore
TArb ConstrNod(TSatelit sat) {
    //  alocarea unui nod nou
    TArb aux = (TArb)malloc(sizeof(TNod));
    //  verificare in caz de esec
    if ( !aux ) {
        return NULL;
    }
    aux->info.frecv = sat.frecv;
    //  alocarea numelui
    aux->info.nume = (char*)malloc((strlen(sat.nume) + 1) * sizeof(char));
    //  verificare in caz de esec
    if ( !aux->info.nume ) {
        free(aux);
        return NULL;
    }
    strcpy(aux->info.nume, sat.nume);
    aux->st = NULL;
    aux->dr = NULL;
    return aux;
}

//  functie pentru eliberarea unui arborelui
void ELibArb(TArb *a) {
    //  verificare daca arborele este gol
	if ( !(*a) ) {
        return;
    }
	ElibNodArb(*a);
	(*a) = NULL;
}

//  functie pentru eliberarea nodurilor din arbore
void ElibNodArb(TArb arb) {
    //  verificare daca arborele este gol
    if ( !arb ) {
        return;
    }
    //  eliberarea recursiva a nodurilor
    ElibNodArb(arb->st);
    ElibNodArb(arb->dr);
    //  eliberarea informatiei din nod
    if ( arb->info.nume ) {
        free(arb->info.nume);
        arb->info.nume = NULL;
    }
    free(arb);
}

//  functie pentru eliberarea unui heap
void ElibHeap(THeap **heap) {
    //  parcurgerea vectorului de sateliti
    for ( int i = 0; i < (*heap)->nrElem; i++ ) {
        if ( (*heap)->info[i].nume ) {
            free((*heap)->info[i].nume);
        }
    }
    //  eliberarea memoriei
    free((*heap)->info);
    free(*heap);
    (*heap) = NULL;
}

//  functie pentru eliberarea unei cozi
void ElibCoada(TCoada **c) {
    TLista list = (*c)->inc, aux;
    //  parcurgerea si eliberarea cozii
    while ( list ) {
        aux = list;
        list = list->urm;
        free(aux);
    }
    free(*c);
    (*c) = NULL;
}
