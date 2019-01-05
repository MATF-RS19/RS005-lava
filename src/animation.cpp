#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2


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
                        m_pom_anim=1;
                        m_score_num=m_score_num+(m_num*m_m.getLifeNum());
                    }
                    
                    else{
                        m_m.setLifeNum(m_m.getLifeNum()-1);
                        m_pom_anim=2;
                    
                    }
                    
                    m_jump_ongoing=0;
                     
                }
                else{
                    m_pom_anim=0;
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
                       
            
            if(m_pom_anim==1){
             m_m.setX(m_s.at(m_num).getX()); 
            }
            if(m_pom_anim == 2){
                potapanje+=0.1;
                m_m.setY(m_m.getY()-potapanje);   
              
            }
            for(int i = 0; i<5; i++){
                
                m_stone_speed = m_s.at(i).getStoneSpeed();
                
                if(i%2==0){
                    if(m_s.at(i).getX() >= 14 || m_s.at(i).getX() <= -14){
                    m_sign.at(i) = m_sign.at(i) * (-1);
                }
                    m_s.at(i).setX(m_s.at(i).getX()+m_stone_speed*m_sign.at(i));
                }
                else{
                    if(m_s.at(i).getX() >= 14 || m_s.at(i).getX() <= -14){
                    m_sign.at(i) = m_sign.at(i) * (-1);
                }
                    m_s.at(i).setX(m_s.at(i).getX()-m_stone_speed*m_sign.at(i));
                }   
                    
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
int Animation::getNum() const{
    return m_num;
}
void Animation::setNum(int j){
        m_num=j;
}
int Animation::getPomAnim() const
{
        return m_pom_anim;
}
void Animation::setPomAnim(int j){
        m_pom_anim=j;
}
float Animation::getScore() const{
 return m_score_num;   
}
void Animation::setScore(float score){
 m_score_num=score;   
}
    

