#pragma once


namespace JsonValueNames {
    const std::string userId = "_id";
    const std::string friendId = "idUser";
    const std::string chatId = "idChat";
    const std::string msgOwner = "owner";
    const std::string text = "text";
    const std::string msgNumber = "number";
    const std::string isChecked = "checked";
    const std::string addMsg = "addMessage";
    const std::string delMsg = "delMessage";
    const std::string changeMsg = "changeMessage";
    const std::string readMsg = "readMessage";
    const std::string addChat = "addChat";
    const std::string delChat = "delChat";
    const std::string msgs = "msgs";
    const std::string login = "login";
    const std::string password = "password";
    const std::string avatar = "pathImage";
    const std::string friends = "friends";
    const std::string chats = "chats";
    const std::string start = "start";
    const std::string end = "end";
    const std::string chatName = "name";
    const std::string users = "users";
    const std::string admins = "admins";
    const std::string chatList = "chatList";
    const std::string frnds = "frnds";
    const std::string time = "time";
    const std::string image = "image";
}

namespace JsonFieldNames{
    const std::string error = "error";
    const std::string status = "status";
    const std::string cmd = "cmd";
    const std::string body = "body";
}

namespace DBValueNames {
    const std::string id = "_id";
    const std::string lastMsgNumber = "last_mes_num";
    const std::string participants = "participants_id";
    const std::string msg = "message";
    const std::string msgOwner = "owner_id";
    const std::string time = "time";
    const std::string cntr = "counter";
    const std::string avatar = "pathImage";
    const std::string chatIds = "chats";
    const std::string chatId = "chat_id";
    const std::string chatNames = "chat_names";
    const std::string chatName = "chat_name";
    const std::string admin = "admin";
    const std::string lastChatId = "last_chat_id";
    const std::string login = "login";
    const std::string password = "password";
    const std::string friends = "friends";
    const std::string isChecked = "checked";
    const std::string image = "image";
}

namespace DBCollectionNames{
    const std::string chat = "Chat";
    const std::string users = "Users";
    const std::string info = "Info";
}

namespace Errors {
    const std::string wrongCommand = "Wrong command ";
    const std::string wrongData = "Таких пользователей у нас нет. Подумай-ка еще ";
    const std::string kill = "KILL";
    const std::string wrongLogin = "Увы, но ты не первый, кому понравился такой ник. Придумай что-то другое ";
    const std::string wrongFrndAdding = "Видно, он тебе очень дорог, раз одного добавления в друзья не хватило ";
    const std::string wrongFrndDel = "Так, спокойно, этот чел и так не твой друг ";
    const std::string wrongId = "Среди нас таких людей нет ";
    const std::string addFrndYourself = "Ты себя в друзья хочешь добавить? Не наше, конечно дело, но позвони как-нибудь: +7 495 051 ";
    const std::string wrongChat = "Такого чата нет, но ты можешь создать ;) ";
    const std::string acsessError = "Хэй, ты же не админ, не надо так ";
}


enum Cmds {
    registration = 1,
    auth = 2,
    getListChat = 3,
    getChatRoom = 4,
    sendMessage = 5,
    getMessages = 6,
    incomingMsgs = 7,
    getLastMsg = 8,
    addFrnd = 9,
    getListFrnd = 10,
    delFrnd = 11,
    getMe = 12,
    getUser = 13,
    createChat = 14,
    delChat = 15,
    addFrndNick = 16,
    changeUser = 17,
    changeMessage = 18,
    delMessage = 19,
    changeChat = 20,
    readChat = 21,
};