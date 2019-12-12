// -*- mode: c++ -*-

#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <vector>
#include <fstream>

#include <jsoncpp/json/json.h>

#define MESSAGE_TYPE_1 1
#define MESSAGE_TYPE_2 2
#define MESSAGE_TYPE_3 3

class Message {
private:
    std::string ID_;
    int type_;
    int year_;
    int month_;
    int day_;
    std::string content_;
public:
    Message();
    void set_ID(std::string const &ID);
    void set_type(int const &type);
    void set_year(int const &year);
    void set_month(int const &month);
    void set_day(int const &day);
    void set_content(std::string const &content);
    const std::string& ID() const;
    const int& type() const;
    const int& year() const;
    const int& month() const;
    const int& day() const;
    const std::string& content() const;
    Json::Value ToJson() const;
};

class MsgList {
private:
    std::vector<Message> messages_;
    char* fname_;
    int count_;
public:
    MsgList();
    const std::vector<Message>& messages() const;
    void JsonSave(const char* filename);
    void JsonReseq(const char* filename);
    void JsonLoad(const char* filename);
    void clear();
    void AddMessage(std::string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, std::string const &content);
    bool erase(std::string mid);
    const std::vector<Message>::iterator& begin();
    const std::vector<Message>::iterator& end();
    int count();
    bool empty();
};

class MessageBank {
private:
    const char* fname_;
    MsgList proclamations_;
    std::vector<Message>::const_iterator vit_;
    int type3_count_;
    int type2_count_;
    int type1_count_;
    int this_year_;
    int this_month_;
    int this_day_;
public:
    MessageBank(const char* fname);
    const std::string& ID() const;
    const int& type() const;
    const int& year() const;
    const int& month() const;
    const int& day() const;
    const std::string& content() const;
    void setCounts(int const &year, int const &month, int const &day);
    int type3count();
    int type2count();
    int type1count();
    std::string getNthEntry(int type, int n);
    void addEntry(std::string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, std::string const &content);
    bool erase(std::string mid);
    std::string getNextID();
    bool CheckID (std::string mid);
    bool getByDate (int month, int day);
    bool getByDateNext (int month, int day);
    bool getAllStart();
    bool getAllNext();
    void save();
    int count();
    void resequence();
    void reload();
};

#endif
