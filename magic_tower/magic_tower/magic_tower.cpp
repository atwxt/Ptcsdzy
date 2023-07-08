#include "magic_tower.h"
#include <QDebug>
#include <iostream>
MagicTower::MagicTower(QWidget *parent): QWidget(parent)

{
    this->grabKeyboard();//设置接收键盘事件
    this->setFixedSize((ONCE_WIDTH+2)*60,ONCE_HEIGHT*60);//设置键位大小
    QLabel* background=new QLabel(this);//设置背景
    background->setFixedSize(this->width(),this->height());
    background->setScaledContents(true);//自动调整大小
    background->setPixmap(QPixmap(tr(":/magic_photos/start.png")));
    background->show();
    //开始按钮
    start_bt=new QPushButton("start game",this);
    start_bt->setFixedSize(150,50);
    start_bt->setFont(QFont("KaiTi",16));//字体设置
    start_bt->move(this->width()/2-70,this->height()/2-25);//位置设置
    //读档按钮
    QPushButton *Read_situation;
    Read_situation=new QPushButton("读档",this);
    Read_situation->setFixedSize(150,50);
    Read_situation->setFont(QFont("KaiTi",16));
    Read_situation->move(this->width()/2-70,this->height()/2+60);
    //初始化各个标志
    restart_signal=false;
    combate_signal=false;
    start_background_signal=false;
    //定义角色并初始化其内容
    heroX=0;
    heroY=0;
    hero->sword=false;
    hero->shield=false;
    //初始化地图lable
    qDebug()<<0;
    for(int i=0;i<ONCE_WIDTH;i++){
        for(int j=0;j<ONCE_HEIGHT;j++){
            mapLabel[i][j]=new QLabel(this);
            mapLabel[i][j]->setFixedSize(60,60);
        }
    }
    connect(start_bt,SIGNAL(clicked(bool)),this,SLOT(startGame()));
    connect(Read_situation,SIGNAL(clicked(bool)),this,SLOT(read_situation()));
}
//开始按钮点击后隐藏按钮背景，传入level初始化角色信息,初始化地图
void MagicTower::startGame()
{
    DifficultyChoose *diff = new DifficultyChoose();
    connect(diff, &DifficultyChoose::levelChosen, this, &MagicTower::startGameWithLevel);
    diff->show();
}
void MagicTower::startGameWithLevel(int level){
    if (level == 1) {
        hero=new Hero(1);
    }
    else if (level == 2) {
        hero=new Hero(2);
    }
    else if (level == 3) {
        hero=new Hero(3);
    }
    start_background_signal=true;
    start_bt->hide();
    initMap();
    init_game=false;
    showHeroInfo();
}

void MagicTower::keyPressEvent(QKeyEvent *event){
    if(!combate_signal){
        int movetype=4;//记录移动类型(0-上 1-下 2-左 3-右)
        nextValue=0;//记录走到的位置有什么东西
        switch (event->key()){
        case Qt::Key_Up:
        case Qt::Key_W:
            movetype=0;
            nextValue=present_map->map[hero->floor][heroX-1][heroY];
            heroMove(movetype);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            movetype=1;
            nextValue=present_map->map[hero->floor][heroX+1][heroY];
            heroMove(movetype);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            movetype=2;
            nextValue=present_map->map[hero->floor][heroX][heroY-1];
            heroMove(movetype);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            movetype = 3;
            nextValue=present_map->map[hero->floor][heroX][heroY+1];
            heroMove(movetype);
            break;
        default:
            break;
        }
        showHeroInfo();//刷新角色信息的显示
    }
}

