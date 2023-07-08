#include "monster.h"

Monster::Monster(int type){
    this->type=type;
    //根据传入类型生成指定怪物
    switch (type){
    case 8:
        blood=30;
        attack=12;
        defense=5;
        money=2;
        name="黄史莱姆";
        break;
    case 9:
        blood=50;
        attack=13;
        defense=5;
        money=3;
        name="蓝史莱姆";
        break;
    case 10:
        blood=50;
        attack=15;
        defense=8;
        money=5;
        name="蝙蝠";
        break;
    case 11:
        blood=100;
        attack=18;
        defense=12;
        money=8;
        name="骷髅";
        break;
    case 12:
        blood=160;
        attack=26;
        defense=10;
        money=10;
        name="法师";
        break;
    default:
        break;
    }
}
