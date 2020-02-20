/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */

/**
 *
 *   c++ version of CordieBot
 *
 *   November, 2019 -- Hal Breidenbach
 *   
 **/
 
#include <jsoncpp/json/json.h>
#include <memory>
#include <string>
#include <algorithm>
#include "messages.h"
#include <iostream>
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
#include <unistd.h>
#include <sys/sendfile.h>  // sendfile
#include <fcntl.h>         // open
#include <unistd.h>        // close
#include <sys/stat.h>      // fstat
#include <sys/types.h>     // fstat

//#define DEBUG

//  digital I/O constants
#define AMP_ENABLE GPIO21 
#define HIGH 1
#define LOW 0
#define FAN GPIO17 
#define SWITCH GPIO25 

//  light constants
#define LEFT_EYE 1
#define RIGHT_EYE 2
// eye blink with incr 100 & delay 20 lasts about 2 seconds.
#define BLINK_INCR 100
#define BLINK_DELAY 20
#define HEAD_LAMP 0
#define BRAIN_LAMP 3
// light ramp with ramp 128 & delay 18 lasts just under 3 seconds.
#define RAMP 128
#define LIGHT_DELAY 18
#define MAX_COLOR 65535

// temperature constants
#define TEMPERATURE_CHIP_SELECT 1
#define MCP3002_CHANNEL 0
#define FAN_LIMIT 100.0

//  mbank, lgen, and tempSensor are used many places
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
 *   convert string to hex for debugging
 **/
#ifdef DEBUG
    inline unsigned int to_uint(char ch)
    {
        // EDIT: multi-cast fix as per David Hammen's comment
        return static_cast<unsigned>(static_cast<unsigned char>(ch));
    }
#endif

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
    std::string totality = prelude;
    totality.append(say);
    totality.append(postlude);
    #ifdef DEBUG
        std::cout << totality << std::endl;
        std::cout << "length of string to speak:  " << totality.length() << std::endl;
        std::cout << std::hex;
        for (char ch : totality)
        {
            std::cout << "0x" << to_uint(ch) << ' '; 
        }
        std::cout << "] end of totality" << std::endl;        
    #endif
    const char *speech = totality.c_str();
    #ifdef DEBUG
        std::cout << "speak: [" << totality.c_str() << "] " << std::endl;
    #endif
    system(speech);
    digitalWrite(AMP_ENABLE, LOW);
}

/**
 *
 *  lightShow(iterations)
 *
 *  Note that the head and brain lamps take iterations + 1 time since they are reset
 *  to zero after the for statement.
 *
 *  setRandLight(r, g, b)
 *
 *  Set the color to random RGB values - randomly selecting one color, setting another 
 *  color to the max value minus the first color, and setting the third to zero.
 *
 **/
 
void setRandLight(int &r, int &g, int &b){
    int v[3] = {0, 0, 0};
    int c1, c2;
    std::uniform_int_distribution<int> ldist(0,MAX_COLOR);
    std::uniform_int_distribution<int> lchoice1(0,2);
    std::uniform_int_distribution<int> lchoice2(0,1);
    c1 = lchoice1(lgen);
    c2 = (c1 + lchoice2(lgen)) % 3;
    v[c1] = ldist(lgen);
    v[c2] = MAX_COLOR - v[c1];
    r = v[0];
    g = v[1];
    b = v[2];
}

