#ifndef PI6_UTILS_H
	#define PI6_UTILS_H

	// assumed scale: 100 pixels = 1AU.
	const long double AU = (149.6e6 * 1000);
	const long double SCALE = 250 / AU;

	// physics
	const long double GRAVITATIONAL_CONSTANT = 6.67 * pow(10, -11);//6.67428e-11;
	const GLfloat PI = 3.1415926535;
	const GLfloat TO_RADIANS = PI / 180.0;
	extern double scale_distance;

	// lights
	const GLfloat LIGHT_0_POSITION[]    = { 1.0, 0.0, 0.0, 0.0};
	const GLfloat LIGHT_1_POSITION[]    = { -1.0, 0.0, 0.0, 0.0};
	const GLfloat LIGHT_2_POSITION[]    = { 0.0, 0.0, 1.0, 0.0};
	const GLfloat LIGHT_3_POSITION[]    = { 0.0, 0.0, -1.0, 0.0};
	const GLfloat LIGHT_AMBIENT[]       = { 0.8, 0.8, 0.8, 1.0};
	const GLfloat LIGHT_DIFFUSE[]       = { 0.9, 0.9, 0.9, 1.0};
	const GLfloat LIGHT_SPECULAR[]      = { 1.0, 1.0, 1.0, 1.0};
	const GLfloat LIGHT_MODEL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0};

	//
	const GLuint ParticleTextureName = -1;
	const GLuint SunTextureName   = 0;
	const GLuint MercuryTextureName = 1;
	const GLuint VenusTextureName = 2;
	const GLuint EarthTextureName = 3;
	const GLuint MarsTextureName = 4;
	const GLuint JupiterTextureName = 5;
	const GLuint SaturnTextureName = 6;
	const GLuint SaturnRingTextureName = -6;
	const GLuint UranusTextureName = 7;
	const GLuint NeptuneTextureName = 8;
	const GLuint PlutoTextureName = 9;
	const GLuint MoonTextureName = 10;


	const GLfloat SUN_RADIUS = 1.0;


	///
	// Viewer Positioning Constants
	const GLfloat MAXIMUM_VIEWER_DISTANCE    = 1000;
	const GLfloat MINIMUM_VIEWER_DISTANCE    = 2;
	const GLfloat INITIAL_VIEWER_DISTANCE    = 30;
	const GLfloat VIEWER_DISTANCE_INCREMENT  = 0.1;
	const GLfloat INITIAL_VIEWER_AZIMUTH     = 0.0;
	const GLfloat INITIAL_VIEWER_ZENITH      = PI / 2.0;
	const GLfloat VIEWER_ANGLE_INCREMENT     = PI / 60.0;
	const GLfloat LOOK_AT_POSITION[] = { 0.0, 0.0, 0.0 };


	static GLfloat ViewerDistance = INITIAL_VIEWER_DISTANCE;

	static GLfloat viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
	static GLfloat viewerZenith  = INITIAL_VIEWER_ZENITH;

	extern GLfloat CurrentEarthRotation;
	extern GLfloat EarthDaysTranspired;
	extern GLfloat EarthDayIncrement;
	extern bool proportionalSize;

	const GLfloat EARTH_ORBIT_DUR = 365;

	struct attraction_force {
		long double x;
		long double y;
	};

	const char PARTICLE_BMP_FILENAME[] = "assets/textures/Particle.bmp";
	const char SUN_BMP_FILENAME[] = "assets/textures/sunmap2.bmp";
	const char MERCURY_BMP_FILENAME[] =	"assets/textures/mercurymap.bmp";
	const char VENUS_BMP_FILENAME[] = 	"assets/textures/venusmap.bmp";
	const char EARTH_BMP_FILENAME[] = "assets/textures/earthmap.bmp";
	const char MARS_BMP_FILENAME[] = 	"assets/textures/marsmap.bmp";
	const char JUPITER_BMP_FILENAME[] = "assets/textures/jupitermap.bmp";
	const char SATURN_BMP_FILENAME[] = 	"assets/textures/saturnmap.bmp";
	const char SATURN_RING_BMP_FILENAME[] = "assets/textures/saturnringmap.bmp";
	const char URANUS_BMP_FILENAME[] = 	"assets/textures/uranusmap.bmp";
	const char NEPTUNE_BMP_FILENAME[] = "assets/textures/neptunemap.bmp";
	const char PLUTO_BMP_FILENAME[] = 	"assets/textures/plutomap.bmp";
	const char MOON_BMP_FILENAME[] = "assets/textures/moonmap.bmp";

#endif