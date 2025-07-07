#pragma once

#include "../include/structuri.h"

secretariat *citeste_secretariat(const char *nume_fisier);

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala);

void elibereaza_secretariat(secretariat **s);

#define SIZE_DATE 300

#define MAX_OF_THEM_ALL 500

#define FLOAT_to_INT  1000

#define ULT_CIFRA  10

#define INT_to_FLOAT  1000.0
