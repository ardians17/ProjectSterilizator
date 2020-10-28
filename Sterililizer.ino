

int counter;
int state;
//waktu LEDmenyala
int waktu = 20;
// PIN (diubah sesuai keperluan)
#define pinOn  2
#define pinLED 3
#define pinIndikator 4
void setinterupt(){
  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 31249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  MCUCR = 0x0a;
  //MCUCSR = 0x00;
  //GICR = 0b11000000;
  //GIFR = 0x40;
  sei();//allow interrupts
}
//timer 1 detik
ISR(TIMER1_COMPA_vect) {
  counter ++;
}
//Indikasi menyala, jika sudah beres LED indikasi mati 
void IndikasiMenyala(){
  digitalWrite(pinIndikator, HIGH);
  counter++;
  delay(500);
  digitalWrite(pinIndikator, LOW);
  delay(500);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  setinterupt();
  counter = 0;
  state = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // kalau tombol power ditekan
  if (digitalRead(PinOn)){
    state = !state;
    digitalWrite(pinLED, HIGH);
  }
  if (state){
    IndikasiMenyala();
    if (counter > (60*waktu)){
      state = !state;
      digitalWrite(pinLED, LOW); 
    }
  }
}
