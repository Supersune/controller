#include <Servo.h>

Servo myservo;

const int BAUDRATE = 9600;
// Aruduino ide doesn't like STX and ETX, so a and b for testing
const char STX = 'a';
const char ETX = 'b';
//const char STX = 0x02;
//const char ETX = 0x02;
const char SEP = ';';
bool serialListen = false;

bool motorAngleSelect = false;
char motorSelect [2] = {0, 0};
char motorAngle[3] = {0, 0, 0};

int angle = 0;
int newAngle = 0;
const int MaxChars = 4;
char strValue[MaxChars+1];
int index = 0;

const int motorCount = 6;
int pwmPins [motorCount] = {3, 5, 6, 9, 10, 11};
Servo servos [motorCount] = {};


void setup()
{
    Serial.begin(BAUDRATE);
    for (int i=0; i < motorCount; i++)
    {
        servos[i].attach(pwmPins[i]);
    }
}
void loop()
{
}

void serialEvent()
{
    while(Serial.available())
    {
        char ch = Serial.read();
        Serial.write(ch);  // TODO: Validation later?
        //Serial.print(ch);
        if (ch == STX)
        {
            index = 0;
            motorAngleSelect = false;
            serialListen = true;
            continue;
        }
        else if (ch == SEP)
        {
            index = 0;
            motorAngleSelect = true;
            continue;
        }
        else if (ch == ETX)
        {
            for (int i=0; i<2; i++)
            {
                Serial.print(motorSelect[i]);
            }
            Serial.print(';');
            for (int i=0; i<3; i++)
            {
                Serial.print(motorAngle[i]);
            }
            serialListen = false;

            servos[atoi(motorSelect)].write(atoi(motorAngle));

            continue;
        }

        if (serialListen)
        {
            if (!motorAngleSelect)
            {
                motorSelect[index++] = ch;
            }
            else
            {
                motorAngle[index++] = ch;
            }
        }
    }
}
