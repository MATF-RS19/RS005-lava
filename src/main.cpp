#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <string>
#include <experimental/random>
#include <ctime>
#include <cstdlib>

#include "image.hpp"
#include "animation.hpp"
#include "object.hpp"

#define LAVATEXTURE "lava.bmp"
#define TIMER_INTERVAL 20
#define TIMER_INTERVAL2 100

#define JUMP_LEN 5
#define JUMP_HEIGHT 2

GLuint lava_texture;
int lvl = 0;
int random_num;
int life_num=3;
int coins_initialized=0;

/*text i text2 nam omogucavaju ispis teksta na ekran. */
std::string text;
std::string text2;

static void on_timer(int value);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x , int y);

/*funkcija za inicijalizaciju tekstura. */
static void initializeTexture(void);
/*funckija za inicijalizaciju kamenja. */
static void initialize_stone();
/*funkcija za inicijalizaciju bonus life-a */
int initialize_bonus(int random_num);
/*funkcija za inicijalizaciju zlatnika */
static void initialize_coins();

void reset();
static void readLevel();


double animation_stones=0.0;
int pom = 1; 
static void initializeTexture(void);

Man man(0, 3,-15,life_num);
std::vector<Stone> stones;
std::vector<Gold> coins;
std::vector<double> stoneSpeed;
std::vector<double> stoneScale;
// Stone stone(0,0,0,1,1);
Island i1(0, 0, -29);
Island i2(0, 0, 29);
Floor_ f(0, 0, 0);
Bonus b(-15,1.5,-35);
Animation a(man, stones, coins, b);

int main(int argc, char** argv){
    
    readLevel();
    initialize_stone();
    initialize_coins();
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
    gluLookAt(-30, 17, 0, 0, 0, 0, 0, 1, 0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    f.f_draw(lava_texture);
    
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
    
    glColor3f(1, 1, 0);
    
	glRasterPos3f(6, 2, 15);
	int len,i,len2;
    
    /*ispisujemo na display Score,Level i Life. */
    text = "Score: " + std::to_string(a.getScore()) + "     " + "Level: " + std::to_string(lvl);
    text2 = "Life: "+  std::to_string(man.getLifeNum());
    
    len= text.length();
    len2=text2.length();

    for(i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
    }
    
    glColor3f(1, 0, 0);
	glRasterPos3f(3, 2, 15);
    
    for(i=0;i<len2;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2.at(i));
    }
    
    f.f_draw(lava_texture);
    /*crtamo velika ostrva. */
    i1.island_draw();
    i2.island_draw();
    
    /*crtamo coveka. */
    man.man_draw();
    
    /*iscrtavamo kamenje. */
    for (Stone stonee: stones){
        stonee.stone_draw();   
    }
    /*crtamo zlatnike. */
    for(Gold coin: coins){

        if(coin.getCaught()==0)
            coin.f_draw();
        
    }
    /*iscrtava bonus life kada je to potrebno. */
    if(initialize_bonus(random_num)==1 &&   b.getPom()==0){
        b.bonus_draw();
    }
    
 	glutSwapBuffers();
}


static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            std::cout<<"Score: "<<a.getScore()<<std::endl;
            exit(0);
            break;
        case 'j':
            if(a.getPomAnim()!=2){
                if(a.getStonemove()==1){
                    if(a.getJumpOngoing()==0){
                        a.setJumpOngoing(1);
                        a.setJumped(0);
                        glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
                    }
                }
            }
            break;
        /*skok unazad. */
        case 'g':
            if(a.getNum()>=0){
                if(a.getPomAnim()!=2){
                    if(a.getStonemove()==1){
                        if(a.getJumpOngoing()==0){
                            a.setJumpOngoing(2);
                            a.setJumped(0);
                            glutTimerFunc(TIMER_INTERVAL, on_timer, 0);
                        }
                    }
                }
            }
            break;
        /*start */
        case 's':
            if(a.getStonemove()==0){
                a.setStonemove(1);
                glutTimerFunc(TIMER_INTERVAL,on_timer, 1);
            }
            break;
            
        /*pauza. */
        case 'p':
            if(a.getStonemove()==1){
                a.setStonemove(0);
            }
            break;
    }
}
int  initialize_bonus(int random_num){
    /*ukoliko je lvl 2 ili 3 dolazi do inicijalizuje i  crtanja bonusa */
    if(std::abs(lvl-2)==0 || std::abs(lvl-3)==0){
        if(std::fmod(random_num,2)==0){
            /*ukoliko je pomocna za bonus life=0 postavljamo koordinate za iscrtavanje. */
            if(b.getPom()==0){
                b.setX(-10);
                b.setZ(random_num*5-10.0);
            }
            return 1;
        }
        else{
          if(b.getPom()==0){
            b.setX(10);
            b.setZ(random_num*5-10.0);
          
          }
          return 1;
        }
    }
    return 0;
}

