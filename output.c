#include "output.h"

void debugOutput(output_t o)
{
    printf("name: %s\n", o.name);
    printf("time: %d\n", o.time);
    printf("diaReq: %d\n", o.diaReq);
    printf("row, col: %d,%d\n", o.row, o.col);
}