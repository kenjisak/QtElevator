#include "Elevator.h"

Elevator::Elevator(const int& elevnum, const int& maxweight, const int& flrnum){
    this->elevnum = elevnum;
    this->currflrnum = 1;
    this->maxweight = maxweight;
    this->maxcapacity = 5;
    this->currweight = 0;
    this->destflrnum = 0;
    this->flrcount = flrnum;
    this->isidle = true;
    this->safetymsg = "";

    this->display = "";
    this->audioSys = "";
}

Elevator::~Elevator(){
    delete this;
}

int Elevator::getElevNum(){
    return elevnum;
}

bool Elevator::checkidle(){
    return isidle;
}

void Elevator::setidle(bool command){
    isidle = command;
}

int Elevator::getcurrflrnum(){
    return currflrnum;
}

int Elevator::getcurrweight(){
    return currweight;
}
int Elevator::getmaxweight(){
    return maxweight;
}

void Elevator::setsafetymsg(string msg){
    safetymsg = msg;
}

string Elevator::move(string direction){
    if (direction == "up"){
        currflrnum += 1;//commanded to move up by 1 floor
    }else{
        currflrnum -= 1;//commanded to move down by 1 floor
    }
    displayandplaysafetymsg();//updates display and plays audio msg if its not empty
    return "\nCar " + to_string(elevnum) + " Display: Floor " + to_string(currflrnum); //shows updated movement
}

string Elevator::ringbell(){
    return "\nCar " + to_string(elevnum) + " Bell Rings.";
}

string Elevator::closeDoor(){
    string returnthis = ringbell() + "\nCar " + to_string(elevnum) + " Closing its Door.";
//    add delay to interrupt closing?
    returnthis += "\nCar " + to_string(elevnum) + " Door is Closed.";
    return returnthis;
}

string Elevator::openDoor(){
    //add a delay?
    return ringbell() + "\nCar " + to_string(elevnum) + " Opened its Door for 5s.";
}

string Elevator::holdOpenDoor(){
    return ringbell() + "\nCar " + to_string(elevnum) + " held Open its Door";
}

string Elevator::interruptclose(){
    string returnthis = "";
    returnthis += ringbell() + "\nCar " + to_string(elevnum) + " Closing its Door.";
    returnthis += "\nCar " + to_string(elevnum) + " Obstacle in the Way.";
    returnthis += openDoor();
    returnthis += closeDoor();
    return returnthis;
}

string Elevator::displayandplaysafetymsg(){

    display = "\nDisplay: Floor " + to_string(currflrnum) + " "+ safetymsg;//updates its display with safetymessage if there is any
    audioSys = "\nAudio: *" + safetymsg + "*";//if there is any to play.
    if (safetymsg == ""){//if empty safetymsg dont play audio
        return display;
    }
    return display + audioSys;//else play audio and display
}

void Elevator::addPassengers(int passweight){
    currweight += passweight;//updates elev weight to add in passenger
}

void Elevator::rmvPassengers(int passweight){
    if (currweight != 0){
        currweight -= passweight;//updates elev weight to remove passenger
    }
}
