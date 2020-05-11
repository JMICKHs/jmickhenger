#include "Business-Logic.h"


template<class Parser>
ResponseStruct BusinessLogic<Parser>::GetResponse() {
    return ResponseStruct();
}

template<class Parser>
BusinessLogic<Parser>::BusinessLogic() {

}

template<class Parser>
BusinessLogic<Parser>::BusinessLogic(Parser &ps) {

}

template<class Parser>
int BusinessLogic<Parser>::SetRequest(const std::string& JsonStr) {
    return 0;
}

template<class Parser>
BusinessLogic<Parser>::~BusinessLogic() {

}

template<class Parser>
int BusinessLogic<Parser>::getCMD(const std::string &filepath, std::string &CMD) {
    return 0;
}
