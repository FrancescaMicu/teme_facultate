#include "chunk.h"

char*** chunk_rotate_y(
    char*** chunk, int width, int height, int depth) {
        int width_nou = depth, height_nou = height, depth_nou = width;
        char*** chunk_rot = (char ***)malloc(width_nou * sizeof(char **));
        if ( !chunk_rot ) {
            // printf("Eroare la alocare");
            return NULL;
        }
        for ( int i = 0; i < width_nou; i++ ) {
            chunk_rot[i] = (char **)malloc(height_nou * sizeof(char *));
            if ( !chunk_rot[i] ) {
                // printf("Eroare la alocare");
                return NULL;
            }
            for ( int j = 0; j < height_nou; j++ ) {
                chunk_rot[i][j] = (char *)malloc(depth_nou * sizeof(char));
                if ( !chunk_rot[i][j] ) {
                    // printf("Eroare la alocare");
                    return NULL;
                }
            }
        }
        for ( int i = 0; i < width; i++ ) {
            for ( int j = 0; j < height; j++ ) {
                for ( int k = 0; k < depth; k++ )  {
                    chunk_rot[depth - (k + 1)][j][i] = chunk[i][j][k];
                }
            }
        }
        for ( int i = 0; i < width; i++ )  {
            for ( int j = 0; j < height; j++ ) {
                free(chunk[i][j]);
            }
            free(chunk[i]);
        }
        free(chunk);
        return chunk_rot;
}

int*** fill_corp(
    int*** chunk, int width, int height, int depth,
    int x, int y, int z, int block, int want_block) {
        if ( x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth ) {
            return chunk;
        }
        if ( chunk[x][y][z] != want_block ) {
            return chunk;
        }
        chunk[x][y][z] = block;
        fill_corp(chunk, width, height, depth, x - 1, y, z, block, want_block);
        fill_corp(chunk, width, height, depth, x, y - 1, z, block, want_block);
        fill_corp(chunk, width, height, depth, x, y, z - 1, block, want_block);
        fill_corp(chunk, width, height, depth, x + 1, y, z, block, want_block);
        fill_corp(chunk, width, height, depth, x, y + 1, z, block, want_block);
        fill_corp(chunk, width, height, depth, x, y, z + 1, block, want_block);
    }

int*** fill_new_corp(
    int*** chunk, int width, int height, int depth,
    int x, int y, int z, int block) {
        if ( x < 0 || x >= width || z < 0 || z >= depth || y < 0 || y >= height ) {
            return chunk;
        }
        if ( chunk[x][y][z] == BLOCK_AIR || chunk[x][y][z] > 3 || chunk[x][y][z] == block ) {
            return chunk;
        }
        chunk[x][y][z] = block;
        fill_new_corp(chunk, width, height, depth, x - 1, y, z, block);
        fill_new_corp(chunk, width, height, depth, x, y, z - 1, block);
        fill_new_corp(chunk, width, height, depth, x + 1, y, z, block);
        fill_new_corp(chunk, width, height, depth, x, y, z + 1, block);
        fill_new_corp(chunk, width, height, depth, x, y - 1, z, block);
        fill_new_corp(chunk, width, height, depth, x, y + 1, z, block);
        return chunk;
}

