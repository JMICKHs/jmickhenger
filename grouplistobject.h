#ifndef GROUPLISTOBJECT_H
#define GROUPLISTOBJECT_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QFocusEvent>
#include <QString>



class GroupListObject : public QListWidget
{
    Q_OBJECT
private:
    std::vector<QListWidgetItem> items;

public slots:


public:
    explicit GroupListObject(QWidget *parent = nullptr);

};

#endif // GROUPLISTOBJECT_H
