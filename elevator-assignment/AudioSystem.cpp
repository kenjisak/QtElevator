#include "AudioSystem.h"

AudioSystem::AudioSystem():msg(""){}

AudioSystem::~AudioSystem(){
    delete this;
}

string AudioSystem::getmsg(){
    return msg;
}

void AudioSystem::play(string msg){
    this->msg = msg;//is set as the message to play on audio, but need to display it in syslog, then in mainwindow, reset the msg when needed back to empty
}