#include "fct_aux_task2.h"

int conditie_stud(secretariat *s, char *camp, char *operator_cond, char *valoare , int i) {
    if ( strcmp(camp, "id") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->studenti[i].id == atoi(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->studenti[i].id >= atoi(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->studenti[i].id <= atoi(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->studenti[i].id > atoi(valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->studenti[i].id < atoi(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->studenti[i].id != atoi(valoare);
        }
    } else if ( strcmp(camp, "nume") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return strcmp(s->studenti[i].nume, valoare) == 0;
        } else if ( !strcmp(operator_cond, ">=") ) {
            return strcmp(s->studenti[i].nume, valoare) >= 0;
        } else if ( !strcmp(operator_cond, "<=") ) {
            return strcmp(s->studenti[i].nume, valoare) <= 0;
        } else if ( !strcmp(operator_cond, ">") ) {
            return strcmp(s->studenti[i].nume, valoare) > 0;
        } else if ( !strcmp(operator_cond, "<") ) {
            return strcmp(s->studenti[i].nume, valoare) < 0;
        } else if ( !strcmp(operator_cond, "!=") ) {
            return strcmp(s->studenti[i].nume, valoare) != 0;
        }
    } else if ( strcmp(camp, "an_studiu") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->studenti[i].an_studiu == atoi(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->studenti[i].an_studiu >= atoi(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->studenti[i].an_studiu <= atoi(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->studenti[i].an_studiu > atoi(valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->studenti[i].an_studiu < atoi(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->studenti[i].an_studiu != atoi(valoare);
        }
    } else if ( strcmp(camp, "statut") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->studenti[i].statut == (*valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->studenti[i].statut >= (*valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->studenti[i].statut <= (*valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->studenti[i].statut > (*valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->studenti[i].statut < (*valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->studenti[i].statut != (*valoare);
        }
    } else if ( strcmp(camp, "medie_generala") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->studenti[i].medie_generala == (float)atof(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->studenti[i].medie_generala >= (float)atof(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->studenti[i].medie_generala <= (float)atof(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->studenti[i].medie_generala > (float)atof(valoare);;
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->studenti[i].medie_generala < (float)atof(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->studenti[i].medie_generala != (float)atof(valoare);
        }
    }
}

int conditie_mat(secretariat *s, char *camp, char *operator_cond, char *valoare, int i) {
    if ( strcmp(camp, "id") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->materii[i].id == atoi(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->materii[i].id >= atoi(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->materii[i].id <= atoi(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->materii[i].id > atoi(valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->materii[i].id < atoi(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->materii[i].id != atoi(valoare);
        }
    } else if ( strcmp(camp, "nume") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return strcmp(s->materii[i].nume, valoare) == 0;
        } else if ( !strcmp(operator_cond, ">=") ) {
            return strcmp(s->materii[i].nume, valoare) >= 0;
        } else if ( !strcmp(operator_cond, "<=") ) {
            return strcmp(s->materii[i].nume, valoare) <= 0;
        } else if ( !strcmp(operator_cond, ">") ) {
            return strcmp(s->materii[i].nume, valoare) > 0;
        } else if ( !strcmp(operator_cond, "<") ) {
            return strcmp(s->materii[i].nume, valoare) < 0;
        } else if ( !strcmp(operator_cond, "!=") ) {
            return strcmp(s->materii[i].nume, valoare) != 0;
        }
    } else if ( strcmp(camp, "nume_titular") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return strcmp(s->materii[i].nume_titular, valoare) == 0;
        } else if ( !strcmp(operator_cond, ">=") ) {
            return strcmp(s->materii[i].nume_titular, valoare) >= 0;
        } else if ( !strcmp(operator_cond, "<=") ) {
            return strcmp(s->materii[i].nume_titular, valoare) <= 0;
        } else if ( !strcmp(operator_cond, ">") ) {
            return strcmp(s->materii[i].nume_titular, valoare) > 0;
        } else if ( !strcmp(operator_cond, "<") ) {
            return strcmp(s->materii[i].nume_titular, valoare) < 0;
        } else if ( !strcmp(operator_cond, "!=") ) {
            return strcmp(s->materii[i].nume_titular, valoare) != 0;
        }
    }
}

int conditie_inrol(secretariat *s, char *camp, char *operator_cond, char *valoare, int i) {
    if ( strcmp(camp, "id_student") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->inrolari[i].id_student == atoi(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->inrolari[i].id_student >= atoi(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->inrolari[i].id_student <= atoi(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->inrolari[i].id_student > atoi(valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->inrolari[i].id_student < atoi(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->inrolari[i].id_student != atoi(valoare);
        }
    } else if ( strcmp(camp, "id_materie") == 0 ) {
        if ( !strcmp(operator_cond, "=") ) {
            return s->inrolari[i].id_materie == atoi(valoare);
        } else if ( !strcmp(operator_cond, ">=") ) {
            return s->inrolari[i].id_materie >= atoi(valoare);
        } else if ( !strcmp(operator_cond, "<=") ) {
            return s->inrolari[i].id_materie <= atoi(valoare);
        } else if ( !strcmp(operator_cond, ">") ) {
            return s->inrolari[i].id_materie > atoi(valoare);
        } else if ( !strcmp(operator_cond, "<") ) {
            return s->inrolari[i].id_materie < atoi(valoare);
        } else if ( !strcmp(operator_cond, "!=") ) {
            return s->inrolari[i].id_materie != atoi(valoare);
        }
    }
}

void interog_simpla(secretariat *s, char **camp, char *tabel, int nr_camp) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            for ( int j = 0; j < nr_camp; j++ ) {
                if ( strcmp(camp[j], "id") == 0 ) {
                    printf("%d", s->studenti[i].id);
                } else if ( strcmp(camp[j], "nume") == 0 ) {
                    printf("%s", s->studenti[i].nume);
                } else if ( strcmp(camp[j], "an_studiu") == 0 ) {
                    printf("%d", s->studenti[i].an_studiu);
                } else if ( strcmp(camp[j], "statut") == 0 ) {
                    printf("%c", s->studenti[i].statut);
                } else if ( strcmp(camp[j], "medie_generala") == 0 ) {
                    printf("%.2f", s->studenti[i].medie_generala);
                } else if ( strcmp(camp[j], "*") == 0 ) {
                    printf("%d ", s->studenti[i].id);
                    printf("%s ", s->studenti[i].nume);
                    printf("%d ", s->studenti[i].an_studiu);
                    printf("%c ", s->studenti[i].statut);
                    printf("%.2f", s->studenti[i].medie_generala);
                }
                if ( j + 1 < nr_camp ) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            for ( int j = 0; j < nr_camp; j++ ) {
                if ( strcmp(camp[j], "id") == 0 ) {
                    printf("%d", s->materii[i].id);
                } else if ( strcmp(camp[j], "nume") == 0 ) {
                    printf("%s", s->materii[i].nume);
                } else if ( strcmp(camp[j], "nume_titular") == 0 ) {
                    printf("%s", s->materii[i].nume_titular);
                } else if ( strcmp(camp[j], "*") == 0 ) {
                    printf("%d ", s->materii[i].id);
                    printf("%s ", s->materii[i].nume);
                    printf("%s", s->materii[i].nume_titular);
                }
                if ( j + 1 < nr_camp ) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            for ( int j = 0; j < nr_camp; j++ ) {
                if ( strcmp(camp[j], "id_student") == 0 ) {
                    printf("%d", s->inrolari[i].id_student);
                } else if ( strcmp(camp[j], "id_materie") == 0 ) {
                    printf("%d", s->inrolari[i].id_materie);
                } else if ( strcmp(camp[j], "note") == 0 ) {
                    for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                        printf("%.2f", s->inrolari[i].note[k]);
                        if ( k + 1 < NUMBER_OF_GRADES ) {
                            printf(" ");
                        }
                    }
                } else if ( strcmp(camp[j], "*") == 0 ) {
                    printf("%d ", s->inrolari[i].id_student);
                    printf("%d ", s->inrolari[i].id_materie);
                    for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                        printf("%.2f", s->inrolari[i].note[k]);
                    }
                }
                if ( j + 1 < nr_camp ) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}

void interog_filtr_simplu(secretariat *s, char **camp, char *tabel, char *camp_filtru,
                           char *operator_cond, char *valoare, int nr_camp) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_filtru, operator_cond, valoare, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id") == 0 ) {
                        printf("%d", s->studenti[i].id);
                    } else if ( strcmp(camp[j], "nume") == 0 ) {
                        printf("%s", s->studenti[i].nume);
                    } else if ( strcmp(camp[j], "an_studiu") == 0 ) {
                        printf("%d", s->studenti[i].an_studiu);
                    } else if ( strcmp(camp[j], "statut") == 0 ) {
                        printf("%c", s->studenti[i].statut);
                    } else if ( strcmp(camp[j], "medie_generala") == 0 ) {
                        printf("%.2f", s->studenti[i].medie_generala);
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->studenti[i].id);
                        printf("%s ", s->studenti[i].nume);
                        printf("%d ", s->studenti[i].an_studiu);
                        printf("%c ", s->studenti[i].statut);
                        printf("%.2f", s->studenti[i].medie_generala);
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if ( conditie_mat(s, camp_filtru, operator_cond, valoare, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id") == 0 ) {
                        printf("%d", s->materii[i].id);
                    } else if ( strcmp(camp[j], "nume") == 0 ) {
                        printf("%s", s->materii[i].nume);
                    } else if ( strcmp(camp[j], "nume_titular") == 0 ) {
                        printf("%s", s->materii[i].nume_titular);
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->materii[i].id);
                        printf("%s ", s->materii[i].nume);
                        printf("%s", s->materii[i].nume_titular);
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
            printf("\n");
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_filtru, operator_cond, valoare, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id_student") == 0 ) {
                        printf("%d", s->inrolari[i].id_student);
                    } else if ( strcmp(camp[j], "id_materie") == 0 ) {
                        printf("%d", s->inrolari[i].id_materie);
                    } else if ( strcmp(camp[j], "note") == 0 ) {
                        for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if ( k + 1 < NUMBER_OF_GRADES ) {
                                printf(" ");
                            }
                        }
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->inrolari[i].id_student);
                        printf("%d ", s->inrolari[i].id_materie);
                        for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                            printf("%.2f", s->inrolari[i].note[k]);
                        }
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }
}

void interog_filtr_compl(secretariat *s, char **camp, char *tabel, char *camp_filtru1, char *operator1, char *valoare1,
                        char *camp_filtru2, char *operator2, char *valoare2, int nr_camp) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_filtru1, operator1, valoare1, i) &&
                conditie_stud(s, camp_filtru2, operator2, valoare2, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id") == 0 ) {
                        printf("%d", s->studenti[i].id);
                    } else if ( strcmp(camp[j], "nume") == 0 ) {
                        printf("%s", s->studenti[i].nume);
                    } else if ( strcmp(camp[j], "an_studiu") == 0 ) {
                        printf("%d", s->studenti[i].an_studiu);
                    } else if ( strcmp(camp[j], "statut") == 0 ) {
                        printf("%c", s->studenti[i].statut);
                    } else if ( strcmp(camp[j], "medie_generala") == 0 ) {
                        // s->studenti[i].medie_generala = 0;
                        printf("%.2f", s->studenti[i].medie_generala);
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->studenti[i].id);
                        printf("%s ", s->studenti[i].nume);
                        printf("%d ", s->studenti[i].an_studiu);
                        printf("%c ", s->studenti[i].statut);
                        printf("%.2f", s->studenti[i].medie_generala);
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if ( conditie_mat(s, camp_filtru1, operator1, valoare1, i) &&
                 conditie_mat(s, camp_filtru2, operator2, valoare2, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id") == 0 ) {
                        printf("%d", s->materii[i].id);
                    } else if ( strcmp(camp[j], "nume") == 0 ) {
                        printf("%s", s->materii[i].nume);
                    } else if ( strcmp(camp[j], "nume_titular") == 0 ) {
                        printf("%s", s->materii[i].nume_titular);
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->materii[i].id);
                        printf("%s ", s->materii[i].nume);
                        printf("%s", s->materii[i].nume_titular);
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_filtru1, operator1, valoare1, i) &&
                 conditie_inrol(s, camp_filtru2, operator2, valoare2, i) ) {
                for ( int j = 0; j < nr_camp; j++ ) {
                    if ( strcmp(camp[j], "id_student") == 0 ) {
                        printf("%d", s->inrolari[i].id_student);
                    } else if ( strcmp(camp[j], "id_materie") == 0 ) {
                        printf("%d", s->inrolari[i].id_materie);
                    } else if ( strcmp(camp[j], "note") == 0 ) {
                        for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if ( k + 1 < NUMBER_OF_GRADES ) {
                                printf(" ");
                            }
                        }
                    } else if ( strcmp(camp[j], "*") == 0 ) {
                        printf("%d ", s->inrolari[i].id_student);
                        printf("%d ", s->inrolari[i].id_materie);
                        for ( int k = 0; k < NUMBER_OF_GRADES; k++ ) {
                            printf("%.2f", s->inrolari[i].note[k]);
                        }
                    }
                    if ( j + 1 < nr_camp ) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }
}

void update_filtr_simplu(secretariat *s, char *tabel, char *camp, char *valoare,
    char *camp_cond, char *operator_cond, char *valoare_cond) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_cond, operator_cond, valoare_cond, i) ) {
                if ( strcmp(camp, "id") == 0 ) {
                    s->studenti[i].id = atoi(valoare);
                } else if ( strcmp(camp, "nume") == 0 ) {
                    snprintf(s->studenti[i].nume, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->studenti[i].nume, valoare);
                } else if ( strcmp(camp, "an_studiu") == 0 ) {
                    s->studenti[i].an_studiu = atoi(valoare);
                } else if ( strcmp(camp, "statut") == 0 ) {
                    s->studenti[i].statut = valoare[0];
                } else if ( strcmp(camp, "medie_generala") == 0 ) {
                    s->studenti[i].medie_generala = (float)atof(valoare);
                }
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if ( conditie_mat(s, camp_cond, operator_cond, valoare_cond, i) ) {
                if ( strcmp(camp, "id") == 0 ) {
                    s->materii[i].id = atoi(valoare);
                } else if ( strcmp(camp, "nume") == 0 ) {
                    snprintf(s->materii[i].nume, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->materii[i].nume, valoare);
                } else if ( strcmp(camp, "nume_titular") == 0 ) {
                    snprintf(s->materii[i].nume_titular, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->materii[i].nume_titular, valoare);
                }
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_cond, operator_cond, valoare_cond, i) ) {
                if ( strcmp(camp, "id_student") == 0 ) {
                    s->inrolari[i].id_student = atoi(valoare);
                } else if ( strcmp(camp, "id_materie") == 0 ) {
                    s->inrolari[i].id_materie = atoi(valoare);
                }
            }
        }
    }
}

void update_filtr_compl(secretariat *s, char *tabel, char *camp, char *valoare, char *camp_cond1,
    char *operator_cond1, char *valoare_cond1, char *camp_cond2, char *operator_cond2, char *valoare_cond2) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_stud(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                if ( strcmp(camp, "id") == 0 ) {
                    s->studenti[i].id = atoi(valoare);
                } else if ( strcmp(camp, "nume") == 0 ) {
                    snprintf(s->studenti[i].nume, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->studenti[i].nume, valoare);
                } else if ( strcmp(camp, "an_studiu") == 0 ) {
                    s->studenti[i].an_studiu = atoi(valoare);
                } else if ( strcmp(camp, "statut") == 0 ) {
                    s->studenti[i].statut = valoare[0];
                } else if ( strcmp(camp, "medie_generala") == 0 ) {
                    s->studenti[i].medie_generala = (float)atof(valoare);
                }
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if (conditie_mat(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_mat(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                if ( strcmp(camp, "id") == 0 ) {
                    s->materii[i].id = atoi(valoare);
                } else if ( strcmp(camp, "nume") == 0 ) {
                    snprintf(s->materii[i].nume, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->materii[i].nume, valoare);
                } else if ( strcmp(camp, "nume_titular") == 0 ) {
                    snprintf(s->materii[i].nume_titular, MAX_STUDENT_NAME, "%s", valoare);
                    // strcpy(s->materii[i].nume_titular, valoare);
                }
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_inrol(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                if ( strcmp(camp, "id_student") == 0 ) {
                    s->inrolari[i].id_student = atoi(valoare);
                } else if ( strcmp(camp, "id_materie") == 0 ) {
                    s->inrolari[i].id_materie = atoi(valoare);
                }
            }
        }
    }
}

float calc_medie(secretariat *s, int poz_stud) {
    int count_materii = 0;
    s->studenti[poz_stud].medie_generala = 0;
    for ( int i = 0; i < s->nr_inrolari ; i++ ) {
        if ( s->studenti[poz_stud].id == s->inrolari[i].id_student ) {
            s->studenti[poz_stud].medie_generala += s->inrolari[i].note[0] +
                   s->inrolari[i].note[1] + s->inrolari[i].note[2];
            count_materii++;
        }
    }
    float medie = (float)s->studenti[poz_stud].medie_generala / (float)count_materii;
    int val_aprox = (int)(medie * FLOAT_to_INT);
    if ( val_aprox % ULT_CIFRA >= 4 ) {  //  marja de eroare
        val_aprox++;
        medie = (float)((float)(val_aprox) / INT_to_FLOAT);
    }
    if ( count_materii == 0 ) {
        medie = 0;
    }
    return medie;
}

secretariat* update_note(secretariat *s, char *camp, char *cuv) {
    cuv = strtok(NULL, ", ");
    char *nota1 = strtok(NULL, ", ");
    char *nota2 = strtok(NULL, ", ");
    char *nota3 = strtok(NULL, ", ");
    cuv = strtok(NULL, ", ");
    char *camp1 = strtok(NULL, ", ");
    char *operator1 = strtok(NULL, ", ");
    char *valoare1 = strtok(NULL, ", ");
    cuv = strtok(NULL, ", ");
    if ( !cuv ) {
        if ( valoare1[strlen(valoare1) - 1] == ';' ) {
            valoare1[strlen(valoare1) - 1] = '\0';
        }
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp1, operator1, valoare1, i) ) {
                s->inrolari[i].note[0] = (float)atof(nota1);
                s->inrolari[i].note[1] = (float)atof(nota2);
                s->inrolari[i].note[2] = (float)atof(nota3);
                for ( int j = 0; j < s->nr_studenti; j++ ) {
                    if ( s->studenti[j].id == s->inrolari[i].id_student ) {
                        s->studenti[j].medie_generala = calc_medie(s, j);
                    }
                }
            }
        }
    } else {
        char *camp2 = strtok(NULL, ", ");
        char *operator2 = strtok(NULL, ", ");
        char *valoare2 = strtok(NULL, ", ");
        if ( valoare2[strlen(valoare2) - 1] == ';' ) {
            valoare2[strlen(valoare2) - 1] = '\0';
        }
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp1, operator1, valoare1, i) &&
                conditie_inrol(s, camp2, operator2, valoare2, i) ) {
                s->inrolari[i].note[0] = (float)atof(nota1);
                s->inrolari[i].note[1] = (float)atof(nota2);
                s->inrolari[i].note[2] = (float)atof(nota3);
                for ( int j = 0; j < s->nr_studenti; j++ ) {
                    if ( s->studenti[j].id == s->inrolari[i].id_student ) {
                        s->studenti[j].medie_generala = calc_medie(s, j);
                    }
                }
            }
        }
    }
    return s;
}

void delete_filtr_simplu(secretariat *s, char *tabel, char *camp_cond, char *operator_cond, char *valoare_cond) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_cond, operator_cond, valoare_cond, i) ) {
                for ( int j = i; j < s->nr_studenti - 1; j++ ) {
                    s->studenti[j] = s->studenti[j + 1];
                }
                i--;
                s->nr_studenti--;
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if ( conditie_mat(s, camp_cond, operator_cond, valoare_cond, i) ) {
                free(s->materii[i].nume);
                free(s->materii[i].nume_titular);
                for ( int j = i; j < s->nr_materii; j++ ) {
                    s->materii[j] = s->materii[j + 1];
                }
                i--;
                s->nr_materii--;
                for ( int j = 0; j < s->nr_studenti; j++ ) {
                    s->studenti[j].medie_generala = calc_medie(s, j);
                }
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_cond, operator_cond, valoare_cond, i) ) {
                for ( int j = i; j < s->nr_inrolari; j++ ) {
                    s->inrolari[j] = s->inrolari[j + 1];
                }
                i--;
                s->nr_inrolari--;
                for ( int j = 0; j < s->nr_studenti; j++ ) {
                    s->studenti[j].medie_generala = calc_medie(s, j);
                }
            }
        }
    }
}

