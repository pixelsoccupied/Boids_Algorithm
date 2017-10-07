//
// Created by Np on 2017-10-03.
//

#ifndef BOIDS_ALGORITHM_BOID_H
#define BOIDS_ALGORITHM_BOID_H

#include <Eigen/Dense>
class Boid {

    //using namespace Eigen;
private:
    float r = 0.0;
    float g = 0.3;
    float b = 0.6;
    float x;
    float y;
    Eigen::Vector2f position;
    Eigen::Vector2f velocity;
    bool boidLeft = true;
    bool boidDown = true;
    float speed;
    static int boidID;
    int iD;




    Eigen::Vector2f futurePosition;
public:
    const Eigen::Vector2f &getFuturePosition() const;

    void setFuturePosition(const Eigen::Vector2f &futurePosition);

    const Eigen::Vector2f &getVelocity() const;

    void setVelocity(const Eigen::Vector2f &velocity);



public:
    Boid();

    Boid(float r, float g, float b);

    virtual ~Boid();

    float getSpeed() const;

    void setSpeed(float speed);

    void drawBoid();

    const Eigen::Vector2f &getPosition() const;

    void setPosition(const Eigen::Vector2f &position);

    //functor operator overloading

    void operator()();



};


#endif //BOIDS_ALGORITHM_BOID_H
