#define LED_GREEN_HI    (2)
#define LED_GREEN_LO    (4)

#define LED_YELLOW_HI   (6)
#define LED_YELLOW_LO   (7)

#define LED_RED         (5)
#define LED_OFF         (0)

void setup() {
    pinMode(0, OUTPUT);   //S1
    pinMode(1, OUTPUT);   //S0
    //pinMode(2, );       //ANALOG voltage
    pinMode(3, INPUT);   //S2
    pinMode(4, INPUT);    //Not used
    
}

/* LED:s connected via 74HC4053 mux */
void setLedOutput(uint8_t led){
    digitalWrite(1, (led & 0x01) ? HIGH : LOW);
    digitalWrite(0, (led & 0x02) ? HIGH : LOW);
    
    //Emulate open-drain to use 1.5k pull-up instead to save power.
    digitalWrite(3, LOW);
    pinMode(3, led & 0x04 ? INPUT : OUTPUT); 
}

void loop() {

  setLedOutput(LED_GREEN_HI);
  delay(500);  
  
  setLedOutput(LED_GREEN_LO);
  delay(500);  

  setLedOutput(LED_YELLOW_HI);
  delay(500);  
  
  setLedOutput(LED_YELLOW_LO);
  delay(500);  

  setLedOutput(LED_RED);
  delay(500);  

  /* LED off */
  setLedOutput(LED_OFF);
  delay(500);  
}
