#ifndef MYRES_H
#define MYRES_H

#include <QLabel>
#include <string>

using namespace std;

class MyRes : public QObject{
    Q_OBJECT
public:
    MyRes();
    QLabel *label;
    int lastInt; //holds the previous input or the output of the previous operation
    int curInt = 0; //holds the current input
    QString lastOp; //holds the operation to be calculated when a operation button is clicked
    QString* curString = new QString(""); //holds the string to be displayed in the calculator


public slots:
    void setMyRes();
};

#endif // MYRES_H
