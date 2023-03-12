#include "Display.h"

Display::Display():safetymsg(""),currflr(1),currmsg("1"){}

Display::~Display(){
    delete this;
}

string Display::getsafetymsg(){
    return safetymsg;
}

int Display::getcurrflr(){
    return currflr;
}

void Display::showmsg(string msg){
    
}

void Display::updatecurrflr(int flrnum){
    
}