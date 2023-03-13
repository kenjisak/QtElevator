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

int ElevatorControlSystem::flrreq(string direction,int serveflrnum){//when an up or down button from the floor is pressed, this finds an elev and sends it there
    //if up then find a non moving elev and make it move to the serveflrnum
    int idleelevnum = -1;//init so if no idle elevator found theyre all in use atm

    //go through and find an idle elevator thats possibly on the same floor already
//    for(int i = 0; i < numofelevs;i++){
//        if (elevators[i]->checkidle() == true && elevators[i]->getcurrflrnum() == serveflrnum){
//            idleelevnum = i;
//            break;
//        }
//    }
//    if(idleelevnum == -1){ //if elevator not found then find any idle elevator
//        for(int i = 0; i < numofelevs;i++){
//            if (elevators[i]->checkidle() == true){
//                idleelevnum = i;
//                break;
//            }
//        }
//    }
    for(int i = 0; i < numofelevs;i++){//go through and find an idle elevator this section is the alloc strategy of alloc a elev to a floor
        if (elevators[i]->checkidle() == true){
            idleelevnum = i;
            break;
        }
    }

    if (idleelevnum != -1){ // if an elevator is found
        while (serveflrnum != elevators[idleelevnum]->getcurrflrnum()){//make the elevator move up or down until it reaches the floor that called one
            elevators[idleelevnum]->setidle(false);//elevator is no longer idle and is moving/serving a passenger
            if(elevators[idleelevnum]->getcurrflrnum() < serveflrnum){// if the elevator is on a floor below the service floor
                elevators[idleelevnum]->move("up");
            }else{// if the elevator is on a floor above the service floor
                elevators[idleelevnum]->move("down");
            }
        }
        return elevators[idleelevnum]->getElevNum();//return the elevator number that reaches the service floor //error here
    }else{//else we didnt find an elevator so just return -1
        return -1;
    }
}

string ElevatorControlSystem::safetyreq(string safetyissue){
    string returnallactions = "";
    int safefloor = 1;
    if (safetyissue == "fire" || "powerout"){
        //send all elevators to floor 1 as safe floor
        //send safety messages to elevator to update its display and audio
        //once elevators reached safe floor return true
        //so it only plays once but doesnt show for each elev but tis still updated
        returnallactions += "\nDisplay: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";
        returnallactions += "\nAudio: Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.";

        for(int i = 0; i < numofelevs;i++){//go through and make all elevators move to safe floor
            elevators[i]->setsafetymsg("Theres a " + safetyissue + " in the building, please disembark the elevator once the elevators reach the main floor.");
            while (safefloor != elevators[i]->getcurrflrnum()){//make the elevator move up or down until it reaches the safe floor
                if(elevators[i]->getcurrflrnum() < i){// if the elevator is on a floor below the safe floor
                    returnallactions += elevators[i]->move("up");
                }else{// if the elevator is on a floor above the safe floor
                    returnallactions += elevators[i]->move("down");
                }
            }
            //once there open it rings and opens its doors

            returnallactions += elevators[i]->openDoor();
        }
    }
    return returnallactions;//return all appended actions instead
}
