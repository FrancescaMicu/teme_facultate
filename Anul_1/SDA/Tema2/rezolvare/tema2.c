/* MICU Francesca-Maria - 313CB */

#include "structuri.h"

int main(int argc, char *argv[]) {
    //  deschiderea fisierelor
    FILE *inp_file = fopen(argv[2], "rt");
    //  verificare in caz de esec
    if ( !inp_file ) {
        printf("Eroare la deschiderea fisierului de input");
        return FAIL;
    }
    FILE *out_file = fopen(argv[3], "wt");
    //  verificare in caz de esec
    if ( !out_file ) {
        printf("Eroare la deschiderea fisierului de output");
        return FAIL;
    }
    TArb arb = NULL;
    //  crearea arborelui
    arb = ImplemArb(inp_file);
    //  implementarea cerintelor
    if ( strcmp(argv[1], "-c1") == 0 ) {
        Task1(arb, out_file);
    } else if ( strcmp(argv[1], "-c2") == 0 ) {
        Task2(inp_file, out_file, arb);
    } else if ( strcmp(argv[1], "-c3") == 0 ) {
        Task3(inp_file, out_file, arb);
    } else if ( strcmp(argv[1], "-c4") == 0 ) {
        Task4(inp_file, out_file, arb);
    }
    //  inchiderea fisierelor
    fclose(inp_file);
    fclose(out_file);
    //  eliberari de memorie
    ELibArb(&arb);
    return 0;
}