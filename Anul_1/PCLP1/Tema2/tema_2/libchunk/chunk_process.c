#include "chunk.h"

char*** chunk_shell(
    char*** chunk, int width, int height, int depth,
    char target_block, char shell_block) {
        char*** chunk_new = (char ***)malloc(width * sizeof(char **));
        if ( !chunk_new ) {
            // printf("Eroare la alocare");
            return NULL;
        }
        for ( int i = 0; i < width; i++ ) {
            chunk_new[i] = (char **)malloc(height * sizeof(char *));
            if ( !chunk_new[i] ) {
                // printf("Eroare la alocare");
                return NULL;
            }
            for ( int j = 0; j < height; j++ ) {
                chunk_new[i][j] = (char *)malloc(depth * sizeof(char));
                if ( !chunk_new[i][j] ) {
                    // printf("Eroare la alocare");
                    return NULL;
                }
                for ( int k = 0; k < depth; k++ ) {
                    chunk_new[i][j][k] = chunk[i][j][k];
                }
            }
        }
        int dx[] = {0, -1, 1, 0, 0, 0, 0, -1, -1, 1, 1, 0, 0, 0, 0, -1, -1, 1, 1};
        int dy[] = {0, 0, 0, -1, 1, 0, 0, -1, 1, -1, 1, -1 , 1, -1, 1, 0, 0, 0, 0};
        int dz[] = {0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0, -1, -1, 1, 1, -1, 1, -1, 1};
        /*int *dx = (int *)malloc(19 * sizeof(int));
        int *dy = (int *)malloc(19 * sizeof(int));
        int *dz = (int *)malloc(19 * sizeof(int));
        dx[0] = 0;  dy[0] = 0;  dz[0] = 0;
        dx[1] = -1; dy[1] = 0;  dz[1] = 0;
        dx[2] = 1;  dy[2] = 0;  dz[2] = 0;
        dx[3] = 0;  dy[3] = -1; dz[3] = 0;
        dx[4] = 0;  dy[4] = 1;  dz[4] = 0;
        dx[5] = 0;  dy[5] = 0;  dz[5] = -1;
        dx[6] = 0;  dy[6] = 0;  dz[6] = 1;
        dx[7] = -1; dy[7] = -1; dz[7] = 0;
        dx[8] = -1; dy[8] = 1;  dz[8] = 0;
        dx[9] = 1;  dy[9] = -1; dz[9] = 0;
        dx[10] = 1; dy[10] = 1; dz[10] = 0;
        dx[11] = 0; dy[11] = -1; dz[11] = -1;
        dx[12] = 0; dy[12] = 1;  dz[12] = -1;
        dx[13] = 0; dy[13] = -1; dz[13] = 1;
        dx[14] = 0; dy[14] = 1;  dz[14] = 1;
        dx[15] = -1; dy[15] = 0; dz[15] = -1;
        dx[16] = -1; dy[16] = 0; dz[16] = 1;
        dx[17] = 1;  dy[17] = 0; dz[17] = -1;
        dx[18] = 1;  dy[18] = 0; dz[18] = 1;*/
        for ( int i = 0; i < width; i++ ) {
            for ( int j = 0; j < height; j++ ) {
                for ( int k = 0; k < depth; k++ ) {
                    if ( chunk[i][j][k] == target_block ) {
                        for ( int dir = 0; dir < SHELL_NR_DIR; dir++ ) {
                            if ( width > i + dx[dir]  && height > dy[dir] + j && depth > dz[dir] + k
                            && i + dx[dir] >= 0 && dy[dir] + j >= 0 && dz[dir] + k >= 0 ) {
                                if ( chunk_new[i + dx[dir]][dy[dir] + j][dz[dir] + k] != target_block ) {
                                    chunk_new[i + dx[dir]][dy[dir] + j][dz[dir] + k] = shell_block;
                                }
                            }
                        }
                    }
                }
            }
        }
        for ( int x = 0; x < width; x++ ) {
            for ( int y = 0; y < height; y++ ) {
                for ( int k = 0; k < depth; k++ ) {
                    chunk[x][y][k] = chunk_new[x][y][k];
                }
            }
        }
        for ( int x = 0; x < width; x++ )  {
            for ( int y = 0; y < height; y++ ) {
                free(chunk_new[x][y]);
            }
            free(chunk_new[x]);
        }
        free(chunk_new);
        // free(dx);
        // free(dy);
        // free(dz);
        return chunk;
}

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        char want_block = chunk[x][y][z];
        chunk_fill_xz_recurs(chunk, width, height, depth, x, y, z, block, want_block);
        return chunk;
    }


char*** chunk_fill(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        char want_block = chunk[x][y][z];
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x, y, z, block, want_block);
        return chunk;
}

char*** chunk_fill_xz_recurs(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block, char want_block) {
        if ( x < 0 || x >= width || z < 0 || z >= depth ) {
            return chunk;
        }
        if ( chunk[x][y][z] != want_block ) {
            return chunk;
        }
        chunk[x][y][z] = block;
        chunk_fill_xz_recurs(chunk, width, height, depth, x - 1, y, z, block, want_block);
        chunk_fill_xz_recurs(chunk, width, height, depth, x, y, z - 1, block, want_block);
        chunk_fill_xz_recurs(chunk, width, height, depth, x + 1, y, z, block, want_block);
        chunk_fill_xz_recurs(chunk, width, height, depth, x, y, z + 1, block, want_block);
        return chunk;
    }

char*** chunk_fill_recurs_all_dir(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block, char want_block) {
        if ( x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth ) {
            return chunk;
        }
        if ( chunk[x][y][z] != want_block ) {
            return chunk;
        }
        chunk[x][y][z] = block;
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x - 1, y, z, block, want_block);
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x, y - 1, z, block, want_block);
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x, y, z - 1, block, want_block);
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x + 1, y, z, block, want_block);
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x, y + 1, z, block, want_block);
        chunk_fill_recurs_all_dir(chunk, width, height, depth, x, y, z + 1, block, want_block);
    }
