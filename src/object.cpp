#include <iostream>
#include "object.hpp"
#include "animation.hpp"


void Stone::stone_draw() const{
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
void Floor_::f_draw(GLuint lava_texture){
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
void Island::island_draw(){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos, m_z_pos);
            glScalef(15, 1, 15);
            island_figure();
        glPopMatrix();	

}
    
void Island::island_figure(){
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


void Man::setX(double x){
    m_x_pos=x;
}
void Man::setY(double y){
    m_y_pos=y;
}
void Man::setZ(double z){
    m_z_pos=z;
}
double Man::getX() const{
    return m_x_pos;
}
double Man::getY() const{
    return m_y_pos;
}
double Man::getZ() const{
    return m_z_pos;
}
void Man::man_figure() const{
    
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
void Man::man_draw(){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos, m_z_pos);
            man_figure();
        glPopMatrix();	
        
    }