// -*- mode: c++ -*-

#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <vector>
#include <fstream>

#include <jsoncpp/json/json.h>

using namespace std;

class Message {
private:
    string ID_;
    int type_;
    int year_;
    int month_;
    int day_;
    std::string content_;
public:
    Message();
    void set_ID(string const &ID);
    void set_type(int const &type);
    void set_year(int const &year);
    void set_month(int const &month);
    void set_day(int const &day);
    void set_content(string const &content);
    const string& ID() const;
    const int& type() const;
    const int& year() const;
    const int& month() const;
    const int& day() const;
    const string& content() const;
    Json::Value ToJson() const;
};

class MsgList {
private:
    vector<Message> messages_;
    char* fname_;
    int count_;
public:
    MsgList();
    const vector<Message>& messages() const;
    void JsonSave(const char* filename);
    void JsonReseq(const char* filename);
    void JsonLoad(const char* filename);
    void clear();
    void AddMessage(string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, string const &content);
    bool erase(string mid);
    const vector<Message>::iterator& begin();
    const vector<Message>::iterator& end();
    int count();
    bool empty();
};

class MessageBank {
private:
    const char* fname_;
    MsgList proclamations_;
    vector<Message>::const_iterator vit_;
public:
    MessageBank(const char* fname);
    const string& ID() const;
    const int& type() const;
    const int& year() const;
    const int& month() const;
    const int& day() const;
    const string& content() const;
    void addEntry(string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, string const &content);
    bool erase(string mid);
    std::string getNextID() ;
    bool CheckID (string mid);
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