void MagicTower::initMap(){
    if(restart_signal){
        //死后重新生成地图
        for(int k=0;k<TOWER_LAYER;k++){
            for(int i=0;i<ONCE_WIDTH;i++){
                for(int j=0;j<ONCE_HEIGHT;j++){
                    present_map->map[k][i][j]=init_map->map[k][i][j];
                }
            }
        }
        restart_signal=false;
    }
    //绘制当前地图
    for(int i=0;i<ONCE_HEIGHT;i++){
        for(int j=0;j<ONCE_WIDTH;j++){
            //每次到达新层，clear并更新maplabel
            mapLabel[i][j]->clear();
            mapLabel[i][j]->move(j*60,i*60);
            mapLabel[i][j]->setPixmap(QPixmap(tr(":/magic_photos/%1.png").arg(present_map->map[hero->floor][i][j])));
            mapLabel[i][j]->setScaledContents(true);
            mapLabel[i][j]->show();
            //查找角色位置
            if(present_map->map[hero->floor][i][j]==19){
                heroX=i;
                heroY=j;
            }
        }
    }
    //状态栏背景
    for(int i=0;i<ONCE_HEIGHT;i++){
        for(int j=ONCE_WIDTH;j<ONCE_WIDTH+2;j++){
            infoLabel=new QLabel(this);
            infoLabel->setFixedSize(60,60);
            infoLabel->setPixmap(QPixmap(tr(":/magic_photos/20.png")));
            infoLabel->setScaledContents(true);
            infoLabel->move(j*60,i*60);
            infoLabel->show();
        }
    }
    //状态栏内容
    //设置字体
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    //难度显示
    if(!init_game)
        diffLabel->clear();
    diffLabel=new QLabel(this);
    diffLabel->setFixedSize(60*2,50);
    diffLabel->move(ONCE_WIDTH*60,0);
    diffLabel->setPalette(palette);
    diffLabel->setFont(QFont("KaiTi",14));
    diffLabel->show();
    //金币显示
    if(!init_game)
        moneyLabel->clear();
    moneyLabel=new QLabel(this);
    moneyLabel->setFixedSize(60*2,50);
    moneyLabel->move(ONCE_WIDTH*60,60*1.5);
    moneyLabel->setPalette(palette);
    moneyLabel->setFont(QFont("KaiTi",14));
    moneyLabel->show();
    //楼层显示
    if(!init_game)
        floorLabel->clear();
    floorLabel=new QLabel(this);
    floorLabel->setFixedSize(60*2,50);
    floorLabel->move(ONCE_WIDTH*60,60*2.8);
    floorLabel->setPalette(palette);
    floorLabel->setFont(QFont("KaiTi",14));
    floorLabel->show();
    //生命值
    if(!init_game)
        bloodLabel->clear();
    bloodLabel=new QLabel(this);
    bloodLabel->setFixedSize(60*2,50);
    bloodLabel->move(ONCE_WIDTH*60,60*4.1);
    bloodLabel->setPalette(palette);
    bloodLabel->setFont(QFont("KaiTi",14));
    bloodLabel->show();
    //攻击力
    if(!init_game)
        attackLabel->clear();
    attackLabel=new QLabel(this);
    attackLabel->setFixedSize(60*2,50);
    attackLabel->move(ONCE_WIDTH*60,60*5.4);
    attackLabel->setPalette(palette);
    attackLabel->setFont(QFont("KaiTi",14));
    attackLabel->show();
    //防御力
    if(!init_game)
        defenseLabel->clear();
    defenseLabel=new QLabel(this);
    defenseLabel->setFixedSize(60*2,50);
    defenseLabel->move(ONCE_WIDTH*60,60*6.7);
    defenseLabel->setPalette(palette);
    defenseLabel->setFont(QFont("KaiTi",14));
    defenseLabel->show();
    //黄钥匙
    if(!init_game)
        yKeyLabel->clear();
    yKeyLabel=new QLabel(this);
    yKeyLabel->setFixedSize(60*2,50);
    yKeyLabel->move(ONCE_WIDTH*60,60*8);
    yKeyLabel->setPalette(palette);
    yKeyLabel->setFont(QFont("KaiTi",16));
    yKeyLabel->show();
    //蓝钥匙
    if(!init_game)
        bKeyLabel->clear();
    bKeyLabel=new QLabel(this);
    bKeyLabel->setFixedSize(60*2,50);
    bKeyLabel->move(ONCE_WIDTH*60,60*9.3);
    bKeyLabel->setPalette(palette);
    bKeyLabel->setFont(QFont("KaiTi",16));
    bKeyLabel->show();
    //怪物图鉴
    QPushButton *Monster_information;
    Monster_information=new QPushButton("图鉴");
    Monster_information->setFixedSize(60*2,50);
    Monster_information->move(ONCE_WIDTH*60,60*10.6);
    Monster_information->setPalette(palette);
    Monster_information->setFont(QFont("KaiTi",16));
    Monster_information->setParent(this);
    connect(Monster_information,&QPushButton::clicked,this,&MagicTower::show_monster_information);
    Monster_information->show();
    //存档
    QPushButton *Save_situation;
    Save_situation=new QPushButton("存档");
    Save_situation->setFixedSize(60*2,50);
    Save_situation->move(ONCE_WIDTH*60,60*11.9);
    Save_situation->setPalette(palette);
    Save_situation->setFont(QFont("KaiTi",16));
    Save_situation->setParent(this);
    connect(Save_situation,&QPushButton::clicked,this,&MagicTower::save_situation);
    Save_situation->show();
}

