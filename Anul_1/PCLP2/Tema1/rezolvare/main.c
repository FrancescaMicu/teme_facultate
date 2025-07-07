#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_reg_inc(char var)
{
	//  testare registre care se afla inainte de virgula in comanda
	if (var == 'a')
		printf("eax, ");
	else if (var == 'b')
		printf("ebx, ");
	else if (var == 'c')
		printf("ecx, ");
	else if (var == 'd')
		printf("edx, ");
	else
		printf("Error");
}

void test_reg_sf(char var)
{
	//  testare registre care se afla dupa virgula in comanda
	if (var == 'a')
		printf("eax");
	else if (var == 'b')
		printf("ebx");
	else if (var == 'c')
		printf("ecx");
	else if (var == 'd')
		printf("edx");
	else
		printf("Error");
}

void corp_fct_simple(char *registru1, char *oper)
{
	// corp de functie comun folosit pentru mai multe operatii
	test_reg_inc(registru1[0]);
	if (oper[0] >= '0' && oper[0] <= '9') {	// test daca al doilea operator
	// e numar sau registru
		printf("%s", oper);
	} else {
		test_reg_sf(oper[0]);
	}
}

void MOV(char *registru, char *oper)
{
	if (registru[0] >= '0' && registru[0] <= '9') {	//  test daca primul
	// operator este numar
		printf("Error");
		return;
	}
	printf("MOV ");
	corp_fct_simple(registru, oper);
}

void MUL(char *registru, char *oper)
{
	//  caz special registrul initial e eax
	if (registru[0] == 'a') {
		if (oper[0] >= '0' && oper[0] <= '9') {
			printf("MUL %s", oper);
		} else {
			printf("MUL ");
			test_reg_sf(oper[0]);
		}
	} else {
		char reg_eax = 'a';
		MOV(&reg_eax, registru);
		printf("\n");
		if (oper[0] >= '0' && oper[0] <= '9') {
			printf("MUL %s", oper);
		} else {
			printf("MUL ");
			test_reg_sf(oper[0]);
		}
		printf("\n");
		MOV(registru, &reg_eax);
	}
}

void DIV(char *registru, char *oper)
{
	//  caz pt comanda de forma "registru / 0"
	if (oper[0] == '0') {
		printf("Error");
		return;
	} else if (registru[0] == 'a') {	//  caz special registrul initial e eax
		if (oper[0] >= '0' && oper[0] <= '9') {
			printf("MUL %s", oper);
		} else {
			printf("MUL ");
			test_reg_sf(oper[0]);
		}
	} else {
		char reg_eax = 'a';
		MOV(&reg_eax, registru);
		printf("\n");
		if (oper[0] > '0' && oper[0] <= '9') {
			printf("DIV %s", oper);
		} else {
			printf("DIV ");
			test_reg_sf(oper[0]);
		}
		printf("\n");
		MOV(registru, &reg_eax);
	}
}

void CMP(char *registru, char *oper)
{
	printf("CMP ");
	corp_fct_simple(registru, oper);
}

void JUMP(char *cond, char *label)
{
	if (!strcmp(cond, "!="))
		printf("JE %s", label);
	else if (!strcmp(cond, "<="))
		printf("JG %s", label);
	else if (!strcmp(cond, ">="))
		printf("JL %s", label);
	else if (!strcmp(cond, ">"))
		printf("JLE %s", label);
	else if (!strcmp(cond, "<"))
		printf("JGE %s", label);
	else if (!strcmp(cond, "=="))
		printf("JNE %s", label);
}

void elimin_enter(char *cuv)
{
	if (!(cuv[0] >= 'a' && cuv[0] <= 'd')) {  //  verificare ca e enter
	// la inceput de comanda
		cuv[0] = cuv[1];
		cuv[1] = '\0';
	}
}

