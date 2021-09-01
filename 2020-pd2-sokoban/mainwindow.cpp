#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPixmap>
#include<iostream>
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("#MainWindow{border-image:url(:/project 2 pic/ground.png);}");

    label_ghost = new QLabel(this);
    label_box1 = new QLabel(this);
    label_box2 = new QLabel(this);
    label_box3 = new QLabel(this);

    label_ghost->setGeometry(posX, posY, 50, 50);
    label_box1->setGeometry(box1_posX, box1_posY, 50, 50);
    label_box2->setGeometry(box2_posX, box2_posY, 50, 50);
    label_box3->setGeometry(box3_posX, box3_posY, 50, 50);

    QPixmap ghost;
    QPixmap box(":/project 2 pic/box.jpg");
    QPixmap coin(":/project 2 pic/coin.png");

    label_box1->setPixmap(box);
    label_box2->setPixmap(box);
    label_box3->setPixmap(box);

    label_box1->setScaledContents(true);
    label_box2->setScaledContents(true);
    label_box3->setScaledContents(true);

    pixmap_wall.load(":/project 2 pic/wall.jpg");
    pixmap_position.load(":/project 2 pic/position.png");

    ui->steps_num->setStyleSheet("font: 18pt;");
    ui->coins_num->setStyleSheet("font: 18pt;");
    ui->level1_point->setStyleSheet("font: 15pt;");
    ui->level1_point_num->setStyleSheet("font: 15pt;");
    ui->level2_point->setStyleSheet("font: 15pt;");
    ui->level2_point_num->setStyleSheet("font: 15pt;");
    ui->total_point->setStyleSheet("font: 15pt;");
    ui->total_point_num->setStyleSheet("font: 15pt;");

    connect(this, SIGNAL(Up_signal()), this, SLOT(Up()));
    connect(this, SIGNAL(Down_signal()), this, SLOT(Down()));
    connect(this, SIGNAL(Left_signal()), this, SLOT(Left()));
    connect(this, SIGNAL(Right_signal()), this, SLOT(Right()));

    connect(this, SIGNAL(hidden_point_signal()), this, SLOT(Hidden_point()));
    connect(this, SIGNAL(Get_coins_signal()), this, SLOT(Get_coins()));

    connect(this, SIGNAL(Restart_signal()), this, SLOT(Restart()));
    connect(this, SIGNAL(check_finished_signal()), this, SLOT(check_finished()));

    connect(ui->restart, SIGNAL(clicked()), this, SLOT(Restart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_the_obstacle(int x, int y, int box_num){

       for(string::size_type i = 0;i<check_wall_posX.size();i++){
           if(x==check_wall_posX.at(i) && y==check_wall_posY.at(i)){
               return false;
           }
       }

       if(box_num==1)
           if((x==box2_posX && y==box2_posY) || (x==box3_posX && y==box3_posY))
                   return false;
       if(box_num==2)
           if((x==box1_posX && y==box1_posY) || (x==box3_posX && y==box3_posY))
                   return false;
       if(box_num==3)
           if((x==box2_posX && y==box2_posY) || (x==box1_posX && y==box1_posY))
                   return false;
       return true;

}

void MainWindow::go_backwards(int action){

    int displacement;
    if(action==1||action==3)
        displacement=50;
    else
        displacement=-50;
    if(action==1||action==2){
        if(!check_the_obstacle(posX, posY, 0)){
        label_ghost->setGeometry(posX, posY+=displacement, 50, 50);
        steps--;
        }
        if(!check_the_obstacle(box1_posX, box1_posY, 1)){
            label_ghost->setGeometry(posX, posY+=displacement, 50, 50);
            label_box1->setGeometry(box1_posX, box1_posY+=displacement, 50, 50);
            steps--;
        }
        if(!check_the_obstacle(box2_posX, box2_posY, 2)){
            label_ghost->setGeometry(posX, posY+=displacement, 50, 50);
            label_box2->setGeometry(box2_posX, box2_posY+=displacement, 50, 50);
            steps--;
        }
        if(!check_the_obstacle(box3_posX, box3_posY, 3)){
            label_ghost->setGeometry(posX, posY+=displacement, 50, 50);
            label_box3->setGeometry(box3_posX, box3_posY+=displacement, 50, 50);
            steps--;
        }
    }
    if(action==3||action==4){
        if(!check_the_obstacle(posX, posY, 0)){
            label_ghost->setGeometry(posX+=displacement, posY, 50, 50);
            steps--;
        }
        if(!check_the_obstacle(box1_posX, box1_posY, 1)){
            label_ghost->setGeometry(posX+=displacement, posY, 50, 50);
            label_box1->setGeometry(box1_posX+=displacement, box1_posY, 50, 50);
            steps--;
        }
        if(!check_the_obstacle(box2_posX, box2_posY, 2)){
            label_ghost->setGeometry(posX+=displacement, posY, 50, 50);
            label_box2->setGeometry(box2_posX+=displacement, box2_posY, 50, 50);
            steps--;
        }
        if(!check_the_obstacle(box3_posX, box3_posY, 3)){
            label_ghost->setGeometry(posX+=displacement, posY, 50, 50);
            label_box3->setGeometry(box3_posX+=displacement, box3_posY, 50, 50);
            steps--;
        }
    }
}

void MainWindow::finish_game(){

    level=3;
    level2_point=coins*20-steps*10;
    ui->level2_point_num->setNum(level2_point);
    total_point=level1_point+level2_point;
    ui->total_point_num->setNum(total_point);
    label_pass_gif->setMovie(movie);
    label_pass_gif->setGeometry(150, 400, 550, 300);
    label_pass_gif->setScaledContents(true);
    movie->start();
    label_pass_gif->show();

}

void MainWindow::check_finished(){

    box_posX_array[0]=box1_posX;
    box_posX_array[1]=box2_posX;
    box_posX_array[2]=box3_posX;
    box_posY_array[0]=box1_posY;
    box_posY_array[1]=box2_posY;
    box_posY_array[2]=box3_posY;

    int success=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(box_posX_array[j]==position_posX_array[i] && box_posY_array[j]==position_posY_array[i])
                success++;
            if(success==3){
                if(level==1){
                    next_level();
                    goto here;
                }
                else if (level==2){
                    finish_game();
                    goto here;
                }
            }
        }
    }
    here:;
}