void lightShow(int iterations){
    std::uniform_int_distribution<int> ldist(0,MAX_COLOR);
    int HeadR, HeadG, HeadB, BrainR, BrainG, BrainB;
    cbotLights lights = cbotLights();
    lights.setIncrements(LEFT_EYE, BLINK_INCR, BLINK_DELAY);  
    lights.setIncrements(RIGHT_EYE, BLINK_INCR, BLINK_DELAY);
    lights.setIncrements(HEAD_LAMP, RAMP, LIGHT_DELAY);
    lights.setIncrements(BRAIN_LAMP, RAMP, LIGHT_DELAY);
    lights.rampPair(LEFT_EYE, RIGHT_EYE, 0, MAX_COLOR / 2, MAX_COLOR,
                                         0, MAX_COLOR / 2, MAX_COLOR);
    for (int ndx = 0; ndx < iterations; ++ndx){
        setRandLight(HeadR, HeadG, HeadB);
        setRandLight(BrainR, BrainG, BrainB);
        lights.rampPair(HEAD_LAMP, BRAIN_LAMP, HeadR, HeadG, HeadB,
                                            BrainR, BrainG, BrainB);
    }
    lights.rampPair(HEAD_LAMP, BRAIN_LAMP, 0, 0, 0, 0, 0, 0);
    lights.rampPair(LEFT_EYE, RIGHT_EYE, 0, 0, 0, 0, 0, 0);

}

/**
 *
 *   internet tests if the internet can be accessed.
 *
 **/
bool internet(int startcount){
    int test_result = 0;
    while (startcount > 0){
        test_result = system("ping -c 1 8.8.8.8");
        #ifdef DEBUG
            std::cout << "ping return: " << test_result << " cnt: "
                                                 << startcount << std::endl;
        #endif
        if (test_result == 0) { return true;}
        startcount--;
        usleep(1000*1000);  // delay 1 second
    }
    speak("I don't appear to be connected to a why fi network.");
    speak("Check if your why fi is running. Check if anyone changed the "
                "password.  Otherwise, grampa might be able to help.");
    return 0;
}

/**
 *  getDay -- used to get the current day (in several places)
 *
 **/
 
int getDay()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    return timePtr->tm_mday;
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
 *   checkFan gets the current inside temperature, updates a running average, and
 *   if the temperature is high, turns on the fan.
 *
 **/
void checkFan(float &average_temp){
    float volts = tempSensor.getVolts();
    float sample_temp = (volts * 190.8) - 68.8;
    average_temp = average_temp * 0.95 + sample_temp * 0.05;
    if (average_temp > FAN_LIMIT){
        digitalWrite(FAN, HIGH);  // Turn on fan
    }
    else
    {
        digitalWrite(FAN, LOW);
    }
}

/**
 *
 *  Self update routines
 *
 *  Check if USB files present.  If it is, /proc/mounts will contain the string
 *   "CORDIEBOT"
 *
 */
 
std::string findCordiebotUSB()
{
    std::string line;
    std::ifstream USBfile ("/proc/mounts");
    if (USBfile.is_open())
    {
        while ( getline (USBfile,line) )
        {
            if (line.find("CORDIEBOT") != std::string::npos) {
                return line;
            }
        }
    USBfile.close();
    }
    return "";
}

void copyFile(const char* infile, const char* outfile){
    int source = open(infile, O_RDONLY, 0);
    int dest = open(outfile, O_WRONLY | O_CREAT, 0644);

    // struct required, rationale: function stat() exists also
    struct stat stat_source;
    fstat(source, &stat_source);

    sendfile(dest, source, 0, stat_source.st_size);

    close(source);
    close(dest);
}

/**
 * check for wpa_supplicant.conf file repacement
 *   If file is present, it is moved to /etc/wpa_supplicant/ and can be used
 *   to find a new wifi network or change the password of an existing network.
 *   Note that the system must be restarted to use the new wpa_supplicant.conf 
 *   file.
 *
 **/

