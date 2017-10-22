//
// Created by Np on 2017-10-03.
//

#include <random>
#include "Boid.h"
#include <GLFW/glfw3.h>
#include <iostream>


//Seed and intialize only once
std::random_device rd;
std::mt19937 e2(rd());


int Boid::boidID = 0;



Boid::Boid() {

    std::cout << "Boid class constructor" << std::endl;

    boidID++;


    iD = boidID;


    std::uniform_real_distribution<> xCordinate(-0.2, 0.2);
    std::uniform_real_distribution<> yCordinate(-0.2, 0.2);

    position(0) =xCordinate(e2);
    position(1) =yCordinate(e2);


    x =  position(0);
    y = position(1);

    //speed = 1;
/*

    std::cout << "vector" <<  position << std::endl;

    std::cout << "x -> " << x << std::endl;
    std::cout << "y -> " << y << std::endl;
*/




}

Boid::Boid(float r, float g, float b) : r(r), g(g), b(b) {

    boidID++;


    iD = boidID;


    velocity(0)=0.001;
    velocity(1)=0.001;



    //randomise position

    std::uniform_real_distribution<> xCordinate(-1, 1);
    std::uniform_real_distribution<> yCordinate(-1, 1);

    //std::uniform_real_distribution<> speedVal(0.1, 0.03);


    position(0) =xCordinate(e2);
    position(1) =yCordinate(e2);


    x =  position(0);
    y = position(1);


}



Boid::~Boid() {


    std::cout << "boids dead " << std::endl;

}


float Boid::getSpeed() const {
    return speed;
}

void Boid::setSpeed(float speed) {
    Boid::speed = speed;
}

void Boid::drawBoid() {


    Eigen::Vector2f temp;
    temp(0) = x;
    temp(1) = y;

    //std::cout<< velocity << "velocity! "<< std::endl;

    //move left n right
   if (boidLeft) {
        if (x > (-1 + 0.01)){
            x -= velocity.norm();
        }
        else {
            boidLeft = false;
        }
    }
    else {
        if (x < (1-0.01)) {
            x += velocity.norm();
        }
        else {
            boidLeft = true;
        }
    }

    //move up n down
    if (boidDown) {
        if (y > (-1+0.01)) {
            y -= velocity.norm();
        }
        else {
            boidDown = false;
        }
    }
    else {
        if (y < (1 - 0.01)) {
            y += velocity.norm();
        }
        else {
            boidDown = true;
        }
    }
    position(0) = x;
    position(1) = y;

/*
    dot = x1*x2 + y1*y2      # dot product between [x1, y1] and [x2, y2]
    det = x1*y2 - y1*x2      # determinant
    angle = atan2(det, dot)  # atan2(y, x) or atan2(sin, cos)*/

    //activate for possible bonus marks

    /*float dot = velocity.dot(position);
    float det = (velocity(1)*position(0)) - (velocity(0)*position(1));
    float rad = atan2(det, dot);*/

/*


    float result = (atan (abs(velocity(1))/abs(velocity(0)))) + (270 * (3.141592653589793238462643383279502884197169399375105820/180));

    float degrees = (result * (180 /3.141592653589793238462643383279502884197169399375105820));

    // std::cout << angle << std::endl;

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(degrees, 0.0, 0.0, 1.0);
    glTranslatef(-x, -y, 0);

*/


    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);

    //glColor3f();
    glVertex2f(0  + x,0.01 + y);
    glVertex2f(-0.01 + x,  -0.01 +y);
    glVertex2f(0.01 + x, -0.01 + y);

    glEnd();

    glPopMatrix();



}

const Eigen::Vector2f &Boid::getPosition() const {
    return position;
}

void Boid::setPosition(const Eigen::Vector2f &position) {

    //mutex lock (std::mutex, std::unique_lock);

    x = position(0);
    y = position(1);

    Boid::position = position;
}

const Eigen::Vector2f &Boid::getFuturePosition() const {
    return futurePosition;
}

void Boid::setFuturePosition(const Eigen::Vector2f &futurePosition) {
    Boid::futurePosition = futurePosition;
}

const Eigen::Vector2f &Boid::getVelocity() const {
    return velocity;
}

void Boid::setVelocity(const Eigen::Vector2f &velocity) {
    Boid::velocity = velocity;
}

void Boid::operator()() {


   std::cout << "hELLOO" << std::endl;

}