void MagicTower::updateMap(int type){
    if(present_map->map[hero->floor][heroX][heroY]!=21){
        present_map->map[hero->floor][heroX][heroY]=1;//先前角色所在地置为地面
    }
    mapLabel[heroX][heroY]->setPixmap(QPixmap(tr(":/magic_photos/%1.png").arg(present_map->map[hero->floor][heroX][heroY])));
    switch(type){
    case 0:
        heroX-=1;
        break;
    case 1:
        heroX+=1;
        break;
    case 2:
        heroY-=1;
        break;
    case 3:
        heroY+=1;
        break;
    default:
        break;
    }
    //角色移动后位置显示角色
    if(present_map->map[hero->floor][heroX][heroY]!=21){
        present_map->map[hero->floor][heroX][heroY]=19;
    }
    mapLabel[heroX][heroY]->setPixmap(QPixmap(tr(":/magic_photos/19.png")));
    //攻击怪物,实现图像闪烁
    if(nextValue>=8&&nextValue<=12){
        //战斗中,停止接收键盘事件
        combate_signal=true;
        //定时器显示怪物图片
        QTimer* timer1=new QTimer(this);
        connect(timer1,&QTimer::timeout,this,&MagicTower::monsterShow);
        //定时器显示角色图片
        QTimer*timer2=new QTimer(this);
        connect(timer2,&QTimer::timeout,this,&MagicTower::heroShow);
        timer1->start(100);
        QThread::msleep(50);//50ms休眠
        timer2->start(100);
        //500ms定时器,定时器结束,闪烁结束
        QTimer*timer=new QTimer(this);
        connect(timer,&QTimer::timeout,this,[=]{
            timer1->stop();
            timer2->stop();
            timer->stop();
            combate_signal=false;
            if(hero->blood>0){
                present_map->map[hero->floor][heroX][heroY]=15;
                mapLabel[heroX][heroY]->setPixmap(QPixmap(tr(":/magic_photos/19.png")));
            }
        });
        timer->start(500);
    }
}

void MagicTower::heroShow(){
    mapLabel[heroX][heroY]->setPixmap(QPixmap(tr(":/magic_photos/19.png")));
}

void MagicTower::monsterShow(){
    mapLabel[heroX][heroY]->setPixmap(QPixmap(tr(":/magic_photos/%1.png").arg(nextValue)));
}

void MagicTower::heroMove(int type){
    if(nextValue==0){//墙
        return;
    }
    else if(nextValue==1){//空地
        updateMap(type);
    }
    else if(nextValue==14&&hero->y_key>0){//黄门
        updateMap(type);
        hero->y_key--;
        showHeroInfo();
    }
    else if(nextValue==16){//黄钥匙
        updateMap(type);
        hero->y_key++;
        showHeroInfo();
    }
    else if(nextValue==13&&hero->b_key>0){//蓝门
        updateMap(type);
        hero->b_key--;
        showHeroInfo();
    }
    else if(nextValue==15){//蓝钥匙
        updateMap(type);
        hero->b_key++;
        showHeroInfo();
    }
    else if(nextValue==4){//小血瓶
        updateMap(type);
        hero->blood+=30;
        showHeroInfo();
    }
    else if(nextValue==5){//大血瓶
        updateMap(type);
        hero->blood+=80;
        showHeroInfo();
    }
    else if(nextValue==6){//红宝石
        updateMap(type);
        hero->attack+=3;
        showHeroInfo();
    }
    else if(nextValue==7){//蓝宝石
        updateMap(type);
        hero->defense+=2;
        showHeroInfo();
    }
    else if(nextValue==2){//上楼
        if(hero->floor==7){
            WinMessage();
        }
        else hero->floor+=1;
        initMap();
    }
    else if(nextValue==3){//下楼
        hero->floor-=1;
        initMap();
    }
    else if(nextValue==17){//剑
        updateMap(type);
        hero->attack+=12;
        hero->sword=true;
        showHeroInfo();
    }
    else if(nextValue==18){//盾
        updateMap(type);
        hero->defense+=8;
        hero->shield=true;
        showHeroInfo();
    }
    else if(nextValue<=12&&nextValue>=8){//怪物
        heroCombat();
        updateMap(type);
        showHeroInfo();
        // 碰见怪物,攻击结束之后判断血量
        if(hero->blood<=0){
            int loseMessage=QMessageBox::information(this,tr("游戏结束"),tr("游戏失败，是否重新开始"),QMessageBox::Yes|QMessageBox::No);
            if(loseMessage==QMessageBox::Yes){
                //重新开始
                hero=new Hero(hero->difficulty);
                restart_signal=true;
                initMap();
            }
            else{
                this->close();
            }
        }
    }
    else if(nextValue==21){
        enter_store();
        updateMap(type);
    }
}

