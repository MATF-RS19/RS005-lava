#pragma once
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <cmath>

#include "object.hpp"

class Animation{
public:
	Animation(Man &m, std::vector<Stone> &s, int jump_ongoing=0, double jumped=0.0, int anim_stone=0, double stone=0.0, int pom=1, int num = -1)
 		: m_m(m), m_s(s), m_jump_ongoing(jump_ongoing), m_jumped(jumped), m_anim_stone(anim_stone), m_stone_speed(stone), m_sign(pom), m_num(num){}
 		
    void jump_anim();
    void animation_stone();
    
    int getJumpOngoing() const;
    void setJumpOngoing(int j);
    
    int getJumped() const;
    void setJumped(int j);
    
    int getStonemove() const;
    void setStonemove(int j);
    
    double getStoneSpeed() const;
    void setStoneSpeed(double j);
    
    int getStoneSize() const;
    
    
    
    

private:
    Man &m_m;
    std::vector<Stone> &m_s;
    int m_jump_ongoing;
    double m_jumped;
    int m_sign;
    int m_anim_stone;
    double m_stone_speed;
    int m_num;
};

