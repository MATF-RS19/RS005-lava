#include <GL/glut.h>
#include <iostream>

static void on_reshape(int width, int height);
static void on_display(void);

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


Island i1(0, 0, -29);
Island i2(0, 0, 29);

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

    i1.island_draw();
    i2.island_draw();
	//nova slika
	glutSwapBuffers();
}
