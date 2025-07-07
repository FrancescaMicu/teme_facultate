#include "fct.h"
#define MAX 10000
#define MIN -1

int main() {
    // citesc task
    int nr_task = 0;
    scanf("%d", &nr_task);
    int N = 0, M = 0;
    scanf("%d %d", &N, &M);

    // alocare si citire matrice
    int **matrice = (int **)malloc(N * sizeof(int *));
    aloc_dinamic(matrice, N, M);
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            scanf("%d", &matrice[i][j]);
        }
    }

    // rezolvare task-uri
    if ( nr_task == 1 ) {
        int col = 0, nr_poz = 0;
        scanf("%d %d", &col, &nr_poz);
        rotire_col(matrice, nr_poz, col, N);
        for ( int i = 0; i < N; i++ ) {
            for ( int j = 0; j < M; j++ ) {
                printf("%d ", matrice[i][j]);
            }
            printf("\n");
        }
    } else if ( nr_task == 2 ) {
        int **matr_calc_scor = (int **)malloc(4 * sizeof(int *));
        aloc_dinamic(matr_calc_scor, 3, M);
        copy_mat(matr_calc_scor, matrice, 3, M);
        printf("%d\n", calc_win(matr_calc_scor, 3, M));
        printf("%d\n", calc_scor(matrice, M));
        free_mem(matr_calc_scor, 3);
    } else if ( nr_task == 3 ) {
        int T = 0, col, rot = 0;
        int **mat_rot = (int **)malloc(4 * sizeof(int *));
        aloc_dinamic(mat_rot, 3, M);
        scanf("%d", &T);
        int score_of_all = 0;
        for ( int k = 0; k < T; k++ ) {
            scanf("%d %d", &col, &rot);
            rotire_col(matrice, rot, col, N);
            copy_mat(mat_rot, matrice, 3, M);
            score_of_all += calc_scor(mat_rot, M);
            // printf("%d\n", calc_scor(mat_rot, N, M));
        }
        printf("%d\n", score_of_all);
        free_mem(mat_rot, 3);
    } else if ( nr_task == 4 ) {
        int **mat_verif = (int **)malloc(4 * sizeof(int *));
        aloc_dinamic(mat_verif, 3, M);
        int scor_maxim = MIN;
        for ( int i = 0; i < 3; i++ ) {
            for ( int j = 0; j < M; j++ ) {
                for ( int val = 0; val < 10; val++ ) {
                    copy_mat(mat_verif, matrice, 3, M);
                    mat_verif[i][j] = val;
                    int scor_verif = calc_scor(mat_verif, M);
                    if ( scor_verif > scor_maxim ) {
                        scor_maxim = scor_verif;
                    }
                }
            }
        }
        printf("%d\n", scor_maxim);
        free_mem(mat_verif, 3);
    } else if ( nr_task == 5 ) {
        int **mat_dublu_rot = (int **)malloc(N * sizeof(int *));
        aloc_dinamic(mat_dublu_rot, N, M);
        int scor_maxim = MIN;
        for ( int rot_col_1 = 0; rot_col_1 < M - 1; rot_col_1++ ) {
            for ( int rot_col_2 = 0; rot_col_2 < M; rot_col_2++ ) {
                for ( int nr_rot1 = 1; nr_rot1 < N; nr_rot1++ ) {
                    for ( int nr_rot2 = 1; nr_rot2 < N; nr_rot2++ ) {
                        copy_mat(mat_dublu_rot, matrice, N, M);
                        rotire_col(mat_dublu_rot, nr_rot1, rot_col_1, N);
                        rotire_col(mat_dublu_rot, nr_rot2, rot_col_2, N);
                        int scor_verif = calc_scor(mat_dublu_rot, M);
                        if ( scor_verif > scor_maxim ) {
                            scor_maxim = scor_verif;
                        }
                    }
                }
            }
        }
        printf("%d\n", scor_maxim);
        free_mem(mat_dublu_rot, N);
    } else if ( nr_task == 6 ) {
        int *dx = (int *)malloc(5 * sizeof(int));
        int *dy = (int *)malloc(5 * sizeof(int));
        if ( !dx ) {
            // free(dx);
            printf("matricea dx nu a fost alocata");
            return -1;
        }
        if ( !dy ) {
            // free(dy);
            printf("matricea dy nu a fost alocata");
            return -1;
        }
        dx[0] = 1; dy[0] = 0;
        dx[1] = 0;  dy[1] = 1;
        dx[2] = 0;  dy[2] = -1;
        dx[3] = -1;  dy[3] = 0;
        int **matr_cost = (int **)malloc(4 * sizeof(int *));
        aloc_dinamic(matr_cost, 3, M);
        for ( int i = 0; i < 3; i++ ) {
            for ( int j = 0; j < M; j++ ) {
                matr_cost[i][j] = MAX;
            }
        }
        matr_cost[0][0] = 0;
        for ( int i = 0; i < 3; i++ ) {
            for ( int j = 0; j < M; j++ ) {
                for ( int d = 0; d < 4; d++ ) {
                    int lin_nou = dx[d] + i;
                    int col_nou = dy[d] + j;
                    if ( lin_nou >= 0 && lin_nou < 3 ) {
                        if ( col_nou >= 0 && col_nou < M ) {
                            int a = matrice[0][0];
                            int cost = abs(matrice[lin_nou][col_nou] - a);
                            int new_cost = matr_cost[i][j] + cost;
                            if ( new_cost < matr_cost[lin_nou][col_nou] ) {
                                matr_cost[lin_nou][col_nou] = new_cost;
                            }
                        }
                    }
                }
            }
        }
        /*for(int i = 0; i < 3; i++) {
            for(int j = 0; j < M; j++) {
                printf("%d ", matr_cost[i][j]);
            }
            printf("\n");
        }*/
        printf("%d\n", matr_cost[2][M - 1]);
        free_mem(matr_cost, 3);
        free(dx);
        // dx = NULL;
        free(dy);
        // dy = NULL;
    }
    free_mem(matrice, N);
    return 0;
}
