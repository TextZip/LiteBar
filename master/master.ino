// ****CONNECTIONS for RTC Module****
    // DS1302 CLK/SCLK --> 14
    // DS1302 DAT/IO --> 27
    // DS1302 RST/CE --> 25
    // DS1302 VCC --> 3.3v - 5v
    // DS1302 GND --> GND


#define countof(a) (sizeof(a) / sizeof(a[0]))

#include <ThreeWire.h>  
#include <RtcDS1302.h>

int hours;
int minutes;
char time[6];

ThreeWire myWire(27,14,25); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(9600);
    Rtc.Begin();
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    String timee = printDateTime(now);
    timee.toCharArray(time,6);
    Serial.println(time);

    if (!now.IsValid())
    {
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(5000); // five seconds
}




String printDateTime(const RtcDateTime& dt)
{
    char datestring[6];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u:%02u"),
            dt.Hour(),
            dt.Minute());
    return datestring;
}
