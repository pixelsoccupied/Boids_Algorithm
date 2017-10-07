#include <iostream>
#include "Engine.h"

int main() {

    std::cout << "Hello, World!" << std::endl;


    Flock flock(3);
    Flock flock2(4);
    Flock flock3(5);
    Flock flock4(6);


    std::vector <Flock> flocks= {flock, flock2, flock3, flock4};

    //flock.randomisePosition();

    Engine engine;
    engine.initialize("boid");





    while(true){
        engine.update();
        engine.render(flocks);
    }






    return 0;
}