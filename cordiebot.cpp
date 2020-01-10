/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */

/**
 *
 *   c++ version of CordieBot
 *
 *   November, 2019 -- Hal Breidenbach
 *   
 **/
 
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <algorithm>
#include "messages.h"
#include <fstream>
#include "countButton.h"
#include "GPIOtoWiringPi.h"
#include <wiringPi.h>
#include "wiringPiTLC59711.h"
#include "wiringPiMCP3002.h"
#include "cbotLights.h"
#include <thread>
#include <random>
#include <curl/curl.h>
#include <bits/stdc++.h> 
#include <curl/curl.h>


#define DEBUG

//  digital I/O constants
#define AMP_ENABLE GPIO21 
#define HIGH 1
#define LOW 0
#define FAN GPIO24 
#define SWITCH GPIO25 

//  light constants
#define LEFT_EYE 1
#define RIGHT_EYE 2
// eye blink with incr 100 & delay 20 lasts about 2 seconds.
#define BLINK_INCR 100
#define BLINK_DELAY 20
#define HEAD_LAMP 0
#define BRAIN_LAMP 3
// light ramp with ramp 64 & delay 30 lasts just under 2 seconds.
#define RAMP 64
#define LIGHT_DELAY 30
#define MAX_COLOR 65535

// temperature constants
#define TEMPERATURE_CHIP_SELECT 1
#define MCP3002_CHANNEL 0

//  mbank and lgen are used many places
MessageBank mbank("proclamations.txt");
std::default_random_engine lgen;
wiringPiMCP3002 tempSensor(TEMPERATURE_CHIP_SELECT, MCP3002_CHANNEL);


/**
 *
 *  convert character array to string.
 *
 *  Thanks to Ivailo Tanusheff
 *
 **/
std::string sconvert(const char *pCh, int arraySize){
    std::string str;
    if (pCh[arraySize-1] == '\0') str.append(pCh);
    else for(int i=0; i<arraySize; i++) str.append(1,pCh[i]);
    return str;
}

/**
 *
 *   replace a portion of a string with another string
 *
 *   Thanks to Mateen Ulhaq
 *
 **/
 
std::string replaceFirst(
    std::string& s,
    const std::string& toReplace,
    const std::string& replaceWith)
{
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return s;
    return s.replace(pos, toReplace.length(), replaceWith);
}

/**
 *  format a string with the speech prelude and postlude and pass it to the system
 *  to be spoken.
 *
 **/
void speak(std::string say){
    digitalWrite(AMP_ENABLE, HIGH);  //  AMP_ENABLE was put in to resolve noise between
                                     //  speech events.  Might have been a Python issue.
    const std::string prelude ("aoss swift \"<prosody rate='-0.3'> ");
    const std::string postlude ("\"");
    std::string totality = prelude + say + postlude;
    const char *speech = totality.c_str();
    system(speech);
    digitalWrite(AMP_ENABLE, LOW);
}

/**
 *
 *  lightShow()
 *
 *  Note that the head and brain lamps take iterations + 1 time since they are reset
 *  to zero after the for statement.
 *
 **/
void lightShow(int iterations){
    std::uniform_int_distribution<int> ldist(0,MAX_COLOR);
    
    cbotLights lights = cbotLights();
    lights.setIncrements(LEFT_EYE, BLINK_INCR, BLINK_DELAY);  
    lights.setIncrements(RIGHT_EYE, BLINK_INCR, BLINK_DELAY);
    lights.setIncrements(HEAD_LAMP, RAMP, LIGHT_DELAY);
    lights.setIncrements(BRAIN_LAMP, RAMP, LIGHT_DELAY);
    lights.rampPair(LEFT_EYE, RIGHT_EYE, 0, MAX_COLOR / 2, MAX_COLOR,
                                         0, MAX_COLOR / 2, MAX_COLOR);
    for (int ndx = 0; ndx < iterations; ++ndx){
        lights.rampPair(HEAD_LAMP, BRAIN_LAMP, ldist(lgen), ldist(lgen), ldist(lgen),
                                            ldist(lgen), ldist(lgen), ldist(lgen));
    }
    lights.rampPair(HEAD_LAMP, BRAIN_LAMP, 0, 0, 0, 0, 0, 0);
    lights.rampPair(LEFT_EYE, RIGHT_EYE, 0, 0, 0, 0, 0, 0);

}

/**
 *
 *   internet tests if the internet can be accessed.
 *
 **/
