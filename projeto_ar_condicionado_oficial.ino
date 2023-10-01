// INCLUSÃO DE BIBLIOTECA
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <dht11.h>

// DEFINIÇÃO DE PINOS
#define DHT11PIN 2

// INSTANCIANDO OBJETOS
IRsend emissorIR;
dht11 DHT11;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// VARIÁVEIS
#define tempoTecla 350
#define frequencia 38  // kHz

float h;
float t;

bool desligar_ar;
bool ligar_ar;
bool inicio = true;

// TECLAS CLONADAS
/*
 * TeclaA: Ligar Televisão
 * TeclaB: Ligar Televisão e Netflix
 * teclaC: Ligar Ar Condicionado
 * teclaD: Desligar Ar Condicionado
 */
unsigned int teclaA[] = { 3976, 4000, 520, 1972, 516, 1976, 520, 1996, 496, 1976, 520, 1004, 476, 1028, 472, 2020, 496, 1004, 476, 1996, 496, 1028, 476, 1996, 496, 1028, 472, 1032, 472, 1028, 472, 1032, 472, 1008, 492, 2000, 492, 2000, 496, 1008, 492, 2000, 496, 1008, 492, 2000, 496, 1004, 496, 2000, 492, 8480, 3980, 4000, 492, 2000, 492, 2000, 496, 2020, 472, 2000, 492, 1012, 492, 1008, 492, 2004, 492, 1008, 492, 2000, 496, 1008, 492, 2000, 492, 1008, 496, 1008, 492, 1008, 496, 1008, 492, 1012, 492, 2000, 492, 2000, 492, 1012, 492, 2000, 492, 1012, 488, 2004, 492, 1012, 488, 2004, 492, };
unsigned int teclaB[] = { 8896, 4556, 584, 1720, 644, 564, 588, 620, 632, 1648, 608, 1724, 532, 1772, 588, 1720, 608, 596, 584, 620, 588, 644, 560, 624, 580, 624, 584, 724, 456, 644, 616, 596, 580, 620, 588, 648, 560, 644, 560, 620, 584, 652, 584, 596, 584, 1716, 588, 1724, 644, 560, 588, 616, 588, 620, 584, 648, 560, 616, 592, 1744, 560, 596, 608, 1744, 536, 648, 580, 624, 584, 1720, 588, 620, 588, 20068, 560, 1744, 560, 644, 536, 672, 560, 672, 540, 616, 588, 696, 508, 644, 564, 620, 584, 1720, 584, 648, 536, 672, 560, 648, 556, 620, 560, 696, 532, 648, 560, 648, 584, 616, 564, 648, 556, 620, 588, 620, 584, 596, 612, 648, 560, 644, 556, 624, 588, 644, 560, 672, 532, 620, 584, 672, 508, 1748, 588, 1720, 584, 620, 560, 676, 532, };
unsigned int teclaC[] = { 8924, 4556, 588, 1724, 584, 620, 588, 596, 608, 1724, 588, 1720, 588, 1696, 612, 1720, 588, 620, 584, 600, 608, 620, 616, 592, 584, 620, 588, 620, 584, 624, 584, 616, 592, 620, 584, 596, 612, 596, 608, 624, 580, 624, 588, 616, 588, 1724, 584, 1696, 612, 616, 592, 620, 584, 624, 584, 624, 584, 600, 608, 1716, 588, 620, 588, 1720, 588, 620, 584, 620, 588, 1720, 588, 620, 584, 20056, 588, 1720, 592, 640, 560, 620, 588, 620, 588, 620, 584, 620, 584, 648, 560, 620, 588, 1720, 588, 616, 588, 624, 584, 648, 560, 616, 584, 624, 584, 624, 584, 620, 584, 620, 584, 620, 588, 624, 584, 620, 612, 592, 612, 600, 584, 620, 584, 624, 584, 620, 584, 620, 588, 620, 584, 620, 588, 1724, 584, 1752, 556, 620, 584, 624, 584, };
unsigned int teclaD[] = { 8948, 4556, 588, 152, 224, 1344, 588, 596, 608, 620, 612, 592, 588, 1724, 584, 1720, 588, 1720, 588, 624, 580, 624, 584, 620, 584, 620, 588, 620, 588, 620, 588, 620, 588, 620, 584, 620, 588, 620, 608, 596, 588, 620, 584, 624, 588, 620, 584, 1720, 584, 620, 592, 616, 588, 620, 584, 624, 584, 620, 588, 620, 584, 1720, 588, 624, 580, 1724, 584, 624, 608, 596, 584, 1724, 584, 624, 584, 20048, 588, 1724, 584, 620, 584, 624, 584, 620, 584, 624, 608, 600, 608, 596, 584, 648, 560, 1724, 584, 1724, 588, 620, 584, 624, 584, 644, 560, 648, 560, 620, 584, 624, 584, 624, 584, 620, 584, 624, 584, 620, 588, 620, 584, 624, 608, 624, 556, 624, 584, 620, 588, 624, 580, 628, 580, 624, 584, 1748, 584, 1696, 584, 620, 588, 1748, 560, };


