#include "Floor.h"

Floor::Floor(const int& name){
    this->flrnum = name;
    this->upBtn = new Button("up");
    this->downBtn = new Button("down");
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
