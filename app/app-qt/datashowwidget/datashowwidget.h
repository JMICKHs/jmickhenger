#ifndef DATASHOWWIDGET_H
#define DATASHOWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "profiledata/profiledata.h"

class DataShowWidget : public QWidget
{
    Q_OBJECT
private:
    ProfileData data;

public:
    DataShowWidget(QWidget *parent = nullptr);
    ProfileData getData();

public slots:
    void GetUserProfile(const ProfileData &data);

};

#endif // DATASHOWWIDGET_H
