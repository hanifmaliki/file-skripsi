void komunikasi_http(void) {
  if((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    if(command=='x') command_send='0'; // HTTP+command nggak dianggap
    else command_send='x'; // HTTP+command=x (netral)

    http.begin("http://192.168.100.56/nodebawah.php?gndacc=" + String(ground_acc,4) + "&angle=" + String(inc_angle,3)
//    http.begin("http://192.168.43.148/nodebawah.php?gndacc=" + String(ground_acc,4) + "&angle=" + String(inc_angle,3)
             + "&drift=" + String(drift_ratio,3) + "&pga=" + String(pga,4) + "&anglepeak=" + String(inc_angle_peak,3)
             + "&height=" + String(h) + "&displacepeak=" + String(displacement_peak) + "&driftpeak=" + String(drift_ratio_peak,3)
             + "&pgadr1=" + String(pga_dr1,4) + "&score=" + String(score) + "&command=" + String(command_send));

    int httpCode = http.GET();
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // Parsing data
        int j = 0;
        dt[j] = "";
        for (int k = 58; k < payload.length()-1; k++) { // panjang = 72, mulai hitung dari data ke 49 yaitu * pertama (default 0)
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
        top_angle_peak = dt[3].toFloat();

//        Serial.println(payload);
//        Serial.println(payload.length());
//        Serial.println(payload[58]);
//        Serial.print(command);
//        Serial.print("\t");
//        Serial.print(server_time);
//        Serial.print("\t");
//        Serial.println(top_angle_peak,3);
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
