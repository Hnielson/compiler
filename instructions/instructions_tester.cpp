#include <iostream>
#include "instructions.h"

using namespace std;

int main()
{
	InstructionsClass myInstructions;
	//myInstructions.PushValue(1000);
	//myInstructions.PopAndWrite(); // prints 1000
	//myInstructions.PushVariable(10);
	//myInstructions.PopAndWrite();
	myInstructions.PushVariable(10);
	myInstructions.PopAndStore(11);
	myInstructions.PushVariable(10);
	myInstructions.PushVariable(11);
	myInstructions.PopPopAddPush();
	myInstructions.PopAndWrite();
	myInstructions.Finish();
	myInstructions.Execute();
	cout << "Finished instructions testing." << endl;
}