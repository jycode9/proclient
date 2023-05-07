#include "mykeyboard.h"

#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QDebug>

#include "base/glog.h"

MyKeyboard::MyKeyboard(QWidget *parent) : QWidget(parent)
{
    setViewConfig();
    connectSignal();
}

MyKeyboard::~MyKeyboard(){
    //因为keyboard为单例，所以关闭这个窗口的时候不会进行析构，只是隐藏

}

void MyKeyboard::showUp(QWidget *focus){
    m_focus_widget=focus;
    //如果键盘没有show，则直接show
    if(m_is_show==false){
        this->show();
        m_is_show=true;
    }
    else{
    }
    // 将焦点重新设置到之前的控件上
    if (m_focus_widget != nullptr) {
        //注意这里需要先将控件设为active，再进行聚焦
        m_focus_widget->activateWindow();
        m_focus_widget->setFocus();
    }
}

void MyKeyboard::connectSignal(){

}

//点击键盘的取消按键、隐藏按键将键盘隐藏掉。或者当前焦点转移在非lineedit类型上，隐藏键盘
void MyKeyboard::hideDown(){
    if(m_is_show==true){
        m_is_show=false;
        this->hide();
    }
    else{

    }
}

void MyKeyboard::setViewConfig(){

    this->setFocusPolicy(Qt::NoFocus);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //添加一个栅格布局
    //添加一个取消、确认按钮
    QGridLayout *t_grid_layout = new QGridLayout();
    t_grid_layout->setContentsMargins(10, 10, 10, 10);


    QPushButton *cancel_button = new QPushButton();
    cancel_button->setText("cancel");
    cancel_button->setFocusPolicy(Qt::NoFocus);

    QPushButton *q_button = new QPushButton();
    q_button->setText("q");
    q_button->setFocusPolicy(Qt::NoFocus);

    QPushButton *p_button = new QPushButton();
    p_button->setText("p");
    p_button->setFocusPolicy(Qt::NoFocus);

    QPushButton *a_button = new QPushButton();
    a_button->setText("a");
    a_button->setFocusPolicy(Qt::NoFocus);

    QPushButton *l_button = new QPushButton();
    l_button->setText("l");
    l_button->setFocusPolicy(Qt::NoFocus);



    connect(cancel_button, &QPushButton::clicked, this, &MyKeyboard::hideDown);
    connect(q_button, &QPushButton::clicked, this, &MyKeyboard::clickedButtonQ);

    t_grid_layout->addWidget(cancel_button, 1, 12);
    t_grid_layout->addWidget(q_button, 2, 1);
    t_grid_layout->addWidget(p_button, 2, 11);
    t_grid_layout->addWidget(a_button, 3, 1);
    t_grid_layout->addWidget(l_button, 3, 10);

    this->setLayout(t_grid_layout);

    //对每一个button设置一个属性用以区分其功能。
    //在点击一个按钮的时候，对比属性，并根据属性匹配事件

}

void MyKeyboard::clickedButtonQ(){

    //点击q按钮，发送信号告知调用的lineedit输入的内容
    emit clickedKey("q");
    // 将焦点重新设置到之前的控件上
    if (m_focus_widget != nullptr) {
        m_focus_widget->activateWindow();
        m_focus_widget->setFocus();
    }
}
