#include "mbed.h"

#include <string>

float Pi = 3.141592654;

 

//Bluetooth communicatie

Serial hm10(D8, D2); //TX RX

Serial pc(USBTX, USBRX);

 

//Arduino comminicatie

AnalogIn Arduino1 (A4);

AnalogIn Arduino2 (A5);

 

//Afstandssensoren

AnalogIn sensorOnder(A0);

AnalogIn sensorLinks(A1);

AnalogIn sensorVoor(A2);

AnalogIn sensorRechts(A3);

 

//Borstels & Motoren

PwmOut borstelLinks(D6);

DigitalOut borstelLinksD (D12);

PwmOut borstelMidden(D10);

DigitalOut borstelMiddenD (D14);

PwmOut borstelRechts(D9);

DigitalOut borstelRechtsD (D13);

 

DigitalOut wielLinksFw(D11); //D2

DigitalOut wielLinksRv(D4);

PwmOut wielLinks(D3);

DigitalOut wielRechtsFw(D7);

DigitalOut wielRechtsRv(D15); //D8

PwmOut wielRechts(D5);

 

PwmOut Fan(D10);

DigitalOut FanD(D14);

 

//setup (value geven aan sommige waarden)

void setup(){

    borstelLinksD = 1;

    borstelMiddenD = 1;

    borstelRechtsD = 1;

    FanD = 1;

    wielLinksFw = 0;

    wielLinksRv = 0;

    wielRechtsFw = 0;

    wielRechtsRv = 0;

}

 

//Afstandsmetingen, aanpasbaar op het teruggeven van de afstand in cm of een waarde van 0 tot 1

float afstandOnder(){

    float value = (1.25*sensorOnder)-0.125;         //0to1

    float afstand = (13.3/(sensorOnder*3.2))-0.42;  //cm

    return  value /* of afstand*/;

}

 

float afstandLinks(){

    float value = (1.25*sensorLinks)-0.125;         //0to1

    float afstand = (13.3/(sensorLinks*3.2))-0.42;  //cm

    return  value /* of afstand*/;

}

 

float afstandVoor(){

    float value = (1.25*sensorVoor)-0.125;          //0to1

    float afstand = (13.3/(sensorVoor*3.2))-0.42;   //cm

    return  value /* of afstand*/;

}

 

float afstandRechts(){

    float value = (1.25*sensorRechts)-0.125;            //0to1

    float afstand = (13.3/(sensorRechts*3.2))-0.42; //cm

    return  value /* of afstand*/;

}

 

//Afstandsmetingen, geeft een 0 of 1 als de afstand onder een gegeven limietwaarde komt

//Use: limitDown/Left/Forward/Right(int: limietwaarde in cm);

int limitOnder(int limiet){

   int output = 0;

    float afstand = 0;

 

    for (int i = 0; i < 10; i++){

        afstand = afstand + ((13.3/(sensorOnder*3.2))-0.42);    //cm

 

        if(i == 9){

            float gemAfstand = afstand / 10;

            if(gemAfstand < limiet){

                output = 1;

            }

        }

    }

    return  output;

}

 

int limitLinks(int limiet){

    int output = 0;

    float afstand = 0;

 

    for (int i = 0; i < 10; i++){

        afstand = afstand + ((13.3/(sensorLinks*3.2))-0.42);    //cm

 

       if(i == 9){

            float gemAfstand = afstand / 10;

            if(gemAfstand < limiet){

                output = 1;

            }

        }

    }

    return  output;

}

 

int limitVoor(int limiet){

    int output = 0;

    float afstand = 0;

 

   for (int i = 0; i < 10; i++){

        afstand = afstand + ((13.3/(sensorVoor*3.2))-0.42); //cm

 

        if(i == 9){

            float gemAfstand = afstand / 10;

            if(gemAfstand < limiet){

                output = 1;

            }

        }

    }

    return  output;

}

 

int limitRechts(int limiet){

    int output = 0;

    float afstand = 0;

 

    for (int i = 0; i < 10; i++){

        afstand = afstand + ((13.3/(sensorRechts

    *3.2))-0.42);   //cm

 

        if(i == 9){

            float gemAfstand = afstand / 10;

            if(gemAfstand < limiet){

                output = 1;

            }

        }

    }

    return  output;

}

 

