#include "mylineedit.h"

#include <QMouseEvent>
#include <QDebug>

#include "tool/mykeyboard/mykeyboard.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
    connectSignal();
}

MyLineEdit::~MyLineEdit()
{

}

void MyLineEdit::mousePressEvent(QMouseEvent *event){
    //当点击输入框的时候，发送对应的信号
    //当控件被设为disenable的时候，是没有点击事件的
    if(event->button() == Qt::LeftButton){
        emit this->clicked();
    }

}

void MyLineEdit::connectSignal(){
    //点击输入框，弹出键盘
    connect(this, &MyLineEdit::clicked, MyKeyboard::getInstance(), &MyKeyboard::popUp);

}