int MagicTower::bloodcount(int monsterType){
    int monster_blood;
    int monster_attack;
    int monster_defense;
    int real_hero_attack;//英雄真伤
    int real_monster_attack;//怪物真伤
    int hero_time;//英雄击败怪物所需轮次
    int monster_time;//怪物击败英雄所需轮次
    switch(monsterType){
    case 8:
        monster_blood=blueSlime->blood;
        monster_attack=blueSlime->attack;
        monster_defense=blueSlime->defense;
        break;
    case 9:
        monster_blood=yellowSlime->blood;
        monster_attack=yellowSlime->attack;
        monster_defense=yellowSlime->defense;
        break;
    case 10:
        monster_blood=smallBat->blood;
        monster_attack=smallBat->attack;
        monster_defense=smallBat->defense;
        break;
    case 11:
        monster_blood=skeletonKnight->blood;
        monster_attack=skeletonKnight->attack;
        monster_defense=skeletonKnight->defense;
        break;
    case 12:
        monster_blood=exorcist->blood;
        monster_attack=exorcist->attack;
        monster_defense=exorcist->defense;
        break;
    }
    real_hero_attack=hero->attack-monster_defense;
    real_monster_attack=monster_attack-hero->defense;
    //英雄攻击不大于怪物防
    if(real_hero_attack<=0)
        return -1;
    //英雄先手，怪物攻击不大于英雄防御
    if(real_monster_attack<=0)
        return 0;
    hero_time=(monster_blood-1)/real_hero_attack+1;
    monster_time=(hero->blood-1)/real_monster_attack+1;
    //战斗结果
    if(hero_time>=monster_time)
        return -1;
    else
        return hero_time*real_monster_attack;
}
void MagicTower::heroCombat(){
    int change_blood=bloodcount(nextValue);
    if(change_blood<0)
        hero->blood=0;
    else{
        int monster_money;//击败怪物后可获得的金币
        switch(nextValue){
        case 8:
            monster_money=blueSlime->money;
            break;
        case 9:
            monster_money=yellowSlime->money;
            break;
        case 10:
            monster_money=smallBat->money;
            break;
        case 11:
            monster_money=skeletonKnight->money;
            break;
        case 12:
            monster_money=exorcist->money;
            break;
        }
        //血量改变
        hero->blood-=change_blood;
        //金钱改变
        hero->money+=monster_money;
    }
}
void MagicTower::show_monster_information(){
    MonsterInformation picture(this);
    QString text;
    //蓝史莱姆图鉴
    text.append("绿史莱姆  攻击:");
    text.append(QString::number(blueSlime->attack));
    text.append("  防御：");
    text.append(QString::number(blueSlime->defense));
    text.append("  生命：");
    text.append(QString::number(blueSlime->blood));
    text.append("  金币：");
    text.append(QString::number(blueSlime->money));
    text.append("  损失血量：");
    if(bloodcount(8)>=0)
        text.append(QString::number(bloodcount(8)));
    else
        text.append("???");
    picture.blueSlimepictureLabel->setPixmap(QPixmap(tr(":/magic_photos/8.png")));
    picture.blueSlimeLabel->setText(text);
    //picture.blueSlimeLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //黄史莱姆图鉴
    text.append("红史莱姆  攻击:");
    text.append(QString::number(yellowSlime->attack));
    text.append("  防御：");
    text.append(QString::number(yellowSlime->defense));
    text.append("  生命：");
    text.append(QString::number(yellowSlime->blood));
    text.append("  金币：");
    text.append(QString::number(yellowSlime->money));
    text.append("  损失血量：");
    if(bloodcount(9)>=0)
        text.append(QString::number(bloodcount(9)));
    else
        text.append("???");
    picture.yellowSlimepictureLabel->setPixmap(QPixmap(tr(":/magic_photos/9.png")));
    picture.yellowSlimeLabel->setText(text);
    //picture.yellowSlimeLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //蝙蝠图鉴
    text.append("蝙蝠  攻击:");
    text.append(QString::number(smallBat->attack));
    text.append("  防御：");
    text.append(QString::number(smallBat->defense));
    text.append("  生命：");
    text.append(QString::number(smallBat->blood));
    text.append("  金币：");
    text.append(QString::number(smallBat->money));
    text.append("  损失血量：");
    if(bloodcount(10)>=0)
        text.append(QString::number(bloodcount(10)));
    else
        text.append("???");
    picture.smallBatpictureLabel->setPixmap(QPixmap(tr(":/magic_photos/10.png")));
    picture.smallBatLabel->setText(text);
    //picture.smallBatLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //骷髅图鉴
        text.append("骷髅  攻击:");
    text.append(QString::number(skeletonKnight->attack));
    text.append("  防御：");
    text.append(QString::number(skeletonKnight->defense));
    text.append("  生命：");
    text.append(QString::number(skeletonKnight->blood));
    text.append("  金币：");
    text.append(QString::number(skeletonKnight->money));
    text.append("  损失血量：");
    if(bloodcount(11)>=0)
        text.append(QString::number(bloodcount(11)));
    else
        text.append("???");
    picture.skeletonKnightpictureLabel->setPixmap(QPixmap(tr(":/magic_photos/11.png")));
    picture.skeletonKnightLabel->setText(text);
    //picture.skeletonKnightLabel->setAlignment(Qt::AlignCenter);
    text.clear();
    //法师图鉴
    text.append("法师  攻击:");
    text.append(QString::number(exorcist->attack));
    text.append("  防御：");
    text.append(QString::number(exorcist->defense));
    text.append("  生命：");
    text.append(QString::number(exorcist->blood));
    text.append("  金币：");
    text.append(QString::number(exorcist->money));
    text.append("  损失血量：");
    if(bloodcount(12)>=0)
        text.append(QString::number(bloodcount(12)));
    else
        text.append("???");
    picture.exorcistpictureLabel->setPixmap(QPixmap(tr(":/magic_photos/12.png")));
    picture.exorcistLabel->setText(text);
    text.clear();
    picture.exec();
}

