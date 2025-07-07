/* MICU Francesca-Maria - 313CB */

#include "structuri.h"

//  alocari de memorie
TPage *AlocPag(int id, char* url, char* descr) {
    //  declarare si alocare pagina
    TPage *pag = (TPage*)malloc(sizeof(TPage));
    //  testare in caz de esec
    if ( !pag ) {
        return NULL;
    }
    //  declararea si alocarea campurilor paginii
    pag->id = id;
    strcpy(pag->url, url);
    int desc_len = strlen(descr) + 1;
    pag->description = (char*)malloc(desc_len * sizeof(char));
    //  testare in caz de esec la alocare
    if ( !pag->description ) {
        free(pag);
        return NULL;
    }
    strcpy(pag->description, descr);
    return pag;
}

TPage *CreatePag_0() {
    //  declararea si alocarea campurilor paginii implicite
    int id = 0;
    char url[MAX_LEN] = "https://acs.pub.ro/";
    char descr[MAX_LEN] = "Computer Science";
    //  apelarea functiei de alocare cu parametrii necesari
    TPage *pag = AlocPag(id, url, descr);
    //  testare in caz de esec la alocare
    if ( !pag ) {
        return NULL;
    }
    return pag;
}

TTab *AlocTab(int id, TPage *curr_page) {
    //  declarare si alocare tab
    TTab *tab = (TTab *)malloc(sizeof(TTab));
    //  testare in caz de esec la alocare
    if ( !tab ) {
        return NULL;
    }
    //  declararea si alocarea campurilor din tab
    tab->id = id;
    tab->currentPage = curr_page;
    tab->backwardStack = NULL;
    tab->forwardStack = NULL;
    return tab;
}

TTab *CreateTab_0(TPage *pag_0) {
    //  declararea campurilor tabului implicit
    int id = 0;
    //  apelarea functiei de alocare tab
    TTab *tab = AlocTab(id, pag_0);
    //  testare in caz de esec la alocare
    if ( !tab ) {
        return NULL;
    }
    return tab;
}

TListTab AlocLista() {
    //  declarare si alocare lista
    TListTab list = (TListTab)malloc(sizeof(TCelTab));
    //  testare in caz de esec la alocare
    if ( !list ) {
        return NULL;
    }
    //  crearea legaturiilor santinelei
    list->urm = list;
    list->pre = list;
    list->info = NULL;
    return list;
}

TListTab AlocNodLista(TTab *tab, TListTab list) {
    //  declararea si alocarea nodului
    TListTab nod = (TListTab)malloc(sizeof(TCelTab));
    //  testare in caz de esec la alocare
    if ( !nod ) {
        return NULL;
    }
    //  legarea de santinela a nodului
    nod->info = tab;
    nod->urm = nod->pre = list;
    return nod;
}

TBrow *AlocBrowser(TPage *pag_0) {
    // declararea si alocarea browserului
    TBrow *brow = (TBrow *)malloc(sizeof(TBrow));
    //  testare in caz de esec la alocare
    if ( !brow ) {
        return NULL;
    }
    //  alocarea tabului implicit 
    brow->current = CreateTab_0(pag_0);
    //  alocare lista
    brow->list_2_inl = AlocLista();
    //  testare in caz de esec la alocare
    if ( !brow->list_2_inl ) {
        free(brow);
        return NULL;
    }
    //  alocare nod cu tab_0 in lista
    TListTab nod = AlocNodLista(brow->current, brow->list_2_inl);
    //  testare in caz de esec la alocare
    if ( !nod ) {
        ElibLista(&brow->list_2_inl);
        free(brow);
        return NULL;
    }
    //  legarea noului nod de lista
    nod->urm = brow->list_2_inl;
    nod->pre = brow->list_2_inl->pre;
    brow->list_2_inl->pre->urm = nod;
    brow->list_2_inl->pre = nod;
    return brow;
}
 
//  alte functii ajutatoare
int ALocNodStiva(TStiva *stiva, TPage *pag) {
    //  alocare nod nou
    TStiva nod = (TStiva)malloc(sizeof(TCelulaStiva));
    //  testare in caz de esec la alocare
    if ( !nod ) {
        return 0;
    }
    //  punerea in stiva a nodului
    nod->info = pag;
    nod->urm = (*stiva);
    (*stiva) = nod;
    return 1;
}

int ExtragNodStiva(TStiva *stiva, TPage **pag) {
    //  testare in caz ca stiva e goala
    if ( !(*stiva) ) {
        return 0;
    }
    //  extragerea nodului din varful stivei
    (*pag) = (*stiva)->info;
    TStiva nod = (*stiva);
    (*stiva) = nod->urm;
    free(nod);
    nod = NULL;
    return 1;
}

void AfisStivaInv(TStiva stiva, FILE *out_file) {
    //  verificare dacă s-a ajuns la final
    if ( !stiva ) {
        return;
    }
    AfisStivaInv(stiva->urm, out_file);
    //  afisare informatie din nod
    fprintf(out_file, "%s\n", stiva->info->url);
}

// eliberari de memorie

