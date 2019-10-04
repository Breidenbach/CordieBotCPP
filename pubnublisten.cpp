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

int main()
{
    try {
        std::string chan("cordietalk");
        pubnub::context pb("pub-c-1b01f37e-e28e-4e77-8f5c-d004f80840ae",
                           "sub-c-a301580a-54a0-11e9-94f2-3600c194fb1c");
 
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
                    std::cout << "msg content:  " << content << std::endl;
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
