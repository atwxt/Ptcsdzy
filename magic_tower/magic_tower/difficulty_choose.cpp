#include "difficulty_choose.h"

DifficultyChoose::DifficultyChoose(QWidget *parent) : QWidget(parent), level(0)
{
    this->setFixedSize(15*60,13*60);
    // 创建三个按钮
    button1 = new QPushButton(tr("难度一"),this);
    button1->setFixedSize(150, 50);
    button1->setFont(QFont("KaiTi",16));
    button1->move(this->width()/2-70,this->height()/2-175);

    button2 = new QPushButton(tr("难度二"),this);
    button2->setFixedSize(150, 50);
    button2->setFont(QFont("KaiTi",16));
    button2->move(this->width()/2-70,this->height()/2-25);

    button3 = new QPushButton(tr("难度三"),this);
    button3->setFixedSize(150, 50);
    button3->setFont(QFont("KaiTi",16));
    button3->move(this->width()/2-70,this->height()/2+125);

    // 连接三个按钮的点击事件到槽函数
    connect(button1, &QPushButton::clicked, this, &DifficultyChoose::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &DifficultyChoose::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &DifficultyChoose::onButton3Clicked);
}

void DifficultyChoose::onButton1Clicked()
{
    level = 1;
    emit levelChosen(level);
    close();
}

void DifficultyChoose::onButton2Clicked()
{
    level = 2;
    emit levelChosen(level);
    close();
}

void DifficultyChoose::onButton3Clicked()
{
    level = 3;
    emit levelChosen(level);
    close();
}
