#ifndef MONSTERINFORMATION_H
#define MONSTERINFORMATION_H
#include "qlabel.h"
#include<QPushButton>
#include<QWidget>
#include<QDialog>
#include<QGridLayout>

class MonsterInformation: public QDialog
{
public:
    MonsterInformation(QWidget* parent=nullptr);
    ~MonsterInformation(){};
    QLabel *blueSlimeLabel=new QLabel(this);//蓝史莱姆图鉴
    QLabel *yellowSlimeLabel=new QLabel(this);//黄史莱姆图鉴
    QLabel *smallBatLabel=new QLabel(this);//蝙蝠图鉴
    QLabel *skeletonKnightLabel=new QLabel(this);//骷髅图鉴
    QLabel *exorcistLabel=new QLabel(this);//法师图鉴
    QLabel *blueSlimepictureLabel=new QLabel(this);//蓝史莱姆图片
    QLabel *yellowSlimepictureLabel=new QLabel(this);//黄史莱姆图片
    QLabel *smallBatpictureLabel=new QLabel(this);//蝙蝠图片
    QLabel *skeletonKnightpictureLabel=new QLabel(this);//骷髅图片
    QLabel *exorcistpictureLabel=new QLabel(this);//法师图片
};

#endif // MONSTERINFORMATION_H
