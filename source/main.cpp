#include "header.h"
#include "utils/RGBpixmap.h" 
#include "utils/ParticleSystem.h"

void drawParticle(Particle currParticle);
void drawAllParticles();

#define FPS 60
#define MAX_NUMBER_OF_BODIES 1000
int NUMBER_OF_BODIES = 11;

long double probability_of_meteor_1 = 0.163746150615596371734;
long double probability_of_meteor_none = 0.818730753077982;
long double probability_of_meteor_morethan1 = 0.1812692469220181413301;

GLfloat current_time;
GLfloat delta_t;

Body** bodies = new Body*[MAX_NUMBER_OF_BODIES];//[NUMBER_OF_BODIES];

int desliga_meteoro = 0;

int qtd_meteoro = 0;
int meteoros_de_30 = 0;
int meteoros_de_50 = 0;

Body *sun = new Body();
Body *sun2 = new Body();
Body *mercury = new Body();
Body *venus = new Body();
Body *earth = new Body();
Body *mars = new Body();
Body *jupiter = new Body();
Body *saturn = new Body();
Body *uranus = new Body();
Body *neptune = new Body();
Body *pluto = new Body();
//Body *moon = new Body();

double scale_distance = 10;
GLfloat EarthDayIncrement;
GLfloat EarthDaysTranspired = 0.0;
GLfloat CurrentEarthRotation = 0.0;
bool proportionalSize = true;
int daysByFrame = 1;

int initial_time = time(NULL), final_time, frame_count = 0;

ParticleSystem particles;

int main(int argc, char** argv) {
	//bodies = new Body*[MAX_NUMBER_OF_BODIES];

	// for(int i = 0; i < NUMBER_OF_BODIES; i++) {
	// 	bodies[i] = new Body();
	// }

	glutInit (&argc, argv);
	current_time = glutGet(GLUT_ELAPSED_TIME);
	delta_time();

	sun->id = 0;
	sun->mass = 1.9891 * pow(10, 30);
	sun->x = 0.0;
	sun->y = 0;
	sun->vy = 0.0;
	sun->vx = 0.0;
	sun->radius = 1.0;
	sun->rotation_dur = -1000;
	sun->active = 1;

	sun2->id = 0;
	sun2->mass = 1.9891 * pow(10, 30);
	sun2->x = -100.0;
	sun2->y = 0;
	sun2->vy = 0.0;
	sun2->vx = 0.0;
	sun2->radius = 1.0;
	sun2->rotation_dur = -1000;
	sun2->active = 0;

	mercury->id = 1;
	mercury->mass = (3.3022 * pow(10, 23));
	mercury->x = 57.91/scale_distance;
	mercury->y = 0.0;
	mercury->vx = 0.0;
	mercury->vy = 47.87 * 1000.0;
	mercury->radius = 0.1;
	mercury->rotation_dur = 59;
	mercury->active = 1;

	venus->id = 2;
	venus->mass = (4.8685 * pow(10, 24));
	venus->x = 108.2/scale_distance;
	venus->y = 0.0;
	venus->vx = 0.0;
	venus->vy = 35.02 * 1000.0;
	venus->radius = 0.18;
	venus->rotation_dur = -243;
	venus->active = 1;

	earth->id = 3;
	earth->mass = (5.9736 * pow(10, 24));
	earth->x = 150/scale_distance;
	earth->y = 0.0;
	earth->vx = 0.0;
	earth->vy = 29.78 * 1000.0;
	earth->radius = 0.18;
	earth->rotation_dur = 1.0;
	earth->active = 1;

	mars->id = 4;
	mars->mass = (6.4185 * pow(10, 23));
	mars->x = 227.9/scale_distance;
	mars->y = 0.0;
	mars->vx = 0.0;
	mars->vy = 24.077 * 1000.0;
	mars->radius = 0.3;
	mars->rotation_dur = 1.0;
	mars->active = 1;

	jupiter->id = 5;
	jupiter->mass = (1.8986 * pow(10, 27));
	jupiter->x = 778.5/scale_distance;
	jupiter->y = 0.0;
	jupiter->vx = 0.0;
	jupiter->vy = 13.07 * 1000.0;
	jupiter->radius = 0.6;
	jupiter->rotation_dur = 0.4;
	jupiter->active = 1;

	saturn->id = 6;
	saturn->mass = (5.6846 * pow(10, 26));
	saturn->x = 1430/scale_distance;
	saturn->y = 0.0;
	saturn->vx = 0.0;
	saturn->vy = 9.69 * 1000.0;
	saturn->radius = 0.5;
	saturn->rotation_dur = 0.4;
	saturn->active = 1;

	uranus->id = 7;
	uranus->mass = (8.6810 * pow(10, 25));
	uranus->x = 2880/scale_distance;
	uranus->y = 0.0;
	uranus->vx = 0.0;
	uranus->vy = 6.81 * 1000.0;
	uranus->radius = 0.3;
	uranus->rotation_dur = -0.7;
	uranus->active = 1;

	neptune->id = 8;
	neptune->mass = (10.243 * pow(10, 25));
	neptune->x = 4500/scale_distance;
	neptune->y = 0.0;
	neptune->vx = 0.0;
	neptune->vy = 5.43 * 1000.0;
	neptune->radius = 0.3;
	neptune->rotation_dur = 0.7;
	neptune->active = 1;

	pluto->id = 9;
	pluto->mass = (1.25 * pow(10, 22));
	pluto->x = 5910/scale_distance;
	pluto->y = 0.0;
	pluto->vx = 0.0;
	pluto->vy = 4.67 * 1000.0;
	pluto->radius = 0.05;
	pluto->rotation_dur = -6;
	pluto->active = 1;

	// moon->id = 10;
	// moon->mass = (7.347 * pow(10, 22));
	// moon->x = 149.615595/scale_distance;//(earth->x - 0.384405)/20.0;
	// moon->y = 0.0;
	// moon->vx = 0.0;
	// moon->vy = 1.022 * 1000;//1.022 * 1000.0;
	// moon->radius = 0.04;
	// moon->rotation_dur = -1000;

	bodies[0] = sun;
	bodies[1] = mercury;
	bodies[2] = venus;
	bodies[3] = earth;
	bodies[4] = mars;
	bodies[5] = jupiter;
	bodies[6] = saturn;
	bodies[7] = uranus;
	bodies[8] = neptune;
	bodies[9] = pluto;
	bodies[10] = sun2;
	//bodies[11] = moon;

	// Set up the display window.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowPosition(INITIAL_WINDOW_POSITION[0], INITIAL_WINDOW_POSITION[1]);
	glutInitWindowSize(currentWindowSize[0], currentWindowSize[1]);
	glutCreateWindow(WINDOW_NAME);

	// Specify the resizing and refreshing routines.
	glutReshapeFunc(resizeWindow);
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutMouseFunc(mouseHandler);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(nonAsciiKeyboardHandler);
	glutDisplayFunc(display);
	glutTimerFunc(1000/FPS, timer, 1);
	glViewport(0, 0, currentWindowSize[0], currentWindowSize[1]);

	//sSet up standard lighting, shading, and depth testing.
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);
	glCullFace(GL_BACK);	
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	setLight();

	// set up all texture maps and texture-mapped objects.
	parseAllTextures();
	glutMainLoop();
	return 0;
}

