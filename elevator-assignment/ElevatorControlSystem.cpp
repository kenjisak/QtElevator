#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight){

    this->numofflrs = flrnum;
    this->numofelevs = elevnum;

    floors = new Floor*[flrnum];
    for (int i = 0;i < flrnum;i++){
        floors[i] = new Floor(i+1);
    }

    elevators = new Elevator*[elevnum];
    for (int i = 0;i < elevnum;i++){
        elevators[i] = new Elevator(i+1,maxweight,flrnum);
    }
}

ElevatorControlSystem::~ElevatorControlSystem(){
    delete this;
}

Floor** ElevatorControlSystem::getflrarr(){
    return floors;
}

Elevator** ElevatorControlSystem::getelevarr(){
    return elevators;
}

void ElevatorControlSystem::flrreq(string direction,int serveflrnum){//when an up or down button from the floor is pressed, this finds an elev and sends it there
    //if up then find a non moving elev and make it move to the serveflrnum
    int idleelevnum;
    if(direction == "up"){
        //go through and find an idle/non moving elevator
        for(int i = 0; i < numofelevs;i++){
            if (elevators[i]->checkidle() == true){
                idleelevnum = i;
                break;
            }
        }

        while (serveflrnum != elevators[idleelevnum]->getcurrflrnum()){//make the elevator move up or down until it reaches the floor that called one
            if(elevators[idleelevnum]->getcurrflrnum() < serveflrnum){// if the elevator is on a floor below the service floor
                elevators[idleelevnum]->move("up");
            }else{// if the elevator is on a floor above the service floor
                elevators[idleelevnum]->move("down");
            }
        }


    }
}
void ElevatorControlSystem::atnewflr(int flrnum, int elevnum){

}
void ElevatorControlSystem::elevreq(int destflrnum,int elevnum){

}
void ElevatorControlSystem::elevreq(string safetyissue, int elevnum){

}
void ElevatorControlSystem::opportunisticstrat(){

}


