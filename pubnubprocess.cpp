/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "pubnub.hpp"

#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <algorithm>
#include "messages.h"
#include <fstream>

#define DEBUG

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

std::string adjustApostropies(std::string str){
    std::string work = str;
    std::replace(work.begin(), work.end(), '\"', '\'' );
    std::replace(work.begin(), work.end(), '\n', ' ' ); 
    return work;                          
}

int main()
{
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
    string message_reply;
    #ifdef DEBUG
        std::cout << "input message count:  " << mbank.count() << std::endl;
    #endif
    try {
      for (;;) {
        enum pubnub_res res;
            char const *chan = "cordiebot";
            pubnub::context pb(pubkey, subkey);
            pubnub::context pb_2(pubkey, subkey);
            JSONCPP_STRING json_err;

            std::string ID;
            int action;
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
                "--------------------------";
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
                "Publishing..." << std::endl <<
                "--------------------------";
        #endif
        
        /* Since the subscribe is ongoing in the `pb` context, we
           can't publish on it, so we use a different context to
           publish
        */
        if (action > 0) {
            pubnub::futres fr_2 = pb_2.publish(chan, message_reply);
        
            #ifdef DEBUG
                std::cout << "Await publish" << std::endl;
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
        }
        /* Now we await the subscribe on `pbp` */
        #ifdef DEBUG
            std::cout << "Await subscribe" << std::endl;
        #endif
        res = futres.end_await();
        action = 0;
        if (PNR_OK == res) {
            #ifdef DEBUG
                std::cout << "Subscribed! Got messages:";
            #endif
            do {
                msg = pb.get();
                string next_entry;
                std::cout << msg << std::endl;
                if (!msg.empty() && (msg != message_reply)){
                    #ifdef DEBUG
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
                    type = root["type"].asInt();
                    day = root["day"].asInt();
                    month = root["month"].asInt();
                    year = root["year"].asInt();
                    content = root["content"].asString();
                    Json::Value reply_root;
                    Json::FastWriter writer;
                    switch (action){
                        case ADD_ENTRY:
                            next_entry = mbank.getNextID();
                            std::cout << "next entry returns:  " << next_entry << std::endl;
                            mbank.addEntry(next_entry, type, year, month, day, content);
                            root["ID"] = next_entry;
                            reply_string = adjustApostropies(writer.write(root));
                            message_reply = "\"Action = add.  New ID is " +
                                        next_entry  + ". " + reply_string +"\"";
                            std::cout << message_reply << std::endl;
                            break;
                        case CHANGE_ENTRY:
                            if (mbank.erase(ID)) {
                                mbank.addEntry(ID, type, year, month, day, content);
                                reply_string = adjustApostropies(writer.write(root));
                                message_reply = "\"Action = change. " + reply_string +"\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"Action = change.  Message " +
                                                             ID + " not found.\"";
                            }  // if (mbank.erase(ID))
                            break;
                        case DELETE_ENTRY:
                            if (mbank.erase(ID)) {
                                reply_string = adjustApostropies(writer.write(root));
                                message_reply = "\"Action = delete. " + reply_string +"\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"Action = delete.  Message " +
                                                             ID + " not found.\"";
                            }  // if (mbank.erase(ID))
                            break;
                        case RETRIEVE_ENTRY:
                            std::cout << "action:  retrieve entry ID matches = "
                                                << mbank.CheckID(ID) << std::endl;
                            if (mbank.CheckID(ID)) {
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                message_reply = adjustApostropies(reply_string);
                                message_reply = "\"Action = retrieve.  " +
                                                         message_reply + "\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"Action = retrieve.  Message " +
                                                             ID + " not found.\"";
                            }  // if (mbank.CheckID(ID))
                            break;
                        case RETRIEVE_DATE:
                            if (mbank.getByDate(month, day)){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                message_reply = adjustApostropies(reply_string);
                                message_reply = "\"Action = get by date.  " +
                                                         message_reply + "\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"Action = get by date.  Entries for " +
                                         to_string(month)  + "/" + to_string(day) +
                                          " not found.\"";
                            }  // if (mbank.getByDate(month, day))
                            break;
                        case RETRIEVE_DATE_NEXT:
                            if (mbank.getByDateNext(month, day)){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                message_reply = adjustApostropies(reply_string);
                                message_reply = "\"Action = get by date next.  " +
                                                         message_reply + "\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply =
                                    "\"End of messages for " +
                                         to_string(month)  + "/" + to_string(day) + "\"";
                            }
                            break;
                        case RETRIEVE_ALL:
                            if (mbank.getAllStart()){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                message_reply = adjustApostropies(reply_string);
                                message_reply = "\"Action = get all.  " +
                                                         message_reply + "\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"Action = get all.  No entries found.\"";
                            }  // if (mbank.getAllStart())
                            break;
                        case RETRIEVE_ALL_NEXT:
                            if (mbank.getAllNext()){
                                reply_root["ID"] = mbank.ID();
                                reply_root["year"] = mbank.year();
                                reply_root["month"] = mbank.month();
                                reply_root["day"] = mbank.day();
                                reply_root["type"] = mbank.type();
                                reply_root["content"] = mbank.content();
                                reply_string = writer.write(reply_root);
                                message_reply = adjustApostropies(reply_string);
                                message_reply = "\"Action = get all.  " +
                                                         message_reply + "\"";
                                std::cout << message_reply << std::endl;
                            } else {
                                message_reply = "\"End of messages.\"";
                            }  // if (mbank.getAllNext())
                            break;
                        case RESEQUENCE:
                            mbank.resequence();
                            message_reply = "\"Resequenced " + 
                                       to_string(mbank.count()) + " messages.\"";
                            break;
                        default:
                                message_reply = "\"Action unknown " + to_string(action)
                                                     + "\"";
                            break;
                    }  //  switch(action)
                }  //  if (!msg.empty() && (msg != sent_message))
            } while (!msg.empty());
        }
        #ifdef DEBUG
            else {
                std::cout << "Subscribing failed with code: " << (int)res << std::endl;
            }
        #endif
      }
    }
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
	
    /* We're done */
    #ifdef DEBUG
        std::cout << "Pubnub subscribe-publish callback demo over." << std::endl;
    #endif
    
    return 0;
}
