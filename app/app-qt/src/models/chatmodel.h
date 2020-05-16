#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include "app-qt/src/custommbutton/custombutton.h"
#include <netlib/info/Info.h>
#include <memory>
#include <time.h>
using MessageItem = inf::Message;

enum class MessageType{
    SELF_MESSAGE_IN_PROGRESS,
    SELF_MESSAGE_DONE,
    OTHER_MESSAGE
};

class Msg : public MessageItem
{
public:
    MessageType type;
    QString time;
    QString nickname;
    Msg(MessageItem &item)
        :MessageItem(std::move(item)){
        type = MessageType::OTHER_MESSAGE;
        char buffer [100];
        tm* timeinfo = localtime(&item.timesend);
        strftime(buffer,100,"%H-%M",timeinfo);
        time = QString::fromStdString(std::string(buffer));
    }
    Msg(){type = MessageType::SELF_MESSAGE_IN_PROGRESS;}
};

Q_DECLARE_METATYPE(Msg)
class ChatModel : public QAbstractListModel,public std::enable_shared_from_this<ChatModel>
{
    Q_OBJECT
public:
    ChatModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addCallbacks();

    void setData(std::vector<MessageItem>& msgs);
    std::function<void(std::vector<MessageItem>&,std::optional<std::string>&)> &getChatCallback() ;
    std::function<void(std::optional<std::string>&)> &getSendMsgCallback() ;
    std::function<void(std::optional<std::string>&)> &getChangeMsgCallback() ;
    std::function<void(std::optional<std::string>&)> &getDelMsgCallback() ;

    void slotEditMessage();
    void DeleteMessage(int pos);
private:
    std::vector<Msg> items;
    bool newMessageOnBottom;
    std::optional<std::string> errString;
    std::function<void(std::vector<MessageItem>&,std::optional<std::string>&)> chatCallback;
    std::function<void(std::optional<std::string>&)> sendMsgCallback;
    std::function<void(std::optional<std::string>&)> changeMsgCallback;
    std::function<void(std::optional<std::string>&)> delMsgCallback;
    std::function<void(inf::UserInfo &info,std::optional<std::string>&)> userInfForMessage;
    std::vector<int> getUniqueIds(const std::vector<MessageItem> &vec);
signals:
    void messageCreateByUser(const Msg &_message);
public slots:
    void createMessage(const Msg &_message);

};

#endif // CHATMODEL_H
