/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */

/*************************************************************************************

  pubnublisten_subloop.cpp -- based on pubnub_subloop.cpp

  Heavily modified by Hal Breidenbach for use in the CordieBot project.  Sept. 2019

  This program is basically used to take a message sent from the CordieBot
  Communication html script and speak it.

**************************************************************************************/

#include "pubnub.hpp"

#include <iostream>
#include <exception>
#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <fstream>

int main()
{
    try {
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
        std::string chan("cordietalk");
            pubnub::context pb(pubkey, subkey);
            pubnub::context pb_2(pubkey, subkey);
 
        if (0 != pb.set_uuid_v4_random()) {
            pb.set_uuid("zeka-peka-iz-jendeka");
        }
        else {
            std::cout << "Generated UUID: " << pb.uuid() << std::endl;
        }

        pubnub::subloop sublup(pb, chan);

        sublup.loop([](std::string msg, pubnub::context&, pubnub_res res) {
                if (PNR_OK != res) {
                    std::cout << "Getting message failed with code: " << res;
                    return -1;
                }
                std::cout << ">201103L: Got message: \n" << msg << std::endl;
                JSONCPP_STRING json_err;
                Json::Value root;
                Json::CharReaderBuilder builder;
                const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
                int rawLength = msg.length();
                if (!reader->parse(msg.c_str(), msg.c_str() + rawLength, &root, &json_err)) {
                    std::cout << "json error" << std::endl;
                } else {
                    const std::string prelude ("aoss swift \"<prosody rate='-0.3'> ");
                    const std::string postlude ("\"");
                    std::string content = root["content"].asString();
                    std::cout << "msg content:  " << content << "  length: " <<
                                     content.length() << std::endl;
                    std::string totality = prelude + content + postlude;
                    const char *speak = totality.c_str();
                    system(speak);
                }

                return 0;
            });
    }
    catch (std::exception &exc) {
        std::cout << "Caught exception: " << exc.what() << std::endl;
    }
    
    return 0;
}