/*postavljamo pocetne pozicije za zlatnike. */
static void initialize_coins(){
    if(coins_initialized==0){
        coins_initialized=1;
        for(int i=0; i<5; i++){
            Gold coin(std::experimental::randint(0,4)*5-10, 2, -10+i*5, 0);
            coins.push_back(coin);
        }
        
    }
    else{
        for(int i=0; i<5; i++){
            Gold coin(std::experimental::randint(0,4)*5-10, 2, -10+i*5, 0);
            coins[i]=coin;
        }

    }
    
}

static void initialize_stone(){
    /*postavljamo pocetne pozicije za kamenje, njihovu brzinu i skaliranje.*/
    
     for (int i=0;i<5;i++){
        
        if(std::fmod(i,2)==0){
            Stone stone(-10,0.5,i*5-10.0,stoneSpeed.at(i),stoneScale.at(i));
            stones.push_back(stone);
        }
        else{
            Stone stone(10,0.5,i*5-10.0,stoneSpeed.at(i),stoneScale.at(i));        
            stones.push_back(stone);  
        }        
    }
}


void reset(){
    /*ukoliko je broj zivota ispod nule ili je presao sve nivoe, sve se resetuje ponovo na pocetak. */
    if(man.getLifeNum()<=0 || lvl==4){
        std::cout<<"Score :"<< a.getScore()<<std::endl;
        lvl=0;
        a.setScore(0);
        man.setLifeNum(3);
        readLevel();
        initialize_coins();
    }

    a.setJumpOngoing(0);
    man.setX(0);
    man.setY(3);
    man.setZ(-15);
    man.setLifeNum(man.getLifeNum());
    a.setPomAnim(0);
    a.setNum(-1);
    b.setY(1.5);
    b.setX(-15);
    b.setZ(-35);
    b.setPom(0);
    a.setStonemove(0);
    for (int i=0;i<5;i++)
    {
        
        if(std::fmod(i,2)==0){
            Stone stone(-10,0.5,i*5-10.0,stoneSpeed.at(i),stoneScale.at(i));
            stones[i]=stone;
        }
        else{            
            Stone stone(10,0.5,i*5-10.0,stoneSpeed.at(i),stoneScale.at(i));
            stones[i]=stone;
        }
    }
    return;
}


void initializeTexture(void)
{
	//kod sa casa
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    Image image(0,0);


    /* Kreira se tekstura */
    image.read(LAVATEXTURE);
    /* Generisu se identifikatori teksture i inicijalizuje tekstura*/
    glGenTextures(1, &lava_texture);

    glBindTexture(GL_TEXTURE_2D, lava_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image.width, image.height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

}
/*funckija za ucitavanje nivoa. */
void readLevel(){
    
    stoneSpeed.clear();
    stoneScale.clear();
    
    lvl+=1;
    
    /*ukoliko je lvl 2 ili 3 uzimamo jedan random broj od 0 do 4 i omogucavamo iscrtavanje bonus zivota. */
    if(lvl==2 || lvl==3){
         random_num=std::experimental::randint(0,4);
         std::cout<<random_num<<std::endl;
         /*pozivamo funkciju za Inicijalizaciju  */
         initialize_bonus(random_num);
    }
    std::string level = "lvl" + std::to_string(lvl);
    
    std::cout<<level<<std::endl;
    
    
    /*ucitavamo level*/
    
    std::ifstream ifile(level.c_str(), std::ios::in);
    if(!ifile.is_open()){
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);
    }
    /*ucitavamo iz datoteke prvo broj za brzinu, a zatim i za skaliranje */
    double num = 0.0;
    double num2=0.0;
    while(ifile >> num){
        /*unosimo brzinu. */
        stoneSpeed.push_back(num);
        /*unosimo skaliranje */
        if(ifile>>num2){
            stoneScale.push_back(num2);
        }
    }
}


static void on_timer(int value){
    
    if(value == 1){
        
        if(man.getY()<=-2){
            reset();  
        }
        /*pomeramo kamenje. */
        if(a.getStonemove()==1){
            a.animation_stone();
        }
        
        glutPostRedisplay();
        
        if(a.getStonemove()==1){
            glutTimerFunc(TIMER_INTERVAL2, on_timer, 1);

        }
    }
    if (value == 0){
        /*ukoliko je vrednost getJumpOngoing 1 ili 2 omogucavamo da covek skoci. */
        if(a.getJumpOngoing()==1 || a.getJumpOngoing()==2){
            a.jump_anim();
            
        }
        /*ukoliko je presao svo kamenje ide na sledeci nivo. */
        if(a.getNum()==5){
            std::cout<<"POBEDA"<<std::endl;
            readLevel();            
            initialize_coins();
            reset();
            
        }
        //ponovo se iscrtava prozor	
        glutPostRedisplay();
        if(a.getJumpOngoing()==1 || a.getJumpOngoing()==2){
            glutTimerFunc(TIMER_INTERVAL, on_timer, 0);

        }
        //ako je presao dovoljno prestaje da skace
    }

}
