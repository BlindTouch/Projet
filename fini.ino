#include<SoftwareSerial.h>

#define RX 7
#define TX 8

SoftwareSerial BlueT(RX,TX);

String reception=""; //création de l'objet String reception

String l1="0";
String c1;
String byte1;
String nombre="0000";
int resul2=0;
int po;

//Broches connectées 74HC595
const int DS = 10; // Données
const int ST_CP = 11; // Verrou
const int SH_CP = 12; // Horloge


String lettre(String car){
  
      if(car=="a"){
        Serial.println("A");
        return "100000";
      }
        
      else if(car=="b"){
        Serial.println("B");
        return "110000";
      }
      
      else if(car=="c"){
        return "100100";
        Serial.println("C");
      }
      
      else if(car=="d"){
        return "100110";
        Serial.println("D");
      }
      else if(car=="e"){
        return "100010";
        Serial.println("E");
      }
      
      else if(car=="f"){
         return "110100";
        Serial.println("F");
      }
      
      else if(car=="g"){
         return "110110";
        Serial.println("G");
      }
      
      else if(car=="h"){
         return "110010";
        Serial.println("H");
      }
      
      else if(car=="i"){
         return "010100";
        Serial.println("I");
      }
      
      else if(car=="j"){
        return "010110";
        Serial.println("J");
      }
      
      else if(car=="k"){
        return "101000";
        Serial.println("K");
      }
      
      else if(car=="l"){
        return "111000";
        Serial.println("L");
      }
      
      else if(car=="m"){
        return "101100";
        Serial.println("M");
      }
      
      else if(car=="n"){
        return "101110";
        Serial.println("N");
      }
      
      else if(car=="o"){
        return "101010";
        Serial.println("O");
      }
      
      else if(car=="p"){
        return "111100";
        Serial.println("P");
      }
      
      else if(car=="q"){
        return "111110";
        Serial.println("Q");
      }
      
      else if(car=="r"){
        return "111010";
        Serial.println("R");
      }
      
      else if(car=="s"){
       return "011100";
        Serial.println("S");
      }
      
      else if(car=="t"){
         return "011110";
        Serial.println("T");
      }
      
      else if(car=="u"){
         return "101001";
        Serial.println("U");
      }
      
      else if(car=="v"){
         return "111001";
        Serial.println("V");
      }
      
      else if(car=="w"){
         return "010111";
        Serial.println("W");
      }
      
      else if(car=="x"){
         return "101101";
        Serial.println("X");
      }
      
      else if(car=="y"){
       return "101111";
        Serial.println("Y");
      }
      
      else if(car=="z"){
        return "101011";
        Serial.println("Z");
      }

       else if(car=="0"){
        return "000000";
        Serial.println("0");
      }
      
      
    }

     
void setup()
{
  pinMode(DS, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  Serial.begin(9600);
  BlueT.begin(9600);
  for(int i=0;i<8;i++){
   digitalWrite(ST_CP, LOW);
   shiftOut(DS, SH_CP, LSBFIRST, 0);
   digitalWrite(ST_CP, HIGH);
   delay(10);
  }
  Serial.println("OK on peut y aller");
}
 
void loop(){
  
  while(BlueT.available()){
    char c = char(BlueT.read());
    reception += String(c);
    delay(10); //petite attente
   
  }


   if(reception!=""){
      Serial.println(reception);
      for(int k=(reception.length()-1); k>=0  ; k--){ 
        l1=String(reception.charAt(k));
        
        if(l1!=""){
          Serial.println(l1);
          nombre=lettre(l1)+nombre;
        }
        
        delay(10);

      } 


      for(int j=(nombre.length()-1); j>=0  ; j--){ 
        if(byte1.length()<8){
          c1=nombre.charAt(j);
          byte1=c1+byte1; 
          if(j==0){
            j=j+1;
          }  
          }
          else{
            if(j!=0){
              j=j+1;
            }
            for(int u=0;u<byte1.length();u++){           
              int by=byte1[u]-'0';
              if(pow(2,7-u)<3){
                po=int(pow(2,7-u));
              }
              else{
                po=int(pow(2,7-u)+1);
              }
            int inter=by*po; 
            resul2=resul2+inter;
         }
        
          digitalWrite(ST_CP, LOW);
          shiftOut(DS, SH_CP, LSBFIRST, resul2);
          digitalWrite(ST_CP, HIGH);
          delay(100);
          resul2=0;
          byte1="";
          }
      }
      reception="";
      nombre="0000";
      delay(10000);
      for(int i=0;i<8;i++){
   digitalWrite(ST_CP, LOW);
   shiftOut(DS, SH_CP, LSBFIRST, 0);
   digitalWrite(ST_CP, HIGH);
   delay(10);
  }
      Serial.println("Encore?");  
    } 
}