bool internet(){
    #ifdef DEBUG
        std::cout << "ping return: " << system("ping -c 1 8.8.8.8") << std::endl;
    #endif
    if (system("ping -c 1 8.8.8.8") != 0){
        speak("I don't appear to be connected to a why fi network.");
        return 0;
    } else {
        return 1;
    }
}

/**
 *
 *   WriteCallback is used when retrieving URLs from the web.
 *
 **/
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
return size * nmemb;
}

/**
 *
 *   checkFan gets the current inside temperature, computes a running average, and
 *   if the temperature is high, turns on the fan.
 *
 **/
float checkFan(float average_temp){
    float volts = tempSensor.getVolts();
    float sample_temp = (volts * 190.8) - 68.8;
    float new_average_temp = average_temp * 0.95 + sample_temp * 0.05;
    if (new_average_temp > 100.0){
        digitalWrite(FAN, HIGH);  // Turn on fan
    }
    else
    {
        digitalWrite(FAN, LOW);
    }
    return new_average_temp;
}


/****************************************************************************
 *
 *   Speech routines
 *
 ****************************************************************************/
 
std::string getProcMsg(){
//    std::default_random_engine lgen;
    std::uniform_int_distribution<int> typeOneDist(0,4);
    if ((mbank.type1count() > 0) && (typeOneDist(lgen) == 2)){
        if (mbank.type1count() == 1){
            return mbank.getNthEntry(MESSAGE_TYPE_1, 1);
        }
        else
        {
            std::uniform_int_distribution<int> randMsg(1,mbank.type1count());
            return mbank.getNthEntry(MESSAGE_TYPE_1, randMsg(lgen));
        }
    }
    std::uniform_int_distribution<int> typeTwoDist(0,3);
    if ((mbank.type2count() > 0) && (typeTwoDist(lgen) == 1)){
        if (mbank.type2count() == 1){
            return mbank.getNthEntry(MESSAGE_TYPE_2, 1);
        }
        else
        {
            std::uniform_int_distribution<int> randMsg(1,mbank.type2count());
            return mbank.getNthEntry(MESSAGE_TYPE_2, randMsg(lgen));
        }
    }
    std::uniform_int_distribution<int> typeThreeDist(0,2);
    int typeThreeChance = typeThreeDist(lgen);
    #ifdef DEBUG
        std::cout << "typeThreeChance: " << typeThreeChance << std::endl;
    #endif
    if ((mbank.type3count() > 0) && (typeThreeDist(lgen) == 1)){
        if (mbank.type3count() == 1){
            return mbank.getNthEntry(MESSAGE_TYPE_3, 1);
        }
        else
        {
            std::uniform_int_distribution<int> randMsg(1,mbank.type3count());
            int typeThreeChoice = randMsg(lgen);
            #ifdef DEBUG
                std::cout << "typeThreeChoice: " << typeThreeChoice << std::endl;
            #endif
            return mbank.getNthEntry(MESSAGE_TYPE_3, typeThreeChoice);
        }
    }
    return "";
}

/**
 *
 *  macro definition for getSpeakTime
 *
 *  calculates the number of light show iterations to speak a string based on the
 *  empirical analysis that a single character takes about 0.11 seconds and that
 *  the light show iterations are about 2 seconds long.  Therefore, 18 characters
 *  should take just one light show iteration.  So the division will round up and
 *  and a bit high, we add 12 to the message length.
 *
 **/
#define getSpeakTime(msg)  ((msg.length() + 12)/18)

void tellTime(){
    int const timeSpeakBase = 3;  // light show iterations to speak time with no message.
    std::string ttmessage = getProcMsg();
    int lightShowTime = timeSpeakBase + getSpeakTime(ttmessage);
    std::thread first (lightShow, lightShowTime);
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"It is %I:%M %p, on  %A,  %B %e, %Y \0",timeinfo);
    std::string time_str = sconvert(buffer, 80);
    #ifdef DEBUG
        std::cout << time_str << std::endl;
        std::cout << "length of time_str:  " << time_str.length() << std::endl;
    #endif
    std::string str = time_str + "<break time='1s' />" + ttmessage;

    #ifdef DEBUG
        std::cout << str << std::endl;
        std::cout << "length of string to speak:  " << str.length() << std::endl;
    #endif

    speak(str);
    first.join();
}

