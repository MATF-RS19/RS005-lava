#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2


void Animation::jump_anim(){
        if(m_jump_ongoing==1){
            if(m_jumped<JUMP_LEN){
                m_jumped+=.2;
                m_m.setZ(m_m.getZ()+.2);
                m_m.setY(3 +(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                
            }
             else{
                m_jump_ongoing=0;
            }
        }          
        else{
            m_jumped=0;
        }

}

int Animation::getJumpOngoing() const
{
        return m_jump_ongoing;
}
void Animation::setJumpOngoing(int j){
        m_jump_ongoing=j;
}

int Animation::getJumped() const
{
        return m_jumped;
}
void Animation::setJumped(int j){
        m_jumped=j;
}
int Animation::getStoneSize() const{
        std::cout<<m_s.size()<<std::endl;
     return m_s.size();   
}


