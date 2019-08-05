/*
Hardware:
Arduino Nano
Plain red and yellow LEDs
Analog Hall Sensors (similar to honeywell)
Button

Software:
Code for crocodile with light feedback to teach the children how to brush properly. 
Each tooth has an inside yellow led and an outside red led, and an hall sensor ( all positioned in the same direction in order to sense the magnetic field the same way).
The code wait to sense something outside the treshold and says "START BRUSHING". When a sensor sense, the corresponding led start to flicker for a t amount of time, with an increasing rate while the t passes and it says " You're doing good".
When t finishes, the led shut down and it says "You cleaned this tooth!". A counter c keeps track of how many teeth you brushed. When you reach the right amount (total number of sides), it says "you finish" and select a random pattern to 
light up the leds.
Error handling:
If you brush over a certain threshold (brushing "too hard") it says you are brushing to hard and restart the sensing.

Get dirty teeth:
a function meant to be started by the caregiver, if the button is pressed it start lighting up the leds during a pre-set amount of time, untile they all "get dirty".

Button to restart when you want to begin again from zero.
*/

//Led pins
int allLedPins[] = {12,10,8,11,9,7};

//Hall sensors
int allHallPins[] ={A0, A1, A2, A0, A1, A2};


const int buttonPin = 5;   
const int t = 5000; //millisec time to stay on each tooth side
const int t_eat = 25000; //the "eating" mode will last 30 secs

int ledState;
unsigned long currentMillis;
unsigned long millis_now;
int c = 0;
bool flag = true;
int out_min = 545;
int in_min =480 ;
int out_max = 858;
int in_max = 210; 
int point = 0;
int speed = 200;
int buttonState = 0;  
int e = 0;
bool  pushedFlag=false;

//vars to make the flickering faster while you are brushing:
// On and Off Times (as int, max=32secs)
const unsigned int onTime = 100;
int offTime = 0;
// Interval is how long we wait
int interval = onTime;
// Used to track if LED should be on or off
boolean ledStateBool = true;
int outputValue = 0; //momento dellintervallo di t
unsigned long previousMillisF;
unsigned long currentMillisF;

void get_dirty_teeth(){
  clearall();
  e=0;
   //if the buttonState is LOW:
   millis_now = millis();
  for( uint32_t t_now = millis();  (millis()-millis_now) < t_eat;  ){
    while (e < sizeof(allLedPins)/2 ) {
      digitalWrite(allLedPins[e], HIGH);
      e++;
      delay(30000/(sizeof(allLedPins)/2)+1);
    }
  }
  e=0;  
 }

//function to make the flicker faster while t passes
void blink_increase(int p, int x){
  
  // map the t variating from 0 to t to a delay value, smaller delay faster blink
  outputValue = map(x, 0, t, 700, 1);
  
  digitalWrite(allLedPins[p], ledStateBool);
  currentMillisF = millis();
  
  if (currentMillisF - previousMillisF >= interval) { 
      if (ledStateBool) {
          // LED is currently on, set time to stay off
          interval = outputValue;
        } else {
          // LED is currently off, set time to stay on
          interval = onTime;
        }
      // Toggle the LED's state, Fancy, eh!?
      ledStateBool = !(ledStateBool);
      // Save the current time to compare "later"
      previousMillisF = currentMillisF;             
      
   }
 }
  

//function for different blinking patterns to use at the FINISH
void clearall(){
 
  for (int pin = 0; pin <= sizeof(allLedPins )/2; pin++) {
    digitalWrite(allLedPins[pin],LOW);
  }
}
 
 
void fillall(){
   for (int pin = 0; pin <= sizeof(allLedPins )/2; pin++){
    digitalWrite(allLedPins[pin], HIGH);
  }
}

void finalBlink1(int repeat){
  for (int r = 0; r<repeat; r++){
    for (int g = 0; g < sizeof(allLedPins )/2; g++) { digitalWrite(allLedPins[g], LOW); }
      digitalWrite(allLedPins[point], HIGH);
      delay(speed);
      point++;
    if (point > sizeof(allLedPins )/2-1) { point = 0; }  
  }
}

void finalBlink2(int repeat){
       for (int q = 0; q <repeat ; q++){
          for (int i = 0; i < sizeof(allLedPins)/2  ; i++) {
              digitalWrite(allLedPins[i], HIGH);
              }
          delay(50);
          for (int i = 0; i < sizeof(allLedPins)/2  ; i++) {
                  digitalWrite(allLedPins[i], LOW);
                  } 
          delay(50);
    }
}

 
void onrun(int delaytime){
 
  for(int pin = 0; pin <= sizeof(allLedPins)/2; pin++){
 
    clearall();
    digitalWrite(allLedPins[pin], HIGH);
    delay(delaytime);
  }
 
  for(int pin = sizeof(allLedPins)/2-1; pin >= 2; pin--){
    clearall();
    digitalWrite(allLedPins[pin], HIGH);
    delay(delaytime);
  }
 
}
 
 
void offrun(int delaytime){
 
  for(int pin = 0; pin <= sizeof(allLedPins)/2; pin++)  {
     fillall();
     digitalWrite(allLedPins[pin], LOW);
     delay(delaytime);
  }
 
  for(int pin = sizeof(allLedPins)/2-1; pin >= 0; pin--){
 
      fillall();
      digitalWrite(allLedPins[pin], LOW);
      delay(delaytime);
     }
 
}
 
 
//Flashing all LEDs ON and OFF
 
