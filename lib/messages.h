// -*- mode: c++ -*-
#pragma once
#include <string>
#include <vector>
#include <fstream>

#include <jsoncpp/json/json.h>


using namespace std;

class Message {
private:
    string ID_ = "0";
    int type_ = 0;
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;
    string content_ = " ";
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
    void JsonLoad(const char* filename);

    void AddMessage(string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, string const &content);
    const vector<Message>::iterator& begin();
    const vector<Message>::iterator& end();
    int count();
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
    string getNextID() ;
//    Message RetrieveOne (string mid);
    bool CheckID (string mid);
    void save();
    int count();
};
