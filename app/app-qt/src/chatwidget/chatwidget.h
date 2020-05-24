#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#import <QWidget>
#import <QLineEdit>
#import <QTextEdit>
#import <QPixmap>

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = nullptr);
    QTextEdit msg;
    QLineEdit name;
    QPixmap *image;
    QWidget showPicture;
    QString avatar;
    QPixmap *check;
    QPixmap *uncheck;
    QPoint offset{5,5};
    int textOffset{15};
    int mainMessageTopOffset{15};
    int baseItemHeight{50};
    int rightMessageOffset{80};
    int avatarRadius{100};
    float baseTextHeight{15};
    QSize avatarSize{35,35};
    QSize avatarScale{45,45};
    QSize sizeHint() const override;
    void paint(QPainter *painter,QFont &font, const QRect &rect,const QPalette &palette) const;
signals:

};

#endif // CHATWIDGET_H
