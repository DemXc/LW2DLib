LW2DLib is a lightweight library for creating games, the library is based on GLFW, you can easily create games in it

LW2D Window Creation Guide
To create and manage a window in LW2D, follow these steps:
1. Include the LW2D Header
Start by importing the LW2D library at the beginning of your program:
#include "lw2d.h"  

2. Initialize Main Function
Declare your main function:
int main() {

3. Create a Window
Use the CreateWindow function to create a window. Specify the width, height, and title:
    LW2DWindow* window = CreateWindow(800, 600, "LW2D Example");

4. Main Rendering Loop
Write a loop to continuously render frames until the window should close:
    while (!shouldClose(window)) {  
        // Set the background color to black  
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
        glClear(GL_COLOR_BUFFER_BIT);  

        // Draw a cube on the screen  
        drawCube();  

        // Handle user input and events  
        pollEvents();  

        // Swap buffers to display the rendered frame  
        swapBuffers(window);  
    }

5. Destroy the Window
Once the rendering loop exits, destroy the window to free resources:
    destroyWindow(window);

6. Exit the Program
Return control to the operating system:

    return 0;  

}  

LW2D Cube Rendering and Controls
This section covers how to render a 2D cube and control its movement using keyboard input in LW2D.

1. Define Cube Position
Declare global variables to store the cube's position

float cubePosX = 0.0f;  
float cubePosY = 0.0f;  


2. Rendering the Cube
Define the drawCube function to render the cube at the specified position:

void drawCube() {  
    glColor3f(1.0f, 0.0f, 0.0f); // Set cube color to red  
    glPushMatrix();  
    glTranslatef(cubePosX, cubePosY, 0.0f); // Move cube to its current position  

    glBegin(GL_QUADS);  
        glVertex2f(-0.2f, -0.2f); // Bottom-left corner  
        glVertex2f( 0.2f, -0.2f); // Bottom-right corner  
        glVertex2f( 0.2f,  0.2f); // Top-right corner  
        glVertex2f(-0.2f,  0.2f); // Top-left corner  
    glEnd();  

    glPopMatrix();  
}  

This function:

Sets the cube's color to red using glColor3f.
Uses glPushMatrix and glPopMatrix to isolate transformations.
Applies a translation with glTranslatef to position the cube.
Draws the cube as a quadrilateral using glBegin and glEnd.

3. Keyboard Input for Movement
Define a callback function to handle key presses and move the cube:

void customKeyCallback(int key, int scancode, int action, int mods) {  
    (void)scancode;  
    (void)mods;  

    if (action == LW2D_PRESS) {  
        if (key == LW2D_KEY_W)  
            cubePosY += 0.1f; // Move up  
        else if (key == LW2D_KEY_S)  
            cubePosY -= 0.1f; // Move down  
        else if (key == LW2D_KEY_A)  
            cubePosX -= 0.1f; // Move left  
        else if (key == LW2D_KEY_D)  
            cubePosX += 0.1f; // Move right  
    }  
}  

This function:

Listens for key press events.
Updates the cube's position (cubePosX, cubePosY) based on W, A, S, D inputs.

4. Register the Callback
Ensure the customKeyCallback function is registered with the LW2D system in your main function:

setKeyCallback(customKeyCallback);  


Complete Example with Cube Rendering and Movement

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
    LW2DWindow* window = CreateWindow(800, 600, "LW2D Example");  
    setKeyCallback(customKeyCallback);  

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



![image](https://github.com/user-attachments/assets/b1175116-e84f-423f-8184-238179eb82a8)
