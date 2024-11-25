#include "lw2d.h"

int main() {
    LW2DWindow* window = createWindow(800, 600, "LW2D Window");

    while (!shouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        swapBuffers(window);
        pollEvents();
    }

    destroyWindow(window);
    return 0;
}
