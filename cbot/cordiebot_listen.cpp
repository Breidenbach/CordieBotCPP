/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "pubnub.hpp"

#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <algorithm>
#include "messages.h"
#include <fstream>

//#define DEBUG

/*
   pubnubprocess.cpp - created from subscribe_publish_callback_sample.cpp
   October, 2019 -- Hal Breidenbach
   
   */

/** This example, while using the C++ API which is "generic" will
    actually work only with the Pubnub C callback "back-end" (notification
    interface). 

    To do the same thing with the "sync back-end", the user should use
    the pubnub::futres::last_result() to check for the outcome of both
    operations that are started concurrently.
    
    
 */
#define ADD_ENTRY          1       //  add an entry
#define CHANGE_ENTRY       2       //  change a specific entry
#define DELETE_ENTRY       3       //  delete a specific entry     
#define RETRIEVE_ENTRY     4       //  retrieve an entry by id
#define RETRIEVE_DATE      5       //  retrieve an entry by month & day
#define RETRIEVE_ALL       6       //  retrieve all entries
#define RESEQUENCE         7       //  resequence entries, giving them sequential
                                  //      ID values.
#define RETRIEVE_DATE_NEXT 8       //  retrieve next entry when retrieving by date
#define RETRIEVE_ALL_NEXT  9       //  retrieve next entry when retrieving all

#define DATA_RETURNED      1       //  Data fields are valid
#define RESPONSE_ONLY      2       //  Data fields are not valid, response is for
                                   //    end of reading sequentially or ID not found.

std::string adjustApostropies(std::string str){
    std::string work = str;
//    std::replace(work.begin(), work.end(), '\"', '\'' );
    std::replace(work.begin(), work.end(), '\n', ' ' ); 
    return work;                          
}

bool internet(){
    int test_result = system("ping -c 1 8.8.8.8");
    #ifdef DEBUG
        std::cout << "listen ping return: " << test_result << std::endl;
    #endif
    return (test_result == 0);
}