void ElibStiva(TStiva *stiva) {
    //  verificare in caz ca stiva e deja goala
    if ( !(*stiva) ) {
        return;
    }
    TStiva nod;
    //  distrugerea celulelor din stiva
    while( (*stiva) ) {
        nod = (*stiva);
        (*stiva) = (*stiva)->urm;
        free(nod);
        nod = NULL;
    }
    (*stiva) = NULL;
}

void ElibLista(TListTab *lista) {
    //  verificare in caz ca lista e deja goala
    if ( !(*lista) ) {
        return;
    }
    TListTab nod = (*lista)->urm;
    TListTab aux = NULL;
    //  distrugerea nodurilor din lista
    while ( nod != (*lista) ) {
        aux = nod;
        nod = nod->urm;
        if ( aux->info ) {
            ElibTab(&aux->info);
        }
        free(aux);
        aux = NULL;
    }
    //  eliberarea santinelei
    free(*lista);
    (*lista) = NULL;
}

void ElibPag(TPage **pag) {
    //  asigurare sa existe pagina
    if ( !(*pag) ) {
        return;
    }
    //  eliberarea tuturor campurilor alocate dinamic
    if ( (*pag)->description ) {
        free((*pag)->description);
        (*pag)->description = NULL;
    }
    free(*pag);
    (*pag) = NULL;
}

void ElibTab(TTab **tab) {
    //  asigurare sa existe tabul
    if ( !(*tab) ) {
        return;
    }
    //  eliberarea tuturor campurilor alocate dinamic
    if ( (*tab)->backwardStack ) {
        ElibStiva(&(*tab)->backwardStack);
        (*tab)->backwardStack = NULL;
    }
    if ( (*tab)->forwardStack ) {
        ElibStiva(&(*tab)->forwardStack);
        (*tab)->forwardStack = NULL;
    }
    free(*tab);
    (*tab) = NULL;
}

void ElibBrow(TBrow **brow) {
     //  asigurare sa existe browserul
    if ( !(*brow) ) {
        return;
    }
    //  eliberarea tuturor campurilor alocate dinamic
    if ( (*brow)->list_2_inl ) {
        ElibLista(&(*brow)->list_2_inl);
        (*brow)->list_2_inl = NULL;
    }
    free(*brow);
    (*brow) = NULL;
}

//  functiile care rezolva task-urile
void NEW_TAB(TBrow *brow, int *tab_id_curr, TPage *pag_0) {
    //  actualizarea id-ului pentru noul tab
    (*tab_id_curr)++;
    //  creare tab
    TPage *pag_curr = pag_0;
    int nou_tab_id = (*tab_id_curr);
    TTab *tab = AlocTab(nou_tab_id, pag_curr);
    //  testare in caz de esec la alocare
    if ( !tab ) {
        return;
    }
    TListTab nod = AlocNodLista(tab, brow->list_2_inl);
    //  testare in caz de esec la alocare
    if ( !nod ) {
        ElibTab(&tab);
        return;
    }
    //  adaugare tab in lista
    nod->urm = brow->list_2_inl;
    nod->pre = brow->list_2_inl->pre;
    brow->list_2_inl->pre->urm = nod;
    brow->list_2_inl->pre = nod;
    //  actualizarea tabului curent in browser
    brow->current = tab;
}

void PRINT(TBrow *brow, FILE *out_file) {
    //  afisarea id-ului tabului curent din browser
    fprintf(out_file, "%d", brow->current->id);
    TListTab lista = brow->list_2_inl->urm;
    //  verificare daca lista contine doar tabul implicit
    if ( lista->pre != lista->urm ) {
        //  determinarea unui pointer la tabul curent corespunzator in lista
        while ( lista->info->id != brow->current->id ) {
            lista = lista->urm;
        }
        lista = lista->urm;
        //  verificare sa nu fi ajuns lista la santinela
        if ( lista == brow->list_2_inl ) {
            lista = lista->urm;
        }
        //  afisarea id-urilor corespunzatoare celorlalte taburi
        while ( lista->info->id != brow->current->id ) {
            fprintf(out_file, " %d", lista->info->id);
            //  cand lista ajunge la santinela sare peste ea
            if ( lista->urm == brow->list_2_inl ) {
                lista = lista->urm;
            }
            lista = lista->urm;
        }
        lista = lista->pre;
        //  cand lista ajunge la santinela sare peste ea
        if ( lista == brow->list_2_inl ) {
            lista = lista->urm;
        }
    }
    //  afisarea descrierii paginii curente din tabul curent
    fprintf(out_file, "\n%s\n", brow->current->currentPage->description);
}

