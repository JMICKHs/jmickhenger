#ifndef SETAVATARWIDGET_H
#define SETAVATARWIDGET_H

#include <QWidget>
#include <vector>
enum class baseAvatars{
    AVATAR1,
    AVATAR2,
    AVATAR3,
    AVATAR4,
    AVATAR5,
    AVATAR6,
    AVATAR7,
    AVATAR8,
};

namespace Ui {
class SetAvatarWidget;
}

class SetAvatarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetAvatarWidget(QWidget *parent = nullptr);
    ~SetAvatarWidget();

private slots:
    void on_acceptButton_clicked();
    void on_comboForAvatars_currentIndexChanged(int index);

signals:
    void avatarChangeSignal(const QString &path);
private:
    Ui::SetAvatarWidget *ui;
    std::vector<std::pair<baseAvatars,QString>> avatars;
};

#endif // SETAVATARWIDGET_H
