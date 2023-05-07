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
    void clickedKey(const QString &word);

private:
    bool m_is_show=false;
    void connectSignal();
    void setViewConfig();
    QWidget *m_focus_widget=nullptr;

public slots:
    void showUp(QWidget *focus);

public:
    void hideDown();

private slots:
    void clickedButtonQ();

};

#endif // MYKEYBOARD_H
