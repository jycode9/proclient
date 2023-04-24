#include "mytable.h"

#include <QDebug>
#include <QMouseEvent>
#include <QBrush>
#include <QHeaderView>  //表头

#include "base/glog.h"


MyTable::MyTable(QWidget *parent) :
    QTableView(parent)
{
    m_model=new QStandardItemModel(this);
    //将model添加到view中
    this->setModel(m_model);
    //选择一个单元格，默认选中一行
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //仅可选择一行（禁止多行）
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置列头和行头不可点击选择
    this->horizontalHeader()->setEnabled(false);
    this->verticalHeader()->setEnabled(false);
}

MyTable::~MyTable()
{

}

void MyTable::setHeader(QStringList& list, TableHeaderType type){
    if(type==TableHeaderType::Vertical){
        m_model->setVerticalHeaderLabels(list);
    }
    else{
        m_model->setHorizontalHeaderLabels(list);
    }
}

bool MyTable::setData(int row, QStringList& list){
    //如果输入的list的列数与表的列数不一致如何处理？
    QList<QStandardItem*> item;
    for(auto itr=list.begin(); itr!=list.end(); itr++){
        if((*itr).isNull()){

            return false;
        }
        item<<new QStandardItem(*itr);
    }
    m_model->insertRow(row, item);
    return true;
}

QStringList MyTable::getDataByRow(int row){
    //model的take方法会将item指针取走。只能遍历
    //注意未设置item的单元格会是空指针，需要进行处理
    int column=m_model->columnCount();
    QStringList list;
    for(int i=0; i<column; i++){
        QStandardItem* item=m_model->item(row, i);
        if(item!=nullptr){
            list.push_back(item->text());
        }
        else{

            list.push_back(QString(""));;
        }
    }
    return list;
}

QStringList MyTable::getDataByColumn(int column){
    int row=m_model->rowCount();
    QStringList list;
    for(int i=0; i<row; i++){
        QStandardItem* item=m_model->item(i, column);
        if(item!=nullptr){
            list.push_back(item->text());
        }
        else{
            list.push_back(QString(""));;
        }
    }
    return list;
}

QString MyTable::getDataByItem(int row, int column){
    QStandardItem* item=m_model->item(row, column);
    if(item!=nullptr){
        return item->text();
    }

    return QString("");
}

void MyTable::mousePressEvent(QMouseEvent *event){
    //获取当前点击的行
    if(event->button()==Qt::LeftButton){
        //必须再次获取才能进行currentrow的切换
        QTableView::mousePressEvent(event);
        if(this->selectedIndexes().size()!=0){
        }
        else{
        }
    }
}

bool MyTable::setRowColor(int row, QColor color){
    //获取这个表有多少column，遍历所有column，将整行设为参数中的颜色
    if(row<0 || row>getRowCount()){

        return false;
    }

    for(int i=0; i<getColumnCount(); i++){
        if(m_model->setData(m_model->index(row, i), QBrush(color), Qt::BackgroundRole)==false){

            return false;
        }
    }
    return true;
}

bool MyTable::setItemColor(int row, int column, QColor color){
    if(row<0 || row>getRowCount()){

        return false;
    }
    if(column<0 || column>getColumnCount()){

        return false;
    }

    if(m_model->setData(m_model->index(row, column), QBrush(color), Qt::BackgroundRole)==false){

        return false;
    }

    return true;
}

int MyTable::getColumnCount(){
    return m_model->columnCount();
}

int MyTable::getRowCount(){
    return m_model->rowCount();
}

int MyTable::getCurRow(){
    return this->currentIndex().row();
}

int MyTable::getSelectRow(){
    if(this->selectedIndexes().size()!=0){
        return this->selectedIndexes().begin()->row();
    }
    else{

        return -1;
    }

}

bool MyTable::setRowReadOnly(int row, bool state){
    //设置一行只读
    for(int i=0; i<getColumnCount(); i++){
        //true为只读
        if(state==true){
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setEditable(false);
        }
        else{
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setEditable(true);
        }
    }
    return true;
}

bool MyTable::setRowEnabled(int row, bool state){
    //设置一行使能状态
    for(int i=0; i<getColumnCount(); i++){
        //true为使能
        if(state==true){
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setEnabled(false);
        }
        else{
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setEnabled(true);
        }
    }
    return true;
}

bool MyTable::setRowSelectable(int row, bool state){
    //设置一行选择状态及编辑状态
    for(int i=0; i<getColumnCount(); i++){
        //true为使能
        if(state==true){
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setFlags(m_model->item(row, i)->flags()&(~Qt::ItemIsSelectable)&(~Qt::ItemIsEditable));
        }
        else{
            if(m_model->item(row, i)==nullptr){

                return false;
            }
            m_model->item(row, i)->setFlags(m_model->item(row, i)->flags()|(Qt::ItemIsSelectable)|(Qt::ItemIsEditable));
        }
    }
    return true;
}
