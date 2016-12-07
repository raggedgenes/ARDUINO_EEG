double s;
  int i = 0;
void setup() {
  // put your setup code here, to run once:
cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0;
  // set timer count for 1khz increments
  OCR1A = 7999;// = (16*10^6) / (1000*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
 
  sei();//allow interrupts
  //END TIMER SETUP
 
  Serial.begin(57600);

}
ISR(TIMER1_COMPA_vect) {
  int val = (512*sin(12*i*6.28/250))+512;
//  Serial.write(0xff);
//  Serial.write((val >> 8) & 0xff);
//  Serial.write(val);
i++;
  outputP2(val, i);
//  if ( i == 250) i = 0;
//  else i++;
  }
void loop() {
  // put your main code here, to run repeatedly:
}

void outputP2(int val, int counter) {
  Serial.write(0xa5);
  Serial.write(0x5a);
  Serial.write(0x01);
  Serial.write(0x01);
  Serial.write(val >> 8 & 0xff);
  Serial.write(val);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x0);
  Serial.write(0x2);
  }