void checkForConf() {

    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    bool shutdown = false;
    bool copy_bot = false;
    stream = popen("ls /media/pi/CORDIEBOT 2>&1", "r");
    if (stream)
    {
        while (!feof(stream))
        {
            if (fgets(buffer, max_buffer, stream) != NULL)
            {
                std::size_t found;
                std::string data;
                std::string match_string = "wpa_supplicant.conf\n";
                data.append(buffer);
                std::cout << "cbot line  " << data << std::endl;
        
                found = data.find(match_string);
                if (found!=std::string::npos)
                {
                    #ifdef DEBUG
                        std::cout << "got wpa_supplicant.conf: " << std::endl;
                    #endif
                    speak("I have found a new why fi name and password file.  "
                                "I will start using that file after I reboot.");
                    system("sudo /home/pi/CordieBot2/cp_wpa_conf.sh"
                                                        " /media/pi/CORDIEBOT");
                    shutdown = true;
                }
                found = data.find("cp_cordiebot.sh");
                if (found!=std::string::npos)
                {
                    #ifdef DEBUG
                        std::cout << "cp_cordiebot.sh found" << std::endl;
                    #endif

                    copyFile("/media/pi/CORDIEBOT/cp_cordiebot.sh","cp_cordiebot.sh");
                                    
                    system("chmod a+x /home/pi/CordieBot2/cp_cordiebot.sh");
                    shutdown = true;
                    copy_bot = true;
                } else {
                    found = data.find("cordiebot");
                    if (found!=std::string::npos)
                    {
                        #ifdef DEBUG
                            std::cout << "at least one cordiebot"
                                                    " executable found" << std::endl;
                        #endif
                        shutdown = true;
                        copy_bot = true;
                    }
                }
            }
        }
        pclose(stream);
        if (copy_bot)
        {
            speak("I have found a new cordee bot file. "
                            "I will start using that file after I reboot.");
            system("/home/pi/CordieBot2/cp_cordiebot.sh /media/pi/CORDIEBOT");
            system ("chmod a+x cp_cordiebot.sh");
        }
        if (shutdown) 
        {
            speak("Remove the USB stick now.");
            usleep(5000*1000);
            sync();
            #ifdef DEBUG
                std::cout << "reboot starts here " << std::endl;
            #endif        
            system("sudo shutdown -r now");
        }
    }
    if ( ! copy_bot && ! shutdown)
    {
        speak("You asked me to check for updates, but either there are no updates"
                                        " or there is no memory stick present. ");
    }
}

/****************************************************************************
 *
 *   Speech routines
 *
 *   returns a message based on the following rules:
 *   1st - if there are messages specific for the day (type 1) those messages
 *     will be returned with certainty.  If there are several for a day, the
 *     they will be returned from the highest ID to the lowest.  This will
 *     only happen at the beginning of the day, or on a reboot.
 *   2nd - messages will be returned based on random numbers, choosing from
 *     type 1 (special day), type 2 (specific day each year), and then
 *     type 3 (any day).  Within each group, a messages is chosen using
 *     a 2nd random number.  
 *
 ****************************************************************************/
 