/**
 *
 *  tellWeather - obtain weather for current zip code, select portions into a statement,
 *  and pretty up the statement.
 *
 *  Thanks to Rami Al-Ghanmi for curl_example.cpp which is the basis for this routine.
 *
 **/
void tellWeather(){
    if (internet()){
        #ifdef DEBUG
            std::cout << "In weather, internet OK" << std::endl;
        #endif
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://geoip-db.com/json/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            #ifdef DEBUG
                std::cout << readBuffer << std::endl;
            #endif
            JSONCPP_STRING json_err;
            Json::Value root;
            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            int rawLength = readBuffer.length();
            if (!reader->parse(readBuffer.c_str(), readBuffer.c_str() + rawLength, &root, &json_err)) {
                #ifdef DEBUG
                    std::cout << "json error" << std::endl;
                #endif
            } else {
                std::string zipCode;
                zipCode = root["postal"].asString();
                std::cout << "current location:  " << zipCode <<  std::endl;
                std::string getWeather;
                getWeather = "http://api.openweathermap.org/data/2.5/weather?zip=" +
                        zipCode + 
                        ",US&units=imperial&APPID=654aba6d654a67d6b2917f37c410141f";
                #ifdef DEBUG
                    std::cout << getWeather << std::endl;
                #endif
                int n = getWeather.length();
                char getWeatherChar[n+1];
                std::strcpy(getWeatherChar, getWeather.c_str());
                std::string readBuffer2;
                curl = curl_easy_init();
                curl_easy_setopt(curl, CURLOPT_URL, getWeatherChar);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer2);
                res = curl_easy_perform(curl);  //  retrieve does not work if this
                                                //  statement is removed.
                curl_easy_cleanup(curl);
                std::cout << readBuffer2 << std::endl;
                int rawLength2 = readBuffer2.length();
                if (!reader->parse(readBuffer2.c_str(), readBuffer2.c_str() + rawLength2, &root, &json_err)) {
                    #ifdef DEBUG
                        std::cout << "json error" << std::endl;
                    #endif
                } else {
                    std::thread first (lightShow, 3);
                    int truncTemp = int(root["main"]["temp"].asDouble() + 0.5);
                    std::string temperature;
                    if ((truncTemp == 1)  || (truncTemp == -1)) {
                        temperature = std::to_string(truncTemp) + " degree";
                    } else {
                        temperature = std::to_string(truncTemp) + " degrees";
                    }
                    std::string descr = root["weather"][0]["description"].asString();
                    #ifdef DEBUG
                        std::cout << "description: " << descr << std::endl;
                        std::cout << "temp: " << temperature << std::endl;
                    #endif
                    descr = replaceFirst(descr, "sky", "skies");
                    descr = replaceFirst(descr, "haze", "hazey skies");
                    descr = replaceFirst(descr, "overcast", "over cast");
                    descr = replaceFirst(descr, "thunderstorm", "thunderstorms");
                    std::string weatherTxt = "The temperature outside is " +
                                temperature + " with " + descr;
                    #ifdef DEBUG
                        std::cout << "weatherTxt: " << weatherTxt << std::endl;
                    #endif
                    speak(weatherTxt);
                    first.join();
                }
            }       
        }
    }
}

void tellDailyQuote(){
    if (internet()){
        int const quoteSpeakBase = 2;  // light show iterations to speak quote with no message.
        #ifdef DEBUG
            std::cout << "In weather, internet OK" << std::endl;
        #endif
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.brainyquote.com/link/quotebr.rss");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            #ifdef DEBUG
                std::cout << readBuffer << std::endl;
            #endif
            std::size_t start = readBuffer.find("<item>") + 6;
            std::size_t len = readBuffer.find("</item>") - start;
            std::string item = readBuffer.substr(start, len);
            #ifdef DEBUG
                std::cout << "item: " << item << ", " << start << ", " << len << std::endl;
            #endif
            start = item.find("<description>") + 14;
            len = item.find("</description>") - start - 1;
            std::string quote = item.substr(start, len);
            #ifdef DEBUG
                std::cout << "quote: " << quote << ", " << start << ", " << len << std::endl;
            #endif
            start = item.find("<title>") + 7;  // I know, title for auther does not make
            len = item.find("</title>") - start;  // sense, however, it is correct.
            std::string author = item.substr(start, len);
            int quoteTime = quoteSpeakBase + getSpeakTime(quote) +
                                                     getSpeakTime(author);
            #ifdef DEBUG
                std::cout << "author: " << author << ", " << start << ", " <<
                                             len << std::endl;
                std::cout << "iterations:  " << quoteTime << std::endl;
            #endif
            std::thread first (lightShow, quoteTime);
            std::string quoteTxt = quote + "<break strength='strong' />" + author;
            speak(quoteTxt);
            first.join();
        }
    }
}

