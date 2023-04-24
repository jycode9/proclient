#include "mykeyboard.h"

#include "base/glog.h"

MyKeyboard::MyKeyboard(QWidget *parent) : QWidget(parent)
{
    connectSignal();
}

MyKeyboard::~MyKeyboard(){
    //因为keyboard为单例，所以关闭这个窗口的时候不会进行析构，只是隐藏

}

void MyKeyboard::popUp(){
    //如果键盘没有show，则直接show
    if(m_is_show==false){
        this->show();
        m_is_show=true;
    }
    else{
    }
}

void MyKeyboard::connectSignal(){

}

void MyKeyboard::hideDown(){
    if(m_is_show==true){
        m_is_show=false;

    }
    else{

    }
}