void MainWindow::next_level(){

    level=2;

    this->setStyleSheet("#MainWindow{border-image:url(:/project 2 pic/snow.png);}");

    check_wall_posX.clear();
    check_wall_posY.clear();
    posX=100;
    posY=50;
    box1_posX=100;
    box1_posY=100;
    box2_posX=150;
    box2_posY=100;
    box3_posX=150;
    box3_posY=150;
    position1_posX=50;
    position1_posY=300;
    position2_posX=200;
    position2_posY=300;
    position3_posX=250;
    position3_posY=250;

    position_posX_array[0]=50;
    position_posX_array[1]=200;
    position_posX_array[2]=250;
    position_posY_array[0]=300;
    position_posY_array[1]=300;
    position_posY_array[2]=250;

    coin_posX_array[0]=50;
    coin_posX_array[1]=100;
    coin_posX_array[2]=300;
    coin_posY_array[0]=100;
    coin_posY_array[1]=300;
    coin_posY_array[2]=150;

    hidden_point_posX=300;
    hidden_point_posY=100;

    level1_point=coins*20-steps*10;
    ui->level1_point_num->setNum(level1_point);

    steps=0;
    ui->steps_num->setNum(steps);
    coins=0;
    ui->coins_num->setNum(coins);

    label_ghost->setGeometry(posX, posY, 50, 50);
    label_box1->setGeometry(box1_posX, box1_posY, 50, 50);
    label_box2->setGeometry(box2_posX, box2_posY, 50, 50);
    label_box3->setGeometry(box3_posX, box3_posY, 50, 50);
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter paint_map(this);

    if(level==1){

    for(int i=0;i<8;i++){
        paint_map.drawPixmap(wall_posX+i*50, wall_posY, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+i*50);
        check_wall_posY.push_back(wall_posY);
    }
    for(int i=0;i<8;i++){
        paint_map.drawPixmap(wall_posX, wall_posY+i*50, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX);
        check_wall_posY.push_back(wall_posY+i*50);
    }
    for(int i=0;i<8;i++){
        paint_map.drawPixmap(wall_posX+350, wall_posY+i*50, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+350);
        check_wall_posY.push_back(wall_posY+i*50);
    }
    for(int i=0;i<8;i++){
        paint_map.drawPixmap(wall_posX+i*50, wall_posY+350, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+i*50);
        check_wall_posY.push_back(wall_posY+350);
    }
    for(int i=0;i<3;i++){
        paint_map.drawPixmap(wall_posX+50, wall_posY+150+50*i, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+50);
        check_wall_posY.push_back(wall_posY+150+50*i);
    }
    paint_map.drawPixmap(wall_posX+100, wall_posY+150, 50, 50, pixmap_wall);
    check_wall_posX.push_back(wall_posX+100);
    check_wall_posY.push_back(wall_posY+150);
    paint_map.drawPixmap(wall_posX+100, wall_posY+250, 50, 50, pixmap_wall);
    check_wall_posX.push_back(wall_posX+100);
    check_wall_posY.push_back(wall_posY+250);
    paint_map.drawPixmap(wall_posX+250, wall_posY+250, 50, 50, pixmap_wall);
    check_wall_posX.push_back(wall_posX+250);
    check_wall_posY.push_back(wall_posY+250);
    paint_map.drawPixmap(wall_posX+250, wall_posY+300, 50, 50, pixmap_wall);
    check_wall_posX.push_back(wall_posX+250);
    check_wall_posY.push_back(wall_posY+300);
    paint_map.drawPixmap(wall_posX+200, wall_posY+150, 50, 50, pixmap_wall);
    check_wall_posX.push_back(wall_posX+200);
    check_wall_posY.push_back(wall_posY+150);

    paint_map.drawPixmap(position1_posX, position1_posY, 50, 50, pixmap_position);
    paint_map.drawPixmap(position2_posX, position2_posY, 50, 50, pixmap_position);
    paint_map.drawPixmap(position3_posX, position3_posY, 50, 50, pixmap_position);
    }

    else{
        for(int i=1;i<8;i++){
            paint_map.drawPixmap(wall_posX+i*50, wall_posY, 50, 50, pixmap_wall);
            check_wall_posX.push_back(wall_posX+i*50);
            check_wall_posY.push_back(wall_posY);
        }
        for(int i=1;i<8;i++){
            paint_map.drawPixmap(wall_posX, wall_posY+i*50, 50, 50, pixmap_wall);
            check_wall_posX.push_back(wall_posX);
            check_wall_posY.push_back(wall_posY+i*50);
        }
        for(int i=0;i<6;i++){
            paint_map.drawPixmap(wall_posX+350, wall_posY+i*50, 50, 50, pixmap_wall);
            check_wall_posX.push_back(wall_posX+350);
            check_wall_posY.push_back(wall_posY+i*50);
        }
        for(int i=0;i<6;i++){
            paint_map.drawPixmap(wall_posX+i*50, wall_posY+350, 50, 50, pixmap_wall);
            check_wall_posX.push_back(wall_posX+i*50);
            check_wall_posY.push_back(wall_posY+350);
        }
        paint_map.drawPixmap(wall_posX+50, wall_posY+50, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+50);
        check_wall_posY.push_back(wall_posY+50);
        paint_map.drawPixmap(wall_posX+100, wall_posY+200, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+100);
        check_wall_posY.push_back(wall_posY+200);
        paint_map.drawPixmap(wall_posX+100, wall_posY+250, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+100);
        check_wall_posY.push_back(wall_posY+250);
        paint_map.drawPixmap(wall_posX+200, wall_posY+200, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+200);
        check_wall_posY.push_back(wall_posY+200);
        paint_map.drawPixmap(wall_posX+250, wall_posY+300, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+250);
        check_wall_posY.push_back(wall_posY+300);
        paint_map.drawPixmap(wall_posX+300, wall_posY+300, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+300);
        check_wall_posY.push_back(wall_posY+300);
        paint_map.drawPixmap(wall_posX+300, wall_posY+250, 50, 50, pixmap_wall);
        check_wall_posX.push_back(wall_posX+300);
        check_wall_posY.push_back(wall_posY+250);

        paint_map.drawPixmap(position1_posX, position1_posY, 50, 50, pixmap_position);
        paint_map.drawPixmap(position2_posX, position2_posY, 50, 50, pixmap_position);
        paint_map.drawPixmap(position3_posX, position3_posY, 50, 50, pixmap_position);
    }

    update();

}