int main(void)
{
	char *comanda = malloc(200 * sizeof(char));
	if (!comanda) {
		printf("Eroare la alocare");
		return -1;
	}
	char *op1, *op2, *op3, *op4, cnt;
	// variabile care actioneaza ca switch
	// pt a determina cand se iese din if/bucla
	int if_fl = 0, wh_fl = 0, for_fl = 0;
	char *label = "end_label";
	while (fgets(comanda, 200 * sizeof(char), stdin)) {
		int len = strlen(comanda);
		//  sterge ";" unde este cazul
		if (comanda[len - 2] == ';')
			comanda[len - 2] = '\0';
		if (strstr(comanda, "for")) {
			// flag activat->intra in for
			for_fl = 1;
			op1 = strtok(comanda, "for(){ ");
			op2 = strtok(NULL, "for(){ ");
			op2 = strtok(NULL, "for(){ ");
			op3 = strtok(NULL, "for(){ ");
			op3 = strtok(NULL, "for(){ ");
			op4 = strtok(NULL, "for(){ ");
			//  sterge ";"
			op2[strlen(op2) - 1] = '\0';
			op4[strlen(op4) - 1] = '\0';
			MOV(op1, op2);
			printf("\nstart_loop:\n");
			CMP(op1, op4);
			printf("\n");
			JUMP(op3, label);
			// retine contorul din for
			cnt = op1[0];
		} else if (strstr(comanda, "&")) {
			op1 = strtok(comanda, " =&");
			op2 = strtok(NULL, " =&");
			op3 = strtok(NULL, " =&");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("AND ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "|")) {
			op1 = strtok(comanda, " =|");
			op2 = strtok(NULL, " =|");
			op3 = strtok(NULL, " =|");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("OR ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "^")) {
			op1 = strtok(comanda, " =^");
			op2 = strtok(NULL, " =^");
			op3 = strtok(NULL, " =^");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("XOR ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "+")) {
			op1 = strtok(comanda, " =+");
			op2 = strtok(NULL, " =+");
			op3 = strtok(NULL, " =+");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("ADD ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "-")) {
			op1 = strtok(comanda, " =-");
			op2 = strtok(NULL, " =-");
			op3 = strtok(NULL, " =-");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("SUB ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "*")) {
			op1 = strtok(comanda, " =*");
			op2 = strtok(NULL, " =*");
			op3 = strtok(NULL, " =*");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			MUL(op1, op3);
		} else if (strstr(comanda, "/")) {
			op1 = strtok(comanda, " =/");
			op2 = strtok(NULL, " =/");
			op3 = strtok(NULL, " =/");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			DIV(op1, op3);
		} else if (strstr(comanda, "<<")) {
			op1 = strtok(comanda, " =<<");
			op2 = strtok(NULL, " =<<");
			op3 = strtok(NULL, " =<<");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("SHL ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, ">>")) {
			op1 = strtok(comanda, " =>>");
			op2 = strtok(NULL, " =>>");
			op3 = strtok(NULL, " =>>");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			if (strcmp(op1, op2) != 0) {
				printf("Error");
				break;
			}
			printf("SHR ");
			corp_fct_simple(op1, op3);
		} else if (strstr(comanda, "if")) {
			op1 = strtok(comanda, "if(){ ");
			op2 = strtok(NULL, "if(){ ");
			op3 = strtok(NULL, "if(){ ");
			CMP(op1, op3);
			printf("\n");
			JUMP(op2, label);
			// flag activat->intra in if
			if_fl = 1;
		} else if (strstr(comanda, "}") && if_fl == 1) {
			// flag oprti->iese din if
			if_fl = 0;
			printf("end_label:");
		} else if (strstr(comanda, "while")) {
			// flag activat->intra in while
			wh_fl = 1;
			printf("start_loop:\n");
			op1 = strtok(comanda, "while(){ ");
			op2 = strtok(NULL, "while(){ ");
			op3 = strtok(NULL, "while(){ ");
			CMP(op1, op3);
			printf("\n");
			JUMP(op2, label);
		} else if (strstr(comanda, "}") && wh_fl == 1) {
			// flag oprti->iese din while
			wh_fl = 0;
			printf("JMP start_loop\n");
			printf("end_label:");
		} else if (strstr(comanda, "}") && for_fl == 1) {
			// flag oprti->iese din for
			for_fl = 0;
			char increment = '1';
			//  urmatoarele 2 linii->se adauga 1 la contor
			printf("ADD ");
			corp_fct_simple(&cnt, &increment);
			printf("\nJMP start_loop\n");
			printf("end_loop:");
		} else if (strstr(comanda, "=")) {
			op1 = strtok(comanda, " =");
			op2 = strtok(NULL, " =");
			// pt cand linia de cod se afla intr-un if/while/for se sterge
			// enterul care ramane in primul operator
			elimin_enter(op1);
			MOV(op1, op2);
		}
		printf("\n");
	}
	free(comanda);
	return 0;
}
