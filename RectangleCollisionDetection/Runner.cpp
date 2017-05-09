// Runner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MainFlow.h"

int main(int argc, char* argv[])
{
	//command line argument in is the file name.

	std::string charactersFilename(argv[1]);

	MainFlow ne;
	auto successful = ne.PerformExercise(charactersFilename);

	if (successful)
		cout << "\n" << "Successful end of program.";
	else
		cout << "\n" << "Unsuccessful.";

    return 0;
}


