#ifndef FRIENDSVIEW_H
#define FRIENDSVIEW_H


#include <QListView>
class FriendsView : public QListView
{
public:
    explicit FriendsView(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *e) override;
};

#endif // FRIENDSVIEW_H
