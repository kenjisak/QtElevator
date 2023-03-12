
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Display {
		
	public:
		//constructor
		Display();

		//destructor
		~Display();

		//getters
		string getsafetymsg();
		int getcurrflr();
		
		//other
        void showmsg(string msg);//displays any messages,safety or wtv
		void updatecurrflr(int flrnum);//updates the current floor for display, its always displayed
	
	private:
		string safetymsg;//empty or has safety message
        int currflr;
		string currmsg;//always shows currflr, appends safety msg if activated
};
#endif
