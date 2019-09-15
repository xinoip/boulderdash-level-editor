#include "output.h"

void debugOutput(output_t o)
{
    printf("name: %s\n", o.name);
    printf("time: %d\n", o.time);
    printf("diaReq: %d\n", o.diaReq);
    printf("row, col: %d,%d\n", o.row, o.col);
}

void initArray(output_t *o)
{
    o->arr = (char **)malloc(o->row * sizeof(char *));
    for (int i = 0; i < o->row; i++)
    {
        o->arr[i] = (char *)malloc(o->col * sizeof(char));
    }

    for (int row = 0; row < o->row; row++)
    {
        for (int col = 0; col < o->col; col++)
        {
            if (row == 0 || row == o->row - 1)
            {
                o->arr[row][col] = borderTile;
            }
            else if (col == 0 || col == o->col - 1)
            {
                o->arr[row][col] = borderTile;
            }
            else
            {
                o->arr[row][col] = emptyTile;
            }
        }
    }
}

void debugArray(output_t o)
{
    for (int row = 0; row < o.row; row++)
    {
        for (int col = 0; col < o.col; col++)
        {
            printf("%c", o.arr[row][col]);
        }
        printf("\n");
    }
}