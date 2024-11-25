#ifndef LW2D_H
#define LW2D_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GLFWwindow* window;
} LW2DWindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;  // Убирает предупреждение об неиспользуемом параметре
    glViewport(0, 0, width, height);
}

LW2DWindow* createWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    LW2DWindow* lwWindow = (LW2DWindow*)malloc(sizeof(LW2DWindow));
    if (!lwWindow) {
        fprintf(stderr, "Failed to allocate memory for LW2DWindow\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    lwWindow->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!lwWindow->window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        free(lwWindow);
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(lwWindow->window);
    glfwSetFramebufferSizeCallback(lwWindow->window, framebuffer_size_callback);

    return lwWindow;
}

int shouldClose(LW2DWindow* lwWindow) {
    return glfwWindowShouldClose(lwWindow->window);
}

void pollEvents() {
    glfwPollEvents();
}

void swapBuffers(LW2DWindow* lwWindow) {
    glfwSwapBuffers(lwWindow->window);
}

void destroyWindow(LW2DWindow* lwWindow) {
    glfwDestroyWindow(lwWindow->window);
    free(lwWindow);
    glfwTerminate();
}

#endif // LW2D_H
