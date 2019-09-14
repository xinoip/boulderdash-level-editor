#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

typedef struct Output
{
    char *name;
    int time;
    int diaReq;
    int row;
    int col;
} output_t;

void debugOutput(output_t o);

#endif