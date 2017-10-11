//
// Created by Np on 2017-10-07.
//

#ifndef BOIDS_ALGORITHM_FLOCKPOOL_H
#define BOIDS_ALGORITHM_FLOCKPOOL_H

//#include <tbb/parallel_do.h>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <stack>


class FlockPool {
public:

    std::mutex lock;
    std::condition_variable cond;

    bool isClose;

    std::stack <std::function <void (void)>> jobStack;
    std::vector <std::thread> threadVector;


    FlockPool(int i);
    ~FlockPool ();
    void work (std::function <void ()> func);


private:

    void threadRun (int i);


};


#endif //BOIDS_ALGORITHM_FLOCKPOOL_H
