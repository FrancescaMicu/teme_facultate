#include "chunk.h"

unsigned char* chunk_encode(
    char*** chunk, int width, int height, int depth,
    int* length) {
        int count_all_of_them = 0;
        char *flat = (char*)malloc(width * height * depth * sizeof(char));
        if ( !flat ) {
            // printf("Eroare la alocare");
            return NULL;
        }
        for ( int j = 0; j < height; j++ ) {
            for ( int k = 0; k < depth; k++ ) {
                for ( int i = 0; i < width; i++ ) {
                    flat[count_all_of_them++] = chunk[i][j][k];
                }
            }
        }
        unsigned char *runs = (unsigned char*)malloc(2 * count_all_of_them * sizeof(unsigned char));
        int count_runs = 0, i = 0;
        while ( i < count_all_of_them ) {
            char this_block = flat[i];
            int count_near = 0;
            while ( i < count_all_of_them && flat[i] == this_block ) {
                count_near++;
                i++;
            }
            runs[count_runs] = (this_block << MASK_110) & (MASK_11 << MASK_110);
            if ( count_near < MASK_100000 ) {
                runs[count_runs] &= ~(MASK_1 << MASK_11);
                runs[count_runs++] |= (count_near & MASK_11111);
            } else if ( count_near < MASK_1000000000000 ) {
                runs[count_runs] |= MASK_100000;
                runs[count_runs++] |= (count_near >> MASK_1000);
                runs[count_runs++] = (count_near & MASK_1111111);
            } else {
                while ( count_near >= NR_CHUNK_ONLY_RUN ) {
                    runs[count_runs] = (this_block << MASK_110) & (MASK_11 << MASK_110);
                    runs[count_runs] |= MASK_100000;
                    runs[count_runs++] |= MASK_1111;
                    runs[count_runs++] |= MASK_1111111;
                    count_near -= NR_CHUNK_ONLY_RUN;
                }
                if ( count_near > 0 ) {
                    if ( count_near >= MASK_100000 ) {
                        runs[count_runs] = (this_block << MASK_110) & (MASK_11 << MASK_110);
                        runs[count_runs] |= MASK_100000;
                        runs[count_runs++] |= (count_near >> MASK_1000);
                        runs[count_runs++] = (count_near & MASK_1111111);
                    } else {
                        runs[count_runs] = (this_block << MASK_110) & (MASK_11 << MASK_110);
                        runs[count_runs] &= ~(MASK_1 << MASK_11);
                        runs[count_runs++] |= (count_near & MASK_11111);
                    }
                }
            }
        }
        (*length) = count_runs;
        free(flat);
        return runs;
    }

char*** chunk_decode(
    unsigned char* code, int width, int height, int depth) {
        char*** chunk = (char ***)malloc(width * sizeof(char **));
        if ( !chunk ) {
            // printf("Eroare la alocare");
            return NULL;
        }
        for ( int i = 0; i < width; i++ ) {
            chunk[i] = (char **)malloc(height * sizeof(char *));
            if ( !chunk[i] ) {
                // printf("Eroare la alocare");
                return NULL;
            }
            for ( int j = 0; j < height; j++ ) {
                chunk[i][j] = (char *)malloc(depth * sizeof(char));
                if ( !chunk[i][j] ) {
                    // printf("Eroare la alocare");
                    return NULL;
                }
            }
        }
        int idx_i = 0, idx_j = 0, idx_k = 0;
        int i = 0, all_of_them = width * height * depth;
        while ( i < all_of_them && code[i] ) {
            char curr_block = (char)((code[i] >> MASK_110) & MASK_11);
            int nr_block = 0;
            if ( (code[i] & MASK_100000) == 0 ) {
                nr_block = (code[i] & MASK_11111);
                i++;
            } else if ( (code[i] & MASK_110000) == MASK_100000 &&
                      (((code[i] & MASK_1111) << MASK_1000) | code[i + 1]) != NR_CHUNK_ONLY_RUN ) {
                nr_block = ((code[i] & MASK_1111) << MASK_1000) | code[i + 1];
                i += 2;
            } else if ( (((code[i] & MASK_1111) << MASK_1000) | code[i + 1]) == NR_CHUNK_ONLY_RUN ) {
                int verif_nr = NR_CHUNK_ONLY_RUN;
                while ( verif_nr == NR_CHUNK_ONLY_RUN ) {
                    nr_block += verif_nr;
                    verif_nr = (((code[i++] & MASK_1111) << MASK_1000) | code[i]);
                }
                verif_nr = (code[i+1] & MASK_11111);
                nr_block += verif_nr;
            }
            while ( idx_j < height  && nr_block != 0 ) {
                    chunk[idx_i][idx_j][idx_k] = curr_block;
                    nr_block--;
                    idx_i++;
                    if ( idx_i == width ) {
                        idx_i = 0;
                        idx_k++;
                    }
                    if ( idx_k == depth ) {
                        idx_k = 0;
                        idx_j++;
                    }
                }
        }
        return chunk;
}
