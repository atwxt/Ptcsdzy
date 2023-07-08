#ifndef DIFFICULTY_CHOOSE_H
#define DIFFICULTY_CHOOSE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class DifficultyChoose : public QWidget
{
    Q_OBJECT

public:
    explicit DifficultyChoose(QWidget *parent = nullptr);
    ~DifficultyChoose() {}

signals:
    void levelChosen(int level);//难度选择

private slots:
    //难度键位点击
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();

private:
    //三个键位和level
    int level;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // DIFFICULTY_CHOOSE_H
