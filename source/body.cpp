#include "header.h"

extern GLfloat EarthDayIncrement;
extern bool proportionalSize;
extern double scale_distance;

void Body::update(Body *bodies[], int number_of_bodies) {
	attraction_force force[number_of_bodies];

	for(int k = 0; k < number_of_bodies; k++) {
		force[k].x = 0;
		force[k].y = 0;
	}

	for(int i = 0; i < number_of_bodies; i++) {
		if(bodies[i] != nullptr) {
			// add up all of the forces exerted on 'body'
			attraction_force total_force;
			total_force.x = 0.0;
			total_force.y = 0.0;

			for(int j = 0; j < number_of_bodies; j++) {
				// don't calculate the body's attraction to itself
				if(j != i && bodies[j] != nullptr) {
					attraction_force af = bodies[i]->attraction(bodies[j]);
					total_force.x += af.x/scale_distance;
					total_force.y += af.y/scale_distance;
				}
			}

			// record the total force exerted.
			force[i] = total_force;
		}
	}


	// update velocities based upon on the force.
	for(int n = 0; n < number_of_bodies; n++) {
		if(bodies[n] != nullptr) {
			bodies[n]->vx += (force[n].x / bodies[n]->mass * EarthDayIncrement * SCALE)/(1000.0*1000.0);
			bodies[n]->vy += (force[n].y / bodies[n]->mass * EarthDayIncrement * SCALE)/(1000.0*1000.0);

			// update positions
			bodies[n]->x += ((bodies[n]->vx * EarthDayIncrement)/(1000.0*1000.0));
			bodies[n]->y += ((bodies[n]->vy * EarthDayIncrement)/(1000.0*1000.0));
		}	
	}
}

// Returns the force exerted upon this body by the other body.
attraction_force Body::attraction(Body *other) {
	attraction_force af;
	af.x = 0;
	af.y = 0;

	if(this->id == other->id) {
		return af;
	}

	// compute the distance of the other body
	GLfloat dx = other->x - this->x;
	GLfloat dy = other->y - this->y;

	GLfloat d = sqrt(pow(dx, 2) + pow(dy, 2));

	// if d == 0 >> collision
	//if(((this->id == 10) && (other->id == 3)) || ((this->id == 3) && (other->id == 10))) {
		if(d >= 0 && d < 1.5) {
			//cout<<"asteroid crashou com a terra maluco"<<endl;
			if(this->mass < other->mass) {
				if(this != nullptr) {
					this->active = 0;
				}
			} else {
				if(other != nullptr) {
					other->active = 0;
				}
			}
		}
	//} 

	// compute the force of attraction
	long double f = (GRAVITATIONAL_CONSTANT * this->mass * other->mass) / pow(d, 2.0);

	GLfloat theta = atan2(dy, dx);
	af.x = cos(theta) * f;
	af.y = sin(theta) * f;

	return af;
}

void Body::draw() {
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				//glRotatef(7, 0.0, 0.0, 1.0);
				//glRotatef(360.0 * (EarthDaysTranspired/365), 0.0, 1.0, 0.0);
				//glTranslatef(orbitRadius, 0.0, 0.0 );
				// glRotatef(360.0 * (CurrentEarthRotation/rotationDuration), 0.0, 1.0, 0.0);
				// glRotatef(-90.0, 1.0, 0.0, 0.0);
				glTranslatef(this->x, this->y, 0.0);
				glRotatef(360.0 * (CurrentEarthRotation/this->rotation_dur), 0.0, 0.0, 1.0);
				glBindTexture(GL_TEXTURE_2D, this->id);
				//glTranslatef(-this->x, -this->y, 0.0);
				if(this->id == 0) {
					gluSphere(quadro, this->radius, 48, 48);
				} else {
					if(proportionalSize) {
						gluSphere(quadro, this->radius, 48, 48);
					} else {
						gluSphere(quadro, 0.8, 48, 48);
					}
				}
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);

	if(this->id == 6) {
		this->drawRing();
	}
}

void Body::drawRing() {
	GLUquadricObj* quadro = gluNewQuadric();							
	gluQuadricNormals(quadro, GLU_SMOOTH);		
	gluQuadricTexture(quadro, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				// glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
				// glRotatef( 360.0 * (EarthDaysTranspired/SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
				// glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0 );
				// glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glTranslatef(this->x, this->y, 0.0);
				glRotatef(360.0 * (CurrentEarthRotation/this->rotation_dur), 0.0, 0.0, 1.0);
				glBindTexture(GL_TEXTURE_2D, -this->id);
				glScalef(1, 1, .02);
				if(proportionalSize) {
					gluSphere(quadro, this->radius * 2, 48, 48);
				} else {
					gluSphere(quadro, 0.8 * 2, 48, 48);
				}
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}