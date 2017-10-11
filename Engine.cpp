//
// Created by Np on 2017-10-03.
//

#include <zconf.h>
#include "Engine.h"


int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow *Engine::window = NULL;

double Engine::limitFPS = 1.0 / 30.0;

Engine::Engine(int numOfFlocks) : flockPool(numOfFlocks) {


}

Engine::~Engine() {


    std:: cout << " Window is closed!" << std::endl;

    glfwDestroyWindow(this->window);
    glfwTerminate();

}

bool Engine::initialize(char *windowTitle) {

    if (!glfwInit()) {
        std::cout << "Error initializing GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL) {
        std::cout << "Error creating window" << std::endl;
        return false;
    }
    glfwSetKeyCallback(window, key_callback);


    //GLFW Setup
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);


    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - SCREEN_WIDTH) / 2;
    int yPos = (mode->height - SCREEN_HEIGHT) / 2;
    glfwSetWindowPos(window, xPos, yPos);




    return true;
}

void Engine::update() {

    //timer starts here
    currentTime = glfwGetTime();
    changeInTime += (currentTime - lastTime) / limitFPS;
    lastTime = currentTime;


    glfwPollEvents();

}


void Engine::render(std::vector<Flock> flock) {


    glClearColor(0.2, 0.3, 0.4, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    //30 frames
    while (changeInTime >= 1.0) {
        // Update function
        for (auto &i : flock) {
            //Flock flock1 = flock[i];
            flockPool.work(std::bind(&Flock::updateBoid, i));

        }

        updates++;
        changeInTime--;
    }


    for (auto flock1 : flock) {
        for (auto j : flock1.getFlock()) {
            j->drawBoid();
        }
    }

    frames++;
    if (glfwGetTime() - timer > 1.0) {
        timer++;
        //std::cout << "Thread vector size - " << threads.size() << std::endl;
        std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
        updates = 0, frames = 0;
    }


    glfwSwapBuffers(window);


}

void Engine::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE || action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

}

GLFWwindow *Engine::getWindow() {
    return window;
}

void Engine::setWindow(GLFWwindow *window) {
    Engine::window = window;
}

