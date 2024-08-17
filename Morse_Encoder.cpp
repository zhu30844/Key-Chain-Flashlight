//This version was tesed on Windows X64
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
/*
get a char , Example 'A' is 65 (Space 26th)
Get the index of list , 'A' - 65 = 0
The structure of one element in this list(uint8_t)
    0000    |0000
    morse   |length
    code    |of code
For example, Morse code of A is ._, we denote it by 01,so the left 4-bit part is 0100
The length od morse code of A is 2, so the right 4-bit part is 0010
In the end 0100 0010 = 0x42
*/
using namespace std;
// put your name here
string name = "A BCDEFGHIJKLMNOPQRSTUVWXYZ";
// get the length of your name 
unsigned int name_len = name.length();
uint8_t morse_list[] = {0x42, 0x84, 0xa4, 0x83, 0x01, 0x24, 0xc3, 0x04, 0x02,
                  0x74, 0xa3, 0x44, 0xc2, 0x82, 0xe3, 0x64, 0xd4, 0x43,
                  0x03, 0x81, 0x23, 0x14, 0x63, 0x94, 0xb4, 0xc4, 0xf1};
// put function declarations here:
void blinker(uint8_t rawChar);
// begin setup
int main()
{
    //find a way to wake uc up 
    // or we use a flag-var to show whether this system is enabled
    //then start to bink 
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    //name.toUpperCase();// change all chars to upper case
    for(unsigned int i=0;i<name_len;i++)
    {
        cout <<name[i] << ":" ;
        blinker((uint8_t)(morse_list[name[i]-65])); // Get index in morse_list of current char, 'A' is 65 in ASCII. 
        //delay(TIMEUNIT*2);
    }
    return 0;
}

void blinker(uint8_t rawChar)
{
    if (rawChar == 0xF1) //Space, we defined space is 0XF1
    {
        // wait 5 units because the total space between two words is 7 units
        //delay(TIMEUNIT*5);
        cout << "space";
        return;
    }
    uint8_t digit = 0X0F & rawChar; // get length of the morse, 
    //because the lower four bits store the length
    for (uint8_t i = 0; i < digit; i++)
    {
        uint8_t bit = rawChar & 0x80;
        // get the highest bit of rawChar
        if (bit == 0)// the highest bit is 0, this is a dot
        {
            cout << ".";
            //digitalWrite(LEDPINOUT,HIGH);
            //delay(TIMEUNIT);
        }
        else// this is a dash
        {
            cout << "_";
            //digitalWrite(LEDPINOUT,HIGH);
            //delay(TIMEUNIT*3);
        }
        rawChar = rawChar << 1;
        //digitalWrite(LEDPINOUT,LOW);
        //delay(TIMEUNIT);
    }
    cout << endl;
}

