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

string Elevator::move(string direction){
    if (direction == "up"){
        currflrnum += 1;//commanded to move up by 1 floor
    }else{
        currflrnum -= 1;//commanded to move down by 1 floor
    }
    displayandplaysafetymsg();//updates display and plays audio msg if its not empty
    return "\nCar " + to_string(elevnum) + " Display: Floor " + to_string(currflrnum); //shows updated movement
}
//have a check for if alarm is on then return audio, maybe
string Elevator::closeDoor(){
    string returnthis = ringbell() + "\nCar " + to_string(elevnum) + " Closing its Door.";
//    add delay to interrupt closing?
    returnthis += "\nCar " + to_string(elevnum) + " Door is Closed.";
    return returnthis;
}

string Elevator::openDoor(){
    string returnthis = "";
    returnthis += ringbell() + "\nCar " + to_string(elevnum) + " Opened its Door for 5s.";
    //add a delay here
    returnthis += closeDoor();
    return returnthis;
}

string Elevator::holdOpenDoor(){
    return ringbell() + "\nCar " + to_string(elevnum) + " held Open its Door";
}

string Elevator::ringbell(){
    return "\nCar " + to_string(elevnum) + " Bell Rings.";
}

string Elevator::interruptclose(){
    string returnthis = "";
    returnthis += ringbell() + "\nCar " + to_string(elevnum) + " Closing its Door.";
    returnthis += "\nCar " + to_string(elevnum) + " Obstacle in the Way.";
    returnthis += openDoor();
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


