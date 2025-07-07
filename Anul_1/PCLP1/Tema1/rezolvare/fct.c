#include "fct.h"


int aloc_dinamic(int **matrice, int N, int M) {
    if ( !matrice ) {
        free(matrice);
        printf("eroare la alocare");
        return -1;
    }
    for (int i = 0; i < N; i++) {
        matrice[i] = (int *)malloc(M * sizeof(int));
        if ( !matrice[i] ) {
            for ( int j = 0; j < N; j++ ) {
                free(matrice[j]);
            }
            free(matrice);
            printf("eroare la alocare");
            return -1;
        }
    }
    return 0;
}


void free_mem(int **matrice, int N) {
    // if ( matrice != NULL ) {
        for ( int i = 0; i < N; i++ ) {
            // if ( matrice[i] != NULL ) {
                free(matrice[i]);
               // matrice[i] = NULL;
            // }
        }
    // }
    free(matrice);
    // matrice = NULL;
}


void copy_mat(int **mat_paste, int **mat_cpy, int N, int M) {
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            mat_paste[i][j] = mat_cpy[i][j];
        }
    }
}


void rotire_col(int ** matrice, int nr_poz, int col, int N) {
    for ( int i = 0; i < nr_poz; i++ ) {
        int aux = matrice[N - 1][col];
        for ( int j = N - 1; j >= 1; j-- ) {
            matrice[j][col] = matrice[j - 1][col];
        }
        matrice[0][col] = aux;
    }
}


int calc_win(int **matrice, int N, int M) {
    if ( M < 3 ) {
        return 0;
    }
    int count_win = 0;
    // calcularea de linii castigatoare
    for ( int i = 0; i < 3; i++ ) {
        int j = 0;
        int maxim = -1;
        while ( j < M ) {
            int count_lin = 1;
            int val = matrice[i][j];
            j++;
            while ( j < M && matrice[i][j] == val ) {
                j++;
                count_lin++;
            }
            if ( count_lin > maxim ) {
                maxim = count_lin;
            }
        }
        if ( maxim >= 3 ) {
            count_win++;
        }
    }
    // calculare de diagonale oblice la dreapta + "X"-uri
    for ( int j = 0; j < M - 2; j++ ) {
        int a = matrice[1][j + 1];
        if ( a == matrice[0][j] && a == matrice[2][j + 2] && a >= 0 ) {
            if ( a == matrice[0][j + 2] && matrice[2][j] == a ) {
                // if ( matrice[0][j] >= 0 ) {
                matrice[1][j + 1] = matrice[2][j] = -1;
            }
            count_win++;
        }
    }
    // calculare scor pe diagonale oblice la stanga
    for ( int j = M - 1; j >= 2; j-- ) {
        int a = matrice[0][j];
        if ( a == matrice[1][j - 1] && a == matrice[2][j - 2] ) {
            count_win++;
            matrice[1][j - 1] = matrice[2][j - 2] = -1;
        }
    }
    return count_win;
}


int calc_scor(int **matrice, int M) {
    if ( M < 3 ) {
        return 0;
    }
    int scor = 0;
    int **matr_aux = (int **)malloc(3 * sizeof(int *));
    aloc_dinamic(matr_aux, 3, M);
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            matr_aux[i][j] = matrice[i][j];
        }
    }
    // calculare scor pe linii
    for ( int i = 0; i < 3; i++ ) {
        int p, maxim = -1;
        int j = 0;
        while ( j < M ) {
            int count_lin = 1;
            int val = matrice[i][j];
            int poz = j;
            j++;
            while ( j < M && matrice[i][j] == val ) {
                j++;
                count_lin++;
            }
            if ( count_lin > maxim ) {
                maxim = count_lin;
                p = poz;
            }
        }
        if ( maxim >= 3 ) {
            if ( matrice[i][p] == 7 ) {
                scor += 2 * maxim;
            } else {
                scor += maxim;
            }
        }
    }
    // calculare scor pe diagonale oblice la dreapta + verifivare "X"-uri
    for ( int j = 0; j < M - 2; j++ ) {
        int a = matrice[1][j + 1];
        if ( a == matrice[0][j] && a == matrice[2][j + 2] && a >= 0 ) {
            if ( a == matrice[0][j + 2] && matrice[2][j] == a ) {
                matrice[1][j + 1] = matrice[2][j] = -1;
                if ( matrice[0][j] == 7 ) {
                    scor += 42;
                } else {
                    scor += 21;
                }
            } else {
                if ( matrice[0][j] == 7 ) {
                    scor += 14;
                } else {
                    scor += 7;
                }
            }
        }
    }
    // calculare scor pe diagonale oblice la stanga
    for ( int j = M - 1; j >= 2; j-- ) {
        int a = matrice[0][j];
        if ( a == matrice[1][j - 1] && a == matrice[2][j - 2] ) {
            if ( matrice[0][j] == 7 ) {
                scor += 14;
            } else {
                scor += 7;
            }
        }
    }
    // determinarea numarului de valori distincte din cadran
    int *frecv =(int *)malloc(11 * sizeof(int));
    if ( !frecv ) {
        // free(frecv);
        printf("vectorul de frecventa nu a fost alocat");
        return -1;
    }
    for ( int i = 0; i < 10; i++ ) {
        frecv[i] = 0;
    }
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            if ( matr_aux[i][j] >= 0 && matr_aux[i][j] <= 9 ) {
                frecv[matr_aux[i][j]]++;
            }
        }
    }
    int count_val_dist = 0;
    for ( int i = 0; i < 10; i++ ) {
        if ( frecv[i] > 0 ) {
            count_val_dist++;
        }
    }
    int count = 0;
    if ( count_val_dist <= 4 ) {
        scor += 15;
        count++;
    } else if ( count_val_dist <= 2 ) {
        scor += 100;
    }
    free(frecv);
    free_mem(matr_aux, 3);
    // frecv = NULL;
    return scor;
}
