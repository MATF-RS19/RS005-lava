#pragma once
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <cmath>

#include "object.hpp"

class Animation{
public:
	Animation(Man m, std::vector<Stone> s, int jump_ongoing=0, double jumped=0)
		: m_m(m), m_s(s), m_jump_ongoing(jump_ongoing), m_jumped(jumped) {}
    void jump_anim();
    int getJumpOngoing() const;
    
    void setJumpOngoing(int j);
    int getJumped() const;
    void setJumped(int j);
    int getStoneSize() const;

private:
	Man m_m;
	std::vector<Stone> m_s;
    int m_jump_ongoing;
    double m_jumped;
};

