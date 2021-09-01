#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <vector>
#include <QMovie>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);//event method
    bool check_the_obstacle(int x, int y, int box);
    void go_backwards(int action);//1 is up, 2 is down, 3 is left, 4 is right
    void next_level();
    void finish_game();

public slots:
    void Up();
    void Down();
    void Left();
    void Right();
    void Hidden_point();
    void Get_coins();
    void Restart();
    void check_finished();
signals:
    void Up_signal();
    void Down_signal();
    void Left_signal();
    void Right_signal();
    void hidden_point_signal();
    void Get_coins_signal();
    void Restart_signal();
    void check_finished_signal();

private:
    Ui::MainWindow *ui;
    QLabel *label_ghost;
    QLabel *label_floor;
    QLabel *label_box1;
    QLabel *label_box2;
    QLabel *label_box3;
    QLabel *label_position1;
    QLabel *label_position2;
    QLabel *label_position3;

    QLabel *label_pass_gif = new QLabel(this);
    QMovie *movie = new QMovie(":/project 2 pic/pass_gif.gif");

    int posX=50;
    int posY=50;

    int box1_posX=150;
    int box1_posY=100;
    int box2_posX=200;
    int box2_posY=100;
    int box3_posX=250;
    int box3_posY=100;

    int hidden_point_posX=100;
    int hidden_point_posY=200;

    int wall_posX=0;
    int wall_posY=0;

    vector <int> check_wall_posX;
    vector <int> check_wall_posY;

    const int box_num=3;

    int position1_posX=50;
    int position1_posY=300;
    int position2_posX=300;
    int position2_posY=50;
    int position3_posX=300;
    int position3_posY=300;

    int box_posX_array[3];
    int box_posY_array[3];
    int position_posX_array[3]={position1_posX, position2_posX, position3_posX};
    int position_posY_array[3]={position1_posY, position2_posY, position3_posY};
    vector<int> coin_posX_array={50, 200, 300};
    vector<int> coin_posY_array={100, 250, 150};

    int steps=0;
    int coins=0;
    int level1_coins=0;

    int best_steps;
    int coin_nums;

    int level=1;

    int level1_point=0;
    int level2_point=0;
    int total_point=0;

    int a=0;

    bool choose_character=false;

    QPixmap pixmap_wall;
    QPixmap pixmap_position;
    QPixmap pixmap_coin;


protected:
    void paintEvent(QPaintEvent *);
};



#endif // MAINWINDOW_H
