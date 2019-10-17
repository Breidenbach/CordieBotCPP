// -*- mode: c++ -*-
#pragma once
#include <string>
#include <vector>
#include <fstream>

#include <jsoncpp/json/json.h>


using namespace std;

class Message {
private:
  string ID_;
  int year_ = 0;
  int month_ = 0;
  int day_ = 0;
  string content_;
public:
  Message();
  void set_ID(string const &ID);
  void set_year(int const &year);
  void set_month(int const &month);
  void set_day(int const &day);
  void set_content(string const &content);
  const string& ID() const;
  const int& year() const;
  const int& month() const;
  const int& day() const;
  const string& content() const;
  Json::Value ToJson() const;
};

class MsgList {
private:
  vector<Message> messages_;
public:
  MsgList();
  const vector<Message>& messages() const;
  void JsonSave(const char* filename);
  void JsonLoad(const char* filename);

  void AddMessage(string const &ID, int const &year, int const &month,
                                    int const &day, string const &content);
  const vector<Message>::iterator& begin();
  const vector<Message>::iterator& end();
};
