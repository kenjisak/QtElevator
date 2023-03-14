#include "Passenger.h"

Passenger::Passenger(const int& number,const int& weight){
    this->number = number;
    this->weight = weight;
}

Passenger::~Passenger(){
    delete this;
}

int Passenger::getNum(){
    return number;
}

int Passenger::getWeight(){
    return weight;
}

void Passenger::walk(string direction,int elevnum){
    
}

void Passenger::press(int destflrnum){
    
}

void Passenger::press(string btn){
    
}
