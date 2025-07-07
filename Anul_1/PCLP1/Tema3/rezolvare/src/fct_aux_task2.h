#include "task2.h"

// funcții auxiliare task 2

// verificare condiții pentru filtrare
int conditie_stud(secretariat *s, char *camp, char *operator_cond, char *valoare , int i);
int conditie_mat(secretariat *s, char *camp, char *operator_cond, char *valoare, int i);
int conditie_inrol(secretariat *s, char *camp, char *operator_cond, char *valoare, int i);

// pentru interogări
void interog_simpla(secretariat *s, char **camp, char *tabel, int nr_camp);
void interog_filtr_simplu(secretariat *s, char **camp, char *tabel, char *camp_filtru,
    char *operator_cond, char *valoare, int nr_camp);
void interog_filtr_compl(secretariat *s, char **camp, char *tabel, char *camp_filtru1, char *operator1, char *valoare1,
    char *camp_filtru2, char *operator2, char *valoare2, int nr_camp);

// pentru update
void update_filtr_simplu(secretariat *s, char *tabel, char *camp, char *valoare,
    char *camp_cond, char *operator_cond, char *valoare_cond);
void update_filtr_compl(secretariat *s, char *tabel, char *camp, char *valoare, char *camp_cond1,
    char *operator_cond1, char *valoare_cond1, char *camp_cond2, char *operator_cond2, char *valoare_cond2);
secretariat* update_note(secretariat *s, char *camp, char *cuv);

// calcularea mediei după anumite modificări(update-uri sau ștergeri)
float calc_medie(secretariat *s, int poz_stud);

// pentru ștergere
void delete_filtr_simplu(secretariat *s, char *tabel, char *camp_cond, char *operator_cond, char *valoare_cond);
void delete_filtr_compl(secretariat *s, char *tabel, char *camp_cond1, char *operator_cond1, char *valoare_cond1,
    char *camp_cond2, char *operator_cond2, char *valoare_cond2);
