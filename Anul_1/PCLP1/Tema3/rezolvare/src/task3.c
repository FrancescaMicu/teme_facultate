#include "task3.h"

char *XOR(char *block, char* apl, int apl_len, int lung) {
    char *xor_apl = (char*)malloc(lung * sizeof(char));
    if ( !xor_apl ) {
        printf("Eroare la alocare");
        return NULL;
    }
    for ( int i = 0; i < lung; i++ ) {
        xor_apl[i] = (char)(block[i] ^ apl[i % apl_len]);
    }
    return xor_apl;
}

char *S_BOX(char *block, void* key, size_t iv_key, int lung) {
    char *key_str = (char*)key;
    char *s_box_apl = (char*)malloc(lung * sizeof(char));
    if ( !s_box_apl ) {
        printf("Eroare la alocare");
        return NULL;
    }
    for ( int i = 0; i < lung; i++ ) {
        s_box_apl[i] = (char)((block[i] ^ key_str[i % iv_key]));
    }
    return s_box_apl;
}

char *P_BOX(char *block, int n) {
    int *mark = (int*)malloc(sizeof(int) * n);
    if ( !mark ) {
        printf("Eroare la alocare");
        return NULL;
    }
    for ( int i = 0; i < n; i++ ) {
        mark[i] = 0;
    }
    for ( int i = 0; i < n; i++ ) {
        int j = (i * (n - 1) + 2) % n;
        if ( mark[j] == 0 ) {
            mark[i] = 1;
            mark[j] = 1;
            char aux = block[i];
            block[i] = block[j];
            block[j] = aux;
        }
    }
    free(mark);
    return block;
}

void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
                        void *iv, size_t iv_len, char *cale_output) {
    char *stud = (char*)malloc(sizeof(student) * secretariat->nr_studenti);
    stud = (char*)secretariat->studenti;
    int dim_all_blocks = (int)sizeof(student) * secretariat->nr_studenti;
    while ( dim_all_blocks % NR_OF_BLOCKS != 0 ) {
        stud[dim_all_blocks] = 0x00;
        dim_all_blocks++;
    }
    int dim_block = dim_all_blocks / NR_OF_BLOCKS;
    char **blocks = (char**)malloc(NR_OF_BLOCKS * sizeof(char*));
    if ( !blocks ) {
        printf("Eroare la alocare");
        // return NULL;
    }
    for ( int i = 0; i < NR_OF_BLOCKS; i++ ) {
        blocks[i] = (char*)malloc(sizeof(char) * dim_block);
        blocks[i] = stud + i * dim_block;
    }

    char **blocks_enc = (char**)malloc(NR_OF_BLOCKS * sizeof(char*));
    if ( !blocks_enc ) {
        printf("Eroare la alocare");
        // return NULL;
    }

    for ( int i = 0; i < NR_OF_BLOCKS; i++ ) {
        if ( i == 0 ) {
            blocks_enc[i] = XOR(blocks[i], (char*)iv, (int)iv_len, dim_block);
        } else {
            blocks_enc[i] = XOR(blocks[i], blocks_enc[i - 1], dim_block, dim_block);
        }
        blocks_enc[i] = S_BOX(blocks_enc[i], key, (int)key_len, dim_block);
        blocks_enc[i] = P_BOX(blocks_enc[i], dim_block);
    }

    FILE *file = fopen(cale_output, "wb");
    if ( !file ) {
        printf("Eroare la deschiderea fisierului");
        // return NULL;
    }
    for ( int i = 0; i < NR_OF_BLOCKS; i++ ) {
        fwrite(blocks_enc[i], 1, dim_block, file);
    }
    fclose(file);
    free(stud);
    /*for ( int i = 0; i < NR_OF_BLOCKS; i++ ) {
        free(blocks[i]);
    }*/
    free(blocks);
    /*for ( int i = 0; i < NR_OF_BLOCKS; i++ ) {
        free(blocks_enc[i]);
    }*/
    free(blocks_enc);
}
