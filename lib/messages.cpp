#include "messages.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

/***********************************************************************************
 *
 *  Message class
 *
 *  ID - unique ID number for Message
 *  type - 1 = specific day of specific year
 *         2 = specific day of any year
 *         3 = any timer
 *  year - year value or 0
 *  month - month value or 0
 *  day - day value or 0  (month and day will either both be set or both
 *            be 0)
 *  content - message to be spoken
 *
 ***********************************************************************************/

Message::Message() {
    ID_ = "0";  // unique number for message
    type_ = 0;  // 1 = specific day of specific year, 
    year_ = 0;
    month_ = 0;
    day_ = 0;
    content_ = "";
}

void Message::set_ID(std::string const &ID) {
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

void Message::set_content(std::string const &content) {
  content_ = content;
}

const std::string& Message::ID() const {
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

const std::string& Message::content() const {
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
  messages_ = std::vector<Message>();
  count_ = 0;
  #ifdef DEBUG
    std::cout << "Constructing MsgList " << std::endl;
  #endif
}

void MsgList::setModTime(const char* filename) {
    struct stat sb;
    stat(filename, &sb);
    lastModTime_ = sb.st_ctime;
    #ifdef DEBUG
        std::cout << "Setting lastModTime " << lastModTime_ << std::endl;
    #endif
}

const std::vector<Message>& MsgList::messages() const {
  return messages_;
}

void MsgList::AddMessage(std::string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, std::string const &content) {
  #ifdef DEBUG
    std::cout << "MsgList::AddMessage " << ID << "," << type << "," << year <<
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
    for (std::vector<Message>::const_iterator vit_ = messages_.begin();
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
    std::ofstream out(filename, std::ofstream::out);
    Json::Value book_json(Json::objectValue), messages_json(Json::arrayValue);
    for (std::vector<Message>::iterator it = messages_.begin(); it != messages_.end(); ++it) {
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
    setModTime(filename);
}

void MsgList::JsonReseq(const char* filename) {
    #ifdef DEBUG
        std::cout << "MsgList::JsonSave filename: " << filename << std::endl;
    #endif
    int new_id_ = 0;
    std::ofstream out(filename, std::ofstream::out);
    Json::Value book_json(Json::objectValue), messages_json(Json::arrayValue);
    for (std::vector<Message>::iterator it = messages_.begin(); it != messages_.end(); ++it) {
        ++new_id_;
        Message temp_ = Message();
        temp_.set_ID(std::to_string(new_id_));
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
    setModTime(filename);
}

void MsgList::clear(){
    messages_.clear();
}

void MsgList::JsonLoad(const char* filename) {
  std::ifstream in(filename);
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
    setModTime(filename);
}

int MsgList::count(){
    #ifdef DEBUG
      std::cout << "retrieving count: " << count_ << std::endl;
    #endif
    return count_;
}

bool MsgList::empty(){
    #ifdef DEBUG
        std::cout << "empty test:  " << messages_.empty() << std::endl;
    #endif
    return messages_.empty();
}

bool MsgList::changed(const char* filename) {
    struct stat sb;
    stat(filename, &sb);
    #ifdef DEBUG
        std::cout << "comparing mod time to current " << lastModTime_ << " >? " <<
                                sb.st_ctime << std::endl;
    #endif
    return(lastModTime_ < sb.st_ctime);
}



/***********************************************************************************
 *
 *  MessageBank class
 *
 *  Counts:
 *   When requested, the class will count records of each type, with the constraint
 *   that the counts of type 2 and 3 messages will only include the ones for a 
 *   specific date.
 *
 ***********************************************************************************/

MessageBank::MessageBank(const char* filename) {
    fname_ = filename;
    proclamations_.JsonLoad(fname_);
    vector_valid_ = false;
    #ifdef DEBUG
      std::cout << "MessageBank::constructor fname_: " << fname_ << std::endl;
    #endif
}

const std::string& MessageBank::ID() const {
    if (! vector_valid_) {return zero_id_;}
    return (*vit_).ID();
}

const int& MessageBank::type() const {
    if (! vector_valid_) {return zero_return_;}
    return (*vit_).type();
}

const int& MessageBank::year() const {
    if (! vector_valid_) {return zero_return_;}
    return (*vit_).year();
}

const int& MessageBank::month() const {
    if (! vector_valid_) {return zero_return_;}
    return (*vit_).month();
}

const int& MessageBank::day() const {
    if (! vector_valid_) {return zero_return_;}
    return (*vit_).day();
}

const std::string& MessageBank::content() const {
    if (! vector_valid_) {return empty_string_;}
    return (*vit_).content();
}

void MessageBank::setCounts(int const &year, int const &month, int const &day){
    type1_count_ = 0;
    type2_count_ = 0;
    type3_count_ = 0;
    this_year_ = year;
    this_month_ = month;
    this_day_ = day;
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        switch ((*vit_).type()) {
            case 1: {   if (((*vit_).year() == year) &&
                        ((*vit_).month() == month) && ((*vit_).day() == day)){
                            ++type1_count_;
                        }
                        break;
                    }
            case 2: {   if (((*vit_).month() == month) && ((*vit_).day() == day)){
                            ++type2_count_;
                        }
                        break;
                    }
            case 3: {   ++type3_count_;
                        break;
                    }
        }
    }
    #ifdef DEBUG
      std::cout << "MessageBank::setCounts: " << type3_count_ << ", " << 
                type2_count_ << ", " << type1_count_ << std::endl;
    #endif
    vector_valid_ = false;
}

int MessageBank::type3count(){
    return type3_count_;
}

int MessageBank::type2count(){
    return type2_count_;
}

int MessageBank::type1count(){
    return type1_count_;
}

/*  Note that getNthEntry() requires that year, month, and day were previously saved,
    Like in setCounts()
*/
std::string MessageBank::getNthEntry(int type, int n){
    int count_ = 0;
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if ((*vit_).type() == type) {
            switch (type) {
                case 1: {   if (((*vit_).year() == this_year_) &&
                                    ((*vit_).month() == this_month_) &&
                                    ((*vit_).day() == this_day_)){
                                ++count_;
                            }
                            if (count_ == n) {
                                vector_valid_ = true;
                                return (*vit_).content();
                            }
                            break;
                        }
                case 2: {   if (((*vit_).month() == this_month_) &&
                                    ((*vit_).day() == this_day_)){
                                ++count_;
                            }
                            if (count_ == n) {
                                vector_valid_ = true;
                                return (*vit_).content();
                            }
                            break;
                        }
                case 3: {   ++count_;
                            if (count_ == n) {
                                vector_valid_ = true;
                                return (*vit_).content();
                            }
                            break;
                        }
            }
         }
    } 
    #ifdef DEBUG
      std::cout << "MessageBank::getNthEntry at end of vector " << std::endl;
    #endif
    vector_valid_ = false;
    return ("I have nothing to say about that.");
}

void MessageBank::addEntry(std::string const &ID, int const &type, int const &year, int const &month,
                                    int const &day, std::string const &content){
    proclamations_.AddMessage(ID, type, year, month, day, content);
    proclamations_.JsonSave(fname_);
    vector_valid_ = false;
} 

bool MessageBank::erase(std::string mid){
    if (proclamations_.erase(mid)){
        proclamations_.JsonSave(fname_);
        vector_valid_ = false;
        return true;
    }
    return false;
}

void MessageBank::save() {
    #ifdef DEBUG
      std::cout << "MessageBank::save fname_: " << fname_ << std::endl;
    #endif
    proclamations_.JsonSave(fname_);
    vector_valid_ = false;
}

std::string MessageBank::getNextID()  {
    int tempID = 0;
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if (stoi((*vit_).ID()) > tempID) { tempID = stoi((*vit_).ID());}
    }
    vector_valid_ = false;
    return std::to_string(tempID + 1);
}

bool MessageBank::CheckID (std::string mid) {
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if (mid == (*vit_).ID()){
            vector_valid_ = true;
            return true;
        }
    }
    vector_valid_ = false;
    return false;
}

bool MessageBank::getByDate (int month, int day){
    for (vit_ = proclamations_.messages().begin();
                         vit_ != proclamations_.messages().end(); ++vit_) {
        if ((month == (*vit_).month()) && (day == (*vit_).day())){
            return true;
            vector_valid_ = true;
        }
    }
    vector_valid_ = false;
    return false;
}

bool MessageBank::getByDateNext (int month, int day){
    for (++vit_ ; vit_ != proclamations_.messages().end(); ++vit_) {
        if ((month == (*vit_).month()) && (day == (*vit_).day())){
            vector_valid_ = true;
            return true;
        }
    }
    vector_valid_ = false;
    return false;
}

bool MessageBank::getAllStart(){
    if (!proclamations_.empty()) {
        vit_ = proclamations_.messages().begin();
        vector_valid_ = true;
        return true;
    }
    vector_valid_ = false;
    return false;
}

bool MessageBank::getAllNext(){
    if (! vector_valid_) {return false;}
    for (++vit_ ; vit_ != proclamations_.messages().end(); ++vit_) {
        vector_valid_ = true;
        return true;
    }
    #ifdef DEBUG
        std::cout << "getAllNext, returning FALSE "  << std::endl;
    #endif
    vector_valid_ = false;
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
    vector_valid_ = false;
}

void MessageBank::reload() {
    proclamations_.clear();
    proclamations_.JsonLoad(fname_);
    vector_valid_ = false;
}

bool MessageBank::changed() {
    return (proclamations_.changed(fname_));
    vector_valid_ = false;
}