/*Window-reshaping callback, adjusting the viewport to be as large as possible within the window,
without changing its aspect ratio.*/

void resizeWindow(GLsizei w, GLsizei h) {
	currentWindowSize[0] = w;
	currentWindowSize[1] = h;
	if (ASPECT_RATIO > w/h) {
		currentViewportSize[0] = w;
		currentViewportSize[1] = w / ASPECT_RATIO;
	} else {
		currentViewportSize[1] = h;
		currentViewportSize[0] = h * ASPECT_RATIO;
	}

	glViewport(0.5*(w-currentViewportSize[0]), 0.5*(h-currentViewportSize[1]), currentViewportSize[0], currentViewportSize[1]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN) {
			// float cartesianx = x - 1280 / 2;
			// float cartesiany = -y + 720 / 2;
			// cout<<cartesianx<<" "<<cartesiany<<endl;
			// Body *b = new Body();
			// b->id = 0;
			// b->mass = 1.9891 * pow(10, 30);
			// mercury->x = cartesianx/scale_distance;
			// mercury->y = cartesiany/scale_distance;
			// //cout<<b->x<<" "<<b->y<<endl;
			// b->vy = 0.0;
			// b->vx = 1.0;
			// b->radius = 1.0;
			// b->rotation_dur = -1000;
			// //bodies[1] = b;
		 }
	}
}