void MainWindow::Up(){
    label_ghost->setGeometry(posX, posY-=50, 50, 50);//up is minus!!

    if(posX==box1_posX && posY==box1_posY){
        label_box1->setGeometry(box1_posX, box1_posY-=50, 50, 50);
    }
    if(posX==box2_posX && posY==box2_posY){
        label_box2->setGeometry(box2_posX, box2_posY-=50, 50, 50);
    }
    if(posX==box3_posX && posY==box3_posY){
        label_box3->setGeometry(box3_posX, box3_posY-=50, 50, 50);
    }
    go_backwards(1);
    steps++;
    ui->steps_num->setNum(steps);
}
void MainWindow::Down(){
    label_ghost->setGeometry(posX, posY+=50, 50, 50);//down is plus!!
    if(posX==box1_posX && posY==box1_posY){
        label_box1->setGeometry(box1_posX, box1_posY+=50, 50, 50);
    }
    if(posX==box2_posX && posY==box2_posY){
        label_box2->setGeometry(box2_posX, box2_posY+=50, 50, 50);
    }
    if(posX==box3_posX && posY==box3_posY){
        label_box3->setGeometry(box3_posX, box3_posY+=50, 50, 50);
    }
    go_backwards(2);
    steps++;
    ui->steps_num->setNum(steps);
}
void MainWindow::Left(){
    label_ghost->setGeometry(posX-=50, posY, 50, 50);
    if(posX==box1_posX && posY==box1_posY){
        label_box1->setGeometry(box1_posX-=50, box1_posY, 50, 50);
    }
    if(posX==box2_posX && posY==box2_posY){
        label_box2->setGeometry(box2_posX-=50, box2_posY, 50, 50);
    }
    if(posX==box3_posX && posY==box3_posY){
        label_box3->setGeometry(box3_posX-=50, box3_posY, 50, 50);
    }
    go_backwards(3);
    steps++;
    ui->steps_num->setNum(steps);
}
void MainWindow::Right(){
    label_ghost->setGeometry(posX+=50, posY, 50, 50);
    if(posX==box1_posX && posY==box1_posY){
        label_box1->setGeometry(box1_posX+=50, box1_posY, 50, 50);
    }
    if(posX==box2_posX && posY==box2_posY){
        label_box2->setGeometry(box2_posX+=50, box2_posY, 50, 50);
    }
    if(posX==box3_posX && posY==box3_posY){
        label_box3->setGeometry(box3_posX+=50, box3_posY, 50, 50);
    }
    go_backwards(4);
    steps++;
    ui->steps_num->setNum(steps);
}

