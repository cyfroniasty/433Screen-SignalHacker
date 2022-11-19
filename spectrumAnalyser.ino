void spectrumAnalyser(){ //sweep 425-450MHz and find highest frequency.
  unselect_T();
  unselect_SD();
  radio_R.initializeReceive();
  unselect_R(); unselect_SD(); 
  delay(200);
  float current_frequency = 425.000; //starting frequency
  float lower_limit = 425.000;
  float upper_limit = 450.000;
  float increment = 1;
  byte highest_rssi = 200;
  byte rssi_reading;
  int division = 10;
  while(1){
    //spc_analyser.updateText(String(digitalRead(DIO2_R)), 40, 0, 1, NORMAL, 1);
    //spc_analyser.updateText(String(radio_R.readReg(REG_RSSIVALUE)), 0, 0, 1, NORMAL, 4);
    
    radio_R.setFrequencyMHz(current_frequency);
    rssi_reading = radio_R.readReg(REG_RSSIVALUE);
    Serial.print(current_frequency); Serial.print(" "); Serial.print(rssi_reading); Serial.print(" "); Serial.println(upper_limit - lower_limit);
    if(rssi_reading < highest_rssi){
      highest_rssi = rssi_reading;
      spc_analyser.updateText(String(current_frequency, 3), 40, 20, 1, NORMAL, 8);
      if (increment >= 0.001){ //shorten the search but increase precision
        increment /= division; //divide increment to increase precision
        upper_limit = current_frequency + ((upper_limit - lower_limit)/division); //decrease the gap
        lower_limit = current_frequency - ((upper_limit - lower_limit)/division);
      } 
    }
    
    current_frequency += increment;
    if(current_frequency >= upper_limit) current_frequency = lower_limit;
    
    if(spc_analyser.clickB()){

      break;
    }
  }
}
