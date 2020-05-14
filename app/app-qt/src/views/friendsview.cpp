#include "friendsview.h"

FriendsView::FriendsView(QWidget *parent)
    :QListView(parent)
{

}

void FriendsView::resizeEvent(QResizeEvent *e)
{
    this->doItemsLayout();
}
