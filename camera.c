#include "./camera.h"

void updateCamera(camera_t *cam, int nRow, int nCol) {
    cam->row = nRow;
    cam->col = nCol;
}

camera_t createCamera() {
    camera_t rtr = {0,0};
    return rtr;
}