// Function to react to ASCII keyboard keys pressed by the user.   //
// +/- keys are used to accelerate/decelerate the animation, while //
// the z/Z keys are used to zoom in and out of the animation.      //
void keyboardHandler(unsigned char pressedKey, int mouseXPosition, int mouseYPosition) {
	glutIgnoreKeyRepeat(false);

	switch(pressedKey) {
		case 'm': {
			if(desliga_meteoro == 0) {
				desliga_meteoro = 1;
			} else {
				desliga_meteoro = 0;
			}
			break;
		}

		case 'g': {
			if(sun2->active == 0) {
				cout<<"aaa"<<endl;
				sun2->active = 1;
			} else {
				sun2->active = 0;
			}
			break;
		}

		case '+': {
			daysByFrame += 1;
			if (daysByFrame > 1000)
				daysByFrame = 1000;
			break;
		}
		
		case '-': {		
			daysByFrame *= 0.5;
			if (daysByFrame < 0)
				daysByFrame = 0;
			break;
		}

		case 'w': {
			ViewerDistance -= VIEWER_DISTANCE_INCREMENT * 10;
			if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
				ViewerDistance = MINIMUM_VIEWER_DISTANCE;
			break; 
		}

		case 's': {
			ViewerDistance += VIEWER_DISTANCE_INCREMENT * 10;
			if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
				ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
			break; 
		}

		case 'p': {
			proportionalSize = !proportionalSize;
		}
	}
}


void mouseMovement(int x, int y) {
}

void nonAsciiKeyboardHandler(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch(pressedKey)
	{
		case GLUT_KEY_RIGHT: { 
			viewerAzimuth += VIEWER_ANGLE_INCREMENT; 
			if (viewerAzimuth > 2*PI) 
				viewerAzimuth -= 2*PI; 
			break; 
		}

		case GLUT_KEY_LEFT: { 
			viewerAzimuth -= VIEWER_ANGLE_INCREMENT; 
			if (viewerAzimuth < 0.0)  
				viewerAzimuth += 2*PI; 
			break; 
		}

		case GLUT_KEY_UP: { 
			viewerZenith -= VIEWER_ANGLE_INCREMENT; 
			if (viewerZenith < VIEWER_ANGLE_INCREMENT) 
				viewerZenith = VIEWER_ANGLE_INCREMENT; 
			break;
		}

		case GLUT_KEY_DOWN:  { 
			viewerZenith += VIEWER_ANGLE_INCREMENT; 
			if (viewerZenith > PI - VIEWER_ANGLE_INCREMENT)  
				viewerZenith = PI - VIEWER_ANGLE_INCREMENT; 
			break; 
		}
	}
}

// Principal display routine: sets up material, lighting, //
// and camera properties, clears the frame buffer, and    //
// draws all texture-mapped objects within the window.    //
void display() {
	// Initialize lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);	
	glEnable(GL_LIGHTING);
	
	// Set up the properties of the viewing camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.5, 0.1, 1000.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//camera();

	// Position and orient viewer.
	gluLookAt(LOOK_AT_POSITION[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth), 
				LOOK_AT_POSITION[1] + ViewerDistance * cos(viewerZenith), 
				LOOK_AT_POSITION[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
				LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
				0.0, 1.0, 0.020);

	// Render scene.
	updateLight();
	for(int i = 0; i < NUMBER_OF_BODIES; i++) {
		if(bodies[i] != nullptr && bodies[i]->active == 1) {
			bodies[i]->draw();
		}
		//cout<<"x: "<<(bodies[10]->x)<<" "<<"y: "<<(bodies[10]->y)<<" "<<"vx: "<<bodies[10]->vx<<" "<<"vy: "<<bodies[10]->vy<<endl;
	}

	//if(blendFlag){ //if the user has selected blending, enable it.
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_COLOR,GL_ONE);
	//}
	//if(particleFlag)
		drawAllParticles();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	glFlush();

	frame_count++;
	final_time = time(NULL);
	if(final_time - initial_time > 0) {
		//cout<<"FPS: "<<frame_count / (final_time - initial_time)<<endl;
		frame_count = 0;
		initial_time = final_time;
	}
}

