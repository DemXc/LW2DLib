#ifndef LW2D_H
#define LW2D_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


#define LW2D_PRESS 1
#define LW2D_RELEASE 0
#define LW2D_REPEAT 2


#define LW2D_KEY_W GLFW_KEY_W
#define LW2D_KEY_S GLFW_KEY_S
#define LW2D_KEY_A GLFW_KEY_A
#define LW2D_KEY_D GLFW_KEY_D

typedef struct {
    GLFWwindow* window;
    void (*key_callback)(int, int, int, int);
} LW2DWindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

int convertActionToLW2D(int action) {
    switch (action) {
        case GLFW_PRESS: return LW2D_PRESS;
        case GLFW_RELEASE: return LW2D_RELEASE;
        case GLFW_REPEAT: return LW2D_REPEAT;
        default: return -1;
    }
}

void internal_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    LW2DWindow* lwWindow = (LW2DWindow*)glfwGetWindowUserPointer(window);
    if (lwWindow && lwWindow->key_callback) {
        int lw2d_action = convertActionToLW2D(action);
        if (lw2d_action != -1) {
            lwWindow->key_callback(key, scancode, lw2d_action, mods);
        }
    }
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
        free(lwWindow);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(lwWindow->window);
    glfwSetFramebufferSizeCallback(lwWindow->window, framebuffer_size_callback);
    glfwSetWindowUserPointer(lwWindow->window, lwWindow);
    lwWindow->key_callback = NULL;
    glfwSetKeyCallback(lwWindow->window, internal_key_callback);

    return lwWindow;
}

void setKeyCallback(LW2DWindow* lwWindow, void (*callback)(int, int, int, int)) {
    lwWindow->key_callback = callback;
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
