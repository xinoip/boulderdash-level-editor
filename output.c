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

void exportOutput(output_t o, char *fileName)
{
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("fileio error!");
        return;
    }

    fprintf(fp, "%s\n", o.name);
    fprintf(fp, "%d %d\n", o.row, o.col);

    for (int row = 0; row < o.row; row++)
    {
        for (int col = 0; col < o.col; col++)
        {
            if (o.arr[row][col] == playerTile)
            {
                fprintf(fp, "%d %d\n", row, col);
                break;
            }
        }
    }
    fprintf(fp, "%d\n", o.diaReq);
    fprintf(fp, "%d %d\n", o.time, 1400);
    fprintf(fp, "%c\n", '-');

    for (int row = 0; row < o.row; row++)
    {
        for (int col = 0; col < o.col; col++)
        {
            fprintf(fp, "%c", o.arr[row][col]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    fp = NULL;
}