void timer(int value) {
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysTranspired += EarthDayIncrement;

	delta_time();

	float yearPercentage = EarthDaysTranspired * 2.4;
	int yearPercentageCasted = (int)yearPercentage;

	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
	cout<<"//---------------------- Simulacao ----------------------//"<<endl;
	cout<<"// Dias passados: "<<EarthDaysTranspired * 2.4<<endl;
	cout<<"// Meteoros gerados: "<<qtd_meteoro<<endl;
	cout<<"// Qtd. de meteoros de até 30M que caíram na Terra: "<<meteoros_de_30<<endl;
	cout<<"// Qtd. de meteoros de até 50M que caíram na Terra: "<<meteoros_de_50<<endl;
	cout<<"//-------------------------------------------------------//"<<endl;

	if(desliga_meteoro == 1) {
		estrela();
	}

	if((yearPercentageCasted % 365) == 0){
		int m = cai_trinta();
		int n = cai_cinquenta();

		if(desliga_meteoro == 0) {
			estrela();
		}
		
		if(m == 1) {
			meteoros_de_30 += 1;
			cout<<"CAI UM ASTEROIDE DE TRINTA METROS NA TERRA"<<endl;
		}

		if(n == 1) {
			meteoros_de_50 += 1;
			cout<<"CAI UM ASTEROIDE DE CINQUENTA METROS NA TERRA"<<endl;
		}
		
	}	


	for(int i = 0; i < NUMBER_OF_BODIES; i++) {
		if(bodies[i] != nullptr && bodies[i]->active == 1) {
			bodies[i]->update(bodies, NUMBER_OF_BODIES);
		}
	}

	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 1);
}

void delta_time() {
	int t;

	t = glutGet(GLUT_ELAPSED_TIME);
	delta_t = (t - current_time) / 1000.0;
	current_time = t;
	EarthDayIncrement = delta_t * daysByFrame;
}

// set the two lights to illuminate the scene
void setLight() {
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

	glLightfv(GL_LIGHT3, GL_AMBIENT,  LIGHT_AMBIENT);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
}


// enable the scene's lighting
void updateLight() {
	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
		glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
		glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);
		glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);
	glPopMatrix();
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void parseAllTextures() {
	parseTexture(PARTICLE_BMP_FILENAME, ParticleTextureName, false);
	parseTexture(SUN_BMP_FILENAME,		SunTextureName,		false);
	parseTexture(MERCURY_BMP_FILENAME, MercuryTextureName, false);
	parseTexture(VENUS_BMP_FILENAME, VenusTextureName, false);
	parseTexture(EARTH_BMP_FILENAME, EarthTextureName, false);
	parseTexture(MARS_BMP_FILENAME, MarsTextureName, false);
	parseTexture(JUPITER_BMP_FILENAME, JupiterTextureName, false);
	parseTexture(SATURN_BMP_FILENAME, SaturnTextureName, false);
	parseTexture(SATURN_RING_BMP_FILENAME, SaturnRingTextureName, false);
	parseTexture(URANUS_BMP_FILENAME, UranusTextureName, false);
	parseTexture(NEPTUNE_BMP_FILENAME, NeptuneTextureName, false);
	parseTexture(PLUTO_BMP_FILENAME, PlutoTextureName, false);
	parseTexture(MOON_BMP_FILENAME, MoonTextureName, false);
	return;
}

// Convert the bitmap with the parameterized name into an OpenGL texture. //
void parseTexture(const char bitmapFilename[], const GLuint &textureName, bool hasAlpha) {
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}

//Cycles through each particle in the particle system and passes it to the
//draw function
void drawAllParticles() {
	particles.updateAll();
	for(int i = 0; i < particles.getNumberOfParticles(); i++)
		drawParticle(particles.getNextParticle());

}

