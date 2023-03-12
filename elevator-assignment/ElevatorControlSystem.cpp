#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem(const int& elevnum,const int& flrnum,const int& maxweight){
    for (int i = 0;i < flrnum;i++){
        this->floors[i] = new Floor(i+1);
    }

    for (int i = 0;i < elevnum;i++){
        this->elevators[i] = new Elevator(i+1,maxweight,flrnum);
    }
}

ElevatorControlSystem::~ElevatorControlSystem(){
    delete this;
}

void ElevatorControlSystem::flrreq(string direction,int serveflrnum){

}
void ElevatorControlSystem::atnewflr(int flrnum, int elevnum){

}
void ElevatorControlSystem::elevreq(int destflrnum,int elevnum){

}
void ElevatorControlSystem::elevreq(string safetyissue, int elevnum){

}
void ElevatorControlSystem::opportunisticstrat(){

}


