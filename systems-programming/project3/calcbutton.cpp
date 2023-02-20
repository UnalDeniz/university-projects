#include "calcbutton.h"
#include <QPushButton>
#include <iostream>
#include "myres.h"

CalcButton::CalcButton(const QString& text, MyRes *mr, int value,
                         QWidget* parent):
    QPushButton(text, parent)
{
    this->mr=mr;
    this->text=text;
    this->value=value;

    QPalette pal = palette(); //palette object for the colors of the button

    pal.setColor(QPalette::Button, QColor(Qt::white));
    pal.setColor(QPalette::ButtonText, QColor(Qt::black));

    setFlat(true);
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void CalcButton::button_clicked(){
    QString& buttonText=this->text;

    if(buttonText=="Clr"){ //if the clr button is clicked the calculator will reset to its inital state.

        mr->curString->clear();
        mr->label->setText("0"); //resets the display
        mr->lastOp = "";
        mr->lastInt = 0; //clears the previous inputs
        mr-> curInt = 0;

    } else if(buttonText=="="){ //if the = button is clicked the previous operation will be calculated and the result will be displayed.

        if(mr->lastOp =="+"){ //if the previous operation is + sums the the previous inputs
            mr->lastInt = mr->lastInt + mr->curInt;
            mr->curInt = 0;
        } else if(mr->lastOp == "-"){ //if the previous operation is - subtracts the the previous inputs
            mr->lastInt = mr->lastInt - mr->curInt;
            mr->curInt = 0;
        } else if(mr->lastOp == "="){ //does nothing on consecutive clicks on = button
        } else { //if the button is pressed without doing any operation the preivous input will be the result
            mr->lastInt = mr->curInt;
            mr->curInt = 0;
        }
        QString result = convert_to_string(mr->lastInt); //converts the output to string to be displayed.
        mr->curString->clear(); //clears the display before appending the result
        mr->curString->append(result);
        mr->setMyRes(); //updates the display
        mr->curString->clear(); //prepares the display for the next input
        mr->lastOp = "="; //sets the last operation as =

    } else if(buttonText=="+" || buttonText=="-"){

        if(mr->lastInt != 0 && mr->curInt == 0 && mr->lastOp == "="){ //if the previous operation is = uses the previous output as input
            mr->lastOp = buttonText;
            mr->curString->clear();
        } else if(mr->lastOp =="+"){ //if the previous operation is + sums the previous 2 inputs and uses the output as the first input of the current operation
            mr->lastInt = mr->lastInt + mr->curInt;
            mr->curInt = 0;
            mr->lastOp = buttonText; //updates the operation
            QString result = convert_to_string(mr->lastInt); //converts the output to string to be displayed.
            mr->curString->clear();
            mr->curString->append(result);
            mr->setMyRes();
            mr->curString->clear();
        } else if(mr->lastOp == "-"){ //if the previous operation is - subtracts the previous 2 inputs and uses the output as the first input of the current operation
            mr->lastInt = mr->lastInt - mr->curInt;
            mr->curInt = 0;
            mr->lastOp = buttonText;
            QString result = convert_to_string(mr->lastInt);
            mr->curString->clear();
            mr->curString->append(result);
            mr->setMyRes();
            mr->curString->clear();
        } else { //if there is no previous operation does nothing until the second input is given
            mr->lastInt = mr->curInt;
            mr->curInt = 0;
            mr->lastOp = buttonText;
            mr->curString->clear();
        }

    } else { //if a number button is clicked updates the current input and display

        mr->curString->append(this->text); //appends the clicked character
        mr->setMyRes(); //updates the display
        mr->curInt = 16 * mr->curInt + this->value;

    }

}

QString CalcButton::convert_to_string(int number){ //converts a number to string

    QString str = "";
    int remainder;
    char character;
    int neg = 0;

    if(number < 0){ //if the number is negative takes its positive to correctly convert it into string and sets neg flag to 1
        neg = 1;
        number = 0-number;
    }
    if(number == 0){
        str.append('0');
    }
    while(number != 0){ //takes the remainder from the division of the number to 16 to get its right most digit, repeats until there is no more digits.

        remainder = number % 16;
        if(remainder > 9){ //if the number is hexadecimal digit adds 55 to convert it to corresponding character
            character = remainder + 55;
        } else { //if the number is decimal digit adds 48 to convert it to corresponding character
            character = remainder + 48;
        }
        str.prepend(character);
        number = number / 16; //takes the quotient as number and repeats the process

    }
    if(neg == 1){ //if the number is negative prepends a - character to the string
        str.prepend('-');
    }
    return str;

}
