#include "hero.h"

Hero::Hero(int _difficulty):difficulty(_difficulty)
{
    //根据level初始化角色数据
    if(difficulty==1){
        blood=200;
        attack=18;
        defense=15;
    }
    else if(difficulty==2){
        blood=150;
        attack=15;
        defense=12;
    }
    else if(difficulty==3){
        blood=120;
        attack=12;
        defense=10;
    }
    money=0;
    floor=0;
    b_key=0;
    y_key=0;
    sword=false;
    shield=false;
}