//Aandrijving, invoer van 0 tot 100%

//Borstels

//Use: snelheidBorstelLinks/Midden/Rechts(int: 0 tot 1);

void snelheidBorstelMidden(float percentage){

    borstelMidden = percentage;

}

 

void snelheidBorstelsZijnkant(float percentage){

    borstelLinks = percentage;

    borstelRechts = percentage;

}

 

void snelheidAlleBorstels(float percentage){

    borstelLinks = percentage;

    borstelMidden = percentage;

    borstelRechts = percentage;

}

 

//Ventilator

//Use: ventilator(float snelheid 0 tot 1)

void ventilator(float percentage){

    Fan = percentage;

}

 

//Wielen

//!Aansturings functie is alleen voor gebruik door andere functies!

void aansturing(float snelheid, std::string richting){

    if(richting == "links"){

        //links neg rechts pos

        wielLinksFw = 0;

        wielLinksRv = 0;

        wielRechtsFw = 0;

        wielRechtsRv = 0;

        wielLinksRv = 1;

        wielRechtsFw = 1;

        wielLinks = snelheid;   

        wielRechts = snelheid;

    }

    if(richting == "rechts"){

        //links pos rechts neg

        wielLinksFw = 0;

        wielLinksRv = 0;

        wielRechtsFw = 0;

        wielRechtsRv = 0;

        wielLinksFw = 1;

        wielRechtsRv = 1;

        wielLinks = snelheid;

        wielRechts = snelheid;

    }

    if(richting == "vooruit"){

        //links pos rechts pos

        wielLinksFw = 0;

        wielLinksRv = 0;

        wielRechtsFw = 0;

        wielRechtsRv = 0;

        wielLinksFw = 1;

        wielRechtsFw = 1;

        wielLinks = snelheid;

        wielRechts = snelheid;

    }

    if(richting == "achteruit"){

        //links neg rechts neg

        wielLinksFw = 0;

        wielLinksRv = 0;

        wielRechtsFw = 0;

        wielRechtsRv = 0;

        wielLinksRv = 1;

        wielRechtsRv = 1;

        wielLinks = snelheid;

        wielRechts = snelheid;

    }

    if(richting == "stop"){

        wielLinksFw = 0;

        wielLinksRv = 0;

        wielRechtsFw = 0;

        wielRechtsRv = 0;

        wielLinksRv = 0;

        wielRechtsRv = 0;

        wielLinks = snelheid;

        wielRechts = snelheid;

    }

}

 

//Use: Vooruit/Achteruit(int: cm per seconde)

void vooruit(int cms){

    int toerental = 120;

    float PWM = cms/((toerental*6.65)/60);

    float snelheid = PWM;

    aansturing(snelheid, "vooruit");

}

 

void achteruit(int cms){

    int toerental = 120;

   float PWM = cms/((toerental*6.65)/60);

    float snelheid = PWM;

    aansturing(snelheid, "achteruit");

}

 

void stop(){

    aansturing(0, "stop");

}

 

//Use links/rechts(int: graden, int: snelheid (vooruit) na sturen 1 tot 0)

void links(int graden, float snelheid){

    int toerental = 120;

    int wielenAfstand = 190;

    float seconden = ((((2*Pi*(wielenAfstand/2))/360)/((toerental/60)*66.5))*graden)*0.5;

    aansturing(1, "links");

    wait(seconden);

    aansturing(snelheid, "vooruit");

}

 

void rechts(int graden, float snelheid){

    int toerental = 120;

    int wielenAfstand = 190;

    float seconden = ((((2*Pi*(wielenAfstand/2))/360)/((toerental/60)*66.5))*graden)*0.5;

    aansturing(1, "rechts");

    wait(seconden);

    aansturing(snelheid, "vooruit");

}

 

// main() runs in its own thread in the OS

int main()

