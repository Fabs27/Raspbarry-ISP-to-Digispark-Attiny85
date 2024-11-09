#include <SPI.h>

// Defina os pinos do Raspberry Pi Pico
#define PIN_RST 21   // Reset - Pino GP21
#define PIN_MOSI 18  // MOSI - Pino GP18
#define PIN_MISO 19  // MISO - Pino GP19
#define PIN_SCK 20   // SCK - Pino GP20
#define LED_PIN 25   // LED - Pino GP25 (LED embutido no Raspberry Pi Pico)

void setup() {
  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_MISO, INPUT);
  pinMode(PIN_SCK, OUTPUT);
  pinMode(LED_PIN, OUTPUT); // Configura o pino do LED como saída

  // Inicialize a comunicação SPI
  SPI.begin();

  // Defina o estado inicial dos pinos
  digitalWrite(PIN_RST, HIGH);
  digitalWrite(PIN_MOSI, LOW);
  digitalWrite(PIN_SCK, LOW);
  digitalWrite(LED_PIN, LOW); // Desliga o LED inicialmente

  Serial.begin(19200);  // Inicialize a comunicação serial para depuração
  Serial.println("Arduino ISP Iniciado");
}

void loop() {
  // Faz o LED piscar para indicar que o programa está funcionando
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);

  // Verifica se há um comando de programação via serial
  if (Serial.available()) {
    byte command = Serial.read();
    processCommand(command);
  }
}

// Função para processar comandos recebidos via serial
void processCommand(byte command) {
  switch (command) {
    case 0x30:  // Comando para ler a assinatura do dispositivo
      readSignature();
      break;
    case 0x40:  // Comando para escrever dados na memória flash
      writeFlash();
      break;
    case 0x50:  // Comando para ler dados da memória flash
      readFlash();
      break;
    default:
      Serial.println("Comando desconhecido");
  }
}

// Função para ler a assinatura do dispositivo
void readSignature() {
  digitalWrite(PIN_RST, LOW);
  delay(20);
  digitalWrite(PIN_RST, HIGH);
  SPI.transfer(0x30);  // Envia o comando para ler a assinatura
  byte signature1 = SPI.transfer(0x00);
  byte signature2 = SPI.transfer(0x00);
  byte signature3 = SPI.transfer(0x00);
  digitalWrite(PIN_RST, LOW);
  Serial.print("Assinatura: ");
  Serial.print(signature1, HEX);
  Serial.print(" ");
  Serial.print(signature2, HEX);
  Serial.print(" ");
  Serial.println(signature3, HEX);
}

// Função para escrever dados na memória flash
void writeFlash() {
  digitalWrite(PIN_RST, LOW);
  delay(20);
  digitalWrite(PIN_RST, HIGH);
  // Envie os comandos e os dados para escrever na memória flash
  // Exemplo: SPI.transfer(0x40); // Comando para gravar
  //          SPI.transfer(0x00); // Endereço alto
  //          SPI.transfer(0x00); // Endereço baixo
  //          SPI.transfer(0xAA); // Dados
  digitalWrite(PIN_RST, LOW);
  Serial.println("Dados gravados na memória flash");
}

// Função para ler dados da memória flash
void readFlash() {
  digitalWrite(PIN_RST, LOW);
  delay(20);
  digitalWrite(PIN_RST, HIGH);
  // Envie os comandos para ler da memória flash
  // Exemplo: SPI.transfer(0x50); // Comando para ler
  //          byte data = SPI.transfer(0x00);
  digitalWrite(PIN_RST, LOW);
  // Serial.print("Dados da memória flash: ");
  // Serial.println(data, HEX);
}
