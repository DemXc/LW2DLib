#include "lw2d.h"

float cubePosX = 0.0f;
float cubePosY = 0.0f;
GLuint texture;

void drawCube() {
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        // Front face
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.9f, -0.9f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.9f, -0.9f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.9f,  0.9f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.9f,  0.9f);
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
    LW2DWindow* window = createWindow(800, 600, "LW2D Example");

    setKeyCallback(window, customKeyCallback);

    // Загрузка текстуры с использованием абсолютного пути
    texture = LW2D_loadTexture("/home/nikita/LW2DLib/src/character.png");
    if (texture == 0) {
        fprintf(stderr, "Failed to load texture\n");
        return -1;
    }

    // Включение поддержки текстур
    glEnable(GL_TEXTURE_2D);

    while (!shouldClose(window)) {
        glClearColor(0.0f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(cubePosX, cubePosY, 0.0f);
        drawCube();
        glPopMatrix();

        pollEvents();
        swapBuffers(window);
    }

    destroyWindow(window);
    return 0;
}
