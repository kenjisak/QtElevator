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
    delete this;
}

int Floor::getflrnum(){
    return flrnum;
}

Button* Floor::getUpBtn(){
    return this->upBtn;
}

Button* Floor::getDownBtn(){
    return this->downBtn;
}