void MagicTower::showHeroInfo(){
    //难度
    diffLabel->setText("难度\n"+QString::number(hero->difficulty));
    diffLabel->setAlignment(Qt::AlignCenter);//居中显示
    //金币
    moneyLabel->setText("金币\n"+QString::number(hero->money));
    moneyLabel->setAlignment(Qt::AlignCenter);
    //楼层
    floorLabel->setText("楼层\n"+QString::number(hero->floor));
    floorLabel->setAlignment(Qt::AlignCenter);
    //生命值
    bloodLabel->setText("生命值\n"+QString::number(hero->blood));
    bloodLabel->setAlignment(Qt::AlignCenter);
    //攻击力
    attackLabel->setText("攻击力\n"+QString::number(hero->attack));
    attackLabel->setAlignment(Qt::AlignCenter);
    //防御力
    defenseLabel->setText("防御力\n"+QString::number(hero->defense));
    defenseLabel->setAlignment(Qt::AlignCenter);
    //蓝钥匙
    bKeyLabel->setText("蓝钥匙\n"+QString::number(hero->b_key));
    bKeyLabel->setAlignment(Qt::AlignCenter);
    //黄钥匙
    yKeyLabel->setText("黄钥匙\n"+QString::number(hero->y_key));
    yKeyLabel->setAlignment(Qt::AlignCenter);
}

