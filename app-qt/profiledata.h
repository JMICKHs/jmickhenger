#ifndef PROFILEDATA_H
#define PROFILEDATA_H

#include <QString>

class ProfileData
{
private:
    int Id;
    QString login;
public:
    void setId(int _Id){ Id = _Id;}
    void setLogin(QString &_login){login = _login;}
    QString getLogin(){return login;}
    int getId(){return Id;}

};

#endif // PROFILEDATA_H
