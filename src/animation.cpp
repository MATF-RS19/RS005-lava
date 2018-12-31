#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2

int pom_anim=0;
float potapanje=0;
void Animation::jump_anim(){
        if(m_jump_ongoing==1){

            if(m_jumped<JUMP_LEN){
                m_jumped+=.2;
                
                m_m.setZ(m_m.getZ()+.2);
                m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                    
                
            }
             else{  
                 m_num += 1;
                 if(m_num<=4){

                    if((m_m.getX()<=(m_s.at(m_num).getX()) +2.5*m_s.at(m_num).getScale()/2)  && 
                    (m_m.getX()>=(m_s.at(m_num).getX()- 2.5*m_s.at(m_num).getScale()/2))  
                    ){
                        pom_anim=1;
                    }
                    
                    else{
                        
                        pom_anim=2;
                    
                    }
                    m_jump_ongoing=0;
                
                     
                }
                else{
                    pom_anim=false;
                    m_num=-1;
                    m_jump_ongoing=0;
                }
            }
            
            
        }          
        else{
            m_num=-1;
            m_jumped=0;
        }

}

void Animation::animation_stone(){
    
        
        if(m_anim_stone<=1){
                       
            
            m_stone_speed = 0.7;
            
            if(pom_anim==1){
             m_m.setX(m_s.at(m_num).getX()); 
            }
            if(pom_anim==2){
                potapanje+=0.1;
                m_m.setY(m_m.getY()-potapanje);   
              
            }
            for(int i = 0; i<5; i++){
                
                if(i%2==0){
                    m_s.at(i).setX(m_s.at(i).getX()+m_stone_speed*m_sign);
                }
                else{
                    m_s.at(i).setX(m_s.at(i).getX()-m_stone_speed*m_sign);
                }   
                    
                }
                if(m_s.at(0).getX() >= 14 || m_s.at(0).getX() <= -14){
                    m_sign = m_sign * (-1);
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
     return m_s.size();   
}




