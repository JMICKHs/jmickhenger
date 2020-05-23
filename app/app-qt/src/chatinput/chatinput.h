#ifndef CHATINPUT_H
#define CHATINPUT_H

#include <QTextEdit>
#include <QWidget>
#include <QPlainTextEdit>

class ChatInput : public QPlainTextEdit
{
    Q_OBJECT
public:
    ChatInput(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    QPixmap image;
    bool created{false};
private:
signals:
    void sendMessageOnEnter();
};

#endif // CHATINPUT_H
