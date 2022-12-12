#include <WiFi.h>
#include <WebServer.h>
#include <String.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";         // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

int led_esq = 5;
int led_dir = 1;
bool led_esq_aceso = false;
bool led_dir_aceso = false;

int btn_esq = 13;
int btn_dir = 20;
bool btn_esq_pressionado = false;
bool btn_dir_pressionado = false;

int val_max = 255;  //valor máximo de energia fornecida pelo ESP, baseado em 8 bytes
int val_min = 0;    //ESP não forncendo energia
int val_atual = val_max;

int tempo_max = 4000;
int tempo_min = 1000;
int pausa = 200;

unsigned long miliseg_esq = 0;  //para usar a função nativa millis() precisa ser do tipo unsigned long
unsigned long miliseg_dir = 0;
unsigned long miliseg_inicial = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led_esq, OUTPUT);
  pinMode(led_dir, OUTPUT);
  pinMode(btn_esq, INPUT);
  pinMode(btn_dir, INPUT);
  delay(1000);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", init);
  server.on("/jogo", jogo);
  server.on("/recomecar", recomecar);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void init() {
  if (led_esq_aceso) {
    digitalWrite(led_esq, LOW);
  } else {
    digitalWrite(led_esq, LOW);
  }

  if (led_dir_aceso) {
    digitalWrite(led_dir, LOW);
  } else {
    digitalWrite(led_dir, LOW);
  }
  server.send(200, "text/html", SendHTML(false));
}

void jogo() {
  server.send(200, "text/html", SendHTML(true));
  //Acende os leds
  analogWrite(led_esq, val_atual);  //analogWrite pois o output varia, sendo mais recomendado do que o digitalWrite nesses casos
  analogWrite(led_dir, val_atual);
  Serial.println("Antes do while: " + String(val_atual));

  while (val_atual > 0) {  //a função roda 5 vezes decrescendo em 51, até que de 255 chegue em 0 e apague os LEDS
    val_atual -= 51;
    analogWrite(led_esq, val_min);
    delay(400);
    analogWrite(led_esq, val_max);
    analogWrite(led_dir, val_min);
    delay(400);
    analogWrite(led_dir, val_max);
    Serial.println("no while:" + String(val_atual));
  }
  analogWrite(led_esq, val_min);
  analogWrite(led_dir, val_min);
  Serial.println("");
  Serial.println("Aguarde...");
  int tempo_randomico = random(tempo_min, tempo_max);  //gera o tempo de espera aleatório entre 1 e 4 seg
  delay(tempo_randomico);
  miliseg_inicial = millis();  //começa a contar o tempo para depois subtrair, tendo o tempo de reação de cada botão
  Serial.println(tempo_randomico);
  Serial.println("Pressione seu botão");

  while (!btn_esq_pressionado || !btn_dir_pressionado) {  //antes de apertar o botão roda esse código
    if (digitalRead(btn_esq) && !btn_esq_pressionado) {   //verifica se o botão esquerdo foi pressionado
      btn_esq_pressionado = true;                         // Salvar que o botão foi pressionado
      miliseg_esq = millis();                             //salva o tempo em que o botão foi pressionado
      analogWrite(led_esq, val_min);                      // apaga o LED esquerdo
      Serial.println("Apertou botão esquerdo");
    }
    if (digitalRead(btn_dir) && !btn_dir_pressionado) {  //verficar se o botão direito foi pressionado
      btn_dir_pressionado = true;                        //salva que o botão foi pressionado
      miliseg_dir = millis();                            //salva o tempo em que o botão direito foi pressionado
      analogWrite(led_dir, val_min);                     //apaga o LED direito
      Serial.println("Apertou botão direito");
    }

    if (millis() - miliseg_inicial > pausa) {  //validação, só vale se apertar depois do intervalo que acende os LEDS
      if (!btn_esq_pressionado) {              //o LED esquerdo só pisca se o botão esquerdo ainda não foi pressionado
        if (led_esq_aceso) {
          analogWrite(led_esq, val_min);
        } else {
          analogWrite(led_esq, val_max);
        }
        led_esq_aceso = !led_esq_aceso;  //apaga se estiver aceso e acende se estiver apagado
      }
      if (!btn_dir_pressionado) {  //o LED direito só pisca se o botão direito ainda não foi pressionado
        if (led_dir_aceso) {
          analogWrite(led_dir, val_min);
        } else {
          analogWrite(led_dir, val_max);
        }
        led_dir_aceso = !led_dir_aceso;  //apaga se estiver aceso e acender se estiver apagado
      }
    }
  }
  Serial.println("Que rufem os tambores!");
  delay(2000);
  Serial.println("");
  if (miliseg_esq != miliseg_dir) {  //verifica se não houve empate
    Serial.print("O botão ");
    if (miliseg_esq < miliseg_dir) {  //verifica se o botão esquerdo foi pressionado mais rapidamente
      Serial.print("esquerdo");
      analogWrite(led_esq, val_max);  //acende LED esquerdo indicando vencedor
    } else {
      Serial.print("direito");
      analogWrite(led_dir, val_max);  //acende LED direito indicando vencedor
    }

    Serial.println(" foi pressionado mais rapidamente");
  } else {
    Serial.println("Empatou! Uau, isso é tão raro...");
  }

  Serial.println("");
  delay(1000);
  Serial.println("Parabéns!");
  Serial.println("");
  Serial.println("Tempos:");
  Serial.print("Esquerdo = ");
  Serial.print(miliseg_esq - miliseg_inicial);  //exibe o tempo demorado para o botão esquerdo ser pressionado
  Serial.println(" ms");
  delay(1000);

  Serial.print("Direito = ");
  Serial.print(miliseg_dir - miliseg_inicial);  //exibe o tempo demorado para o botão direito ser pressionado
  Serial.println(" ms");
  delay(1000);

  Serial.println("");
  Serial.println("Pressione recomeçar para jogar de novo");
  Serial.println("");
  // Apagar LEDs
  analogWrite(led_esq, val_min);
  analogWrite(led_dir, val_min);
}

void loop() {
  server.handleClient();
}

void recomecar() {
  analogWrite(led_esq, LOW);
  analogWrite(led_dir, LOW);
  val_atual = val_max;
  btn_esq_pressionado = false;
  btn_dir_pressionado = false;

  Serial.println("Recomeçando...");
  server.send(200, "text/html", SendHTML(false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(int jogar) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta charset=\"UTF-8\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title> Quem é o mais rápido? </title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 22px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1> Teste de reflexo </h1>\n";
  ptr += "<h3> Seja o mais rápido a clicar no botão após o led acender! </h3>\n";

  if (jogar) {
    ptr += "<p> Jogo em andamento </p><a class=\"button button-off\" href=\"/recomecar\">Recomeçar</a>\n";
    ptr += "<p> Quando os 2 LEDs acenderem após piscar, seja o 1º clicar no botão do ESP! </p>";
    ptr += "<p> O LED piscará no lado que clicou mais rápido na sequência! </p>";
  } else {
    ptr += "<p> COMECAR JOGO! </p><a class=\"button button-on\" href=\"/jogo\">JOGAR</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}