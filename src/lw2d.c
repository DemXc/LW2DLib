#include "lw2d.h"

float cubePosX = 0.0f;
float cubePosY = 0.0f;
GLuint texture;

void drawCube() {
    LW2D_bindTexture(texture);
    glBegin(GL_QUADS);
        LW2D_setTexCoord(0.0f, 0.0f); glVertex2f(-0.9f, -0.9f);
        LW2D_setTexCoord(1.0f, 0.0f); glVertex2f( 0.9f, -0.9f);
        LW2D_setTexCoord(1.0f, 1.0f); glVertex2f( 0.9f,  0.9f);
        LW2D_setTexCoord(0.0f, 1.0f); glVertex2f(-0.9f,  0.9f);
    glEnd();
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
    LW2DWindow* window = LW2D_createWindow(800, 600, "LW2D Example");
    LW2D_setKeyCallback(window, customKeyCallback);

    texture = LW2D_loadTexture("/home/nikita/LW2DLib/src/character.png");
    if (texture == 0) {
        fprintf(stderr, "Failed to load texture\n");
        return -1;
    }

    LW2D_enableTextures();

    while (!LW2D_shouldClose(window)) {
        LW2D_clearScreen(0.0f, 0.05f, 0.5f, 1.0f);

        glPushMatrix();
        LW2D_translate(cubePosX, cubePosY, 0.0f);
        drawCube();
        glPopMatrix();

        LW2D_pollEvents();
        LW2D_swapBuffers(window);
    }

    LW2D_destroyWindow(window);
    return 0;
}
