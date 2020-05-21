//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_PARSER_H
#define NETLIB_PARSER_H

#import <string>

#import <boost/property_tree/ptree.hpp>
#import <boost/property_tree/json_parser.hpp>


class AbstractParser {
public:
    virtual void addBool(bool value, const std::string & name) = 0;
    virtual void addInt(int value, const std::string & name) = 0;
    virtual void addStr(const std::string & value, const std::string & name) = 0;
    virtual void addArrInt(const std::vector<int> & vec, const std::string & name) = 0;
    virtual void addArrStr(const std::vector<std::string> & vec, const std::string & name) = 0;
    virtual void clear() = 0;
    virtual std::string getJson() = 0;
    virtual void setJson(const std::string & jsonData) = 0;
    virtual bool getBool(const std::string & name) = 0;
    virtual int getInt(const std::string & name) = 0;
    virtual std::string getStr(const std::string & name) = 0;
    virtual std::vector<int> getArrInt(const std::string & name) = 0;
    virtual std::vector<std::string> getArrStr(const std::string & name) = 0;
    virtual void addCustom(const std::string & json, const std::string & name) = 0;
    virtual void addArrCustom(const std::vector<std::string> & jsons, const std::string & name) = 0;
    virtual std::string getCustom(const std::string & name) = 0;
    virtual std::vector<std::string> getArrCustom(const std::string & name) = 0;
};

class Parser: public AbstractParser {
private:
    boost::property_tree::ptree root;
    static const std::string emptyArr;
public:
    Parser(): root() {}
    void addBool(bool value, const std::string & name) override;
    void addInt(int value, const std::string & name) override;
    void addStr(const std::string & value, const std::string & name) override;
    void addArrInt(const std::vector<int> & vec, const std::string & name) override;
    void addArrStr(const std::vector<std::string> & vec, const std::string & name) override;
    void clear() override;
    std::string getJson() override;
    void setJson(const std::string & jsonData) override;
    bool getBool(const std::string & name) override;
    int getInt(const std::string & name) override;
    std::string getStr(const std::string & name) override;
    std::vector<int> getArrInt(const std::string & name) override;
    std::vector<std::string> getArrStr(const std::string & name) override;
    void addCustom(const std::string & json, const std::string & name) override;
    void addArrCustom(const std::vector<std::string> & jsons, const std::string & name) override;
    std::string getCustom(const std::string & name) override;
    std::vector<std::string> getArrCustom(const std::string & name) override;
};


#endif //NETLIB_PARSER_H
