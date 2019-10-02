#include <SPI.h>// Seri haberleşme kütüphanesi eklendi
#include "PN532_SPI.h"// kutuphane eklendi
#include "PN532.h"// kutuphane eklendi
#include "NfcAdapter.h"// kutuphane eklendi
#include <Servo.h>// servo kutuphanesi eklendi

String kayit_uid_dizi[50];
int kayit_dizi_buyukluk = sizeof(kayit_uid_dizi);
int kayit_ekle_sira = 0;
int kayit_sil_sira = 0;
int kayit_kontrol_sira = 0;

int servoPin = 5; //servo değişkenine 2.pin atanmış oldu
int buzzer = 4;// buzzer 3.pin
int buton_format = 3;
int buton_kayit = 2;
int buton_kayit_silme = 9;
int kayit_sira = 0;
int led_yesil = 6;
int led_kirmizi = 7;
int led_sari = 8 ;
Servo servo; //servo sınıfının kapsadığı servo adında değişken  oluşturuldu

PN532_SPI interface(SPI, 10); // 10. dijital  pin spı iletişimi için seçildi
NfcAdapter nfc = NfcAdapter(interface); // nfc adaptörü nesnesi oluşturuldu
 
void setup(void) {
    Serial.begin(115200); // seri mönitor 115200 baud da başlatıldı
    Serial.println("NDEF Reader");// seri mönitor e yazıldı
    nfc.begin(); // nfc başlatıldı
    pinMode(buton_format,INPUT);
    pinMode(buton_kayit,INPUT);
    pinMode(buton_kayit_silme,INPUT);
    
    pinMode(led_yesil,OUTPUT);
    pinMode(led_kirmizi,OUTPUT);
    pinMode(led_sari,OUTPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(servoPin,OUTPUT);
   
    
}
 
void loop(void) {
  kayit_uid_dizi[0]="a";
  kayit_uid_dizi[1]="a";
  kayit_uid_dizi[2]="a";
  kayit_uid_dizi[3]="a";
  kayit_uid_dizi[4]="a";
  kayit_uid_dizi[5]="a";
  kayit_uid_dizi[6]="a";
  kayit_uid_dizi[7]="a";
  kayit_uid_dizi[8]="a";

  Serial.print("h");
   
    if(digitalRead(buton_format) == HIGH){
      digitalWrite(led_sari,HIGH);
      digitalWrite(led_kirmizi,HIGH);
      Serial.println("kartı yerleştirin.");
      if (nfc.tagPresent()) 
      {
          bool success = nfc.format();
          if (success) 
          {
            Serial.println("kart formatlandı");
          } else 
          {
            Serial.println("kart formatlama basarısız");
          }
      delay(5000);
      }
    }


   if(digitalRead(buton_kayit_silme) == HIGH)
   {
    NfcTag tag = nfc.read(); // nfc kartı okunuyor
    String scannedUID = tag.getUidString(); // kartın uıd si okunuyor

    for(int i = 0;i<kayit_dizi_buyukluk;i++)
    {
      if(kayit_uid_dizi[kayit_sil_sira] == scannedUID)
      {
        int x = 0;
        kayit_uid_dizi[kayit_sil_sira] = x ;
        break;
      }
      else
      {
        kayit_sil_sira++;
        if(kayit_sil_sira == kayit_dizi_buyukluk)
        {
          Serial.println("silincek birsey bulunamadı");
          break;
        }
      }
    }
   }

    if(digitalRead(buton_kayit) == HIGH)
    {
      NfcTag tag = nfc.read(); // nfc kartı okunuyor
      String scannedUID = tag.getUidString(); // kartın uıd si okunuyor
           for( int i = 0; i<kayit_dizi_buyukluk; i++)
           {
           
               if( kayit_uid_dizi[kayit_ekle_sira] == "a")
               {
                 kayit_uid_dizi[kayit_ekle_sira] = scannedUID;
                 Serial.println("kayit eklendi");
                 break;
               }
               else
               { 
                   kayit_ekle_sira++;
                   if(kayit_ekle_sira == kayit_dizi_buyukluk)
                   {
                     Serial.println("kayıt edicek yer yok");
                     break;
                   }
              }
           }              
    }      
  
          else if(nfc.tagPresent())
         {
           for( int i=0; i<kayit_dizi_buyukluk; i++)
           {
              NfcTag tag = nfc.read(); // nfc kartı okunuyor
              String scannedUID = tag.getUidString(); // kartın uıd si okunuyor
              
                    if(scannedUID == kayit_uid_dizi[kayit_kontrol_sira])
                    {
                      Serial.println("kayit bulundu");
                 
                    }
                    else
                    {
                      kayit_kontrol_sira++;
                        if(kayit_kontrol_sira == kayit_dizi_buyukluk)
                        {
                          Serial.println("kayıt bulunamadı");
                          break;
                        }
                    }
             }
        delay(2000);
      }
     
}