void setup() {
  // COMANDOS DE INICIALIZAÇÃO
  Serial.begin(9600);

  // DISPLAY
  lcd.begin();
  lcd.backlight();  // ligando display
  lcd.clear();      // limpando display
  delay(500);

  lcd.setCursor(1, 0);
  lcd.print("  Bem-vindo");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("de volta, Roger!");
  delay(1000);

  lcd.clear();
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("Setup concluido!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" Bons estudos!");
  delay(3000);

  Serial.println("Setup concluído!");
  delay(1500);
  lcd.clear();
  delay(500);
}

void loop() {
  // TERMOSTATO
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  h = (float)DHT11.humidity, 2;

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);
  t = (float)DHT11.temperature, 2;

  Serial.println("----- -----");
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.setCursor(9, 0);
  lcd.print(h);
  delay(500);

  lcd.setCursor(0, 1);  // posiciona o cursor na primeira coluna da linha 2
  lcd.print("Temperatura:");
  lcd.setCursor(12, 1);  // posiciona o cursor na primeira coluna da linha 2
  lcd.print(t);
  delay(3000);

  // LEITURA INICIAL
  while (inicio == true) {
    if (t <= 18.00) {  // DESLIGAR AR
      desligar_ar = true;
      ligar_ar = false;
    } else {
      desligar_ar = false;
      ligar_ar = true;
    }

    inicio = false;
  }


  if (t <= 18.00) {
    if (desligar_ar == true) {
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print(" Desligando Ar");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print(" Condicionado!");
      delay(1500);

      // DESLIGANDO AR CONDICIONADO
      emissorIR.sendRaw(teclaD, sizeof(teclaD) / sizeof(teclaD[0]), frequencia);

      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ar Condicionado");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print("   Desligado!");
      Serial.println("Ar condicionado DESLIGADO!");

      delay(3500);  // Pausa entre os sinais
      desligar_ar = false;
      ligar_ar = true;
    }
  }


  if ((t <= 26.00) || (t > 26.00)) {
    if (ligar_ar == true) {
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("  Ligando Ar");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print(" Condicionado!");
      Serial.println("Ligando Ar condicionado!");
      delay(1500);

      // LIGANDO AR CONDICIONADO
      emissorIR.sendRaw(teclaC, sizeof(teclaC) / sizeof(teclaC[0]), frequencia);

      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ar Condicionado");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print("    Ligado!");
      Serial.println("Ar condicionado LIGADO!");

      delay(3500);  // Pausa entre os sinais
      desligar_ar = true;
      ligar_ar = false;
    }
  }

  delay(5000);
  lcd.clear();
  delay(500);
}
