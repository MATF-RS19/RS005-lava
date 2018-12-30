#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2


void Animation::jump_anim(){
        if(m_jump_ongoing==1){

            if(m_jumped<JUMP_LEN){
                m_jumped+=.2;
                
                m_m.setZ(m_m.getZ()+.2);
                m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                
            }
             else{
                m_jump_ongoing=0;
            }
        }          
        else{
            m_jumped=0;
        }

}

void Animation::animation_stone(){
    
        
        if(m_anim_stone<=1){
                       

            m_stone_speed = 0.7;
             
            for(int i = 0; i<5; i++){
                    if(i%2==0){
                        m_s.at(i).setX(m_s.at(i).getX()+m_stone_speed*m_pom);
                    }
                    else{
                        m_s.at(i).setX(m_s.at(i).getX()-m_stone_speed*m_pom);
                    }   
                
            }
            
            if(m_s.at(0).getX() >= 14 || m_s.at(0).getX() <= -14){
                m_pom = m_pom * (-1);
            }
          
        }          
        else{
            m_stone_speed=0;
        }

}

int Animation::getStonemove() const
{
        return m_anim_stone;
}
void Animation::setStonemove(int j){
        m_anim_stone=j;
}

double Animation::getStoneSpeed() const
{
        return m_stone_speed;
}
void Animation::setStoneSpeed(double j){
        m_stone_speed=j;
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