int main()
{
    while (! internet())  // wait for internet to connect
    {
        usleep(500*1000);  // delay 1/2 second
    }
    #ifdef DEBUG
        std::cout << "Starting cordiebot_listen  9/19/2021  14:45" << std::endl;
    #endif
    std::ifstream keyfile("keys.js");
    std::string pubkey, subkey;
    std::string line;
    while (std::getline(keyfile, line))
    {
        int at, start;
        if ((at = line.find("Publish")) >= 0){
            start = line.find('\'');
            pubkey = line.substr(start+1,line.find_last_of('\'')-start-1);
        }
        if ((at = line.find("Subscribe")) >= 0){
            start = line.find('\'');
            subkey = line.substr(start+1,line.find_last_of('\'')-start-1);
        }
    }    
    
    MessageBank mbank("proclamations.txt");
    std::string message_reply;
    #ifdef DEBUG
        std::cout << "input message count:  " << mbank.count() << std::endl;
    #endif
    try {
      for (;;) {
        enum pubnub_res res;
        char const *chan = "cordiebot";
        pubnub::context pb(pubkey, subkey);
        pubnub::context pb_2(pubkey, subkey);
        std::string uuid("CordieBot2");
        pb.set_uuid(uuid);
        pb_2.set_uuid(uuid);
        JSONCPP_STRING json_err;

        std::string ID;
        int action = 0;
        int type;
        int day;
        int month;
        int year;
        std::string content;
        
        std::string sent_message;
        std::string msg;

        #ifdef DEBUG
            std::cout << "--------------------------" << std::endl <<
                "Subscribing..." << std::endl <<
                "--------------------------" << std::endl;
	    #endif
        /* First subscribe, to get the time token */
        res = pb.subscribe(chan).await();
        if (PNR_STARTED == res) {
            #ifdef DEBUG
                std::cout << "await() returned unexpected: PNR_STARTED" << std::endl;
            #endif
            return -1;
        }
        #ifdef DEBUG
            if (PNR_OK == res) {
                std::cout << "Subscribed!" << std::endl;
            }
            else {
                std::cout << "Subscribing failed with code: " << (int)res << std::endl;;
            }
        #endif

        /* The "real" subscribe, with the just acquired time token */
        pubnub::futres futres = pb.subscribe(chan);
	
        /* Don't do "full" await here, because we didn't publish
         * anything yet! */
        futres.start_await();
    
        #ifdef DEBUG
            std::cout << "--------------------------" << std::endl <<
                "Publishing, with action = " << action << std::endl <<
                "--------------------------" << std::endl;
        #endif
        
        /* Now we await the subscribe on `pbp` */
        #ifdef DEBUG
            std::cout << "Await subscribe" << std::endl;
        #endif
        res = futres.end_await();
        if (PNR_OK == res) {
            #ifdef DEBUG
                std::cout << "Subscribed! Got messages:";
            #endif
            do {  // while (!msg.empty())
                msg = pb.get();
                std::string next_entry;
                
                #ifdef DEBUG
                	std::cout << msg << std::endl;
                    std::cout << "start of do loop"  << std::endl;
                    std::cout << "msg.empty(): " << msg.empty() << "  msg.compare(): " <<
                                 msg.compare(message_reply) << std::endl;
                #endif
                if (!msg.empty() && (msg.compare(message_reply) != 0)){
                    #ifdef DEBUG
                        std::cout << "msg: |" << msg << "|" << std::endl;
                        std::cout << "message_reply:  |" << message_reply << "|" << std::endl;
                        std::cout << "bool = " << !msg.empty() <<
                                             (msg != message_reply) << std::endl;
                        std::cout << "Just checked if not equal to sent message again" 
                                                << std::endl;
                    #endif
                    std::string reply_string;
                    Json::Value root;
                    Json::Reader reader;
                    reader.parse(msg, root);
                    ID = root["ID"].asString();
                    action = root["action"].asInt();
                    if (root["day"].isNull()) { day = 0; }
                        else {day = root["day"].asInt();}
                    if (root["month"].isNull()) { month = 0; }
                        else {month = root["month"].asInt();}
                    if (root["year"].isNull()) { year = 0; }
                        else {year = root["year"].asInt();}
                    if (root["type"].isNull() || root["type"].compare("") == 0)
                    { 
                        if (year == 0 && month == 0 && day == 0)
                        { type = 3; }
                        else
                        {
                            if (year == 0)
                            { type = 2; }
                            else
                            { type = 1; }
                        }
                    }
                    else
                    {
                        type = root["type"].asInt();
                    }
                    content = root["content"].asString();
                    #ifdef DEBUG
                        std::cout << "action = " << action << std::endl;
                    #endif
                    Json::Value reply_root;
                    reply_root = root;
                    reply_root["type"] = type;
                    Json::FastWriter writer;
                    switch (action){
                        case ADD_ENTRY:
                            next_entry = mbank.getNextID();
                            std::cout << "next entry returns:  " << next_entry << std::endl;
                            mbank.addEntry(next_entry, type, year, month, day, content);
                            reply_root["ID"] = next_entry;
                            reply_root["response"] = "Message added.";
                            reply_root["responseType"] = DATA_RETURNED;
                            break;
                        case CHANGE_ENTRY:
                            std::cout << "action:  change entry ID matches = "
                                     << mbank.CheckID(ID) << " " << ID << std::endl;
                            if (mbank.erase(ID)) {
                                mbank.addEntry(ID, type, year, month, day, content);
                                reply_root["response"] = "Message changed.";
                            } else {
                                reply_root["response"] = "Message " + ID + " not found.";
                            }  // if (mbank.erase(ID))
                            reply_root["responseType"] = DATA_RETURNED;
                            break;
                        case DELETE_ENTRY:
                            std::cout << "action:  delete entry ID matches = "
                                     << mbank.CheckID(ID) << " " << ID << std::endl;
                            if (mbank.erase(ID)) {
                                reply_root["response"] = "Message deleted.";
                            } else {
                                reply_root["response"] = "Message " + ID + " not found.";
                            }  // if (mbank.erase(ID))
                            reply_root["responseType"] = DATA_RETURNED;
                            break;
                        case RETRIEVE_ENTRY:
                            std::cout << "action:  retrieve entry ID matches = "
                                     << mbank.CheckID(ID) << " " << ID << std::endl;
                            if (mbank.CheckID(ID)) {
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_root["response"] = "Message retrieved.";
                            	reply_root["responseType"] = DATA_RETURNED;
                            } else {
                                reply_root["response"] = "Message " + ID + " not found.";
                            	reply_root["responseType"] = RESPONSE_ONLY;
                            }  // if (mbank.CheckID(ID))
                            break;
                        case RETRIEVE_DATE:
                            std::cout << "action:  retrieve date " << std::endl;
                            if (mbank.getByDate(month, day)){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                reply_root["response"] = "First entry for this date.";
                            	reply_root["responseType"] = DATA_RETURNED;
                            } else {
                                reply_root["response"] =
                                        "Get by date: No entries found for this date.";
                            	reply_root["responseType"] = DATA_RETURNED;
                            }  // if (mbank.getByDate(month, day))
                            break;
                        case RETRIEVE_DATE_NEXT:
                            std::cout << "action:  retrieve date next " << std::endl;
                            if (mbank.getByDateNext(month, day)){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                reply_root["response"] = "Next entry for this date.";
                            	reply_root["responseType"] = DATA_RETURNED;
                            } else {
                                reply_root["response"] = "No more messages for this date.";
                            	reply_root["responseType"] = RESPONSE_ONLY;
                            }
                            break;
                        case RETRIEVE_ALL:
                            std::cout << "action:  retrieve all start " << std::endl;
                            if (mbank.getAllStart()){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_root["response"] = "First entry for get all.";
                             	reply_root["responseType"] = DATA_RETURNED;
                           } else {
                                reply_root["response"] = "Get all.  No entries found.";
                            	reply_root["responseType"] = RESPONSE_ONLY;
                            }  // if (mbank.getAllStart())
                            break;
                        case RETRIEVE_ALL_NEXT:
                            std::cout << "action:  retrieve all next " << std::endl;
                            if (mbank.getAllNext()){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_root["response"] = "Get all:  Next entry.";
                            	reply_root["responseType"] = DATA_RETURNED;
                            } else {
                                reply_root["response"] = "Get all:  No more messages.";
                            	reply_root["responseType"] = RESPONSE_ONLY;
                            }  // if (mbank.getAllNext())
                            break;
                        case RESEQUENCE:
                            std::cout << "action:  resequence " << std::endl;
                            mbank.resequence();
                            reply_root["response"] = "Resequenced " + 
                                   std::to_string(mbank.count()) + " messages.";
                            reply_root["responseType"] = RESPONSE_ONLY;
                            break;
                        default:
                            std::cout << "action:  resequence " << std::endl;
                            reply_root["response"] = "Action unknown.";
                            reply_root["responseType"] = RESPONSE_ONLY;
                            break;
                    }  //  switch(action)
                    message_reply = writer.write(reply_root);
                    message_reply.pop_back();  //  remove \n from end of string.
			
					/* 
					   Return formatted message --
		   
					   Since the subscribe is ongoing in the `pb` context, we
					   can't publish on it, so we use a different context to
					   publish
					*/
 
			
					pubnub::futres fr_2 = pb_2.publish(chan, message_reply);
		
					#ifdef DEBUG
						std::cout << "Await publish with action = " << action << std::endl;
					#endif
					res = fr_2.await();
					if (res == PNR_STARTED) {
						#ifdef DEBUG
							std::cout << "await() returned unexpected: PNR_STARTED" << std::endl;
						#endif
						return -1;
					}
					#ifdef DEBUG
						if (PNR_OK == res) {
							std::cout << "Published! Response from Pubnub: " 
												<< pb_2.last_publish_result() << std::endl;
						}
						else if (PNR_PUBLISH_FAILED == res) {
							std::cout << "Published failed on Pubnub, description: " 
												<< pb_2.last_publish_result() << std::endl;
						}
						else {
							std::cout << "Publishing failed with code: " << (int)res << std::endl;
						}
					#endif
                }  //  if (!msg.empty() && (msg != sent_message))
                #ifdef DEBUG
                    std::cout << "After if !msg.empty && msg != sent" << std::endl;
                #endif
            } while (!msg.empty());
        }  //  if (PNR_OK == res)
        #ifdef DEBUG
            else {
                std::cout << "Subscribing failed with code: " << (int)res << std::endl;
            }
        #endif
      }  //  for(;;;)
    }  // try
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
	
    /* We're done */
    #ifdef DEBUG
        std::cout << "Pubnub subscribe-publish callback demo over." << std::endl;
    #endif
    
    return 0;
}
