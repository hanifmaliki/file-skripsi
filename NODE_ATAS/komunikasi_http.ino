void komunikasi_http(void) {
  if((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    if(command=='x') command_send='0'; // HTTP+command nggak dianggap
    else command_send='x'; // HTTP+command=x (netral)

    if (pidCal_http==1) {pidCal_http=0; pidCal_send=1;}
    else if (pidCal_http==0) {pidCal_send=0;}

    http.begin("http://192.168.100.56/nodeatas.php?angle=" + String(inc_angle,3) + "&anglepeak=" + String(inc_angle_peak,3)
//    http.begin("http://192.168.43.148/nodeatas.php?angle=" + String(inc_angle,3) + "&anglepeak=" + String(inc_angle_peak,3)
             + "&axOff=" + String(axOff) + "&ayOff=" + String(ayOff) + "&azOff=" + String(azOff)
             + "&gxOff=" + String(gxOff) + "&gyOff=" + String(gyOff) + "&gzOff=" + String(gzOff)
             + "&command=" + String(command_send) + "&pidCal=" + String(pidCal_send));

    int httpCode = http.GET();
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        
        // Parsing data
        int j = 0;
        dt[j] = "";
        for (int k = 49; k < payload.length()-1; k++) { // panjang = 72, mulai hitung dari data ke 49 yaitu * pertama (default 0)
          if ((payload[k] == '#') || (payload[k] == '*')) {
            j++;
            dt[j] = "";
          }
          else {
            dt[j] = dt[j] + payload[k];
          }
        }
        command = dt[1][0];
        server_time = dt[2];

//        Serial.println(payload);
//        Serial.println(payload.length());
//        Serial.println(payload[49]);
        Serial.print(command);
        Serial.print("\t");
        Serial.println(server_time);
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
