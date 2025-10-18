#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CHUNK_H
#define CHUNK_H

#define BLOCK_AIR       0
#define BLOCK_GRASS     1
#define BLOCK_WOOD      2
#define BLOCK_STONE     3
#define SHELL_NR_DIR    19
#define MASK_110        6
#define MASK_11         3
#define MASK_100000     32
#define MASK_11111      31
#define MASK_1000000000000  4096   
#define MASK_1000       8
#define MASK_1111111    255
#define NR_CHUNK_ONLY_RUN   4095
#define MASK_1111       15
#define MASK_110000     48
#define MASK_1          1

// Partea A
char*** chunk_place_block(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block);

char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth,
    int x0, int y0, int z0, int x1, int y1, int z1, char block);

char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, double radius, char block);

// Partea B

char*** chunk_shell(
    char*** chunk, int width, int height, int depth,
    char target_block, char shell_block);

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block);

char*** chunk_fill(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block);

// Partea C

char*** chunk_rotate_y(
    char*** chunk, int width, int height, int depth);

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height);

// Partea D

unsigned char* chunk_encode(
    char*** chunk, int width, int height, int depth,
    int* length);

char*** chunk_decode(
    unsigned char* code, int width, int height, int depth);
    
#endif  // CHUNK_H

// Functii auxiliare

void let_it_fall(char*** chunk, int*** chunk_new,
    int width, int height, int depth, int mark_find_corp,
    int *max_y, int *falls);
int*** fill_corp(
    int*** chunk, int width, int height, int depth,
    int x, int y, int z, int block, int want_block);
int*** fill_new_corp(
    int*** chunk, int width, int height, int depth,
    int x, int y, int z, int bloc);
char*** chunk_fill_xz_recurs(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block, char want_block);
char*** chunk_fill_recurs_all_dir(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block, char want_block);
int minim(int a, int b);
int maxim(int a, int b);
