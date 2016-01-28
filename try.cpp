#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const int gridSize = 32;

const int SCREEN_WIDTH = gridSize*32;
const int SCREEN_HEIGHT = gridSize*16;

static void inputK(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

int main(void){
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MSSIN_no", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, inputK);

    while (!glfwWindowShouldClose(window)){
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();


        glOrtho(0, width, height, 0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    //attempt to draw lines
    glBegin(GL_LINES);
    //horizontal
    for (int i = 0; i < SCREEN_HEIGHT; i+=gridSize){
        glVertex2f(0, i);
        glVertex2f(SCREEN_WIDTH,i);
    }
    //vertical
    for (int i = 0; i < SCREEN_WIDTH; i += gridSize){
        glVertex2f(i,0);
        glVertex2f(i, SCREEN_HEIGHT);
    }
    glEnd();


    glfwSwapBuffers(window);
    glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

