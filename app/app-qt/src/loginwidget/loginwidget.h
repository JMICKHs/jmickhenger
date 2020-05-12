#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <netlib/info/Info.h>
#include <app-qt/src/models/usermodel.h>
#include <memory>
using namespace inf;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void login(const QString &log,const QString &password);
    void registration(const Account &acc);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

    void on_RegistrationButton_clicked();

    void on_returnButton_clicked();

    void on_registrateButton_clicked();
public slots:
    void showMainWidgetSlot();
signals:
   void openMainWidget(std::shared_ptr<UserModel> &);

private:
    Ui::LoginWidget *ui;
    QWidget *log;
    QWidget *reg;
    std::shared_ptr<UserModel> userPtr;
};

#endif // LOGINWIDGET_H
