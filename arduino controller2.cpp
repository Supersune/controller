#include <Servo.h>

Servo myservo;

const int BAUDRATE = 9600;
const char STX = 0x02;
const char ETX = 0x02;
bool serialListen = false;

bool motorAngleSelect = false;
char motorSelect [2] = {0, 0};
char motorAngle[3] = {0, 0, 0};

int angle = 0;
int newAngle = 0;
const int MaxChars = 4;
char strValue[MaxChars+1];
int index = 0;

const int motorCount = 5;
int pwmPins [motorCount] = {3, 5, 6, 9, 10};
Servo servos [motorCount] = {};


void setup()
{
    Serial.begin(BAUDRATE);
    for (int i=0; i < motorCount; i++)
    {
        servos[i].attach(pwmPins[i])
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
        Serial.print(ch);
        if (ch == STX)
        {
            index = 0;
            motorAngleSelect = false;
            serialListen = true;
            continue;
        }
        else if (ch == ";")
        {
            index = 0;
            motorAngleSelect = true;
            continue;
        }
        else if (ch == ETX)
        {
            serialListen = false;

            servos[atoi(motorSelect)].write(atoi(motorAngle))

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
        //if(index < MaxChars && isDigit(ch))
        //{
        //    strValue[index++] = ch;
        //}
        /*
        else
        {
            strValue[index] = 0;
            newAngle = atoi(strValue);
            if (newAngle >= 0 && newAngle <= 180)
            {
                if (newAngle < angle)
                {
                    for(; angle > newAngle; angle -= 1)
                    {
                        myservo.write(angle);
                    }
                }
                else
                {
                    for(; angle < newAngle; angle += 1)
                    {
                        myservo.write(angle);
                    }
                }
            }
            index = 0;
            angle = newAngle;
        }
        */
    }
}
