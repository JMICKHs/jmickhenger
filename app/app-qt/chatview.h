#ifndef CHATVIEW_H
#define CHATVIEW_H


#include <QListView>


class ChatView : public QListView
{
public:
    ChatView(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
private:
    QImage *background;
public slots:
    void scrollWhileDataChandeg();
};

#endif // CHATVIEW_H
