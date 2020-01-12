/*

    msgtest.cpp  -  create msgTest file (use CB_Json_test.mk)
    created from an example by Rudolf Olah
                                 at https://github.com/rudolfolah/learning-jsoncpp
    I am much indebted to him.

    Revisions for CordieBot by Hal Breidenbach, October 2019

*/

#include <cstring>
#include <iostream>

#include "messages.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " COMMAND FILENAME" << endl
         << "COMMAND: 'load' or 'save'" << endl
         << "Load will load the JSON file, FILENAME, and print out its contents." << endl
         << "Save will save a sample address book to FILENAME in JSON format." << endl;
    return 1;
  }
  MsgList proclamations;
  if (strcmp(argv[1], "load") == 0) {
    std::cout << "ID  type  year   month   day   content" << std::endl;
    proclamations.JsonLoad(argv[2]);
    for (vector<Message>::const_iterator it = proclamations.messages().begin();
                         it != proclamations.messages().end(); ++it) {
      cout << (*it).ID() << ", " << (*it).type() << ", "
                << (*it).year() << ", " << (*it).month() << ", " << (*it).day() << ", " 
                << (*it).content() << endl;
    }
  } else if (strcmp(argv[1], "save") == 0) {
    proclamations.AddMessage("1", 1, 2020, 01, 01, "Happy New Year and welcome to 2020");
    proclamations.AddMessage("2", 2, 0, 05, 15, "Today is Moms birthday.");
    proclamations.AddMessage("3", 2, 0, 05, 12, "Moms birthday is pretty soon.");
    proclamations.AddMessage("4", 2, 0, 06, 10, "Today is Dads birthday.");
    proclamations.AddMessage("5", 2, 0, 06, 10, "Dads birthday is pretty soon.");
    proclamations.AddMessage("6", 3, 0, 0, 0, "Were off to see the wizard.");
    proclamations.AddMessage("7", 3, 0, 0, 0, "I am all shined up with no place to go.");
    proclamations.AddMessage("8", 3, 0, 0, 0, "Bots rule.");
    proclamations.AddMessage("9", 3, 0, 0, 0, "has anybody seen r 2 d 2?");
    proclamations.AddMessage("10", 3, 0, 0, 0, "I must not say: voldehmort.");
    proclamations.AddMessage("11", 3, 0, 0, 0, "its a  bird, its a  plane, its, superman.");
    proclamations.AddMessage("12", 3, 0, 0, 0, "i would like to taste a butter beer, but i dont have a tongue.");
    proclamations.AddMessage("13", 3, 0, 0, 0, "yubba dubba doo.");
    proclamations.AddMessage("14", 3, 0, 0, 0, "what would skoobie do?");
    proclamations.AddMessage("15", 3, 0, 0, 0, "Is it true?  Is it kind?  Will it help?");
    proclamations.AddMessage("16", 3, 0, 0, 0, "B B 8.  That droid is great.");
    proclamations.AddMessage("17", 3, 0, 0, 0, "Am I the droid you are looking for?");
    proclamations.AddMessage("18", 3, 0, 0, 0, "Minecraft is fun.");
    proclamations.AddMessage("19", 3, 0, 0, 0, "I have nothing to say about that.");
    proclamations.AddMessage("20", 3, 0, 0, 0, "Apologize.  Apologize.");
    proclamations.AddMessage("21", 3, 0, 0, 0, "Im sorry.  Oh, that is Victors line.");
    proclamations.AddMessage("22", 3, 0, 0, 0, "Kibo says Hi");
    proclamations.AddMessage("23", 3, 0, 0, 0, "Is that a robophobic remark?");
    proclamations.JsonSave(argv[2]);
  }
  return 0;
}
