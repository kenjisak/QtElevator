#include "Passenger.h"

Passenger::Passenger(const string& name,const int& weight){
    this->name = name;
    this->weight = weight;
}

Passenger::~Passenger(){
    delete this;
}

string Passenger::getName(){
    return name;
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