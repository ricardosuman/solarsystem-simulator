class Body {
	public:
		GLuint id;
    	long double mass;
    	long double vx;
    	long double vy;
    	long double x;
    	long double y;
		GLfloat inclination;
		GLfloat orbit_duration;
		GLfloat orbit_radius;
		GLfloat rotation_dur;
		GLfloat radius;
		int active;

		// methods
		void update(Body *bodies[], int number_of_bodies);
		attraction_force attraction(Body *other);
		void draw();
		void drawRing();
};