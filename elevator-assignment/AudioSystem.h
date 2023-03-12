
#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class AudioSystem {
		
	public:
		//constructor
		AudioSystem();
		//destructor
		~AudioSystem();

		//getters
		string getmsg();	
		//other
        void play(string msg);//play any message given, like safety messages
	
	private:
		string msg;
};
#endif
