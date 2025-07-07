#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "task1.h"

secretariat *citeste_secretariat(const char *nume_fisier) {
    secretariat *date_sec = (secretariat*)malloc(sizeof(secretariat));
    FILE *file = fopen(nume_fisier, "rt");
    if ( !file ) {
        printf("Eroare la deschiderea fisierului");
        return NULL;
    }
    char *date = (char*)malloc(SIZE_DATE *sizeof(char));
    fgets(date, SIZE_DATE, file);
    int nr_stud = 0;
    date_sec->studenti = malloc(MAX_OF_THEM_ALL * sizeof(student));
    while ( strcmp(fgets(date, SIZE_DATE, file), "[MATERII]\n") != 0 ) {
        char *id = strtok(date, ", ");
        char *nume = strtok(NULL, ", ");
        char *prenume = strtok(NULL, ", ");
        char *an_stud = strtok(NULL, ", ");
        char *statut = strtok(NULL, ", ");
        char nume_complet[MAX_STUDENT_NAME];
        snprintf(nume_complet, MAX_STUDENT_NAME, "%s %s", nume, prenume);
        date_sec->studenti[nr_stud].id = atoi(id);
        memcpy(date_sec->studenti[nr_stud].nume, nume_complet, MAX_STUDENT_NAME);
        date_sec->studenti[nr_stud].an_studiu = atoi(an_stud);
        date_sec->studenti[nr_stud].statut = (statut[0]);
        date_sec->studenti[nr_stud++].medie_generala = 0;
    }
    date_sec->nr_studenti = nr_stud;
    int nr_mat = 0;
    date_sec->materii = malloc(MAX_OF_THEM_ALL * sizeof(materie));
    while ( strcmp(fgets(date, SIZE_DATE, file), "[INROLARI]\n") != 0 ) {
        char *id = strtok(date, ", ");
        char *nume_mat = strtok(NULL, ", ");
        char *nume_tit = strtok(NULL, ", ");
        char *pren_tit = strtok(NULL, ", ");
        char nume_complet[MAX_STUDENT_NAME];
        snprintf(nume_complet, MAX_STUDENT_NAME, "%s %s", nume_tit, pren_tit);
        date_sec->materii[nr_mat].id = atoi(id);
        date_sec->materii[nr_mat].nume = strdup(nume_mat);
        date_sec->materii[nr_mat].nume_titular = strdup(nume_complet);
        date_sec->materii[nr_mat].nume_titular[strlen(date_sec->materii[nr_mat].nume_titular) - 1] = '\0';
        nr_mat++;
    }
    date_sec->nr_materii = nr_mat;
    int nr_inrol = 0;
    date_sec->inrolari = malloc(MAX_OF_THEM_ALL * sizeof(inrolare));
    while ( fgets(date, SIZE_DATE, file) ) {
        char *id_stud = strtok(date, ", ");
        char * id_mat = strtok(NULL, ", ");
        char *nota_1 = strtok(NULL, ", ");
        char *nota_2 = strtok(NULL, ", ");
        char *nota_3 = strtok(NULL, ", ");
        date_sec->inrolari[nr_inrol].id_student = atoi(id_stud);
        date_sec->inrolari[nr_inrol].id_materie = atoi(id_mat);
        date_sec->inrolari[nr_inrol].note[0] = (float)atof(nota_1);
        date_sec->inrolari[nr_inrol].note[1] = (float)atof(nota_2);
        date_sec->inrolari[nr_inrol].note[2] = (float)atof(nota_3);
        float suma = (float)((float)atof(nota_1) + (float)atof(nota_2) + (float)atof(nota_3));
        for ( int i = 0; i < date_sec->nr_studenti; i++ ) {
            if ( date_sec->studenti[i].id == date_sec->inrolari[nr_inrol].id_student ) {
                date_sec->studenti[i].medie_generala += suma;
            }
        }
        nr_inrol++;
    }
    date_sec->nr_inrolari = nr_inrol;
    for ( int i = 0; i < date_sec->nr_studenti; i++ ) {
        int count_materii = 0;
        for ( int j = 0; j < date_sec->nr_inrolari; j++ ) {
            if ( date_sec->studenti[i].id == date_sec->inrolari[j].id_student ) {
                count_materii++;
            }
        }
        float medie = (float)date_sec->studenti[i].medie_generala / (float)count_materii;
        int val_aprox = (int)(medie * FLOAT_to_INT);
        if ( val_aprox % ULT_CIFRA >= 4 ) {  //  marja de eroare
            val_aprox++;
            medie = (float)(val_aprox) / FLOAT_to_INT;
        }
        date_sec->studenti[i].medie_generala = medie;
        if ( count_materii == 0 ) {
            date_sec->studenti[i].medie_generala = 0;
        }
    }
    fclose(file);
    free(date);
    return date_sec;
    // return NULL;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    int i = s->nr_studenti;
    s->nr_studenti++;
    s->studenti[i].id = id;
    // strcpy(s->studenti[i].nume, nume);
    memcpy(s->studenti[i].nume, nume, MAX_STUDENT_NAME);
    s->studenti[i].an_studiu = an_studiu;
    s->studenti[i].statut = statut;
    s->studenti[i].medie_generala = medie_generala;
}

void elibereaza_secretariat(secretariat **s) {
    free((*s)->studenti);
    for ( int i = 0; i < (*s)->nr_materii; i++ ) {
        free((*s)->materii[i].nume);
        free((*s)->materii[i].nume_titular);
    }
    free((*s)->materii);
    free((*s)->inrolari);
    free((*s));
    (*s) = NULL;
}