//Draws one individual particle, given a particle struct from the particle
//system object
void drawParticle(Particle currParticle) {	
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(sun->x, sun->y, 0.0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glRotatef(currParticle.azimuthRotation, 0, 1, 0);
			glRotatef(currParticle.zenithRotation, 0, 0, 1);
			glTranslatef(sun->radius + currParticle.surfaceTranslationFactor, 0 ,0);
			glRotatef(90, 0 , 1, 0);
			glScalef(.5, .5, 1.0);
			glBindTexture(GL_TEXTURE_2D, ParticleTextureName);

			// Logo Facing Earth
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); 
					glVertex3f(0.5f, 0.5f, 0.0f); // Top Right
				glTexCoord2d(0,1);
					glVertex3f(-0.5f, 0.5f, 0.0f); // Top Left
				glTexCoord2d(1,0); 
					glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Right
				glTexCoord2d(0,0); 
					glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
			glEnd();

			// Logo Facing Away From Earth
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); 
					glVertex3f(-0.5f, 0.5f, 0.0f); // Top Right
				glTexCoord2d(0,1);
					glVertex3f(0.5f, 0.5f, 0.0f); // Top Left
				glTexCoord2d(1,0); 
					glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Right
				glTexCoord2d(0,0); 
					glVertex3f(0.5f, -0.5f, 0.0f); // Bottom Left
			glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void estrela() {
	if(NUMBER_OF_BODIES < MAX_NUMBER_OF_BODIES) {
	    float a = 100; //variavel para o random da semente
	    float semente = ((float)rand()/(float)(RAND_MAX)) * a; //gerando valor aleatório
		int nascimento=rand()%100+1; // número aleatorio entre 1 e 100
		int b = 50;
	    int semente2 = rand()%b+1;
	    int c = 50;
	    int semente3 = rand()%c+1;


		if(semente <= 81.87) {
			//cout<<"cai nenhum meteoro"<<endl;
		} else if(semente > 81.87 && semente <= 98.24) {
			//cout<<"cai 1 meteoro"<<endl;
			//cout<<"1 meteoro na posicao "<<semente2<<" "<<semente3<<endl;
			Body *a = new Body();
			a->id = 10;
			a->mass = (10.0 * pow(10, 12));
			a->x = semente2;//(earth->x - 0.384405)/20.0;
			a->y = semente3;
			a->vx = 0.0;
			a->vy = 30.0 * 1000;//1.022 * 1000.0;
			a->radius = 0.2;
			a->rotation_dur = -1000;
			a->active = 1;
			bodies[NUMBER_OF_BODIES] = a;
			NUMBER_OF_BODIES++;
			qtd_meteoro += 1;
		} else if(semente > 98.24) {
			//cout<<"cai mais de 1 meteoro"<<endl;
		}
	}
	//cout<<"so um: "<<(probability_of_meteor_1/probability_of_meteor_none) * EarthDaysTranspired<<" nenhum: "<<endl;
	// float estrela_massa; //massa da estrela medida em massa solar (M)
 //    float estrela_vida; //vida da estrela medida em milhões de anos
 //    float a = EarthDayIncrement; //variavel para o random da semente
	// srand(time(0)); // numero aleatorio com o tempo
 //    float semente = ((float)rand()/(float)(RAND_MAX)) * a; //gerando valor aleatório
	// int nascimento=rand()%100+1; // número aleatorio entre 1 e 100

 //    //printf("Valor aleatório: %f \n nascimento: %d \n", semente, nascimento);
 //    if(nascimento > 98){
    	
 //        //verifica em qual massa caiu o valor aleatorio
 //        if (semente < 80.85){
 //            estrela_massa = 1;
 //            estrela_vida = 10000;
 //        }
 //        else if(semente < 96.71){
 //              estrela_massa = 2;
 //              estrela_vida = 1767;
 //        }
 //        else if(semente < 98.55){
 //            estrela_massa = 5;
 //            estrela_vida = 179;
 //        }
 //        else if(semente < 99.16){
 //            estrela_massa = 8;
 //            estrela_vida = 55;
 //        }
 //        else if(semente < 99.52){
 //            estrela_massa = 10;
 //            estrela_vida = 31;
 //        }
 //        else if(semente < 99.75){
 //            estrela_massa = 12;
 //            estrela_vida = 20;
 //        }
 //        else if(semente < 99.89){
 //            estrela_massa = 15;
 //            estrela_vida = 11;
 //        }
 //        else if(semente < 99.96){
 //            estrela_massa = 20;
 //            estrela_vida = 5;
 //        }
 //        else if(semente <= 100){
 //            estrela_massa = 25;
 //            estrela_vida = 3;
 //        }

 //        cout<<"GERA UMA ESTRELA GRANDE COM MASSA: "<<estrela_massa<<" E VIDA: "<<estrela_vida<<endl;
 //        //printf("Valor aleatório: %f \n Massa da estrela: %f \n Vida da estrela: %f \n", semente, estrela_massa, estrela_vida);
 //    }
}

int cai_trinta(){
    float trinta_metros_prob = 0.7143; //probabilidade do asteroide de 30m cair
    float a = 100; //variavel para o random da semente
    float semente = ((float)rand()/(float)(RAND_MAX)) * a; //gerando valor aleatório
    if (semente < trinta_metros_prob){ //verifica se esta na prob
        return 1;
    }
    else
        return 0;
}


int cai_cinquenta(){
    float trinta_metros_prob = 0.1428; //probabilidade do asteroide de 30m cair
    float a = 100; //variavel para o random da semente
    float semente= ((float)rand()/(float)(RAND_MAX)) * a; //gerando valor aleatório
    if (semente < trinta_metros_prob){ //verifica se esta na prob
        return 1;
    }
    else
        return 0;
}