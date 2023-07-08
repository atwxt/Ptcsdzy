#include "monsterinformation.h"

MonsterInformation::MonsterInformation(QWidget* parent):QDialog(parent)
{
    //标签与图片排版
    QGridLayout *layout = new QGridLayout(parent);
    layout->addWidget(blueSlimepictureLabel,0,0);
    layout->addWidget(blueSlimeLabel,0,1);
    layout->addWidget(yellowSlimepictureLabel,1,0);
    layout->addWidget(yellowSlimeLabel,1,1);
    layout->addWidget(smallBatpictureLabel,2,0);
    layout->addWidget(smallBatLabel,2,1);
    layout->addWidget(skeletonKnightpictureLabel,3,0);
    layout->addWidget(skeletonKnightLabel,3,1);
    layout->addWidget(exorcistpictureLabel,4,0);
    layout->addWidget(exorcistLabel,4,1);
    setLayout(layout);
}
