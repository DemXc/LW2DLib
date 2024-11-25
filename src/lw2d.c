#include "lw2d.h"

float cubePosX = 0.0f;
float cubePosY = 0.0f;

void drawCube() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(cubePosX, cubePosY, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();

    glPopMatrix();
}

void customKeyCallback(int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    if (action == LW2D_PRESS) {
        if (key == LW2D_KEY_W)
            cubePosY += 0.1f;
        else if (key == LW2D_KEY_S)
            cubePosY -= 0.1f;
        else if (key == LW2D_KEY_A)
            cubePosX -= 0.1f;
        else if (key == LW2D_KEY_D)
            cubePosX += 0.1f;
    }
}

int main() {
    LW2DWindow* window = createWindow(800, 600, "LW2D Example");

    setKeyCallback(window, customKeyCallback);

    while (!shouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawCube();

        pollEvents();
        swapBuffers(window);
    }

    destroyWindow(window);
    return 0;
}
