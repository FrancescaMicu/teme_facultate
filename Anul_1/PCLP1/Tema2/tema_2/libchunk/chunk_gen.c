#include "chunk.h"

char*** chunk_place_block(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
    if ( width > x && height > y && depth > z && x >= 0 && y >= 0 && z >=0 ) {
        chunk[x][y][z] = block;
    }
    return chunk;
}

char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth,
    int x0, int y0, int z0, int x1, int y1, int z1, char block) {
    int min_x = minim(x1, x0);
    int min_y = minim(y0, y1);
    int min_z = minim(z0, z1);
    int max_x = maxim(x1, x0) + 1;
    int max_y = maxim(y0, y1) + 1;
    int max_z = maxim(z0, z1) + 1;
    for ( int i = min_x; i < max_x; i++ ) {
        for ( int j = min_y; j < max_y; j++ ) {
            for ( int k = min_z; k < max_z; k++ ) {
                chunk_place_block(chunk, width, height, depth, i, j, k, block);
            }
        }
    }
    return chunk;
}

char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, double radius, char block) {
        for ( int i = 0; i < width; i++ ) {
            for ( int j = 0; j < height; j++ ) {
                for ( int k = 0; k < depth; k++ ) {
                    double dis = sqrt(pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2));
                    if ( dis < radius ) {
                        chunk[i][j][k] = block;
                    }
                }
            }
        }
        return chunk;
}

int maxim(int a, int b) {
    if ( a > b ) {
        return a;
    }
    return b;
}

int minim(int a, int b) {
    if ( a < b ) {
        return a;
    }
    return b;
}
