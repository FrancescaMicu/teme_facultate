#include "task2.h"
#include "fct_aux_task2.h"

int main(int argc, char *argv[]) {
    int nr_comand = 0;
    scanf("%d", &nr_comand);
    secretariat *date_sec = NULL;
    date_sec = citeste_secretariat(argv[argc - 1]);
    char *comanda = (char*)malloc(SIZE_DATE * sizeof(char));
    if ( !comanda ) {
        printf("Eroare la alocare");
        return -1;  //  aveam eroare cu NULL
    }
    fgets(comanda, SIZE_DATE, stdin);
    for ( int i = 0; i < nr_comand; i++ ) {
        fgets(comanda, SIZE_DATE, stdin);
        comanda[strcspn(comanda, "\n")] = '\0';  //  șterge newline
        int count_camp = 1;
        int nr_caract = (int)strlen(comanda);
        for ( int i = 0; i < nr_caract; i++ ) {
            if ( comanda[i] == ',' ) {
                count_camp++;
            }
        }
        char *cuv = strtok(comanda, ", ");
        // SELECT
        if ( strcmp(cuv, "SELECT") == 0 ) {
            char **campuri = (char **)malloc(count_camp * sizeof(char*));
            if ( !campuri ) {
                printf("Eraoare la alocare");
                return -1;
            }
            for ( int i = 0; i < count_camp; i++ ) {
                campuri[i] = strtok(NULL, ", ");
            }
            char *tabel = strtok(NULL, ", ");
            tabel = strtok(NULL, ", ");
            cuv = strtok(NULL, " ");
            if ( !cuv ) {
                if ( tabel[strlen(tabel) - 1] == ';' ) {
                    tabel[strlen(tabel) - 1] = '\0';
                }
                interog_simpla(date_sec, campuri, tabel, count_camp);
            } else {  //  FILTRARE SIMPLA
                char *camp1 = strtok(NULL, ", ");
                char *operator1 = strtok(NULL, ", ");
                char *valoare1 = strtok(NULL, ", ");
                cuv = strtok(NULL, ", ");
                if ( !cuv ) {
                    if ( valoare1[strlen(valoare1) - 1] == ';' ) {
                       valoare1[strlen(valoare1) - 1] = '\0';
                    }
                    interog_filtr_simplu(date_sec, campuri, tabel, camp1, operator1, valoare1, count_camp);
                } else {  //  FILTRARE COMPLEXA
                    char *camp2 = strtok(NULL, ", ");
                    char *operator2 = strtok(NULL, ", ");
                    char *valoare2 = strtok(NULL, ", ");
                    if ( valoare2[strlen(valoare2) - 1] == ';' ) {
                       valoare2[strlen(valoare2) - 1] = '\0';
                    }
                    interog_filtr_compl(date_sec, campuri, tabel, camp1, operator1,
                        valoare1, camp2, operator2, valoare2, count_camp);
                }
            }
            free(campuri);
        // UPDATE
        } else if ( strcmp(cuv, "UPDATE") == 0 ) {
            char *tabel = strtok(NULL, ", ");
            cuv = strtok(NULL, ", ");
            char *camp = strtok(NULL, ", ");
            // printf("%s \n", camp);
            if ( strcmp(camp, "note") == 0 ) {
                date_sec = update_note(date_sec, camp, cuv);
                // printf("%s \n", camp);
            } else {
                cuv = strtok(NULL, ", ");
                char *valoare = '\0';
                if ( strcmp(camp, "nume") == 0 || strcmp(camp, "nume_titular") == 0 ) {
                    char *nume = strtok(NULL, ", ");
                    int nr_car_num = (int)strlen(nume);
                    for ( int i = 0; i < nr_car_num - 1; i++ ) {
                        nume[i] = nume[i + 1];
                    }
                    nume[nr_car_num - 1] = '\0';
                    char *prenume = strtok(NULL, ", ");
                    prenume[strlen(prenume) - 1] = '\0';
                    char nume_complet[MAX_STUDENT_NAME];
                    snprintf(nume_complet, MAX_STUDENT_NAME, "%s %s", nume, prenume);
                    valoare = nume_complet;
                } else {
                    valoare = strtok(NULL, ", ");
                }
                cuv = strtok(NULL, ", ");
                char *camp_cond1 = strtok(NULL, ", ");
                char *operator_cond1 = strtok(NULL, ", ");
                char *valoare_cond1 = strtok(NULL, ", ");
                cuv = strtok(NULL, ", ");
                if ( !cuv ) {  //  FILTRARE SIMPLA
                    if ( valoare_cond1[strlen(valoare_cond1) - 1] == ';' ) {
                        valoare_cond1[strlen(valoare_cond1) - 1] = '\0';
                    }
                    update_filtr_simplu(date_sec, tabel, camp, valoare, camp_cond1, operator_cond1, valoare_cond1);
                } else {
                    char *camp_cond2 = strtok(NULL, ", ");
                    char *operator_cond2 = strtok(NULL, ", ");
                    char *valoare_cond2 = strtok(NULL, ", ");
                    if ( valoare_cond2[strlen(valoare_cond2) - 1] == ';' ) {
                        valoare_cond2[strlen(valoare_cond2) - 1] = '\0';
                    }
                    update_filtr_compl(date_sec, tabel, camp, valoare, camp_cond1, operator_cond1, valoare_cond1,
                                   camp_cond2, operator_cond2, valoare_cond2);
                }
            }
        } else if ( strcmp(cuv, "DELETE") == 0 ) {
            cuv = strtok(NULL, ", ");
            char *tabel = strtok(NULL, ", ");
            cuv = strtok(NULL, ", ");
            char *camp_cond1 = strtok(NULL, ", ");
            char *operator_cond1 = strtok(NULL, ", ");
            char *valoare_cond1 = strtok(NULL, ", ");
            cuv = strtok(NULL, ", ");
            if ( !cuv ) {
                if ( valoare_cond1[strlen(valoare_cond1) - 1] == ';' ) {
                    valoare_cond1[strlen(valoare_cond1) - 1] = '\0';
                }
                delete_filtr_simplu(date_sec, tabel, camp_cond1, operator_cond1, valoare_cond1);
            } else {
                char *camp_cond2 = strtok(NULL, ", ");
                char *operator_cond2 = strtok(NULL, ", ");
                char *valoare_cond2 = strtok(NULL, ", ");
                if ( valoare_cond2[strlen(valoare_cond2) - 1] == ';' ) {
                    valoare_cond2[strlen(valoare_cond2) - 1] = '\0';
                }
                delete_filtr_compl(date_sec, tabel, camp_cond1, operator_cond1,
                    valoare_cond1, camp_cond2, operator_cond2, valoare_cond2);
            }
        }
    }
    free(date_sec->studenti);
    for ( int i = 0; i < date_sec->nr_materii; i++ ) {
        free(date_sec->materii[i].nume);
        free(date_sec->materii[i].nume_titular);
    }
    free(date_sec->materii);
    free(date_sec->inrolari);
    free(date_sec);
    date_sec = NULL;
    free(comanda);
    return 0;
}
