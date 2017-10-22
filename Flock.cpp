//
// Created by Np on 2017-10-03.
//

#include <random>
#include <iostream>
#include <thread>
#include "Flock.h"
using namespace Eigen;

float Flock::rgb = 0.15;

std::random_device rd2;
std::mt19937 e23(rd2());


Flock::Flock(int numOfBoids) {


    for (int i=0; i <numOfBoids; i++){
        auto * boid = new Boid(0.1+rgb,0.045+rgb,0.4+rgb);
        flock.push_back(boid);


    }




    rgb += rgb;

}

Flock::~Flock() {

    //std::cout << "flcoks dead" << std::endl;

}

const std::vector<Boid *> &Flock::getFlock() const {
    return flock;
}

void Flock::setFlock(const std::vector<Boid *> &flock) {
    Flock::flock = flock;
}
//just to test OPENGL
void Flock::randomisePosition() {

    for (auto &i : flock) {
        std::uniform_real_distribution<> xCordinate(-1, 1);
        std::uniform_real_distribution<> yCordinate(-1, 1);

        Vector2f newPosition;
        newPosition(0) = xCordinate(e23);
        newPosition(1) = yCordinate(e23);

        i->setFuturePosition(newPosition);

    }

}

void Flock::updateBoid() {



    std::thread::id this_id = std::this_thread::get_id();




    Vector2f v1, v2, v3, v4;

    v1(0)=0;
    v1(1)=0;

    v2(0)=0;
    v2(1)=0;

    v3(0)=0;
    v3(1)=0;


    for (auto &i : flock) {

        // Boids try to fly towards the centre of mass of neighbouring boids.
        v1 = cohesion(i);
        //Boids try to keep a small distance away from other objects (including other boids).
        v2 = separation(i);
        //Boids try to match velocity with near boids.
        v3 = alignment(i);


        //boid threads start here?


        i->setVelocity(i->getVelocity() + v1 + v2 + v3);
        limitSpeed(i);


        //threading starts here!!
        Vector2f sendPosition = i->getPosition() + i->getVelocity();
        thread.push_back(new std::thread(init_thread , i, sendPosition));


       // flock[i]->setPosition(flock[i]->getPosition() + flock[i]->getVelocity());
    }


    for (auto &i : thread) {

        i->join();

    }



}
//first rule
Eigen::Vector2f Flock::cohesion(Boid *boidj) {


    Vector2f pcJ; //Pecived center, to get the average of all the birds except the guy using
    pcJ(0) = 0;
    pcJ(1) = 0;

    int neighbour = 0;
    Vector2f currentBoidPosition = boidj->getPosition();
    Vector2f otherBoidsPosition;

    //boidsPosition.

    for (auto &i : flock) {


        if (i != boidj) {
            otherBoidsPosition = i->getPosition();
            pcJ(0) += otherBoidsPosition(0);
            pcJ(1) += otherBoidsPosition(1);
            neighbour++;

        }

    }

    //std ::cout << neighbour << std::endl;
    //Take the average of the position

    pcJ(0) = (pcJ(0)/neighbour);
    pcJ(1) = (pcJ(1)/neighbour);

    Vector2f newDirection;
    newDirection(0) = (pcJ(0) - boidj->getPosition()(0))/120;
    newDirection(1) = (pcJ(1) - boidj->getPosition()(1))/120;



    return newDirection;


}

Eigen::Vector2f Flock::separation(Boid *boidj) {

    Vector2f c;
    c(0)=0;
    c(1)=0;

    Vector2f k;
    k(0) = 0.2;
    k(1) = 0.2;

    for (auto &i : flock) {
        if (i !=  boidj){
            if ( (i->getPosition() - boidj->getPosition()).norm() < 0.06){
                c = c - (i->getPosition() - boidj->getPosition());
            }
        }

    }


    return c;


}

Eigen::Vector2f Flock::alignment(Boid *boidj) {


    Vector2f pvJ; //Pecived center, to get the average of all the birds except the guy using
    pvJ(0) = 0;
    pvJ(1) = 0;

    int neighbour = 0;
    //Vector2d keepAway(0.1, 0.1);
    Vector2f currentBoidPosition = boidj->getPosition();
    Vector2f otherBoidsVelocity;

    //boidsPosition.

    for (auto &i : flock) {


        if (i != boidj) {
            otherBoidsVelocity = i->getVelocity();
            pvJ(0) += otherBoidsVelocity(0);
            pvJ(1) += otherBoidsVelocity(1);
            neighbour++;

        }

    }

    //std ::cout << neighbour << std::endl;
    //Take the average of the position

    pvJ(0) = (pvJ(0)/neighbour);
    pvJ(1) = (pvJ(1)/neighbour);

    Vector2f newVelocity;

    newVelocity(0) = (pvJ(0) - boidj->getVelocity()(0))/10;
    newVelocity(1) = (pvJ(1) - boidj->getVelocity()(1))/10;



    return newVelocity;

}

void Flock::limitSpeed(Boid *boid) {
  // For a limiting speed vlim:

   // PROCEDURE limit_velocity(Boid b)
    float vlim = 0.008;
    Vector2f newVelocity = boid->getVelocity();




    if (boid->getVelocity().norm() > vlim) {
        newVelocity(0) = ((boid->getVelocity()(0) / boid->getVelocity().norm() ) * vlim);
        newVelocity(1) = ((boid->getVelocity()(1) / boid->getVelocity().norm() ) * vlim);

    }

    boid->setVelocity(newVelocity);


    //std::cout<<"======\n" << boid->getVelocity() <<std::endl;
}

Eigen::Vector2f Flock::boundPosition(Boid* boid) {
/*
    float Xmin, Xmax, Ymin, Ymax;
    Vector2f v;

    if( boid->getPosition()(0) < Xmin){
        v.x = 10
    }

    else if( boid->getPosition()(0) > Xmax ) {
        v.x = -10
    }
    END IF
    IF b.position.y < Ymin THEN
    v.y = 10
    ELSE IF b.position.y > Ymax THEN
    v.y = -10
    END IF
    IF b.position.z < Zmin THEN
    v.z = 10
    ELSE IF b.position.z > Zmax THEN
    v.z = -10
    END IF


    return Eigen::Vector2f();*/
}

void Flock::init_thread(Boid* boid, Eigen::Vector2f newPosition) {


    boid->setPosition(newPosition);



   // std::cout << "Threads chilling"  << std::endl;



}


