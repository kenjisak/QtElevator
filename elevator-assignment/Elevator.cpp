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

    this->door = new Door();
    this->openBtn = new Button("open");
    this->closeBtn = new Button("close");
    this->helpBtn = new Button("help");
    this->fireBtn = new Button("fire");

    this->display = "";
    this->audioSys = "";

    for (int i = 0;i < 5;i++){
        this->passengers[i] = NULL;//when adding and removing passengers, maybe just copy the object into this array?
    }

    destBtns = new Button*[flrnum];
    for (int i = 0;i < flrnum;i++){
        destBtns[i] = new Button(to_string(i+1));
    }
}

Elevator::~Elevator(){
    delete door;
    delete openBtn;
    delete closeBtn;
    delete helpBtn;
    delete fireBtn;

    for (int i = 0;i < 5;i++){
        delete passengers[i];
    }

    for (int i = 0;i < flrcount;i++){
        delete destBtns[i];
    }
}

int Elevator::getElevNum(){
    return elevnum;
}

void Elevator::closeDoor(){
    door->close();
}

void Elevator::openDoor(){
    door->open();
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

void Elevator::setsafetymsg(string msg){
    safetymsg = msg;
}

void Elevator::move(string direction){
    if (direction == "up"){
        currflrnum += 1;//commanded to move up by 1 floor
    }else{
        currflrnum -= 1;//commanded to move down by 1 floor
    }

    display = to_string(currflrnum) + safetymsg;//updates its display with safetymessage if there is any
    audioSys += safetymsg;//if there is any to play.
}



