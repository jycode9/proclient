#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QObject>
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();

protected:
    //override关键字，指定当前虚函数为父类的函数，可以确保重写的是父类函数
    virtual void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();

private:
    void connectSignal();

private slots:
    void clickedKey(const QString &word);
};

#endif // MYLINEEDIT_H
