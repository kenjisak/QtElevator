#include "Door.h"

Door::Door():status(false){}

Door::~Door(){
    delete this;
}

bool Door::getstatus(){
    return status;
}

void Door::open(){
    status = true;
}

void Door::close(){
    status = false;
}
