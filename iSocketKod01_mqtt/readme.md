# **IoT MQTT**

## MQTT Library
MQTT by Joel Gaehwiler

## Kawalan Relay
```
 if(String(topic) == "socketLA01/buzzer") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(buzzer,HIGH);
      Serial.println("Buzzer ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(buzzer,LOW);
        Serial.println("Buzzer OFF");
        
      }
  } 


  if(String(topic) == "socketLA01/socket1") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay01,HIGH);
      Serial.println("socket1 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,LOW);
        Serial.println("socket1 OFF");
      }
  }

   if(String(topic) == "socketLA01/socket2") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay02,HIGH);
      Serial.println("socket2 ON");
  
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,LOW);
        Serial.println("Buzzer OFF");
     
      }
  }
```
## Ujikaji 1c: kawal 2 LED
```
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,HIGH);
  delay(1000);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,LOW);
  delay(1000);
```
