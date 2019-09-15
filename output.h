#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "./base.h"

typedef struct Output
{
    char *name;
    int time;
    int diaReq;
    int row;
    int col;
    char **arr;
} output_t;

void debugOutput(output_t o);

void debugArray(output_t o);

void initArray(output_t *o);

void exportOutput(output_t o, char *fileName);

#endif