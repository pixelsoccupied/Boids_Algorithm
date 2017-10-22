#include <iostream>
#include "Engine.h"






int main() {

    std::cout << "Hello, World!" << std::endl;


    Flock flock(20);
    Flock flock2(10);
    Flock flock3(14);
    Flock flock4(16);
  /*  Flock flock5(20);
    Flock flock6(10);
    Flock flock7(14);
    Flock flock8(16);*/

    std::vector <Flock> flocks= {flock, flock2, flock3, flock4};

    //flock.randomisePosition();

    Engine engine(flocks.size());
    engine.initialize("boid");






    while(!glfwWindowShouldClose(engine.getWindow())){
        engine.update();
        engine.render(flocks);
    }



    std::cout << "This program ends heree" << std::endl;



    return 0;
}