#include "Elevator.h"

Elevator::Elevator(const int& elevnum, const int& maxweight, const int& flrnum){
    this->elevnum = elevnum;
    this->currflrnum = 1;
    this->maxweight = maxweight;
    this->maxcapacity = 5;
    this->destflrnum = NULL;
    this->flrcount = flrnum;
    this->isnotmoving = true;
    this->alarmmode = "";

    this->door = new Door();
    this->openBtn = new Button("open");
    this->closeBtn = new Button("close");
    this->helpBtn = new Button("help");
    this->fireBtn = new Button("fire");

    this->display = new Display();
    this->audioSys = new AudioSystem();

    for (int i = 0;i < 5;i++){
        this->passengers[i] = NULL;//when adding and removing passengers, maybe just copy the object into this array?
    }

    for (int i = 0;i < flrnum;i++){
        this->destBtns[i] = new Button(to_string(i+1));
    }
}

Elevator::~Elevator(){
    delete door;
    delete openBtn;
    delete closeBtn;
    delete helpBtn;
    delete fireBtn;
    delete display;
    delete audioSys;

    for (int i = 0;i < 5;i++){
        delete passengers[i];
    }

    for (int i = 0;i < flrcount;i++){
        delete destBtns[i];
    }
}
