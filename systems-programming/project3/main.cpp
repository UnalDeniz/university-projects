#include <QApplication>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "calcbutton.h"
#include <QGridLayout>
#include "myres.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QWidget *cw = new QWidget; // main widget
    QVBoxLayout *vb = new QVBoxLayout(cw); // timer, grid and spaceritem
    vb->setSpacing(0); //remove spaces between objects
    MyRes* mr=new MyRes(); //MyRes object for result part of the calculator
    QGridLayout *gl = new QGridLayout;
    vb->setContentsMargins(0, 0, 0, 0); //remove spaces around the window
    QString arr[20]={"+","-","=","Clr","0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

    for(int row=0; row<5;row++){
        for(int col=0; col<4; col++){ //build the calculator

            CalcButton *randButton = new CalcButton(arr[4*row+col], mr, 4*row+col-4);
            QObject::connect(randButton, SIGNAL(clicked()), randButton, SLOT(button_clicked()));

            gl->addWidget(randButton, row, col, 1, 1);

        }
    }
    QLabel* pLabel = mr -> label; //take label of the result part to add it to layout.
    pLabel->setStyleSheet("QLabel { background-color : #afeeee; }"); //change label background
    vb->addWidget(pLabel);
    vb->addLayout(gl);
    cw->setWindowTitle("Calculator");
    cw->show();
    return app.exec();
}
