#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const String cambiocodice = "****";
String codice = "1234";
String cod_ins = "";
char chiusura = ' ';
int err = 0;
int secondi_blocco = 30;
int sup = 0;

const int err_max = 4;
const int colonne = 3;
const int righe = 4;
const int servo = 9;
const int buzzer = 10;
const int illum = 11;
const int verde = 12;
const int rosso = 13;



  //------------------------------------ Keyboard initialization
char keys[righe][colonne] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'},
};

byte pinrighe[righe] = {8, 7, 6, 5};
byte pincolonne[colonne] = {4, 3, 2};
Keypad tastiera = Keypad(makeKeymap(keys), pinrighe, pincolonne, righe, colonne);

  //------------------------------------ Display initialization
const int rs = 14, en = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

  //------------------------------------ Servo initialization
Servo myservo;
// 80° open

byte lucchettoChiuso[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11011,
  0b11011,
  0b11111
};

byte lucchettoAperto[8] = {
  0b01110,
  0b10000,
  0b10000,
  0b10000,
  0b11111,
  0b11011,
  0b11011,
  0b11111
};


  //------------------------------------ Setup
void setup() {
 

Serial.begin(9600);

 lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 
  delay(500);
 lcd.clear();
 
myservo.attach(servo);
myservo.write(80);

pinMode(verde, OUTPUT);
pinMode(rosso, OUTPUT);
lcd.createChar(0, lucchettoChiuso);
lcd.createChar(1, lucchettoAperto);
}

void loop() {
  INIZIO:

  //---------------------------------------------------------------- Error checking



  cod_ins = "";
  lcd.clear();
  lucchetto();
 
  lcd.setCursor(0,0);
 
  lcd.print("Inserisci PIN:");
  Serial.println("Inserisci PIN:");
  lcd.setCursor(0,1);
  //--------------------------------- Enter code
  inserimento_cod();
 
  if(cod_ins == codice){
    //--------------------------------- Exact code
    lcd.setCursor(0,1);
    lcd.print("Codice esatto");
    Serial.println("Codice esatto");
    delay(500);
    //--------------------------------- Port Management
    lcd.clear();
    lucchetto();

    err = 0;
    lcd.setCursor(0,0);
    lcd.print("Premi #");
    lcd.setCursor(0,1);
    lcd.print("per chiudere");
    Serial.println("Premi # per chiudere");
    myservo.write(90);
    lucchetto();
 
  RIMANI:
  chiusura = ' ';
     chiusura = tastiera.waitForKey();
 
    tone(buzzer,800,70);
    delay(70);
 
    if(chiusura == '#'){
     lcd.clear();
     lcd.setCursor(0,1);
     lcd.print("Chiusura");
     Serial.println("Chiusura");
     
    lucchetto();
   
     myservo.write(0);
     delay(1000);
    }else{
   goto RIMANI;
    }
   
     cod_ins = "";
  }else
   
   
    if(cod_ins == cambiocodice){
    //--------------------------------- Code change
    lcd.clear();
   
    lucchetto();
   
    lcd.setCursor(0,0);
    lcd.print("Cambio codice");
    Serial.println("Cambio codice");
    delay(1000);
    lcd.clear();
   
   
    lcd.print("Ins. PIN prec:");
    Serial.println("Ins. PIN prec:");
    lucchetto();
    lcd.setCursor(0,1);
    cod_ins = "";

     inserimento_cod();

    if(cod_ins == codice){
    lcd.setCursor(0,0);
    lcd.print("Codice esatto");
      Serial.println("Codice esatto");
    delay(500);
      cod_ins = "";
    } else{
       //--------------------------------- Incorrect code change code
      lcd.clear();
      lucchetto();

      lcd.setCursor(0,1);
      lcd.print("Codice errato");
      Serial.println("Codice errato");
      suon_err();
      err = err + 1;
         if(err >= err_max){
  blocco();
}
     
      delay(500);
      goto INIZIO;
    }
   
    lcd.clear();
    lucchetto();
   
    lcd.setCursor(0,0);
    lcd.print("Ins. nuovo PIN:");
    Serial.println("Ins. nuovo PIN:");
    lcd.setCursor(0,1);

    inserimento_cod();

    if(cod_ins == cambiocodice){
      lcd.clear();
    lucchetto();
      lcd.setCursor(0,0);
     lcd.print("PIN non");
      lcd.setCursor(0,1);
      lcd.print("inseribile");
    Serial.println("Codice non inseribile (il codice non può essere come la password di cambio password)");
      suon_err();
      delay(1000);
    }else{
    codice = cod_ins;
    lcd.setCursor(0,0);
    lcd.clear();
    lucchetto();
   
    lcd.print("Password cambiata");
    Serial.println("Password cambiata");
    delay(500);
    }
  }
  else{
    lcd.clear();
    lucchetto();
      lcd.setCursor(0,1);
      Serial.println("Codice errato");
    lcd.print("Codice errato");
    suon_err();
    delay(500);
    err = err + 1;
      cod_ins = "";
      delay(1000);
    if(err >= err_max){
  blocco();
}
      goto INIZIO;
    }
 
}

void lucchetto(){
  if(myservo.read() == 0){
    lcd.setCursor(15,1);
    lcd.write(byte(0));
    digitalWrite(verde, LOW);
    digitalWrite(rosso, HIGH);
  }else if(myservo.read() == 90){
    lcd.setCursor(15,1);
    lcd.write(byte(1));
    digitalWrite(rosso, LOW);
    digitalWrite(verde, HIGH);
   
  }
  return;
}

void blocco(){
 
  if(err == 4){
    sup = 0;
  }else if(err < 6){
    sup = 30;
  }else if(err < 8){
    sup = 60;
  }else if(err < 10){
    sup = 90;
  }else if(err > 9){
    sup = 270;
  }
  int tem = secondi_blocco + sup;
  for(int i = tem ; i > 0; i-- ){
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(err);
  lcd.setCursor(2,0);
    lcd.print(" Errori");
    lcd.setCursor(0,1);
    lcd.print("Riprova tra:");
    lcd.print(i);
    Serial.println(i);
    lucchetto();
    delay(1000);
 
  }
  return;
}

void suon_err(){
  delay(200);
  tone(buzzer,100,1000);
  digitalWrite(verde, LOW);
  for(int i = 3; i > 0; i--){
    digitalWrite(rosso, LOW);
    delay(180);
    digitalWrite(rosso, HIGH);
    delay(120);
   
  }
}

void inserimento_cod(){
for(int i=4; i>0; i--){
  char ins = tastiera.waitForKey();
   
    tone(buzzer,800,70);
    delay(70);
    lcd.print("*");
   

    //------------------------------------ I read code
  cod_ins = cod_ins + ins;
  }
}