void MagicTower::enter_store(){
    // 创建主窗口
    QDialog *store = new QDialog();
    store->setWindowTitle("商店");
    store->setFixedSize((ONCE_WIDTH-2)*60,ONCE_HEIGHT*60);

    // 创建标签
    QLabel *label = new QLabel("这里是商店，你可以使用20金币购买物品",store);
    label->setFont(QFont("KaiTi",16));
    label->move(this->width()/2-300,150);

    // 创建购买按钮
    QPushButton *buyButton1 = new QPushButton("购买攻击力3",store);
    buyButton1->setFixedSize(150, 50);
    buyButton1->setFont(QFont("KaiTi",16));
    buyButton1->move(this->width()/2-190,this->height()/2-175);

    QPushButton *buyButton2 = new QPushButton("购买防御力3",store);
    buyButton2->setFixedSize(150, 50);
    buyButton2->setFont(QFont("KaiTi",16));
    buyButton2->move(this->width()/2-190,this->height()/2-25);

    QPushButton *buyButton3 = new QPushButton("购买血量120",store);
    buyButton3->setFixedSize(150, 50);
    buyButton3->setFont(QFont("KaiTi",16));
    buyButton3->move(this->width()/2-190,this->height()/2+125);

    // 显示主窗口
    store->show();
    // 连接按钮的点击事件到对应的函数
    connect(buyButton1, &QPushButton::clicked, this, &MagicTower::buyAttack);
    connect(buyButton2, &QPushButton::clicked, this, &MagicTower::buyDefense);
    connect(buyButton3, &QPushButton::clicked, this, &MagicTower::buyBlood);
}
void MagicTower::buyAttack(){
    //金币不足弹出提示
    if(hero->money<20){
        QLabel *MoneyLabel=new QLabel(tr("你的金币不足"));
        MoneyLabel->setFixedSize(150, 50);
        MoneyLabel->setFont(QFont("KaiTi",16));
        MoneyLabel->move(this->width()-120,this->height()/2-25);
        MoneyLabel->show();
    }
    if(hero->money>=20){
        hero->attack+=3;
        hero->money-=20;
        showHeroInfo();
    }
}
void MagicTower::buyDefense(){
    if(hero->money<20){
        QLabel *MoneyLabel=new QLabel(tr("你的金币不足"));
        MoneyLabel->setFixedSize(150, 50);
        MoneyLabel->setFont(QFont("KaiTi",16));
        MoneyLabel->move(this->width()-120,this->height()/2-25);
        MoneyLabel->show();
    }
    if(hero->money>=20){
        hero->defense+=3;
        hero->money-=20;
        showHeroInfo();
    }
}
void MagicTower::buyBlood(){
    if(hero->money<20){
        QLabel *MoneyLabel=new QLabel(tr("你的金币不足"));
        MoneyLabel->setFixedSize(150, 50);
        MoneyLabel->setFont(QFont("KaiTi",16));
        MoneyLabel->move(this->width()-120,this->height()/2-25);
        MoneyLabel->show();
    }
    if(hero->money>=20){
        hero->blood+=120;
        hero->money-=20;
        showHeroInfo();
    }
}
//游戏胜利窗口
void MagicTower::WinMessage(){
    QDialog* Message=new QDialog();
    Message->setFixedSize(8*60,4*60);
    Message->setModal(true);
    QLabel* message1=new QLabel(tr("你赢了！，你的状态是：\n"),Message);
    message1->setFont(QFont("KaiTi",20));
    int mark=((hero->attack+hero->defense)*50+hero->blood)*hero->difficulty;
    QLabel* message2=new QLabel("难度:"+QString::number(hero->difficulty)
                                +"  攻击力"+QString::number(hero->attack)
                                +"  防御力"+QString::number(hero->defense)
                                +"  生命"+QString::number(hero->blood)
                                +"  得分"+QString::number(mark),Message);
    message2->setFont(QFont("KaiTi",14));
    message2->move(0,60);
    Message->show();
    Message->exec();
    int select=QMessageBox::information(this,tr("游戏结束"),tr("是否重新开始"),QMessageBox::Yes|QMessageBox::No);
    if(select==QMessageBox::Yes){
        //重新开始
        hero=new Hero(hero->difficulty);
        restart_signal=true;
        initMap();
    }
    else{
        this->close();
    }
}
//存档的实现
void MagicTower::save_situation(){
    freopen("/situation.txt","w",stdout);
    std::cout<<hero->attack<<' '<<hero->defense<<' '<<hero->blood<<' '<<hero->money<<' '<<hero->b_key<<' '<<hero->y_key<<' '<<hero->floor<<' '<<hero->sword<<' '<<hero->shield<<std::endl;
    std::cout<<heroX<<' '<<heroY<<std::endl;
    for(int i=0;i<8;i++){
        for(int j=0;j<13;j++){
            for(int k=0;k<13;k++){
                std::cout<<present_map->map[i][j][k]<<std::endl;
            }
        }
    }
}
//读档
void MagicTower::read_situation(){
    hero=new Hero(1);
    start_background_signal=true;
    start_bt->hide();
    //Read_situation->hide();
    repaint();
    freopen("/situation.txt","r",stdin);
    std::cin>>hero->attack>>hero->defense>>hero->blood>>hero->money>>hero->b_key>>hero->y_key>>hero->floor>>hero->sword>>hero->shield;
    std::cin>>heroX>>heroY;
    for(int i=0;i<8;i++){
        for(int j=0;j<13;j++){
            for(int k=0;k<13;k++){
                std::cin>>present_map->map[i][j][k];
            }
        }
    }
    initMap();
    init_game=false;
    showHeroInfo();
}