void flash(int delaytime){
 
  for(int i = 1; i <=sizeof(allLedPins)/2+1; i++) {
 
      clearall();
      delay(delaytime);
      fillall();
      delay(delaytime);
     }
 
}
 
void alternate(int delaytime){
 
  for (int n = 1; n <= 5; n++)  {
 
  clearall();
   for (int i = 0; i <= sizeof(allLedPins)/2-1; i += 2){
 
    digitalWrite(allLedPins[i], HIGH);
 
   }
 
   delay(delaytime);
   clearall();
 
  for (int j = 3; j <= sizeof(allLedPins)/2; j += 2) {
     digitalWrite(allLedPins[j], HIGH);
    }
  delay(delaytime);
 
  }
 
}

void stack(int delaytime){
 
    int stack = 0;
    while(stack < sizeof(allLedPins)/2-1){
     
      for(int pos = 0; pos <= (sizeof(allLedPins)/2 - stack); pos++){
     
        clearall();
        digitalWrite(allLedPins[pos], HIGH);
        drawstack(stack);
        delay(delaytime);
      }
     
      stack++;
    }
 
}
 
//Subfunction of the stack function
 
void drawstack(int stack){
 
  for(int n = sizeof(allLedPins)/2; n > (sizeof(allLedPins)/2 - stack); n--){
 
    if(n >= 2){
 
      digitalWrite(allLedPins[n], HIGH);
 
      } 
    }
}

// function to print to Serial/file in a tabular format

void print_to_file(String string , int i){
  for (int hs = 0; hs < sizeof(allHallPins)/2 ; hs++) {
    Serial.print(allHallPins[hs]);
    Serial.print('\t');
    Serial.print(analogRead(allHallPins[hs]));
    Serial.print('\t');
    Serial.print(digitalRead(allLedPins[hs]));
    Serial.print('\t');
    Serial.print(flag);
    Serial.print('\t');
    Serial.print(c);
    Serial.print('\t');
    Serial.println(string);
  }}

  
void setup() { 
  
  // led pins init 
  for (int i = 0; i < sizeof(allLedPins)/2 ; i++) {
    pinMode(allLedPins[i], OUTPUT); 
    digitalWrite(allLedPins[i], HIGH);
  }
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("position\thallPinValue\tLedState\tblinking\tteethBrushed\tFeedback"); //header 
}


void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) pushedFlag = true;
  if (pushedFlag == true){
    get_dirty_teeth();
    pushedFlag=false;  
  }else {
  
        for (int i = 0; i < sizeof(allLedPins)/2   ;i++ ) {
          
          if (analogRead(allHallPins[i]) > out_min && analogRead(allHallPins[i])<out_max && c < sizeof(allLedPins)/2 && digitalRead(allLedPins[i])==HIGH) {
              currentMillis= millis();
              for( uint32_t tStart = millis();  (millis()-currentMillis) < t;  ) {
                
                  blink_increase(i, (millis()-currentMillis));
                  flag=false;
                  print_to_file( "Ok, you're doing good", i) ;
              
              }
             
             if(flag == false){
                digitalWrite(allLedPins[i], LOW);
                c++;
                flag=true;
                print_to_file("you cleaned this tooth!", i);
                delay(1000);
                
             }  
                          
                     
          } else if (analogRead(allHallPins[i]) < in_min && analogRead(allHallPins[i])>in_max  && c < sizeof(allLedPins)/2 && digitalRead(allLedPins[i+3])==HIGH ) {
              currentMillis= millis();
              for( uint32_t tStart = millis();  (millis()-currentMillis) < t;  ) {
                
                  blink_increase(i+3, (millis()-currentMillis) );
                  flag = false;           
                  print_to_file( "Ok, you're doing good", i);
                
              }
      
             if(flag == false){ 
                digitalWrite(allLedPins[i+3], LOW);
                c++;
                flag=true;
                print_to_file("you cleaned this tooth!", i);
                delay(1000);
             }
             
                   
          }else if (analogRead(allHallPins[i]) > out_min && analogRead(allHallPins[i])<out_max  && digitalRead(allLedPins[i])==LOW ){
            
           print_to_file("You already brushed this tooth!", i);
            
          }else if  (analogRead(allHallPins[i]) < in_min && analogRead(allHallPins[i])>in_max  && digitalRead(allLedPins[i+3])==LOW ){
          
            print_to_file("You already brushed this tooth!",i);
          
          }else if ( c >= sizeof(allLedPins )/2 ){
              print_to_file("you finished!" ,i);
              delay(1000);
              int pickme = random(1,7); // picks a random pattern of LED patterns from those defined above
              switch(pickme) {
                case 1:
                  onrun(random(20,1000));
                  break;
                case 2:
                  alternate(random(80,1000));
                  break;
                case 3:
                  offrun(random(20,100));
                  break;
                case 4:
                  stack(random(30,100));
                  break;
                case 5:
                  finalBlink1(random(30, 100));
                  break;
                case 6:
                  finalBlink2(random(30, 100));
                  break;
              }     
                  clearall();
                  c = 0;
                  delay(2000);
                  fillall();
                  delay(1000);
                  
          }else if (analogRead(allHallPins[i]) < out_min  &&  analogRead(allHallPins[i]) > in_min){
                
                print_to_file("START BRUSHING!",i);
          
          }else if (analogRead(allHallPins[i]) <= in_max  ||  analogRead(allHallPins[i]) >= out_max){
                
                print_to_file("Ouch!! Aren't you brushing too harshly?",i);
            }
          
        }
  } 
  delay(500);
}
