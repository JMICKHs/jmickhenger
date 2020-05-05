#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include <QMdiArea>
#include <QSize>
#include <QPoint>
#include <QVBoxLayout>
#include <QPushButton>
#include "custommbutton/CustomButton.h"
#include <QLabel>
#include <QFrame>
#include "grouplist/grouplist.h"


namespace Ui {
class MenuWidget;
}

class MenuWidget : public QFrame
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
     CustomButton* getCreateButton();
    ~MenuWidget();

private:
    Ui::MenuWidget *ui;

public slots:
    void setPosition();

signals:
    void createGroupSignal(Chat &chat);
};

#endif // MENUWIDGET_H
