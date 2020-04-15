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
int BusinessLogic<Parser>::SetRequest(std::string JsonStr) {
    return 0;
}

template<class Parser>
BusinessLogic<Parser>::~BusinessLogic() {

}
