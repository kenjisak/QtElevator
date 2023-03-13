#include "Button.h"

Button::Button(const string& btnname){
    this->btnname = btnname;
    this->status = false;
    this->light = false;
}

Button::~Button(){
    delete this;
}

string Button::getbtnname(){
    return btnname;
}

bool Button::getstatus(){
    return status;
}

bool Button::getlight(){
    return light;
}

void Button::press(){
    //once this button is pressed, illuminate its light, ui will print its action. return strings to print out of actions?
    status = true;
    illuminate(true);
}

void Button::hold(int numsecs){
    //if its the open door button then prints open for 1-numsecs and closes the door

}

void Button::illuminate(bool status){
    light = status;
}
