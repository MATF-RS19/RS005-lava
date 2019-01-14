#include <functional>
#include <iostream>
#include "animation.hpp"
#include "object.hpp"

#define JUMP_LEN 5
#define JUMP_HEIGHT 2

/*poredimo da li je jedna vrednost manja od druge. */
template <typename T1, typename T2, typename L = std::less<>>
bool f(T1 a, T2 b, L l = L())
{
    return l(a, b);
}

float potapanje=0;
/*promenljiva za nestanak detelinke posle odredjenog vremena. */
float nestanak=0;
/*promenljiva koja vraca kamen u prvobitni polozaj nakon potapanja. */
float nestanak2=0;
/*promenljiva koja nam omogucava potapanje kamena. */
float nestanak_kamena=0;

void Animation::jump_anim(){
        /*ukoliko je pokrenut skok napred ili nazad ulazimo. */
        if(m_jump_ongoing==1 || m_jump_ongoing==2){
            
            /*provera da li je skok dostigao odredjenu vrednost,ako nije pomeraju mu se i dalje koordinate. */
            if(f(m_jumped,JUMP_LEN)==1){
                /*ukoliko je skok napred, pomeramo coveku koordinate u skladu sa tim.*/
                if(m_jump_ongoing == 1){
                    m_jumped+=.2;
                    m_m.setZ(m_m.getZ()+.2);
                    m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                }

                /*ukoliko je skok nazad, pomeramo coveku koordinate u skladu sa tim.*/

                else{
                    m_jumped+=.2;
                    m_m.setZ(m_m.getZ()-.2);
                    m_m.setY(3+(-4*JUMP_HEIGHT*m_jumped*m_jumped)/(JUMP_LEN*JUMP_LEN)+4*JUMP_HEIGHT*m_jumped/JUMP_LEN);
                
                }
            }
                 /*ako je dostigao duzinu skoka */
             else{  
                 /*ukoliko je bio u pitanju skok napred povecavamo vrednost m_num za 1, kako bi imali redni broj kamena na kom se nalazi covek. */
                 if(m_jump_ongoing==1)
                    m_num += 1;
                 
                 /*ukoliko je bio u pitanju skok nazad smanjujemo vrednost m_num za 1, kako bi imali redni broj kamena na kom se nalazi covek. */
                 else
                     m_num -= 1;
                 /*ukoliko covek nije presao svo kamenje moze jos uvek da skace i skuplja poene. */
                 if(f(m_num,5)==1 && m_num>=0){
                     /*provera da li je covek uspeo bezbedno da skoci na kamen. */
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
                    nestanak2=0;
                    m_pom_anim=0;
                    m_jump_ongoing=0;
                }
                    nestanak_kamena=0;
            }
        }          
        else{
//             m_num=-1;
            m_jumped=0;
        }
}



void Animation::animation_stone(){
        if(m_anim_stone<=1){
                       
            /*covek je dobro skocio. */
            if(m_pom_anim==1){
                /*koordinata x coveka prati koordinatu x kamena. */
                m_m.setX(m_s.at(m_num).getX()); 
                /*proveravamo da li je covek uspeo da pokupi zlatnik, ukoliko jeste dodajemo mu 5 poena na dotadasnje skupljene.*/
                for(int i=0; i<5; i++){
                    if(std::abs(m_g[i].getZ()-m_m.getZ())<=0.1 && std::abs(m_m.getX()-m_g[i].getX())<=0.5 && m_g[i].getCaught()==0){
                        m_g[i].setCaught();
                        m_score_num+=5;
                        
                    }
                }
                /*proveravamo da li je covek uspeo da uzme bonus zivot, ako jeste povecavamo mu zivot za 1. i bonus zivot nestaje sa scene.*/
                if(std::abs(m_b.getZ()-m_m.getZ())<=0.001 && std::abs(m_m.getX()-m_b.getX())<=0.001 && m_b.getPom()==0){
                    m_m.setLifeNum(m_m.getLifeNum()+1);
                    std::cout<<"LIFE: "<<m_m.getLifeNum()<<std::endl;   
                    m_b.setY(-15);
                    m_b.setX(-15);
                    m_b.setPom(1);
                    /*postavljamo nestanak na 0.5 kako bi  se za odredjeno vreme se ponovo pojavio bonus zivot. */
                    nestanak=0.5;
                }
                /*posle odredjenog vremena bonus promeni svoje mesto ukoliko nije pokupljen ili jeste pa ponovo treba da se pojavi. */
                nestanak+=0.01;
                /*nestanak2 nam omogucava da vratimo kamen posle potapanja u prvobitni polozaj. */
                nestanak2+=0.01;
                /*ukoliko nestanak predje 1 ponovo se javlja bonus life.*/
                if(f(nestanak,1)==0){                        
                /*ponovo biramo ostrvo na kome ce da se pojavi bonus */
                    int random_n=std::experimental::randint(0,4);
//                     std::cout<<random_n<<std::endl;
                    /*postavljamo koordinate. */
                    m_b.setX(m_s.at(random_n).getX());
                    m_b.setY(1.5);
                    m_b.setZ(m_s.at(random_n).getZ());
                    m_b.setPom(0);
//                     std::cout<<m_b.getX()<<"  : "<<m_b.getZ()<<std::endl;
                    
                    /*postavljamo pomocnu za bonus na 0 , kako bi ponovo doslo do crtanja na zeljenoj poziciji.*/
                    nestanak=0;
                }
                /*ukoliko covek ne skoci na vreme sa jednog kamena na drugo moze da izgubi zivot.*/
                if(f(nestanak_kamena,0.045)==1){
                    /*povecavamo nestanak_kamena zeljenim intervalom. */
                    nestanak_kamena+=0.0002;
                    /*smanjujemo Y kordinatu kamena gde se nalazi covek. */
                    m_s.at(m_num).setY(m_s.at(m_num).getY()-nestanak_kamena);
                    /*ukoliko covek nije skocio na vreme sa kamena pri njegovom potapanju, gubi zivot. */
                    if(f(0.017,nestanak_kamena)==1){
                        m_pom_anim=2;   
                        m_m.setLifeNum(m_m.getLifeNum()-1);
                        /*postavljamo promenljivu za nestanak_kamena na 0, zbog sledeceg potapanja. */
                        nestanak_kamena=0;   
                    }
                    /*ukoliko covek skoci na vreme sa kamena na kamen pre nego sto potone, taj kamen se vraca na prvobutnu vrednost. */
                    if(m_jump_ongoing==1 || m_jump_ongoing==2){
                        m_s.at(m_num).setY(m_s.at(m_num).getY()+nestanak2);   
                        /*postavljamo nestanak2 na 0 , kako bi ponovo mogli da racunamo i vratimo sledeci kamen na koji skoci. */
                        nestanak2=0;
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
                /*zavisno od toga da li je pozicija kamena parna ili neparna, krecu se suprotno. */
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
/*get i set za klasu Animation. */
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
    

