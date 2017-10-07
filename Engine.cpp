//
// Created by Np on 2017-10-03.
//

#include <zconf.h>
#include "Engine.h"


int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = NULL;

double Engine::limitFPS = 1.0 / 30.0;

Engine::Engine() {

}

Engine::~Engine() {


    glfwDestroyWindow(this->window);
    glfwTerminate();

}

bool Engine::initialize(char *windowTitle) {

    if (!glfwInit())
    {
        std::cout << "Error initializing GLFW" <<std:: endl;
        return false;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error creating window" << std::endl;
        return false;
    }

    //GLFW Setup
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);


    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - SCREEN_WIDTH) / 2;
    int yPos = (mode->height - SCREEN_HEIGHT) / 2;
    glfwSetWindowPos(window, xPos, yPos);


    return true;
}

void Engine::update() {

    // - Measure time
    nowTime = glfwGetTime();
    deltaTime += (nowTime - lastTime) / limitFPS;
    lastTime = nowTime;


    glfwPollEvents();
}




void Engine::render(std::vector<Flock> flock){



    glClearColor(0.2, 0.3, 0.4, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // - Only update at 30 frames / s
    while (deltaTime >= 1.0){
        //update();   // - Update function
        for(int i =0; i<flock.size(); i++) {
            Flock flock1 = flock[i];
            std::thread* t = new std::thread (&Flock::updateBoid, flock1);

            t->join();
            //flock1.updateBoid();
        }

        updates++;
        deltaTime--;
    }


    for(int i =0; i<flock.size(); i++) {
        Flock flock1 = flock[i];
        for (int j=0; j <flock1.getFlock().size(); j++){
            flock1.getFlock()[j]->drawBoid();
        }
    }

    frames++;

    if (glfwGetTime() - timer > 1.0) {
        timer ++;
        //std::cout << "Thread vector size - " << threads.size() << std::endl;

        std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
        updates = 0, frames = 0;
    }


    glfwSwapBuffers(window);





}
