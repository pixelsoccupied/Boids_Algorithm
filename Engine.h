//
// Created by Np on 2017-10-03.
//



#ifndef BOIDS_ALGORITHM_ENGINE_H
#define BOIDS_ALGORITHM_ENGINE_H


#include <iostream>
#include <GLFW/glfw3.h>
#include "Boid.h"
#include "Flock.h"
#include "FlockPool.h"


class Engine {
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    // static float getDT();

    Engine(int i);
    ~Engine();

    bool initialize(char* windowTitle);

    void update();
    void render(std::vector<Flock> flock);

    static double limitFPS ;

    double lastTime = glfwGetTime(), timer = lastTime;
    double changeInTime = 0, currentTime = 0;
    int frames = 0 , updates = 0;

    std::mutex mtx;
    // bool init = true;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

    static GLFWwindow *getWindow();

    static void setWindow(GLFWwindow *window);

public:
    static GLFWwindow* window;
    FlockPool flockPool;

};


#endif //BOIDS_ALGORITHM_ENGINE_H
