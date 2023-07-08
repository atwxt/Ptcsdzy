#ifndef HERO_H
#define HERO_H
#include<QString>

class Hero
{
public:
    Hero(int =0);
    ~Hero();
    int blood;          //血量
    int attack;         //攻击力
    int defense;        //防御力
    int money;          //金钱
    int floor;          //楼层
    int b_key;          //蓝钥匙
    int y_key;          //黄钥匙
    bool sword;         //是否持剑
    bool shield;        //是否持盾
    int difficulty;     //难度
};

#endif // HERO_H
