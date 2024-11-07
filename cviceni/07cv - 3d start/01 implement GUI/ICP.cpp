// icp.cpp 
// author: JJ

// our awesome headers
#include "App.hpp"

// define our application
App app;

// MAIN program function
int main()
{
	if (app.init())
		return app.run();
}

/* */