void MainWindow::Hidden_point(){

    if(level==1){
       cout << "You step on hidden point. Go to level 2 directly." << endl;
       next_level();
    }
    else{
       if(a!=1){
       cout << "You step on hidden point and pass all levels. Congrats." << endl;
       a++;
       }
       finish_game();
    }
}

void MainWindow::Get_coins(){
    coins+=10;
    ui->coins_num->setNum(coins);
}

void MainWindow::Restart(){
    if(level==1){
        posX=50;
        posY=50;
        box1_posX=150;
        box1_posY=100;
        box2_posX=200;
        box2_posY=100;
        box3_posX=250;
        box3_posY=100;
        coin_posX_array[0]=50;
        coin_posX_array[1]=200;
        coin_posX_array[2]=300;
        coin_posY_array[0]=100;
        coin_posY_array[1]=250;
        coin_posY_array[2]=150;
        coins=0;
    }
    else{
        posX=100;
        posY=50;
        box1_posX=100;
        box1_posY=100;
        box2_posX=150;
        box2_posY=100;
        box3_posX=150;
        box3_posY=150;
        coin_posX_array[0]=50;
        coin_posX_array[1]=100;
        coin_posX_array[2]=300;
        coin_posY_array[0]=100;
        coin_posY_array[1]=300;
        coin_posY_array[2]=150;
        coins=0;
        if(level==3){
            level--;
            label_pass_gif->hide();
            level2_point=0;
            total_point=0;
            a=0;
            ui->level2_point_num->setNum(level2_point);
            ui->total_point_num->setNum(total_point);
        }
    }
    steps=0;
    label_ghost->setGeometry(posX, posY, 50, 50);
    label_box1->setGeometry(box1_posX, box1_posY, 50, 50);
    label_box2->setGeometry(box2_posX, box2_posY, 50, 50);
    label_box3->setGeometry(box3_posX, box3_posY, 50, 50);
    ui->coins_num->setNum(coins);
    ui->steps_num->setNum(steps);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(level!=3 && choose_character==true){
        if(e->key()==Qt::Key_Up){
            //Up();
            emit Up_signal();
            emit check_finished_signal();
        }
        if(e->key()==Qt::Key_Down){
            //Down();
            emit Down_signal();
            emit check_finished_signal();
        }
        if(e->key()==Qt::Key_Left){
            //Left();
            emit Left_signal();
            emit check_finished_signal();
        }
        if(e->key()==Qt::Key_Right){
            //Right();
            emit Right_signal();
            emit check_finished_signal();
        }
     }
        if(posX==hidden_point_posX && posY==hidden_point_posY){
            emit hidden_point_signal();
        }
        for(string::size_type i=0;i<coin_posX_array.size();i++){
            if(coin_posX_array[i]==posX && coin_posY_array[i]==posY){
                coin_posX_array[i]=-1;
                coin_posY_array[i]=-1;
                emit Get_coins_signal();
            }
        }
    if(choose_character==false){
        if(e->key()==Qt::Key_1){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/Boos.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
        if(e->key()==Qt::Key_2){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/King_koopa.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
        if(e->key()==Qt::Key_3){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/Toad.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
        if(e->key()==Qt::Key_4){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/Koopa.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
        if(e->key()==Qt::Key_5){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/Yoshi.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
        if(e->key()==Qt::Key_6){
            choose_character=true;
            QPixmap ghost(":/project 2 pic/Goomba.png");
            label_ghost->setPixmap(ghost);
            label_ghost->setScaledContents(true);
        }
   }

}
