
#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Button {

	public:
		//constructor
		Button(const string& btnname);

		//destructor
		~Button();

		//getters
		string getbtnname();
		bool getstatus();
		bool getlight();
		
		//other
		void press();//uses illluminate if its an up or down btn, if close it doesnt, if btnname is help or fire then uses alarm()
		void hold(int numsecs);//hold open door for num of secs
		void illuminate(bool);//illuminates the button

	private:
		string btnname;//up,down,hold,close
		bool status;//true = pressed/hold, false = inactive
		bool light;//for illuminated
};
#endif
