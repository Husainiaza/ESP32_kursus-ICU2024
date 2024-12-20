void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("kursusIcu012336495047")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  client.subscribe("kursusICU/buzzer");
  client.subscribe("kursusICU/socket1");
  client.subscribe("kursusICU/socket2");
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  //==============================================================
  if(String(topic) == "kursusICU/buzzer") 
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


  if(String(topic) == "kursusICU/socket1") 
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

   if(String(topic) == "kursusICU/socket2") 
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

  //==============================================================
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}