#ifndef UTILS_H
#define UTILS_H

#include <QWidget>
#include <QPoint>

class Utils{
public:
    Utils() = default;
    static QPoint moveToCenter(QWidget* parent){
        return QPoint(parent->pos().x() + parent->size().width()/(4),
                    parent->pos().y() + parent->size().height()/(4));
    }
};

#endif // UTILS_H
