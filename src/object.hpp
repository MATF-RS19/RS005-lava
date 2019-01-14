#pragma once
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#define PI 3.1415927

class Animation;

class Stone{
    
public:
    Stone(double x_pos, double y_pos, double z_pos, double stone_speed, double scale)
    :m_x_pos(x_pos),m_y_pos(y_pos),m_z_pos(z_pos), m_speed(stone_speed),m_scale(scale){};
    
    void stone_draw() const;
    void stone_figure() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setScale(double s);
    double getX() const;
    double getY() const;
    double getZ() const;
    double getScale() const;
    double getStoneSpeed() const;
    
    friend class Animation;
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    double m_speed;
    double m_scale;
};

class Gold{
public:
    Gold(double x_pos, double y_pos, double z_pos, int caught):
    m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos), m_caught(caught)
    {};
    void f_draw() const;
    void pom_f_draw() const;
    void setCaught();
    int getCaught() const;
    double getX() const;
    double getY() const;
    double getZ() const;
    friend class Animation;
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    int m_caught;
};

class Floor_{
public: 
    Floor_(double x_pos, double y_pos, double z_pos):
    m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos)
    {};
    
    void f_draw(GLuint lava_texture);
    friend class Animation;
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
    void island_draw();
    void island_figure();
    friend class Animation;    
    
private:
    double m_x_pos;
    double m_y_pos;
    double m_z_pos;
    
};

class Man{
public:
    Man(double x_pos, double y_pos, double z_pos,int life_num=3)
    :m_x_pos(x_pos), m_y_pos(y_pos), m_z_pos(z_pos) , m_life_num(life_num)
    {};
  
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    double getX() const;
    double getY() const;
    double getZ() const;
    int getLifeNum() const;
    void setLifeNum(int life);
    void man_figure() const;
    void man_draw();
    friend class Animation;
    
private:
    double m_x_pos, m_y_pos, m_z_pos;
    int m_life_num;
};

class Bonus{
public:  
    Bonus(double x_pos, double y_pos, double z_pos,int pom=0)
    :m_x_pos(x_pos),m_y_pos(y_pos), m_z_pos(z_pos),m_pom(pom){};
    
    void bonus_figure() const ;
    void bonus_draw();
    
    void setX(double x);
    
    void setY(double x);
    void setZ(double z);
    void setPom(int x);
    int getPom();
    
    double getX() const;
    double getZ() const;
    friend class Animation;
private:
    double m_x_pos,m_y_pos, m_z_pos;
    int m_pom;
};
