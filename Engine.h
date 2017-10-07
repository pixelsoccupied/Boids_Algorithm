//
// Created by Np on 2017-10-03.
//



#ifndef BOIDS_ALGORITHM_ENGINE_H
#define BOIDS_ALGORITHM_ENGINE_H


#include <iostream>
#include <GLFW/glfw3.h>
#include "Boid.h"
#include "Flock.h"


class Engine {
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    // static float getDT();

    Engine();
    ~Engine();

    bool initialize(char* windowTitle);

    void update();
    void render(std::vector<Flock> flock);

    static double limitFPS ;

    double lastTime = glfwGetTime(), timer = lastTime;
    double deltaTime = 0, nowTime = 0;
    int frames = 0 , updates = 0;

    std::mutex mtx;
    // bool init = true;

    static void renderThread(Flock flock);


private:
    static GLFWwindow* window;

    //  static float dt;
    std::vector<std::thread*>threads;
    std::vector<Flock> flock;


    void startFlockThreads();
};


#endif //BOIDS_ALGORITHM_ENGINE_H
