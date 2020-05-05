#ifndef CHATVIEW_H
#define CHATVIEW_H


#include <QListView>


class ChatView : public QListView
{
public:
    ChatView(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
private:
    QImage *background;
};

#endif // CHATVIEW_H
