#ifndef CHATINPUT_H
#define CHATINPUT_H

#include <QWidget>
#include <QPlainTextEdit>

class ChatInput : public QPlainTextEdit
{
    Q_OBJECT
public:
    ChatInput(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent *e) override;
    QPixmap image;
    bool created{false};
    bool changeMsg{false};
    int baseHeight;
public slots:
    void textForChange(const QString& str);
private:
signals:
    void changeSpacer(int h);
    void sendMessageOnEnter();
    void sendMessageForChange();
};

#endif // CHATINPUT_H
