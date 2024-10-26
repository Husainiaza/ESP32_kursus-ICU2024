# **IoT MQTT**

## MQTT Library
MQTT by Joel Gaehwiler

## Baca suhu

DS18B20.requestTemperatures();       // arahan baca suhu
  dataSuhuC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
 
  Serial.print("Temperature: ");
  Serial.print(dataSuhuC);    
  Serial.println("°C");
  client.publish("socketLA01/suhu", String(dataSuhuC));

  if (dataSuhuC < 25) {
    Serial.println(" suhu paras sejuk ");    
  }
  else if (dataSuhuC > 25 && dataSuhuC < 33 ) {
    Serial.println(" suhu paras normal ");  
    strcpy(statusSuhu, "suhu paras normal");
   // display.display();
  }

  else if (dataSuhuC > 33 && dataSuhuC < 41 ) {
    Serial.println("suhu paras panas ");   
    strcpy(statusSuhu, "suhu paras panas ");
    digitalWrite(buzzer,HIGH);
    delay(10);
    digitalWrite(buzzer,LOW);
    delay(100);
   
  }

  else if (dataSuhuC > 40 ) {
  Serial.println("suhu paras bahaya ");    
  strcpy(statusSuhu, "suhu paras bahaya");
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
 
  }

  else {
    Serial.print(" bacaan suhu tidak normal ");  
    digitalWrite(buzzer,LOW);
    digitalWrite(buzzer,LOW);
  }
```

```

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

