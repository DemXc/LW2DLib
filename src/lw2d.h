#ifndef LW2D_H
#define LW2D_H

#include "stb/stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h> // Используем GLEW для работы с современным OpenGL

#define LW2D_PRESS 1
#define LW2D_RELEASE 0
#define LW2D_REPEAT 2

#define LW2D_KEY_W 87
#define LW2D_KEY_S 83
#define LW2D_KEY_A 65
#define LW2D_KEY_D 68

typedef struct {
    int width, height;
    const char* title;
    void* internal_context; // Хранение контекста платформы
    void (*key_callback)(int, int, int);
} LW2DWindow;

typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint shader_program;
} LW2DRenderContext;

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

// ====== Инициализация и управление окном ======

LW2DWindow* LW2D_createWindow(int width, int height, const char* title);
void LW2D_destroyWindow(LW2DWindow* window);
void LW2D_pollEvents(LW2DWindow* window);
void LW2D_setKeyCallback(LW2DWindow* window, void (*callback)(int, int, int));
bool LW2D_shouldClose(LW2DWindow* window);

// ====== Управление контекстом рендеринга ======

LW2DRenderContext* LW2D_initRenderContext();
void LW2D_clear(float r, float g, float b, float a);
void LW2D_swapBuffers(LW2DWindow* window);

// ====== Частицы ======

void LW2D_addParticle(ParticleSystem* ps, float x, float y, float z);
void LW2D_updateParticles(ParticleSystem* ps, float deltaTime);
void LW2D_renderParticles(const ParticleSystem* ps, const LW2DRenderContext* context);

// ====== Загрузка текстур ======

GLuint LW2D_loadTexture(const char* filename);

// ====== Реализация ======

LW2DWindow* LW2D_createWindow(int width, int height, const char* title) {
    // Инициализация платформозависимого окна и OpenGL контекста
    printf("Creating window: %dx%d, %s\n", width, height, title);

    LW2DWindow* window = (LW2DWindow*)malloc(sizeof(LW2DWindow));
    if (!window) {
        fprintf(stderr, "Failed to allocate memory for LW2DWindow\n");
        exit(EXIT_FAILURE);
    }
    window->width = width;
    window->height = height;
    window->title = title;
    window->key_callback = NULL;

    // Здесь должна быть инициализация контекста (например, EGL, GLX или Cocoa)
    // Пример будет работать на платформозависимом уровне
    return window;
}

void LW2D_destroyWindow(LW2DWindow* window) {
    // Освобождение ресурсов окна
    free(window);
}

void LW2D_pollEvents(LW2DWindow* window) {
    // Обработка событий
    // Реализуйте на уровне системы (например, X11, WinAPI)
}

void LW2D_setKeyCallback(LW2DWindow* window, void (*callback)(int, int, int)) {
    window->key_callback = callback;
}

bool LW2D_shouldClose(LW2DWindow* window) {
    // Проверьте, был ли запрос на закрытие окна
    return false; // Замените на платформозависимую проверку
}

// ====== Рендеринг ======

LW2DRenderContext* LW2D_initRenderContext() {
    LW2DRenderContext* context = (LW2DRenderContext*)malloc(sizeof(LW2DRenderContext));
    if (!context) {
        fprintf(stderr, "Failed to allocate memory for LW2DRenderContext\n");
        exit(EXIT_FAILURE);
    }

    // Инициализация OpenGL объектов
    glGenVertexArrays(1, &context->vao);
    glGenBuffers(1, &context->vbo);
    glGenBuffers(1, &context->ebo);

    // Создание и компиляция шейдеров (реализуйте шейдеры отдельно)
    context->shader_program = glCreateProgram();
    // Пример шейдера должен быть написан и загружен сюда
    return context;
}

void LW2D_clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LW2D_swapBuffers(LW2DWindow* window) {
    // Обмен буферов (например, через платформозависимый вызов)
}

// ====== Управление частицами ======

void LW2D_addParticle(ParticleSystem* ps, float x, float y, float z) {
    if (ps->count >= ps->capacity) return;

    float vx = (float)rand() / RAND_MAX - 0.5f;
    float vy = (float)rand() / RAND_MAX - 0.5f;
    float vz = (float)rand() / RAND_MAX - 0.5f;

    ps->particles[ps->count++] = (Particle){x, y, z, vx, vy, vz, 1.0f};
}

void LW2D_updateParticles(ParticleSystem* ps, float deltaTime) {
    for (int i = 0; i < ps->count; ++i) {
        Particle* p = &ps->particles[i];
        p->x += p->vx * deltaTime;
        p->y += p->vy * deltaTime;
        p->z += p->vz * deltaTime;
        p->life -= deltaTime;
        if (p->life <= 0.0f) {
            ps->particles[i--] = ps->particles[--ps->count];
        }
    }
}

void LW2D_renderParticles(const ParticleSystem* ps, const LW2DRenderContext* context) {
    glBindVertexArray(context->vao);
    glUseProgram(context->shader_program);

    // Загрузите данные частиц в VBO
    glBindBuffer(GL_ARRAY_BUFFER, context->vbo);
    glBufferData(GL_ARRAY_BUFFER, ps->count * sizeof(Particle), ps->particles, GL_DYNAMIC_DRAW);

    // Настройка атрибутов шейдера и отрисовка
    glDrawArrays(GL_POINTS, 0, ps->count);
}

// ====== Текстуры ======

GLuint LW2D_loadTexture(const char* filename) {
    int width, height;
    unsigned char* data = stbi_load(filename, &width, &height, NULL, 4);
    if (!data) {
        fprintf(stderr, "Failed to load texture: %s\n", filename);
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
}

#endif // LW2D_H
