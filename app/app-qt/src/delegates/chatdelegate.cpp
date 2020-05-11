#include "chatdelegate.h"
#include "app-qt/src/custommbutton/custombutton.h"
#include <QApplication>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QDebug>

ChatDelegate::ChatDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    avatar = new QPixmap("/home/kostikan/jmickhenger/app/img/standartAvatar.jpg");
    check = new QPixmap("/home/kostikan/jmickhenger/app/img/check.png");
    uncheck = new QPixmap("/home/kostikan/jmickhenger/app/img/unchecked.png");
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Message item = index.model()->data(index).value<Message>();
    QRect MessageRect = option.rect;
    MessageRect.setY(MessageRect.y() + 15);
    MessageRect.setX(45);
    MessageRect.setWidth(option.widget->width() - 80);
    QFontMetrics fMetrics(option.font);
    int strWidth = fMetrics.horizontalAdvance(QString::fromStdString(item.text));
    int strHeight = fMetrics.height();
    int aspectRatio = strWidth / (option.widget->width() - 80);
    int aspect = 15 + aspectRatio * strHeight;
    qDebug() <<aspect;
    if(aspect <= 45)
        return QSize(option.widget->width(),45);
    else {
         return QSize(option.widget->width(),aspect);
    }
}

bool ChatDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

    QRect ButtonRect = option.rect;
    ButtonRect.setWidth(45);
    if (mouse_event->button() == Qt::LeftButton)
    {
         if(ButtonRect.contains(mouse_event->pos())) {
             qDebug() << "kek";
         }
    }
}

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        Message item = index.model()->data(index).value<Message>();
        QStyleOptionViewItem myOpt = option;
        myOpt.displayAlignment = Qt::AlignLeft;
        painter->save();
        painter->setClipping(true);

        QRect rect(myOpt.rect);
        rect.setHeight(sizeHint(option,index).height());
        const QPalette &palette(myOpt.palette);
        QFont f(myOpt.font);

        painter->fillRect(rect, myOpt.state & QStyle::State_Selected ?
                                 palette.highlight().color() :
                                 palette.light().color());
        painter->setFont(myOpt.font);

        int width = sizeHint(option,index).width();

        QFontMetrics font(f);

        QRect ButtonRect = myOpt.rect;
        ButtonRect.setX(ButtonRect.x() + 5);
        ButtonRect.setY(ButtonRect.y());
        ButtonRect.setWidth(20);
        ButtonRect.setHeight(55);

        QPixmap scaled = avatar->scaled(40, 40, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QBrush brush(scaled);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(brush);
        painter->translate(QPointF(ButtonRect.x(),ButtonRect.y()));
        painter->drawRoundedRect(5, 5, 30, 30, 100, 100);

        painter->restore();
        painter->save();
        QRect NameRect = myOpt.rect;
        NameRect.setHeight(15);
        NameRect.setX(45);
        NameRect.setWidth(width - 45);

        painter->setFont(f);
        painter->setPen(QColor(76,148,224));
        //painter->drawText(NameRect, Qt::TextSingleLine,
      //                 QString::fromStdString(item.name));

        QRect TimeRect = myOpt.rect;
        TimeRect.setHeight(15);
        TimeRect.setX(45);
        TimeRect.setWidth(width - 45);

        QRect MessageRect = myOpt.rect;
        MessageRect.setY(MessageRect.y() + 15);
        MessageRect.setX(45);
        MessageRect.setWidth(width - 80);

        painter->setFont(f);
        painter->setPen(palette.text().color());
        painter->drawText(MessageRect, Qt::TextWrapAnywhere,
                       QString::fromStdString(item.text));



        QPen pen;
        painter->setRenderHint(QPainter::Antialiasing);
        pen.setWidth(1);
        pen.setColor(Qt::white);
        painter->setPen(pen);
        painter->translate(QPointF(myOpt.widget->width() - 54,myOpt.widget->height() - 54));
        painter->drawRoundedRect(5, 5, 40, 40, 100, 100);
        pen.setColor(Qt::blue);
        painter->setPen(pen);
        painter->drawRoundedRect(5, 5, 40, 40, 100, 100);
        painter->translate(QPointF(0,6));
        painter->drawLine(16,13,25,25);
        painter->translate(QPointF(25,25));
        painter->drawLine(0,0, 10,-13);
        painter->restore();

        painter->save();

        QPixmap checkScaled = check->scaled(20, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        QBrush check(checkScaled);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(check);
        painter->translate(QPointF(rect.width()-20,rect.y() + 10));
        painter->fillRect(checkScaled.rect(),Qt::transparent);

        painter->drawPixmap(checkScaled.rect(),checkScaled);
        painter->restore();

}


