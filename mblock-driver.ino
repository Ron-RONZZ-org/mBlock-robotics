  #include <Arduino.h>
  #include <Wire.h>
  #include <SoftwareSerial.h>
  
  #include <MeAuriga.h>
  
  //Encoder Motor
  MeEncoderOnBoard Encoder_1(SLOT1);
  MeEncoderOnBoard Encoder_2(SLOT2);
  
  void isr_process_encoder1(void)
  {
         if(digitalRead(Encoder_1.getPortB()) == 0){
               Encoder_1.pulsePosMinus();
         }else{
               Encoder_1.pulsePosPlus();
         }
  }
  
  void isr_process_encoder2(void)
  {
         if(digitalRead(Encoder_2.getPortB()) == 0){
               Encoder_2.pulsePosMinus();
         }else{
               Encoder_2.pulsePosPlus();
         }
  }
  
  void move(int direction, int speed)
  {
         int leftSpeed = 0;
         int rightSpeed = 0;
         if(direction == 1){
               leftSpeed = -speed;
               rightSpeed = speed;
         }else if(direction == 2){
               leftSpeed = speed;
               rightSpeed = -speed;
         }else if(direction == 3){
               leftSpeed = -speed;
               rightSpeed = -speed;
         }else if(direction == 4){
               leftSpeed = speed;
               rightSpeed = speed;
         }
         Encoder_1.setTarPWM(leftSpeed);
         Encoder_2.setTarPWM(rightSpeed);
  }
  void moveDegrees(int direction,long degrees, int speed_temp)
  {
         speed_temp = abs(speed_temp);
         if(direction == 1)
         {
               Encoder_1.move(-degrees,(float)speed_temp);
               Encoder_2.move(degrees,(float)speed_temp);
         }
         else if(direction == 2)
         {
               Encoder_1.move(degrees,(float)speed_temp);
               Encoder_2.move(-degrees,(float)speed_temp);
         }
         else if(direction == 3)
         {
               Encoder_1.move(-degrees,(float)speed_temp);
               Encoder_2.move(-degrees,(float)speed_temp);
         }
         else if(direction == 4)
         {
               Encoder_1.move(degrees,(float)speed_temp);
               Encoder_2.move(degrees,(float)speed_temp);
         }
  }
  
  double angle_rad = PI/180.0;
  double angle_deg = 180.0/PI;
  
  void setup(){
       //Set Pwm 8KHz
       TCCR1A = _BV(WGM10);
       TCCR1B = _BV(CS11) | _BV(WGM12);
       TCCR2A = _BV(WGM21) | _BV(WGM20);
       TCCR2B = _BV(CS21);
        attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
       attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
       Encoder_1.setPulse(9);
       Encoder_1.setRatio(39.267);
       Encoder_1.setPosPid(1.8,0,1.2);
       Encoder_1.setSpeedPid(0.18,0,0);
       Encoder_2.setPulse(9);
       Encoder_2.setRatio(39.267);
       Encoder_2.setPosPid(1.8,0,1.2);
       Encoder_2.setSpeedPid(0.18,0,0);
       moveDegrees(1,860,150);
  }
  
  void loop(){
       _loop();
  }
  
  void _delay(float seconds){
       long endTime = millis() + seconds * 1000;
       while(millis() < endTime)_loop();
  }
  
  void _loop(){
       Encoder_1.loop();
       Encoder_2.loop();
  }
