// DCC track voltage detector based on Digistump T85 with 7805 + custom board.
// Digistump board modification: LED removed to get lower power usage + PB5 jumper bootloader
// BOARD: Digispark(1Mhz - No usb)

//
// Change values below to get other limits

#define LEVEL4      24000
#define LEVEL3      22000
#define LEVEL2      20000
#define LEVEL1      17000


/* Do not change below */
#define ADC_DIVIDER     29

#define LED_OFF         (0)
#define LED_RED         (1)
#define LED_YELLOW_LO   (2)
#define LED_YELLOW_HI   (3)
#define LED_GREEN_LO    (4)
#define LED_GREEN_HI    (5)

void setup() {
    pinMode(0, OUTPUT);   //S1
    pinMode(1, OUTPUT);   //S0
    //pinMode(2, );       //ANALOG voltage
    //pinMode(3, INPUT);  //USB
    //pinMode(3, INPUT);  //USB
    pinMode(5, OUTPUT);   //S2
    /* Use internal 1.1v reference */
    analogReference(INTERNAL1V1);
}

//S0 = PB1
//S1 = PB0
//S2 = PB5
#define MUX_NONE  (0x00)
#define MUX_S0    (0x02)
#define MUX_S1    (0x01)
#define MUX_S2    (0x20)

/* LED:s connected via 74HC4053 mux */
void setLedOutput(uint8_t led){
    const uint8_t mux[] = {
      MUX_NONE,                 /* LED_OFF */
      MUX_S0 | MUX_S2,          /* LED_RED */
      MUX_S0 | MUX_S1 | MUX_S2, /* LED_YELLOW_LO */
      MUX_S2 | MUX_S1,          /* LED_YELLOW_HI */
      MUX_S2,                   /* LED_GREEN_LO */
      MUX_S1,                   /* LED_GREEN_HI */
    };

    /* Direct write to PORT to avoid Arduino slow digitalWrite */
    PORTB = mux[led];  /* all off */
}

void testled(){
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

  setLedOutput(LED_OFF);
  delay(500);  
  
}

void loop() {
  uint16_t adc = analogRead(1); //ADC1, PB2

  if(adc >= (LEVEL4/ADC_DIVIDER)){
    setLedOutput(LED_GREEN_HI);
    delay(5);
    setLedOutput(LED_GREEN_LO);
    delay(5);
  }else if(adc >= (LEVEL3/ADC_DIVIDER)){
    setLedOutput(LED_GREEN_LO);
    delay(5);
    setLedOutput(LED_OFF);
    delay(5);
  }else if(adc >= (LEVEL2/ADC_DIVIDER)){
    setLedOutput(LED_YELLOW_HI);
    delay(5);
    setLedOutput(LED_YELLOW_LO);
    delay(5);
  }else if(adc >= (LEVEL1/ADC_DIVIDER)){
    setLedOutput(LED_YELLOW_LO);
    delay(5);
    setLedOutput(LED_OFF);
    delay(5);
  }else{
    setLedOutput(LED_RED);
    delay(5);
    setLedOutput(LED_OFF);
    delay(5);
  }  
}
