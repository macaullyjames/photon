#include "application.h"

TCPClient client;
byte server[] = { 10, 0, 1, 26 }; // Mac's desktop
void setup()
{
  pinMode(D7, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (!client.connected())
  {
    Serial.print("Reconnecting... ");
    if (client.connect(server, 8089))
    {
      Serial.println("success");
    }
    else
    {
      Serial.println("failed");
      Serial.println("Waiting 5s to try again.");
      delay(5000);
    }
  }
  

  if (client.available())
  {
    char c = client.read();
    Serial.print("received: ");
    Serial.print(c);
    Serial.println();

    if (c == '1')
    {
        digitalWrite(D7, HIGH);
    }
    else
    {
      digitalWrite(D7, LOW);
    }
  }
}
