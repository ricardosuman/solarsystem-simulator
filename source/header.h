#ifndef PI6_MAINHEADER_H
	#define PI6_MAINHEADER_H

	#ifdef __APPLE__
		#include <GLUT/glut.h>
	#elif __linux__
		#include <GL/glut.h>
	#else // _WIN32
		#include "glut.h"
		#include <windows.h>
	#endif

	#include <iostream>
	#include <math.h>
	#include <time.h>

	#include "setup.h"

	#include "utils.h"
	#include "body.h"

	#include "functions.h"
	

	using namespace std;
#endif 