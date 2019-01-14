#include <functional>
#include <iostream>
#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2

template <typename T1, typename T2, typename L = std::less<>>
bool f(T1 a, T2 b, L l = L())
{
    return l(a, b);
}


float potapanje=0;
float nestanak=0;
float nestanak_kamena=0;

void Animation::jump_anim(){

        if(m_jump_ongoing==1 || m_jump_ongoing==2){
            
            /*provera da li je skok dostigao odredjenu vrednost. */
            if(f(m_jumped,JUMP_LEN)==1){
                if(m_jump_ongoing == 1){
                    m_jumped+=.2;
                    m_m.setZ(m_m.getZ()+.2);
                    m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                }
                else{
                    m_jumped+=.2;
                    m_m.setZ(m_m.getZ()-.2);
                    m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                
                }
            }
             else{  
                 if(m_jump_ongoing==1)
                    m_num += 1;
                 else
                     m_num -= 1;
                 
                 if(f(m_num,5)==1 && m_num>=0){
                     if((m_m.getX()<=(m_s.at(m_num).getX()) +2.5*m_s.at(m_num).getScale()/2)  && 
                     (m_m.getX()>=(m_s.at(m_num).getX()- 2.5*m_s.at(m_num).getScale()/2))  
                     ){
                         /*covek je uspeo da skoci bezbedno.Dodajemo mu poene i postavljamo m_pom_anim na 1. */
                        m_pom_anim=1;
                        /*dodajemo dobijene poene. */
                        m_score_num=m_score_num+((m_num+1)*m_m.getLifeNum());
                    
                    }
                    else{
                        /*smanjujemo broj zivota za 1 ukoliko nije preziveo i postavljamo m_pom_anim na 2.*/
                        m_m.setLifeNum(m_m.getLifeNum()-1);
                        m_pom_anim=2;
                    
                    }
                    /*resetujemo m_jump_ongoing na 0 zbog narednog skoka. */
                    m_jump_ongoing=0;
                     
                }

                else{
                    /*ukoliko nemamo vise kamena da predjemo resetujemo. */
                    nestanak=0;
                    m_pom_anim=0;
                    m_jump_ongoing=0;
                }
                    nestanak_kamena=0;
            }
        }          
            
            
        else{
            m_num=-1;
            m_jumped=0;
            

        }
}



void Animation::animation_stone(){
        if(m_anim_stone<=1){
                       
            /*covek je dobro skocio. */
            if(m_pom_anim==1){
                /*koordinata x coveka prati koordinatu x kamena. */
                m_m.setX(m_s.at(m_num).getX()); 
//                 std::cout<<"STOJi NA ISTOM: Z: "<<std::abs(m_b.getZ()-m_m.getZ())<<std::endl;
//                 std::cout<<"STOJi NA ISTOM: X: "<<std::abs(m_b.getX()-m_m.getX())<<std::endl;
                
                /*ukoliko su z i x koordinata bonusa== z i x koordinati coveka povecavamo zivot za 1 i bonus treba da nestane. */
//                 std::cout<<"ANIM STONE: "<<m_b.getPom()<<std::endl;
                
                
                if(std::abs(m_b.getZ()-m_m.getZ())<=0.001 && std::abs(m_m.getX()-m_b.getX())<=0.001 && m_b.getPom()==0){
                    m_m.setLifeNum(m_m.getLifeNum()+1);
                    std::cout<<"LIFE: "<<m_m.getLifeNum()<<std::endl;   
                    m_b.setY(-15);
                    m_b.setX(-15);
                    m_b.setPom(1);
                    nestanak=0.5;
                }
                /*posle odredjenog vremena bonus promeni svoje mesto */
                nestanak+=0.01;
                /*ukoliko nestanak predje 1 ponovo se javlja bonus life.*/
                if(f(nestanak,1)==0){                        
                /*ponovo biramo ostrvo na kome ce da se pojavi bonus */
                    int random_n=std::experimental::randint(0,4);
                    m_b.setX(m_s.at(random_n).getX());
                    m_b.setY(1.5);
                    m_b.setZ(m_s.at(random_n).getZ());
                    /*postavljamo pomocnu za bonus na 0 , kako bi ponovo doslo do crtanja na zeljenoj poziciji.*/
                    m_b.setPom(0);
                    /*resetujemo nestanak bonusa na 0 */
                    nestanak=0;
                }
                /*ukoliko covek ne skoci na vreme sa jednog kamena na drugo moze da izgubi zivot.*/
                if(f(nestanak_kamena,0.04)==1){
                    /*povecavamo nestanak_kamena zeljenim intervalom. */
                    nestanak_kamena+=0.0002;
                    /*smanjujemo Y kordinatu kamena gde se nalazi covek. */
                    m_s.at(m_num).setY(m_s.at(m_num).getY()-nestanak_kamena);
                    if(f(0.017,nestanak_kamena)==1){
//                     if(nestanak_kamena>=0.0165){
                        m_pom_anim=2;   
                        m_m.setLifeNum(m_m.getLifeNum()-1);
                        nestanak_kamena=0;   
                    }
                    /*ukoliko covek skoci na vreme sa kamena na kamen pre nego sto potone, taj kamen se vraca na prvobutnu vrednost. */
                    if(m_jump_ongoing==1 || m_jump_ongoing==2){
                        m_s.at(m_num).setY(m_s.at(m_num).getY()+nestanak);   
                        nestanak=0;
                    }
                }
             
            }
            
            /*ukoliko covek ne stane na ostrvo kako treba, pocinje da tone.*/ 
            if(m_pom_anim == 2){
                /*resetujemo nestanak za bonus zivot. */
                nestanak=0;
                /*polako se covek spusta po Y koordinati. */
                potapanje+=0.1;
                m_m.setY(m_m.getY()-potapanje);   
              
            }
            for(int i = 0; i<5; i++){
                
                /*na osnovu zeljene brzine kamena se pomeraju. */
                m_stone_speed = m_s.at(i).getStoneSpeed();
                
                if(std::fmod(i,2)==0){
                    if(std::abs(m_s.at(i).getX())>=14){
                        
                        m_sign.at(i) = m_sign.at(i) * (-1);
                    }
                    /*postavljamo x koordinatu za ostrvo */
                    m_s.at(i).setX(m_s.at(i).getX()+m_stone_speed*m_sign.at(i));
                }
                else{
                    if(std::abs(m_s.at(i).getX())>=14){
                        m_sign.at(i) = m_sign.at(i) * (-1);
                    }
                    /*postavljamo x koordinatu za ostrvo */
                    m_s.at(i).setX(m_s.at(i).getX()-m_stone_speed*m_sign.at(i));
                }   
                    
            }
        }          
        else{
            m_stone_speed=0;
             nestanak_kamena=0;
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
int Animation::getScore() const{
 return m_score_num;   
}
void Animation::setScore(int score){
 m_score_num=score;   
}
    

