#include "messages.h"

Message::Message() {
}

void Message::set_ID(string const &ID) {
  ID_ = ID;
}

void Message::set_year(int const &year) {
  year_ = year;
}

void Message::set_month(int const &month) {
  month_ = month;
}

void Message::set_day(int const &day) {
  day_ = day;
}

void Message::set_content(string const &content) {
  content_ = content;
}

const string& Message::ID() const {
  return ID_;
}

const int& Message::year() const {
  return year_;
}

const int& Message::month() const {
  return month_;
}

const int& Message::day() const {
  return day_;
}

const string& Message::content() const {
  return content_;
}

Json::Value Message::ToJson() const {
  Json::Value value(Json::objectValue);
  value["ID"] = ID_;
  value["year"] = year_;
  value["month"] = month_;
  value["day"] = day_;
  value["content"] = content_;
  return value;
}

MsgList::MsgList() {
  messages_ = vector<Message>();
}

const vector<Message>& MsgList::messages() const {
  return messages_;
}

void MsgList::AddMessage(string const &ID, int const &year, int const &month,
                                    int const &day, string const &content) {
  Message msg = Message();
  msg.set_ID(ID);
  msg.set_year(year);
  msg.set_month(month);
  msg.set_year(year);
  msg.set_content(content);
  messages_.push_back(msg);
}

void MsgList::JsonSave(const char* filename) {
  ofstream out(filename, ofstream::out);
  Json::Value book_json(Json::objectValue), messages_json(Json::arrayValue);
  for (vector<Message>::iterator it = messages_.begin(); it != messages_.end(); ++it) {
    messages_json.append((*it).ToJson());
  }
  book_json["proclamations"] = messages_json;
  out << book_json;
  out.close();
}

void MsgList::JsonLoad(const char* filename) {
  ifstream in(filename);
  Json::Value book_json;
  in >> book_json;
  for (Json::Value::iterator it = book_json["proclamations"].begin(); it != book_json["proclamations"].end(); ++it) {
    AddMessage((*it)["ID"].asString(), (*it)["year"].asInt(), (*it)["month"].asInt(),
                            (*it)["day"].asInt(), (*it)["content"].asString());
  }
  in.close();
}
