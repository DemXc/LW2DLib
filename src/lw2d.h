#ifndef LW2D_H
#define LW2D_H

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb/stb_image.h"

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

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life;
} Particle;

typedef struct {
    Particle* particles;
    int count;
    int capacity;
} ParticleSystem;

void addParticle(ParticleSystem* ps, float x, float y, float z) {
    if (ps->count >= ps->capacity) return; // Проверка на переполнение

    float vx = (float)rand() / RAND_MAX - 0.5f;
    float vy = (float)rand() / RAND_MAX - 0.5f;
    float vz = (float)rand() / RAND_MAX - 0.5f;

    ps->particles[ps->count++] = (Particle){x, y, z, vx, vy, vz, 1.0f};
}

void updateParticles(ParticleSystem* ps, float deltaTime) {
    for (int i = 0; i < ps->count; ++i) {
        Particle* p = &ps->particles[i];
        p->x += p->vx * deltaTime;
        p->y += p->vy * deltaTime;
        p->z += p->vz * deltaTime;
        p->life -= deltaTime;
        if (p->life <= 0.0f) {
            // Замена текущей частицы последней и уменьшение количества
            ps->particles[i--] = ps->particles[--ps->count];
        }
    }
}

void renderParticles(const ParticleSystem* ps) {
    glBegin(GL_POINTS);
    for (int i = 0; i < ps->count; ++i) {
        const Particle* p = &ps->particles[i];
        glVertex3f(p->x, p->y, p->z);
    }
    glEnd();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

GLuint LW2D_loadTexture(const char* filename) {
    int width, height;
    printf("Attempting to load texture from: %s\n", filename); // Отладочный вывод

    unsigned char* data = stbi_load(filename, &width, &height, NULL, 0);
    if (!data) {
        printf("Failed to load texture data: %s\n", stbi_failure_reason()); // Отладочный вывод
        return 0;
    }

    printf("Texture loaded successfully: %dx%d\n", width, height); // Отладочный вывод

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
                 GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
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
