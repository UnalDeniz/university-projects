#include "myres.h"

MyRes::MyRes(){

    label = new QLabel("0");

}

void MyRes::setMyRes(){
    label->setText(*curString);
}
