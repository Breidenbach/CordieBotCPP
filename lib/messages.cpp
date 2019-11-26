#include "messages.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

/***********************************************************************************
 *
 *  Message class
 *
 ***********************************************************************************/

Message::Message() {
    ID_ = "0";
    type_ = 0;
    year_ = 0;
    month_ = 0;
    day_ = 0;
    content_ = "";
}

void Message::set_ID(string const &ID) {
  ID_ = ID;
}

void Message::set_type(int const &type) {
  type_ = type;
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

const int& Message::type() const {
  return type_;
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
  value["type"] = type_;
  value["year"] = year_;
  value["month"] = month_;
  value["day"] = day_;
  value["content"] = content_;
  return value;
}

/***********************************************************************************
 *
 *  MsgList class
 *
 ***********************************************************************************/

MsgList::MsgList() {
  messages_ = vector<Message>();
  count_ = 0;
  #ifdef DEBUG
    std::cout << "Constructing MsgList " << std::endl;
  #endif
}

const vector<Message>& MsgList::messages() const {
  return messages_;
}

void MsgList::AddMessage(string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, string const &content) {
  #ifdef DEBUG
    std::cout << "MsgList::AddMEssage " << ID << "," << type << "," << year <<
                         "," << month << "," << day << "," << content << std::endl;
  #endif
  Message msg = Message();
  msg.set_ID(ID);
  msg.set_type(type);
  msg.set_year(year);
  msg.set_month(month);
  msg.set_day(day);
  msg.set_content(content);
  messages_.push_back(msg);
}

bool MsgList::erase(std::string mid){
    for (vector<Message>::const_iterator vit_ = messages_.begin();
                         vit_ != messages_.end(); ++vit_) {
        if (mid == (*vit_).ID()){
            messages_.erase(vit_);
            #ifdef DEBUG
                std::cout << "erasing  id: " << mid << std::endl;
            #endif
            return true;
        }
    }
    return false;
}

void MsgList::JsonSave(const char* filename) {
    #ifdef DEBUG
        std::cout << "MsgList::JsonSave filename: " << filename << std::endl;
    #endif
    ofstream out(filename, ofstream::out);
    Json::Value book_json(Json::objectValue), messages_json(Json::arrayValue);
    for (vector<Message>::iterator it = messages_.begin(); it != messages_.end(); ++it) {
        ++count_;
        messages_json.append((*it).ToJson());
    }
    book_json["proclamations"] = messages_json;
    #ifdef DEBUG
        std::cout << book_json << std::endl;
    #endif
    out << book_json;
    out.close();
    #ifdef DEBUG
        std::cout << "JsonSave before resetting count, count: " << count_ << std::endl;
    #endif
}

void MsgList::JsonReseq(const char* filename) {
    #ifdef DEBUG
        std::cout << "MsgList::JsonSave filename: " << filename << std::endl;
    #endif
    int new_id_ = 0;
    ofstream out(filename, ofstream::out);
    Json::Value book_json(Json::objectValue), messages_json(Json::arrayValue);
    for (vector<Message>::iterator it = messages_.begin(); it != messages_.end(); ++it) {
        ++new_id_;
        Message temp_ = Message();
        temp_.set_ID(to_string(new_id_));
        temp_.set_type((*it).type());
        temp_.set_year((*it).year());
        temp_.set_month((*it).month());
        temp_.set_day((*it).day());
        temp_.set_content((*it).content());
        messages_json.append(temp_.ToJson());
    }
    book_json["proclamations"] = messages_json;
    #ifdef DEBUG
        std::cout << book_json << std::endl;
    #endif
    out << book_json;
    out.close();
    #ifdef DEBUG
        std::cout << "JsonSave before resetting count, count: " << count_ << std::endl;
    #endif
}

void MsgList::clear(){
    messages_.clear();
}

void MsgList::JsonLoad(const char* filename) {
  ifstream in(filename);
  Json::Value book_json;
  in >> book_json;
  count_ = 0;
#ifdef DEBUG
  std::cout << book_json << std::endl;
#endif
  for (Json::Value::iterator it = book_json["proclamations"].begin(); it != book_json["proclamations"].end(); ++it) {
    AddMessage((*it)["ID"].asString(), (*it)["type"].asInt(), (*it)["year"].asInt(), (*it)["month"].asInt(),
                            (*it)["day"].asInt(), (*it)["content"].asString());
    count_++;
    #ifdef DEBUG
      std::cout << "in for loop, count: " << count_ << std::endl;
    #endif
  }
  in.close();
  #ifdef DEBUG
    std::cout << "closing in file, count: " << count_ << std::endl;
  #endif
}

int MsgList::count(){
    #ifdef DEBUG
      std::cout << "retrieving count: " << count_ << std::endl;
    #endif
    return count_;
}

bool MsgList::empty(){
    #ifdef DEBUG
        std::cout << "empty test:  " << messages_.empty() << endl;
    #endif
    return messages_.empty();
}

/***********************************************************************************
 *
 *  MessageBank class
 *
 ***********************************************************************************/

MessageBank::MessageBank(const char* filename) {
    fname_ = filename;
    proclamations_.JsonLoad(fname_);
    #ifdef DEBUG
      std::cout << "MessageBank::constructor fname_: " << fname_ << std::endl;
    #endif
}

const string& MessageBank::ID() const {
    return (*vit_).ID();
}

const int& MessageBank::type() const {
    return (*vit_).type();
}

const int& MessageBank::year() const {
    return (*vit_).year();
}

const int& MessageBank::month() const {
    return (*vit_).month();
}

const int& MessageBank::day() const {
    return (*vit_).day();
}

const string& MessageBank::content() const {
    return (*vit_).content();
}

void MessageBank::addEntry(string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, string const &content){
    proclamations_.AddMessage(ID, type, year, month, day, content);
    proclamations_.JsonSave(fname_);
} 

bool MessageBank::erase(std::string mid){
    if (proclamations_.erase(mid)){
        proclamations_.JsonSave(fname_);
        return true;
    }
    return false;
}

void MessageBank::save() {
    #ifdef DEBUG
      std::cout << "MessageBank::save fname_: " << fname_ << std::endl;
    #endif
     proclamations_.JsonSave(fname_);
}

std::string MessageBank::getNextID()  {
    int tempID = 0;
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if (stoi((*vit_).ID()) > tempID) { tempID = stoi((*vit_).ID());}
    }
    return to_string(tempID + 1);
}

