#ifndef CAMERA_H
#define CAMERA_H

typedef struct camera {
    int row, col;
} camera_t;

void updateCamera(camera_t *cam, int nRow, int nCol);

camera_t createCamera();

#endif