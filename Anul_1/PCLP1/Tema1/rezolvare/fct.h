#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int aloc_dinamic(int **matrice, int N, int M);

void free_mem(int **matrice, int N);

void copy_mat(int **mat_paste, int **mat_cpy, int N, int M);

void rotire_col(int ** matrice, int nr_poz, int col, int N);

int calc_win(int **matrice, int N, int M);

int calc_scor(int **matrice, int M);
