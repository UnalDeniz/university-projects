#ifndef CALCBUTTON_H
#define CALCBUTTON_H

#include <QPushButton>
#include <QPalette>
#include "myres.h"

class CalcButton : public QPushButton
{
    Q_OBJECT
public:
    CalcButton(const QString& text, MyRes *mr, int value,
                QWidget* parent = 0);
    QString text; //text of the button
    MyRes *mr;  //pointer to result section
    int value;
public slots:
    void button_clicked(); //holds the function for the clicking the button activities.
    QString convert_to_string(int number); //convert number to string.
};


#endif // CALCBUTTON_H
