#ifndef MYKEYBOARD_H
#define MYKEYBOARD_H

#include <QWidget>

#include "base/singleton.h"

class MyKeyboard : public QWidget, public Singleton<MyKeyboard>
{
    Q_OBJECT
public:
    explicit MyKeyboard(QWidget *parent = nullptr);
    ~MyKeyboard();

signals:


private:
    bool m_is_show=false;
    void connectSignal();

public slots:
    void popUp();

public:
    void hideDown();

private slots:


};

#endif // MYKEYBOARD_H