void let_it_fall(char*** chunk, int*** chunk_new, int width, int height,
 int depth, int mark_find_corp, int *max_y, int *falls) {
    for ( int i = 4; i < mark_find_corp; i++ ) {
        int min_down = height;
        for ( int x = 0; x < width; x++ ) {
            for ( int y = 0; y < height; y++ ) {
                for ( int z = 0; z < depth; z++ ) {
                    if ( chunk_new[x][y][z] == i ) {
                        int down = y;
                        int count_down = 0;
                        while ( down - 1 >= 0 && (chunk_new[x][down - 1][z] == i ||
                        chunk_new[x][down - 1][z] == BLOCK_AIR) ) {
                            down--;
                            count_down++;
                        }
                        if ( count_down < min_down ) {
                            min_down = count_down;
                        }
                    }
                }
            }
        }
        for ( int x = 0; x < width; x++ ) {
            for ( int y = 0; y < height; y++ ) {
                for ( int z = 0; z < depth; z++ ) {
                    if ( chunk_new[x][y][z] == i ) {
                        char block_corp = chunk[x][y][z];
                        chunk[x][y][z] = BLOCK_AIR;
                        chunk_new[x][y][z] = BLOCK_AIR;
                        chunk[x][y - min_down][z] = block_corp;
                        chunk_new[x][y - min_down][z] = i;
                        if ( (*max_y) < y - min_down ) {
                           (*max_y) = y - min_down;
                        }
                        if ( y != y - min_down ) {
                            (*falls) = 1;
                        }
                    }
                }
            }
        }
    }
}

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height) {
       int*** chunk_new = (int ***)malloc(width * sizeof(int **));
        for ( int i = 0; i < width; i++ ) {
            chunk_new[i] = (int **)malloc(height * sizeof(int *));
            for ( int j = 0; j < height; j++ ) {
                chunk_new[i][j] = (int *)malloc(depth * sizeof(int));
            }
        }
        int falls = 1;
        int max_y = 0;
        while ( falls == 1 ) {
            falls = 0;
            for ( int x = 0; x < width; x++ ) {
                for ( int y = 0; y < height; y++ ) {
                    for ( int z = 0; z < depth; z++ ) {
                        chunk_new[x][y][z] = (int)chunk[x][y][z];
                    }
                }
            }
            // corpuri separate
            int mark_find_corp = 4;
            for ( int i = 0; i < width; i++ ) {
                for ( int j = 0; j < height; j++ ) {
                    for ( int k = 0; k < depth; k++ ) {
                        if ( chunk[i][j][k] != BLOCK_AIR
                        && chunk_new[i][j][k] <= 3 ) {
                            int block_corp = (int)chunk[i][j][k];
                            fill_corp(chunk_new, width, height, depth,
                            i, j, k, mark_find_corp, block_corp);
                            mark_find_corp++;
                        }
                    }
                }
            }
            let_it_fall(chunk, chunk_new, width, height, depth, mark_find_corp, &max_y, &falls);
        }
        max_y = 0;
        falls = 1;
        while ( falls == 1 ) {
            falls = 0;
            // corpuri comune
            for ( int x = 0; x < width; x++ ) {
                for ( int y = 0; y < height; y++ ) {
                    for ( int z = 0; z < depth; z++ ) {
                        chunk_new[x][y][z] = (int)chunk[x][y][z];
                    }
                }
            }
            int mark_find_corp = 4;
            for ( int i = 0; i < width; i++ ) {
                for ( int j = 0; j < height; j++ ) {
                    for ( int k = 0; k < depth; k++ ) {
                        if ( chunk[i][j][k] != BLOCK_AIR && chunk_new[i][j][k] <= 3 ) {
                            fill_new_corp(chunk_new, width, height, depth, i, j, k, mark_find_corp);
                            mark_find_corp++;
                        }
                    }
                }
            }
            let_it_fall(chunk, chunk_new, width, height, depth, mark_find_corp, &max_y, &falls);
        }
        (*new_height) = max_y + 1;
        if ( (*new_height) != height ) {
            for ( int j = (*new_height); j < height; j++ ) {
                for ( int i = 0; i < width; i++ ) {
                    free(chunk[i][j]);
                }
            }
        }
        for ( int i = 0; i < width; i++ ) {
            for ( int j = 0; j < (*new_height); j++ ) {
                chunk[i] = realloc(chunk[i], (*new_height) * sizeof(int**));
                if ( !chunk[i] ) {
                    // printf("Eroare la realocare");
                    return NULL;
                }
            }
        }
        for ( int i = 0; i < width; i++ ) {
            for ( int j = 0; j < height; j++ ) {
                    free(chunk_new[i][j]);
                }
                free(chunk_new[i]);
            }
        free(chunk_new);
        return chunk;
    }