std::string getProcMsg(int &type1count){
//    std::default_random_engine lgen;
    #ifdef DEBUG
        std::cout << "type1count: " << type1count << std::endl;
    #endif
    if (type1count > 0) {   //  if there exists a message for today which
                            //  has not been returned.
        int msgnum = type1count;
        type1count--;
        return mbank.getNthEntry(MESSAGE_TYPE_1, msgnum);
    }
    // on to the random groups
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
    if ((mbank.type3count() > 0) && (typeThreeChance == 1)){
        if (mbank.type3count() == 1){
            return mbank.getNthEntry(MESSAGE_TYPE_3, 1);
        }
        else
        {
            std::uniform_int_distribution<int> randMsg(1,mbank.type3count());
            int typeThreeChoice = randMsg(lgen);
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
 *  the light show iterations are about 3 seconds long.  Therefore, 36 characters
 *  should take just one light show iteration.  So the division will round up and
 *  and a bit high, we add 12 to the message length.
 *
 **/
#define getSpeakTime(msg)  ((msg.length() + 12)/27)

void tellTime(int &type1count){
    int const timeSpeakBase = 3;  // light show iterations to speak time with no message.
    std::string ttmessage = getProcMsg(type1count);
    #ifdef DEBUG
        std::cout << "time message: " << ttmessage << std::endl;
    #endif
    int lightShowTime = timeSpeakBase + getSpeakTime(ttmessage);
    std::thread first (lightShow, lightShowTime);
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"It is %I:%M %p, on  %A,  %B %e, twenty %y \0",timeinfo);
    std::string time_str = sconvert(buffer, 80);
    size_t zero_ndx = time_str.find('\0');
    if (zero_ndx!=std::string::npos)
    {
        time_str.erase(zero_ndx);
    }
    #ifdef DEBUG
        std::cout << time_str << std::endl;
        std::cout << "length of time_str:  " << time_str.length() << std::endl;
    #endif
    std::string str = "<break time='1s' />";
    time_str.append(str);
    time_str.append(ttmessage);

    #ifdef DEBUG
        std::cout << time_str << std::endl;
        std::cout << "length of string to speak:  " << time_str.length() << std::endl;
        std::cout << std::hex;
        for (char ch : time_str)
        {
            std::cout << "0x" << to_uint(ch) << ' '; 
        }
        std::cout << "] end of str" << std::endl;        
    #endif

    speak(time_str);
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
    if (internet(1)){
        #ifdef DEBUG
            std::cout << "In weather, internet OK" << std::endl;
        #endif
        CURL *curl;
        std::string readBuffer;
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://geoip-db.com/json/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            #ifdef DEBUG
                std::cout << readBuffer << std::endl;
            #endif
            JSONCPP_STRING json_err;
            Json::Value root;
            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            int rawLength = readBuffer.length();
            if (!reader->parse(readBuffer.c_str(), readBuffer.c_str() + rawLength,
                                                                     &root, &json_err))
            {
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
                curl_easy_perform(curl);  //  retrieve does not work if this
                                                //  statement is removed.
                curl_easy_cleanup(curl);
                std::cout << readBuffer2 << std::endl;
                int rawLength2 = readBuffer2.length();
                if (!reader->parse(readBuffer2.c_str(), readBuffer2.c_str() +
                                                     rawLength2, &root, &json_err))
                {
                    #ifdef DEBUG
                        std::cout << "json error" << std::endl;
                    #endif
                } else {
                    std::thread first (lightShow, 2);
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

/**
 *
 *  tellDailyQuote - retrieve and speak the daily quote.
 *
 **/
void tellDailyQuote(){
    if (internet(1)){
        int const quoteSpeakBase = 1;  // light show iterations to speak quote
                                        // with no message.
        #ifdef DEBUG
            std::cout << "In weather, internet OK" << std::endl;
        #endif
        CURL *curl;
        std::string readBuffer;
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL,
                                         "https://www.brainyquote.com/link/quotebr.rss");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            #ifdef DEBUG
                std::cout << readBuffer << std::endl;
            #endif
            std::size_t start = readBuffer.find("<item>") + 6;
            std::size_t len = readBuffer.find("</item>") - start;
            std::string item = readBuffer.substr(start, len);
            #ifdef DEBUG
                std::cout << "item: " << item << ", " << start << ", " <<
                                                                 len << std::endl;
            #endif
            start = item.find("<description>") + 14;
            len = item.find("</description>") - start - 1;
            std::string quote = item.substr(start, len);
            #ifdef DEBUG
                std::cout << "quote: " << quote << ", " << start << ", " <<
                                                                 len << std::endl;
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

/**
 *
 *  tellOrigin - explain how the Cordie bot began.
 *
 **/

void tellOrigin(){
    int const lightShowTime = 5;
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

/**
 *
 *  tellInternalTemp - give the value of the temperature sensor.  This is really
 *  intended to be a diagnostic tool.
 *
 **/

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

/**
 *
 *  tellEasterEgg - this will test the curiosity of the user.
 *
 **/

void tellEasterEgg(){
    int const lightShowTime = 2;
    #ifdef DEBUG
        std::cout << "Easter egg" << std::endl;
    #endif
    std::thread first (lightShow, lightShowTime);
    speak("you found an easter egg<break time='1s' />good job.");
    first.join();
}

/**
 *
 *  repeatLast - say the last message spoken.
 *
 **/
void repeatLast()
{
    std::string dup_message = mbank.content();
    if (dup_message.length() <= 1)
    {
        dup_message = "You pressed 4 to repeat a message,"
                                    " but no messages have been spoken yet.";
    }
    int lightShowTime = getSpeakTime(dup_message);
    std::thread first (lightShow, lightShowTime);
    speak(dup_message);
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
    mbank.setCounts(timePtr->tm_year+1900,timePtr->tm_mon+1,timePtr->tm_mday);
    #ifdef DEBUG
        std::cout << "Today = " << timePtr->tm_mon+1 << "/" << timePtr->tm_mday <<
                             "/" << timePtr->tm_year+1900 << std::endl;
        std::cout << "Today type 1 " << mbank.type1count() << std::endl;
        std::cout << "Today type 2 " << mbank.type2count() << std::endl;
        std::cout << "Today type 3 " << mbank.type3count() << std::endl;
    #endif
}

void init()
{
    //   Initialize wiringPi
    wiringPiSetup();	// for digital I/O
    pinMode(AMP_ENABLE, OUTPUT);  // Amplifier is disabled between speech events.
    srand (time(NULL));   // random number seed to simulate random start
    pinMode(FAN, OUTPUT);
    set_mbank_counts();
    speak("  ");  // initialize aoss, without this the first speech request happens
                // after a significant delay.
    
}


/****************************************************************************
 *
 *  Main
 *
 ****************************************************************************/

int main()
{
    std::cout << "Starting CordieBot 2/20/2020 11:10 " << std::endl;
    std::string intro = "I am cordeebot 2.0";
    
    init();
    
    int counter;
    int periodic_counter = 0;
    float internal_temp = 70.0;   // Initialize to reasonable starting point of 70 deg.
    internet(10);
    #ifdef DEBUG
        std::cout << "Internet present = " << internet(1) << std::endl;
    #endif
    double touchButtonGap = 0.6;
    countButton button(SWITCH, touchButtonGap);		// Setup the switch
    int type1count = mbank.type1count();
    int current_day = getDay();
    #ifdef DEBUG
        std::cout << "Today is:  " << current_day << std::endl;
    #endif
	    
    while(1) {
        counter = button.read();
        if( counter == 0){
            usleep(200*1000); 	// Delay 100ms
        } else {
            #ifdef DEBUG
                std::cout << "button:  " << counter << std::endl;
            #endif
            switch (counter) {
                case 1: {   tellTime(type1count);
                            break;
                        }
                case 2: {   tellWeather();
                            break;
                        }
                case 3: {   tellDailyQuote();
                            break;
                        }
                case 4: {   repeatLast();
                            break;
                        }
                case 5: {   speak(intro);
                            break;
                        }
                case 6: {   checkForConf();    // look for USB
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
                case 255:
                        {
                            speak("goodbye");
                            sync();
                            #ifdef DEBUG
                                std::cout << "reboot starts here " << std::endl;
                            #endif        
                            system("sudo shutdown now");
                        }
                default: {
                            #ifdef DEBUG
                                std::cout << "Invalid option selected." << std::endl;
                            #endif
                        }
            }
        }
        checkFan(internal_temp);
        ++periodic_counter;
        if (periodic_counter > 300){  // check once a minute (with 200ms sleep)
            if (mbank.changed())  // if proclamations file has changed, reload it.
            {
                mbank.reload();
                set_mbank_counts();
                #ifdef DEBUG
                    std::cout << "reloading messages" << std::endl;
                #endif
            }
            int new_day = getDay();
            if (current_day != new_day)  // if day has changed, reset type1count
            {
                current_day = new_day;
                type1count = mbank.type1count();
                set_mbank_counts();
                #ifdef DEBUG
                    std::cout << "it is a new day:  " << current_day << std::endl;
                #endif
            }
            periodic_counter = 0;
        }
    }
    return 0;
}
