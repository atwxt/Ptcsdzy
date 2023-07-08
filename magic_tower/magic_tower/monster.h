#ifndef MONSTER_H
#define MONSTER_H
#include<QString>

class Monster
{
public:
    Monster(int);
    ~Monster();
    QString name;
    int blood;//生命值
    int attack;//攻击力
    int defense;//防御力
    int money;//金钱
    int type;//类型    8-蓝史莱姆  9-黄史莱姆  10-蝙蝠  11-骷髅 12-法师
};

#endif // MONSTER_H