void tellOrigin(){
    int const lightShowTime = 7;
    std::string const myStory = "I am Cordeebot.<break strength='strong' />"
                                "I was made by Grampa in 20 16 for Cordies 11th birthday."
                                "<break strength='strong' />"
                                "In 20 19 Grampa gave me a new brain."
                                "<break strength='strong' />"                 
                                "I feel much smarter now.";
    std::thread first (lightShow, lightShowTime);
    speak(myStory);
    first.join();
}

void tellInternalTemp(float current_temp){
    int const lightShowTime = 2;
    std::string my_temp = "My internal temperature is " +
                                            std::to_string(int(current_temp)) + " degrees.";
    #ifdef DEBUG
        std::cout << my_temp << std::endl;
    #endif
    std::thread first (lightShow, lightShowTime);
    speak(my_temp);
    first.join();
}

void tellEasterEgg(){
    int const lightShowTime = 2;
    #ifdef DEBUG
        std::cout << "Easter egg" << std::endl;
    #endif
    std::thread first (lightShow, lightShowTime);
    speak("you found an easteregg<break time='1s' />good job.");
    first.join();
}

/****************************************************************************
 *
 *  Initialization routines
 *
 ****************************************************************************/

void set_mbank_counts() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    mbank.setCounts(timePtr->tm_year+1900,timePtr->tm_mon,timePtr->tm_mday);
    #ifdef DEBUG
        std::cout << "Today = " << timePtr->tm_mon << "/" << timePtr->tm_mday <<
                             "/" << timePtr->tm_year+1900 << std::endl;
        std::cout << "Today type 1 " << mbank.type1count() << std::endl;
        std::cout << "Today type 2 " << mbank.type2count() << std::endl;
        std::cout << "Today type 3 " << mbank.type3count() << std::endl;
    #endif
}

void signal_handler( int signal_num ){
    #ifdef DEBUG
        std::cout << "Received SIGUSR1, reloading messages." << std::endl;
    #endif
    mbank.reload();
}
 
void init()
{
    //   Initialize wiringPi
    wiringPiSetup();	// for digital I/O
    pinMode(AMP_ENABLE, OUTPUT);  // Amplifier is disabled between speech events.
    srand (time(NULL));   // random number seed to simulate random start
    pinMode(FAN, OUTPUT);

    set_mbank_counts();
    
    signal(SIGUSR1, signal_handler);
}


/****************************************************************************
 *
 *  Main
 *
 ****************************************************************************/

int main()
{
    #ifdef DEBUG
        std::cout << "Starting CordieBot" << std::endl;
    #endif
    std::string intro = "I am cordeebot.";
    
    init();
    
    int counter;
    int file_check_counter = 0;
    float internal_temp;
    bool internetPresent = internet();
    #ifdef DEBUG
        std::cout << "Internet present = " << internetPresent << std::endl;
    #endif
    double touchButtonGap = 0.6;
    countButton button(SWITCH, touchButtonGap);		// Setup the switch
	    
    while(1) {
        counter = button.read();
        if( counter == 0){
            usleep(200*1000); 	// Delay 100ms
        } else {
            #ifdef DEBUG
                std::cout << "button:  " << counter << std::endl;
            #endif
            switch (counter) {
                case 1: {   tellTime();
                            break;
                        }
                case 2: {   tellWeather();
                            break;
                        }
                case 3: {   tellDailyQuote();
                            break;
                        }
                case 8: {   tellOrigin();
                            break;
                        }
                case 9: {   tellInternalTemp(internal_temp);
                            break;
                        }
                case 17: {  tellEasterEgg();
                            break;                        
                        }
                default: {
                            #ifdef DEBUG
                                std::cout << "Invalid option selected." << std::endl;
                            #endif
                        }
            }
        }
        internal_temp = checkFan(internal_temp);
        ++file_check_counter;
        if (file_check_counter > 300){  // check once a minute (with 200ms sleep)
            if (mbank.changed()){
                mbank.reload();
                #ifdef DEBUG
                    std::cout << "reloading messages" << std::endl;
                #endif
             }
             file_check_counter = 0;
        }
    }
    return 0;
}