void CLOSE(TBrow *brow, FILE *out_file) {
    //  parcurgere lista si identificarea tabului curent
    TListTab lista = brow->list_2_inl->urm;
    while ( lista != brow->list_2_inl ) {
        if ( lista->info == brow->current ) {
            break;
        }
        lista = lista->urm;
    }
    //  verificare daca tabul este cel initial
    if ( lista->info->id == 0 ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  refacerea legaturilor
    brow->current = lista->pre->info;
    lista->pre->urm = lista->urm;
    lista->urm->pre = lista->pre;
    //  eliberarea memoriei
    ElibTab(&lista->info);
    free(lista);
}

void OPEN(TBrow *brow, char *id, FILE *out_file) {
    //  transformarea id-ului din char in int
    int id_cautat = atoi(id);
    //  cautarea tabului cu id-ul cerut
    TTab *tab_cautat = NULL;
    TListTab lista = brow->list_2_inl->urm;
    while ( lista != brow->list_2_inl ) {   
        if ( lista->info->id == id_cautat ) {
            tab_cautat = lista->info;
        }
        lista = lista->urm;
    }
    //  verificarea existentei tabului
    if ( !tab_cautat ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  actualizarea tabului curent in browser
    brow->current = tab_cautat;
}

void NEXT(TBrow *brow) {
    TListTab lista = brow->list_2_inl->urm;
    //  cautarea tabului cu id-ul curent in lista
    while ( lista->info->id != brow->current->id ) {
        lista = lista->urm;
    }
    //  trecerea la urmatorul tab si verificare in caz ca e santinela
    lista = lista->urm;
    if ( lista == brow->list_2_inl ) {
        lista = lista->urm;   
    }
    //  actualizarea tabului curent
    brow->current = lista->info;
}

void PREV(TBrow *brow) {
    TListTab lista = brow->list_2_inl->urm;
    //  cautarea tabului cu id-ul curent in lista
    while ( lista->info->id != brow->current->id ) {
        lista = lista->urm;
    }
    //  trecerea la tabul anterior si verificare in caz ca e santinela
    lista = lista->pre;
    if ( lista == brow->list_2_inl ) {
        lista = lista->pre;   
    }
    //  actualizarea tabului curent
    brow->current = lista->info;
}

void PAGE(TBrow *brow, char *id, TPage **pag, int nr_pag, FILE *out_file) {
    //  verificare daca exista pagini citite
    if ( nr_pag == 1 || !pag ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  convertirea id-ului din char in int
    int id_pag = atoi(id);
    int pag_caut = 0;
    int idx_pag_cautat;
    //  cautarea paginii cu id-ul din comanda in vectorul de pagini
    for ( int i = 0; i < nr_pag; i++ ) {
        if ( pag[i]->id == id_pag ) {
            pag_caut = 1;
            idx_pag_cautat = i;
        }
    }
    //  afisarea mesajului de eroare pentru negasirea id-ului
    if ( !pag_caut ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  adaugarea paginii curente in stiva backward
    if ( !ALocNodStiva(&brow->current->backwardStack, brow->current->currentPage) ) {
        return;
    }
    //  stergerea continutului stivei Forward
    ElibStiva(&brow->current->forwardStack);
    //  deschiderea paginii cu noul id
    brow->current->currentPage = pag[idx_pag_cautat];
}

void PRINT_HISTORY(TBrow *brow, FILE *out_file, char *id) {
    //  convertire id-ului din char in int
    int id_cautat = atoi(id);
    //  cautarea tabului in lista
    TTab *tab_cautat = NULL;
    TListTab lista = brow->list_2_inl->urm;
    while ( lista != brow->list_2_inl ) {
        if ( lista->info->id == id_cautat ) {
            tab_cautat = lista->info;
        }
        lista = lista->urm;
    }
    //  afisare mesaj de eroare
    if ( !tab_cautat ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  afisarea url-urilor din stiva Forward
    TStiva stiva = tab_cautat->forwardStack;
    AfisStivaInv(stiva, out_file);
    //  afisarea url-ului din pagina curenta a tabului curent
    fprintf(out_file, "%s\n", tab_cautat->currentPage->url);
    //  afisarea url-urilor din stiva Backward
    stiva = tab_cautat->backwardStack;
    while ( stiva != NULL ) {
        fprintf(out_file, "%s\n", stiva->info->url);
        stiva = stiva->urm;
    }
}

void BACKWARD(TBrow *brow, FILE *out_file) {
    //  verificarea stivei Backward
    if ( !brow->current->backwardStack ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  adaugarea paginii curente in stiva Forward
    if ( !ALocNodStiva(&brow->current->forwardStack, brow->current->currentPage) ) {
        return;
    }
    //  accesarea ultimei pagini dn stiva Backward
    TPage *pag_ant = NULL;
    if ( !ExtragNodStiva(&brow->current->backwardStack, &pag_ant) ) {
        return;
    }
    //  actualizarea paginii curente din tabul curent
    brow->current->currentPage = pag_ant;
}

void FORWARD(TBrow *brow, FILE *out_file) {
    //  verificarea stivei Forward
    if ( !brow->current->forwardStack ) {
        fprintf(out_file, "403 Forbidden\n");
        return;
    }
    //  adaugarea paginii curente in stiva Backward
    if ( !ALocNodStiva(&brow->current->backwardStack, brow->current->currentPage) ) {
        return;
    }
    //  accesarea ultimei pagini dn stiva Forward
    TPage *pag_urm = NULL;
    if ( !ExtragNodStiva(&brow->current->forwardStack, &pag_urm) ) {
        return;
    }
    //  actualizarea paginii curente din tabul curent
    brow->current->currentPage = pag_urm;
}
