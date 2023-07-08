#ifndef MAGIC_TOWER_H
#define MAGIC_TOWER_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QThread>
#include <QPushButton>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "map.h"
#include "hero.h"
#include "monster.h"
#include "monsterinformation.h"
#include "difficulty_choose.h"


class MagicTower : public QWidget
{
    Q_OBJECT
public slots:
    void startGame();//开始游戏
    void startGameWithLevel(int);//结合难度选择的开始游戏
    void show_monster_information();//显示怪物信息
    void read_situation();//读档
    void enter_store();//进入商店
public:
    MagicTower(QWidget *parent = 0);
    ~MagicTower(){};
    void keyPressEvent(QKeyEvent *event);//键盘事件重写，上下左右与WASD键的改写
    void initMap();//初始化游戏地图函数
    void updateMap(int type);  //刷新游戏地图函数
    void heroMove(int type); //角色移动判断函数
    void heroCombat();//角色战斗判断函数
    void showHeroInfo();//显示角色信息函数
    void buyAttack();//购买攻击力
    void buyDefense();//购买防御力
    void buyBlood();//购买血量
    void WinMessage();//游戏获胜信息
    void heroShow();//定时器显示角色
    void monsterShow();//定时器显示怪物
    int bloodcount(int monsterType);//计算损失血量
    void save_situation();//存档

private:
    QPushButton *start_bt;//开始按钮
    bool combate_signal;//角色战斗标志
    bool restart_signal;//死亡重开标志
    bool start_background_signal;//更新背景图标志
    bool init_game=true;//判断是否是第一次进入游戏
    QLabel *mapLabel[13][13];//当前地图
    QLabel *infoLabel;//背景标签
    QLabel *diffLabel;//难度标签
    QLabel *moneyLabel;//金币
    QLabel *floorLabel; //楼层
    QLabel *bloodLabel;//生命值
    QLabel *attackLabel;//攻击力
    QLabel *defenseLabel;//防御力
    QLabel *bKeyLabel;//蓝钥匙
    QLabel *yKeyLabel;//黄钥匙
    DifficultyChoose* diff;//难度标签
    Map *present_map=new Map;//当前游戏的地图
    Map *init_map=new Map;//初始地图，用于重新开始
    Hero *hero;//角色
    int heroX;//角色的X坐标
    int heroY;//角色的Y坐标
    int nextValue;//角色下一步位置的值
    //声明定义怪物
    Monster *blueSlime=new Monster(8);
    Monster *yellowSlime=new Monster(9);
    Monster *smallBat=new Monster(10);
    Monster *skeletonKnight=new Monster(11);
    Monster *exorcist=new Monster(12);
};
#endif // MAGIC_TOWER_H
