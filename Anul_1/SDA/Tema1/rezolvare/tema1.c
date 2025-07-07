/* MICU Francesca-Maria - 313CB */

#include "structuri.h"

int main() {
    //  deschidere fisiere
    FILE *inp_file = fopen("tema1.in", "rt");
    //  afisare mesaj de eroare
    if ( !inp_file ) {
        printf("Eroare la deschiderea fisierului de input");
        return FAIL;
    }
    FILE *out_file = fopen("tema1.out","wt");
    //  afisare mesaj de eroare
    if ( !out_file ) {
        printf("Eroare la deschiderea fisierului de output");
        return FAIL;
    }
    int nr_pag;
    fscanf(inp_file, "%d\n", &nr_pag);
    //  tin cont si de pagina implicita
    nr_pag++;
    //  declarare si alocare vector de pagini
    TPage **pag = (TPage**)malloc(nr_pag * sizeof(TPage*));
    //  afisare mesaj de eroare alocare
    if ( !pag ) {
        printf("Eroare la alocare");
        return FAIL;
    }
    //  alocarea paginii implicite
    pag[0] = CreatePag_0();
    //  afisare mesaj de eroare la alocare
    if ( !pag[0] ) {
        free(pag);
        printf("Eroare la alocare");
        return FAIL;
    }
    //  verificare dacă sunt pagini de citit din fisier
    if ( nr_pag != 1 ) {
        int id;
        char url[MAX_LEN], descr[MAX_LEN];
        //  citirea din fisier a paginilor, alocarea lor si introducerea in vectorul de pagini
        for ( int i = 1; i < nr_pag; i++ ) {
            fscanf(inp_file, "%d\n", &id);
            fgets(url, MAX_LEN, inp_file);
            //  pune NULL in loc de newline
            url[strcspn(url, "\n")] = '\0';
            fgets(descr, MAX_LEN, inp_file);
            //  pune NULL in loc de newline
            descr[strcspn(descr, "\n")] = '\0';
            pag[i] = AlocPag(id, url, descr);
            //  afisare mesaj de eroare la alocare
            if ( !pag[i] ) {
                for ( int j = 0; j < i; j++ ) {
                    if ( pag[j] ) {
                        ElibPag(&pag[j]);
                    }
                }
                free(pag);
                printf("Eroare la alocare");
                return FAIL;
            }
        }
    }
    //  alocare browser
    TBrow *brow = AlocBrowser(pag[0]);
    //  afisare mesaj de eroare la alocare
    if ( !brow ) {
        for ( int i = 0; i < nr_pag; i++ ) {
            if ( pag[i] ) {
                ElibPag(&pag[i]);
            }
        }
        free(pag);
        printf("Eroare la alocare");
        return FAIL;
    }
    //  crearea variabilei care retine id-ul ultimului tab deschis
    int tab_id_curr = 0;
    //  citire operatii din fisier
    int nr_oper;
    fscanf(inp_file, "%d", &nr_oper);
    char *oper = (char*)malloc(MAX_LEN * sizeof(char));
    //  afisare mesaj de eroare la alocare
    if ( !oper ) {
        for ( int i = 0; i < nr_pag; i++ ) {
            if ( pag[i] ) {
                ElibPag(&pag[i]);
            }
        }
        free(pag);
        ElibBrow(&brow);
        printf("Eroare la alocare");
        return FAIL;
    }
    //  pentru a scapa de linia goala ramasa dupa fscanf
    fgets(oper, MAX_LEN, inp_file);
    for ( int i = 0; i < nr_oper; i++ ) {
        fgets(oper, MAX_LEN, inp_file);
        //  pune NULL in loc de newline
        oper[strcspn(oper, "\n")] = '\0';
        if ( strstr(oper, "NEW_TAB") ) {
            NEW_TAB(brow, &tab_id_curr, pag[0]);
        } else if ( strstr(oper, "CLOSE") ) {
            CLOSE(brow, out_file);
        } else if ( strstr(oper, "OPEN ") ) {
            //  obtinerea id-ului din comanda
            char *id = strtok(oper, " ");
            id = strtok(NULL, " ");
            OPEN(brow, id, out_file);
        } else if ( strstr(oper, "NEXT") ) {
            NEXT(brow);
        } else if ( strstr(oper, "PREV") ) {
            PREV(brow);
        } else if ( strstr(oper, "PAGE") ) {
            //  obtinerea id-ului din comanda
            char *id_pag = strtok(oper, " ");
            id_pag = strtok(NULL, " ");
            PAGE(brow, id_pag, pag, nr_pag, out_file);
        } else if ( strstr(oper, "BACKWARD") ) {
            BACKWARD(brow, out_file);
        } else if ( strstr(oper, "FORWARD") ) {
            FORWARD(brow, out_file);
        } else if ( strstr(oper, "PRINT_HISTORY") ) {
            //  obtinerea id-ului din comanda
            char *id = strtok(oper, " ");
            id = strtok(NULL, " ");
            PRINT_HISTORY(brow, out_file, id);
        } else if ( strstr(oper, "PRINT") ) {
            PRINT(brow, out_file);
        }
    }
    //  inchidere fisiere și eliberari de memorie
    fclose(inp_file);
    fclose(out_file);
    free(oper);
    for ( int i = 0; i < nr_pag; i++ ) {
        if ( pag[i] ) {
            ElibPag(&pag[i]);
        }
    }
    free(pag);
    ElibBrow(&brow);
    return 0;
}