bool MessageBank::CheckID (string mid) {
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if (mid == (*vit_).ID()){
            return true;
        }
    }
    return false;
}

bool MessageBank::getByDate (int month, int day){
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if ((month == (*vit_).month()) && (day == (*vit_).day())){
            return true;
        }
    }
    return false;
}

bool MessageBank::getByDateNext (int month, int day){
    for (++vit_ ; vit_ != proclamations_.messages().end(); ++vit_) {
        if ((month == (*vit_).month()) && (day == (*vit_).day())){
            return true;
        }
    }
    return false;
}

bool MessageBank::getAllStart(){
    if (!proclamations_.empty()) {
        vit_ = proclamations_.messages().begin();
        return true;
    }
    return false;
}

bool MessageBank::getAllNext(){
    for (++vit_ ; vit_ != proclamations_.messages().end(); ++vit_) {
        return true;
    }
    #ifdef DEBUG
        std::cout << "getAllNext, returning FALSE "  << std::endl;
    #endif
    return false;
}

int MessageBank::count() {
    #ifdef DEBUG
      std::cout <<  "MessageBank::count: " << proclamations_.count() << std::endl;
    #endif
    return proclamations_.count();
}

/**  resequence()
 * 
 *  save original vector with key changes
 *  clean out vector
 *  reload vector
 *
 */
void MessageBank::resequence() {
    proclamations_.JsonReseq(fname_);
    proclamations_.clear();
    proclamations_.JsonLoad(fname_);
}

void MessageBank::reload() {
    proclamations_.clear();
    proclamations_.JsonLoad(fname_);
}

