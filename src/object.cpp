#include <iostream>
#include "object.hpp"
#include "animation.hpp"

void Stone::stone_draw() const{
    glPushMatrix();
            glTranslatef(m_x_pos,m_y_pos,m_z_pos);
            stone_figure();
    glPopMatrix();
    
}

void Stone::stone_figure() const{
        glPushMatrix();
             glColor3f(0.5,0.5,0.4);
//              glTranslatef(m_x_pos,m_y_pos,m_z_pos);
             glScalef(2.5*m_scale,.3,2.5*m_scale);
             glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.6,0.6,0.5);
//             glTranslatef(m_x_pos,m_y_pos,m_z_pos);
            glScalef(2*m_scale,.4,2*m_scale);
            glutSolidCube(1);
         glPopMatrix();
}

void Gold::f_draw(){
    if(m_caught!=1){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos, m_z_pos);
            
            pom_f_draw();
        glPopMatrix();
    }
}
void Gold::pom_f_draw(){
    glScalef(.4, .4, .4);
    glColor3f(212.0/255.0,120.0/255.0, 0);
    glutSolidSphere(1, 20, 20);


}
void Gold::setCaught(){
    m_caught=1;
}
int Gold::getCaught() const{
    return m_caught;
}

double Gold::getX() const{
    return m_x_pos;
}
double Gold::getY() const{
    return m_y_pos;
}
double Gold::getZ() const{
    return m_z_pos;
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

void Stone::setX(double x){
    m_x_pos=x;
}
void Stone::setY(double y){
    m_y_pos=y;
}
void Stone::setZ(double z){
    m_z_pos=z;
}
void Stone::setScale(double z){
    m_scale=z;
}
double Stone::getX() const{
    return m_x_pos;
}
double Stone::getY() const{
    return m_y_pos;
}
double Stone::getZ() const{
    return m_z_pos;
}
double Stone::getScale() const{
    return m_scale;
}

double Stone::getStoneSpeed() const{
     return m_speed;
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
int Man::getLifeNum() const{
    return m_life_num;
}
void Man::setLifeNum(int life){
    m_life_num=life;
}
void Man::man_figure() const{
    /*ideja preuzeta iz projekta Katarine Rudinac.*/
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

/* detelinka */
void Bonus::bonus_figure() const {
  
    glPushMatrix();
        glColor3f(0,1,0);
         glScalef(0.1,0.3,0.1);
        glutSolidSphere(1,50,50);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0,1,0);
        glutSolidSphere(0.2,50,50);
    glPopMatrix();
    
     glPushMatrix();
         glColor3f(0,1,0);
         glTranslatef(0.1,0.3,0);
         glutSolidSphere(0.2,50,50);
     glPopMatrix();
    
    
    glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(-0.1,0.3,0);
        glutSolidSphere(0.2,50,50);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(-0.1,0,0);
        glutSolidSphere(0.2,50,50);
    glPopMatrix();
    
}

void Bonus::bonus_draw(){
        glPushMatrix();
            glTranslatef(m_x_pos, m_y_pos,m_z_pos);
            bonus_figure();
        glPopMatrix();
}

void Bonus::setX(double x){
    m_x_pos=x;
}
 
void Bonus::setY(double y){
    m_y_pos=y;    
}

void Bonus::setZ(double z){
 m_z_pos=z;   
}
    
void Bonus::setPom(int x){
 m_pom=x;
}   

int Bonus::getPom(){
 return m_pom;
}   
double Bonus::getX() const{
 return m_x_pos;   
}

double Bonus::getZ() const{
 return m_z_pos;   
}
