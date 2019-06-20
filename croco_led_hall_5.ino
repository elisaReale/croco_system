//8571 millisec per lato
//accendo tutti i led in rosso
//da quando il led inizia a sentire il magnete parte il conto dei 8571 millisecondi
//alla fine di quei x secondi il led si spegne e se ne accende uno dietro
//ripeti
//cambia dente
//ripeti
//speaker in sottofondo fa sentire uccellino
//speaker con croco che interagisce in base a cosa fai
//errro handling: se il magnete viene percepito da un sensore diverso da quello dovuto, il coccodrillo deve dare dei feedback, e dire di tornare indietro

//Hall sensors

int allLedPins[] = {12,10,8,11,9,7};
int allHallPins[] ={A0, A1, A2, A0, A1, A2};
char done ;
int ledState;
//time to stay on each tooth side
const int t = 4000; //millisec
unsigned long currentMillis;
int c = 0;
bool flag = true;
int out_min = 545;
int in_min =480 ;
int out_max = 858;
int in_max = 210; 

void setup() { 
  
  // led pins init 
  /*for (byte i = 0; i < sizeof(allLedPins) -1 ;i++ ) {
    pinMode(allLedPins[i], OUTPUT); 
    digitalWrite(allLedPins[i], HIGH);
  }*/
  for (int i = 0; i < sizeof(allLedPins)/2 ; i++) {
    pinMode(allLedPins[i], OUTPUT); 
    digitalWrite(allLedPins[i], HIGH);
  }
  Serial.begin(9600);

}


void loop() {
  Serial.print(analogRead(allHallPins[0]));
  Serial.print('\t');
  Serial.print(analogRead(allHallPins[1]));
  Serial.print('\t');
  Serial.print(analogRead(allHallPins[2]));  
  Serial.print('\t');
  Serial.println(c); 
  
  for (int i = 0; i < sizeof(allLedPins)/2   ;i++ ) {
    
    if (analogRead(allHallPins[i]) > out_min && analogRead(allHallPins[i])<out_max && c < sizeof(allLedPins)/2 && digitalRead(allLedPins[i])==HIGH) {
        currentMillis= millis();
        for( uint32_t tStart = millis();  (millis()-currentMillis) < t;  ) {
          if ( analogRead(allHallPins[i]) > out_min && analogRead(allHallPins[i])<out_max){
            
            Serial.print(analogRead(allHallPins[i]));
            Serial.print("\t");
            Serial.println("Ok, you're doing good");
            blinking(i);
            flag=false;
            
          }else if (analogRead(allHallPins[i]) < out_min && analogRead(allHallPins[i])> in_min ) {
            Serial.println("You should restart!");
            flag = true;
            digitalWrite(allLedPins[i], HIGH);
            break;
            }
        }
        
       if(flag == false){
          Serial.println("you cleaned this tooth!");
          digitalWrite(allLedPins[i], LOW);
          c++;
          flag=true;
          delay(500);
       }  
                           
               
    } else if (analogRead(allHallPins[i]) < in_min && analogRead(allHallPins[i])>in_max  && c < sizeof(allLedPins)/2 && digitalRead(allLedPins[i+3])==HIGH ) {
        currentMillis= millis();
        for( uint32_t tStart = millis();  (millis()-currentMillis) < t;  ) {
          if ( analogRead(allHallPins[i]) < in_min && analogRead(allHallPins[i])>in_max){
            
            Serial.print(analogRead(allHallPins[i]));
            Serial.print("\t");
            Serial.println("Ok, you're doing good");
            blinking(i+3);
            flag = false;           
            
            
          }else if (analogRead(allHallPins[i]) < out_min && analogRead(allHallPins[i])> in_min ) {
            Serial.println("You should restart!");
            digitalWrite(allLedPins[i+3], HIGH);
            flag=true;
            break;
            }
        }
    
       if(flag == false){ 
          Serial.println("you cleaned this tooth!");
          digitalWrite(allLedPins[i+3], LOW);
          c++;
          flag=true;
          delay(500);
       }
             
    }else if (analogRead(allHallPins[i]) > out_min && analogRead(allHallPins[i])<out_max  && digitalRead(allLedPins[i])==LOW ){
      
      Serial.println("You already brushed this tooth!");
      
    }else if  (analogRead(allHallPins[i]) < in_min && analogRead(allHallPins[i])>in_max  && digitalRead(allLedPins[i+3])==LOW ){
    
      Serial.println("You already brushed this tooth!");
    
    }else if ( c >= sizeof(allLedPins )/2 ){
        delay(1000);
        Serial.println("you finished!");
        delay(1000);
        for (int i = 0; i < sizeof(allLedPins)/2  ; i++) {
            digitalWrite(allLedPins[i], HIGH);
            }
        delay(100);
        for (int i = 0; i < sizeof(allLedPins)/2  ; i++) {
                digitalWrite(allLedPins[i], LOW);
                } 
        delay(100);
        for (int i = 0; i < sizeof(allLedPins)/2 ; i++) {
            digitalWrite(allLedPins[i], HIGH);
            }
        delay(100);
        for (int i = 0; i < sizeof(allLedPins)/2 ; i++) {
            digitalWrite(allLedPins[i], LOW);
       c = 0;
       delay(2000);
    }else if (analogRead(allHallPins[i]) < out_min  &&  analogRead(allHallPins[i]) > in_min){
          
          Serial.println("START BRUSHING!");
    
    }else if (analogRead(allHallPins[i]) <= in_max  ||  analogRead(allHallPins[i]) >= out_max){
          
          Serial.println("Ouch!! Aren't you brushing too harshly?");
      }
  
  }
delay(1000);
}

void blinking(int t){
if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
// set the LED with the ledState of the variable:
    digitalWrite(allLedPins[t], ledState);
            
}
