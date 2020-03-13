#include <require_cpp11.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <SPI.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Criar instancia MFRC522
int led_liberado = 5;
int led_negado = 6;
 
void setup() {
  pinMode(led_liberado, OUTPUT);
  pinMode(led_negado, OUTPUT);
  Serial.begin(9600);   //Iniciar serial de comunicação
  SPI.begin();         //iniciar SPI bus
  mfrc522.PCD_Init();  //inciar MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}

void loop() {
  //Procure novos cartões
  if ( ! mfrc522.PICC_IsNewCardPresent()) {  return;  }
  //Selecione um dos cartões
  if ( ! mfrc522.PICC_ReadCardSerial()) {  return;  }
  //Mostrar UID no monitor serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " ...0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " .0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //altere aqui o UID do cartão que você deseja dar acesso
  {
    Serial.println("ACESSO AUTORIZADO");
    Serial.println();
    delay(3000);
    digitalWrite(led_liberado, LOW);
  }else{
    Serial.println(" Acesso NEGADO");
     for (int i= 1; i<5 ; i++)
    {
      digitalWrite(led_negado, HIGH);
      delay(200);
      digitalWrite(led_negado, LOW);
      delay(200);
    }
  }
  delay(1000);
}