{  

    setup();

 

    char bluetooth = ' ';

    char lInput = ' ';

    string f = "";

    int X = 0;

    int Y = 0;

   

    hm10.baud(9600); //make sure the baud rate is 9600

    while (!hm10.writeable()) { } //wait until the HM10 is ready

    hm10.printf("AT+TYPE0\r\n");

    pc.printf("Fuck1 \r\n");

    while (true) {

        //START

        //Autonoom

        while (Arduino1 == 1) {

            vooruit(10);

            if (limitVoor(10) == 1){

                pc.printf("1 \r\n");

                vooruit(0);

                rechts((rand() % 90) + 90, 1);

            }

            if (limitOnder(10) == 0){

                pc.printf("2 \r\n");

                achteruit(10);

                wait_ms(400);

                rechts(90, 1);

            }

            if (limitLinks(7) == 1){

                vooruit(0);

                pc.printf("3 \r\n");

                rechts(10, 1);

            }

            if (limitRechts(7) == 1){

                pc.printf("4 \r\n");

                vooruit(0);

                links(10, 1);

            }

        }

 

        //Bestuurd

        while (Arduino2 == 1) {

            //Waarde ophalen

            if (hm10.readable()){

                bluetooth = hm10.getc();

                X = 0;

                Y = 0;

                string x = "0";

                string y = "0";

                int counter = 0;

                string s(1, bluetooth);

                f = f + s[0];

                if (bluetooth == '$') {

                    //pc.printf("%s \r\n", f.c_str());

                    for (int i = 0; f.size() > i; i++) {

                        if (!isdigit(f[i])) {

                            counter = counter + 1;

                        }

                        if (isdigit(f[i]) && counter == 1) {

                            x = x + f[i];

                        }

                        if (isdigit(f[i]) && counter == 2) {

                            y = y + f[i];

                        }

                    }

                    if (!(counter == 3)) {

                        pc.printf("ERROR \r\n");

                    }

                    if (counter == 3) {

                        X = (stoi(x)*2)-98;

                        Y = (stoi(y)*2)-98;

                       float lX = X;

                        float lY = Y;

                        //pc.printf("X = %i, Y = %i \r\n", X, Y);

 

                        if (lX > 0 && lY < 0) {

                            wielLinksRv = 0;

                            wielRechtsRv = 0;

                            wielLinksFw = 1;

                            wielRechtsFw = 1;

                            wielLinks = ((lY*-1)/100);

                            wielRechts = ((lY*-1)/100)-(lX/100);

                        }

                        if (lX > 0 && lY > 0 ) {

                            wielLinksFw = 0;

                            wielRechtsFw = 0;

                            wielLinksRv = 1;

                            wielRechtsRv = 1;

                            wielLinks = (lY/100);

                            wielRechts = (lY/100)-(lX/100);

                        }

                        if (lX < 0 && lY > 0) {

                            wielLinksFw = 0;

                            wielRechtsFw = 0;

                            wielLinksRv = 1;

                            wielRechtsRv = 1;

                            wielLinks = (lY/100)-((lX*-1)/100);

                            wielRechts = (lY/100);

                        }

                        if (lX < 0 && lY < 0) {

                            wielLinksRv = 0;

                            wielRechtsRv = 0;

                            wielLinksFw = 1;

                            wielRechtsFw = 1;

                            wielLinks = ((lY*-1)/100)-((lX*-1)/100);

                            wielRechts = ((lY*-1)/100);

                        }

                        if (lX == 0 && lY == 0) {

                            wielLinksFw = 0;

                            wielLinksRv = 0;

                            wielRechtsFw = 0;

                            wielRechtsRv = 0;

                            wielLinks = 0;

                            wielRechts = 0;

                        }

                    }

                    f = "";

                }

           

                if (bluetooth == 'A' || bluetooth == 'B') {

                    f = "";

                    if (bluetooth == 'A'){

                        pc.printf("Borstels aan\r\n");

                        snelheidBorstelsZijnkant(1);

                       ventilator(1);

                    }

                    if (bluetooth == 'B'){

                        pc.printf("Borstels uit\r\n");

                        snelheidAlleBorstels(0);

                        ventilator(0);

                    }  

                }

            }

        }

 

        while (Arduino1 == 0 && Arduino2 == 0) {

            wielLinksFw = 0;

            wielLinksRv = 0;

            wielRechtsFw = 0;

            wielRechtsRv = 0;

            wielLinks = 0;

            wielRechts = 0;

            snelheidAlleBorstels(0);

            ventilator(0);

            wait_ms(100);

        }

 

    }

}
