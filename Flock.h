//
// Created by Np on 2017-10-03.
//

#ifndef BOIDS_ALGORITHM_FLOCK_H
#define BOIDS_ALGORITHM_FLOCK_H


#include <vector>
#include "Boid.h"
#include <Eigen/Dense>
#include <thread>



class Flock {
private:
    std::vector <Boid*> flock;
    //color the flocks
    static float rgb;
    std::vector<std::thread* >thread;
    int rc;
    //std::mutex g_display_mutex;


public:


    Flock(int numOfBoids);

    virtual ~Flock();

    const std::vector<Boid *> &getFlock() const;

    void setFlock(const std::vector<Boid *> &flock);

    void randomisePosition();


    void updateBoid();

    Eigen::Vector2f cohesion(Boid *pBoid);

    Eigen::Vector2f separation(Boid *pBoid);

    Eigen::Vector2f alignment(Boid *boid);

    //supporting methods
    void limitSpeed(Boid *boid);
    Eigen::Vector2f boundPosition(Boid *boid);


   static void init_thread(Boid* boid, Eigen::Vector2f newPostion);
};


#endif //BOIDS_ALGORITHM_FLOCK_H
