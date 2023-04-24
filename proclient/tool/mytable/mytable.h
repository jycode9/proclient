#ifndef MYTABLE_H
#define MYTABLE_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QScroller>

enum TableHeaderType{
    Horizontal,
    Vertical
};

class MyTable : public QTableView
{
    Q_OBJECT

public:
    explicit MyTable(QWidget *parent = nullptr);
    ~MyTable();

private:
    QStandardItemModel *m_model=nullptr;
    //item初始flag配置
    Qt::ItemFlags m_init_flags=Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled;
    QScroller *m_scroller=nullptr;

public:
    void setHeader(QStringList& list, TableHeaderType type);
    bool setData(int row, QStringList& list);
    QStringList getDataByRow(int row);
    QStringList getDataByColumn(int column);
    QString getDataByItem(int row, int column);
    bool setRowColor(int row, QColor color);
    bool setItemColor(int row, int column, QColor color);
    int getColumnCount();
    int getRowCount();
    int getCurRow();
    int getSelectRow();
    bool setRowReadOnly(int row, bool state);
    bool setRowEnabled(int row, bool state);
    bool setRowSelectable(int row, bool state);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYTABLE_H
