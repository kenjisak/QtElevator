#include "Floor.h"

Floor::Floor(const int& name){
    this->flrnum = name;
    this->upBtn = new Button("up");
    this->downBtn = new Button("down");

    for (int i = 0;i < 5;i++){
        this->passengers[i] = new Passenger("pass" + to_string(i),100);
    }
}

Floor::~Floor(){
    delete upBtn;
    delete downBtn;
    for (int i = 1;i <= 5;i++){
        delete passengers[i];
    }
    delete this;
}

int Floor::getflrnum(){
    return flrnum;
}


void Floor::notify(string direction){
    
}

void Floor::arrived(string direction){
    
}

void Floor::addPassengers(){
    
}
void Floor::rmvPassengers(){
    
}