void delete_filtr_compl(secretariat *s, char *tabel, char *camp_cond1, char *operator_cond1, char *valoare_cond1,
                        char *camp_cond2, char *operator_cond2, char *valoare_cond2) {
    if ( strcmp(tabel, "studenti") == 0 ) {
        for ( int i = 0; i < s->nr_studenti; i++ ) {
            if ( conditie_stud(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_stud(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                for ( int j = i; j < s->nr_studenti - 1; j++ ) {
                    s->studenti[j] = s->studenti[j + 1];
                }
                i--;
                s->nr_studenti--;
            }
        }
    } else if ( strcmp(tabel, "materii") == 0 ) {
        for ( int i = 0; i < s->nr_materii; i++ ) {
            if ( conditie_mat(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_mat(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                free(s->materii[i].nume);
                free(s->materii[i].nume_titular);
                for ( int j = i; j < s->nr_materii; j++ ) {
                    s->materii[j] = s->materii[j + 1];
                }
                i--;
                s->nr_materii--;
            }
        }
    } else if ( strcmp(tabel, "inrolari") == 0 ) {
        for ( int i = 0; i < s->nr_inrolari; i++ ) {
            if ( conditie_inrol(s, camp_cond1, operator_cond1, valoare_cond1, i) &&
               conditie_inrol(s, camp_cond2, operator_cond2, valoare_cond2, i) ) {
                for ( int j = i; j < s->nr_inrolari; j++ ) {
                    s->inrolari[j] = s->inrolari[j + 1];
                }
                i--;
                s->nr_inrolari--;
            }
        }
    }
}
