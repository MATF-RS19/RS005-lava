#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "image.h"

#define LAVATEXTURE "lava.bmp"
#define TIMER_INTERVAL 20
#define JUMP_LEN 5
#define JUMP_HEIGHT 2

GLuint lava_texture;


static void on_timer(int value);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x , int y);
static void initializeTexture(void);

class Stone{
    
public:
    Stone(double x_pos, double y_pos, double z_pos, double stone_speed, double scale)
    :m_x_pos(x_pos),m_y_pos(y_pos),m_z_pos(z_pos), m_speed(stone_speed),m_scale(scale){};
    
    void stone_draw() const{
        glPushMatrix();
             glColor3f(0.5,0.5,0.4);
             glTranslatef(m_x_pos,m_y_pos,m_z_pos);
             glScalef(2.5*m_scale,.3,2.5*m_scale);
             glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.6,0.6,0.5);
            glTranslatef(m_x_pos,m_y_pos,m_z_pos);
            glScalef(2*m_scale,.4,2*m_scale);
            glutSolidCube(1);
         glPopMatrix();
    }
    
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    double m_speed;
    double m_scale;
};

static void initializeTexture(void);

class Floor{
public: 
    Floor(double x_pos, double y_pos, double z_pos):
    m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos)
    {};
    
    void floor_draw(GLuint lava_texture){
        //initializes textures
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, lava_texture);
        glPushMatrix();
            glColor3f(1,.6,0);
            glBegin(GL_QUADS);
            //draws polygon with textures
                glNormal3f(0, 1, 0);
                glTexCoord2f(0, 0);	
                glVertex3f(-400+m_x_pos, 0+m_y_pos, -400+m_z_pos); 
                glTexCoord2f(40, 0);	
                glVertex3f(400+m_x_pos, 0+m_y_pos, -400+m_z_pos); 
                glTexCoord2f(40, 40);	
                glVertex3f(400+m_x_pos, 0+m_y_pos, 400+m_z_pos); 
                glTexCoord2f(0, 60);	
                glVertex3f(-400+m_x_pos, 0+m_y_pos, 400+m_z_pos);
            glEnd();
      		glBindTexture(GL_TEXTURE_2D, 0);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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
  
    void setX(double x){
        m_x_pos=x;
    }
    void setY(double y){
        m_y_pos=y;
    }
    void setZ(double z){
        m_z_pos=z;
    }
    double getX() const{
        return m_x_pos;
    }
    double getY() const{
        return m_y_pos;
    }
    double getZ() const{
        return m_z_pos;
    }
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
		glColor3f(.8, .7, .45);
		glTranslatef(-.62, .09, 0);
		glScalef(.2, 1.3, .2);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(.62, .09, 0);
		glScalef(.2, 1.3, .2);
		glutSolidCube(1);
	glPopMatrix();

	//vrat 
	glPushMatrix();  
		glColor3f(.9, .7, .45);
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
            glTranslatef(m_x_pos+0.0, m_y_pos, m_z_pos);
            man_figure();
        glPopMatrix();	
        
    }
    
    
private:
    double m_x_pos, m_y_pos, m_z_pos;
};



class Animation{
public:
	Animation(Man m, std::vector<Stone> s, int jump_ongoing=0, double jumped=0)
		: m_m(m), m_s(s), m_jump_ongoing(jump_ongoing), m_jumped(jumped) {}
	void move_stones(){
        
        
    }
    
    void jump_anim(){
        if(m_jump_ongoing==1){
            if(m_jumped<JUMP_LEN){
                m_jumped+=.2;
                m_m.setZ(m_m.getZ()+.2);
                m_m.setY((-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                std::cout<<m_m.getZ()<<","<<m_m.getY()<<std::endl;
                //glutPostRedisplay();
            }
        }
    }
    int getJumpOngoing() const
    {
        return m_jump_ongoing;
    }
    void setJumpOngoing(int j){
        m_jump_ongoing=j;
    }
    int getJumped() const
    {
        return m_jumped;
    }
    void setJumped(int j){
        m_jumped=j;
    }


private:
	Man m_m;
	std::vector<Stone> m_s;
    int m_jump_ongoing;
    double m_jumped;
};




Man man(0,3,-15);
std::vector<Stone> stones;

// Stone stone(0,0,0,1,1);
Island i1(0, 0, -29);
Island i2(0, 0, 29);
Floor floor(0, 0, 0);
Animation a(man, stones, 0, 0);
    
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

	initializeTexture();

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
	gluLookAt(-30, 20, 0, 0, 0, 0, 0, 1, 0);

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    floor.floor_draw(lava_texture);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    GLfloat light_position[]={-30,20,6,0};
    GLfloat ambient_coefs[]={0.1,0.2,0.3,1};
    GLfloat diffuse_coefs[]={1,1,1,1};
    GLfloat specular_coefs[]={0.9,.7,.8,1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_coefs);
    glLightfv(GL_LIGHT0,GL_SPECULAR, specular_coefs);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_coefs);
 
    GLfloat ambient_material[]={0.2,.3,.3,1};
    GLfloat specular_material[]={.5,.6,.6,1};
    GLfloat shininess=90;
    
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,ambient_material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
    
    floor.floor_draw(lava_texture);
    i1.island_draw();
    i2.island_draw();
    man.man_draw();
    for (int i=0;i<5;i++)
    {
        if(i%2==0){
            Stone stone(-10,0.0,i*5-10.0,0.1,1);
            stones.push_back(stone);
        }
        else{
            Stone stone(10,0.0,i*5-10.0,0.1,1);
            stones.push_back(stone);      
        }
    }
    for (Stone stonee: stones){
        stonee.stone_draw();   
    }
    
	glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        case 'j':
            if(a.getJumpOngoing()==0){
                a.setJumpOngoing(1);
                a.setJumped(0);
                std::cout<<a.getJumpOngoing()<<std::endl;
       			glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
            }
            break;
    }
}




void initializeTexture(void)
{
	//kod sa casa
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	/* Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz fajla */
    Image *image = image_init(0, 0);


    /* Kreira se tekstura */
    image_read(image, LAVATEXTURE);

    /* Generisu se identifikatori teksture i inicijalizuje tekstura*/
    glGenTextures(1, &lava_texture);

    glBindTexture(GL_TEXTURE_2D, lava_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}


static void on_timer(int value){
	if (value != 0)
        return;
    if(a.getJumpOngoing()==1){
        a.jump_anim();
    }
	//ponovo se iscrtava prozor	
	glutPostRedisplay();

    //ako je presao dovoljno prestaje da skace
    glutTimerFunc(TIMER_INTERVAL, on_timer, 0);

}
