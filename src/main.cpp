#include <GL/glut.h>
#include <iostream>

static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x , int y);

class Floor{
public: 
    Floor(double x_pos, double y_pos, double z_pos):
    m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos)
    {};
    
    void floor_draw(){
        glPushMatrix();
            glBegin(GL_QUADS);
                glNormal3f(0, 1, 0);
                glVertex3f(-400+m_x_pos, 0+m_y_pos, -400+m_z_pos); 
                glVertex3f(400+m_x_pos, 0+m_y_pos, -400+m_z_pos); 
                glVertex3f(400+m_x_pos, 0+m_y_pos, 400+m_z_pos); 
                glVertex3f(-400+m_x_pos, 0+m_y_pos, 400+m_z_pos);
            glEnd();
        glPopMatrix();
  
        
    }
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    
};

class Island{
public:
    Island(double x_pos, double y_pos, double z_pos):
    m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos)
    {};
    
    void island_draw(){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos, m_z_pos);
            glScalef(15, 1, 15);
            island_figure();
        glPopMatrix();	

    };
    
    void island_figure(){
        //openGL deo preuzet iz mog projekta za RG
        glPushMatrix();    
            glColor3f(.3, .3, .3);
            glScalef(2, .3, 2);
            glutSolidCube(1);
        glPopMatrix();
        
        //sredina
        glPushMatrix();
            glTranslatef(0, .3, 0);
            glColor3f(.3, .3, .3);
            glScalef(1.93, .25, 1.93);
            glutSolidCube(1);
        glPopMatrix();
        
        //vrh
        glPushMatrix();
            glTranslatef(0, .55, 0);
            glColor3f(.3, .3, .3);
            glScalef(1.86, .15, 1.86);
            glutSolidCube(1);
        glPopMatrix();
    }
    
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    
};

class Man{
public:
    Man(double x_pos, double y_pos, double z_pos)
    :m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos) 
    {};
  
    void man_figure() const{
    
     glPushMatrix();    
		glColor3f(.8, 0.2, 0.2);
		glScalef(1, 1.43, .5);
		glutSolidCube(1);
	glPopMatrix();
	
	
	//noge
	glPushMatrix();
		glColor3f(0.2, 0.5, 0.2);
		glTranslatef(-.35, -1.5, 0);
		glScalef(.4, 1.5, .4);
		glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
		glColor3f(0.2, 0.5, 0.2);
		glTranslatef(.35, -1.5, 0);
		glScalef(.4, 1.5, .4);
		glutSolidCube(1);
	glPopMatrix();
    
    //ruke
	glPushMatrix();
		glColor3f(.8, .65, .45);
		glTranslatef(-.62, .084, 0);
		glScalef(.2, 1.3, .2);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(.62, .084, 0);
		glScalef(.2, 1.3, .2);
		glutSolidCube(1);
	glPopMatrix();

	//vrat 
	glPushMatrix();  
		glColor3f(.8, .65, .45);
		glTranslatef(0, .86, 0);
		glScalef(.3, .3, .3);
		glutSolidCube(1);
	glPopMatrix();
	
	//glava
	glPushMatrix();
		glColor3f(.8, .65, .45);
		glTranslatef(0, 1.3, 0);
		glScalef(.35, .45, .3);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//oci
	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(-.17, 1.3, .32);
		glScalef(.04, .04, .04);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(0.17, 1.3, .32);
		glScalef(.04, .04, .04);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
		  
    //nos
    glPushMatrix();
        glColor3f(.8,0.8,0.9);
        glTranslatef(0,1.2,0.3);
        glScalef(.05,.1,.05);
        glutSolidCube(1);
    glPopMatrix();
    
    //usta
    glPushMatrix();
        glColor3f(.8,0.7,0.3);
        glTranslatef(0,1,0.3);
        glScalef(.1,.05,.05);
        glutSolidSphere(1,20,20);   
    
    glPopMatrix();
    }
    void man_draw(){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos, m_z_pos);
            man_figure();
        glPopMatrix();	
        
    }
    
    
private:
    double m_x_pos, m_y_pos, m_z_pos;
};

Man man(0,3,-15);


Island i1(0, 0, -29);
Island i2(0, 0, 29);
Floor floor(0, 0, 0);

int main(int argc, char** argv){
	//inicijalizujemo glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	//kreiramo prozor
	glutInitWindowSize(1300, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	
	
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    
    
	glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);    
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	
	//glavna petlja
	glutMainLoop();
	return 0;
}

void on_reshape(int width, int height) {
	//viewport
	glViewport(0, 0, width, height);

	//perspektiva tj odsecanje
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, (float) width / height, 1, 1500);
}



void on_display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//podesavamo lookat
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//iz svih uglova
	gluLookAt(-30, 17, 0, 0, 0, 0, 0, 1, 0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    floor.floor_draw();

    i1.island_draw();
    i2.island_draw();
    man.man_draw();
    
	glutSwapBuffers();
}
static void on_keyboard(unsigned char key, int x, int y){
 switch(key){
     case 27:
         exit(0);
         break;
 }
}
