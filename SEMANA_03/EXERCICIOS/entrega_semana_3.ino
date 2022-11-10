//definição das portas que estão ligadas aos componentes
int led_green = 3;
int led_white = 5;
int led_yellow = 7;
int led_blue = 9;
int ldr = 16;
int buzzer = 37;
int btn_le_antigos = 40;
int btn_le_atual = 42;
int valorldr = 0;  //declara a variável como inteiro
int num_binario[4] = {};  //há 5 espaços pq é necessário haver um vazio dps dos 4 binários
int salvos[100] = {};  //coloca o valor do LDR de 0 a 15 a cada clique do botão, sendo útil para retomar os valores antigos com o outro botão
int som_buzzer[100] = {}; //coloca o valor do buzzer no array, assim como o valor do LDR
int contador = 0;

void setup() {
  Serial.begin(115200);
  //define que cada led representa um output e os botões e o LDR inputs 
  pinMode(led_green, OUTPUT);
  pinMode(led_white, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btn_le_antigos, INPUT);
  pinMode(btn_le_atual, INPUT);
}

void loop() {
  if (digitalRead(btn_le_atual) == LOW)
  {
    salvar();
  } 
  if (digitalRead(btn_le_antigos) == LOW)
  {
    executar();
  }
}

//com base no valor vindo de outra função, toca o valor correspondente
void toca_buzzer(int som) {
  tone(buzzer, som);
  delay(500);
  noTone(buzzer);
}

//essa função atribui valores "inputados" a cada um dos leds correspondentes, sendo útil para ligá-los em outra função
void acende_led(int input_green, int input_white, int input_yellow, int input_blue, int luz) {
  digitalWrite(led_green, input_green);
  digitalWrite(led_white, input_white);
  digitalWrite(led_yellow, input_yellow);
  digitalWrite(led_blue, input_blue);
  toca_buzzer(luz * 200);

  delay(500);
  digitalWrite(led_green, LOW);
  digitalWrite(led_white, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_blue, LOW);
}

//coloca os valores inputados dos binários de cada item do array de forma individual, de maneira que armazena a cada 4 novos valores dos leds
void armazena_led(int val_0, int val_1, int val_2, int val_3) {
  num_binario[0] = val_0;
  num_binario[1] = val_1;
  num_binario[2] = val_2;
  num_binario[3] = val_3;
  Serial.println(num_binario[0]);
  Serial.println(num_binario[1]);
  Serial.println(num_binario[2]);
  Serial.println(num_binario[3]);
  Serial.println(num_binario[4]);
}

//coloca os valores inputados de som de cada item do array de forma individual
void armazena_buzzer(int som_salva) {
  som_buzzer[0] = som_salva;
  Serial.println(som_buzzer[0]);
}

void salvar() {
  //Lê o valor do sensor ldr e armazena_led na variável valorldr
  int valor_ldr = analogRead(ldr);
  //normaliza os valores do sensor de luz para ficar entre 0 e 15
  int luz = map(valor_ldr, 725, 4095, 1, 15);
  Serial.println("O valor lido pelo ldr é: ");  //Imprime na serial a mensagem Valor lido pelo LDR
  Serial.println(luz);                          //Imprime na serial os dados de valorldr
  delay(0);

  //coloca o valor do LDR no array que salva cada valor da luz, e faz com que a luz e o som sejam emitidos a partir desse array
  if(contador < 100) {
    salvos[contador] = luz;
    tocar(luz);
    contador++;
  }
}

//faz com que seja tocado cada um dos valores de 0 a 15 armazenado no array após apertar o botão _le_antigos
void executar() {
  for (int i=0; i < contador; i++) {
    int luz = salvos[i];
    tocar(luz);
  }
  salvos[100] = {};
  contador = 0;
}

void tocar(int luz) {
  //faz com que o número obtido no sensor seja convertido para binário
  if (luz == 1) {
    acende_led(0, 0, 0, 1, luz);
    armazena_led(0, 0, 0, 1);
    armazena_buzzer(200);
  } else if (luz == 2) {
    acende_led(0, 0, 1, 0, luz);
    armazena_led(0, 0, 1, 0);
    armazena_buzzer(400);
  } else if (luz == 3) {
    acende_led(0, 0, 1, 1, luz);
    armazena_led(0, 0, 1, 1);
    armazena_buzzer(600);
  } else if (luz == 4) {
    acende_led(0, 1, 0, 0, luz);
    armazena_led(0, 1, 0, 0);
    armazena_buzzer(800);
  } else if (luz == 5) {
    acende_led(0, 1, 0, 1, luz);
    armazena_led(0, 1, 0, 1);
    armazena_buzzer(1000);
  } else if (luz == 6) {
    acende_led(0, 1, 1, 0, luz);
    armazena_led(0, 1, 1, 0);
    armazena_buzzer(1200);
  } else if (luz == 7) {
    acende_led(0, 1, 1, 1, luz);
    armazena_led(0, 1, 1, 1);
    armazena_buzzer(1400);
  } else if (luz == 8) {
    acende_led(1, 0, 0, 0, luz);
    armazena_led(1, 0, 0, 0);
    armazena_buzzer(1600);
  } else if (luz == 9) {
    acende_led(1, 0, 0, 1, luz);
    armazena_led(1, 0, 0, 1);
    armazena_buzzer(1800);
  } else if (luz == 10) {
    acende_led(1, 0, 1, 0, luz);
    armazena_led(1, 0, 1, 0);
    armazena_buzzer(2000);
  } else if (luz == 11) {
    acende_led(1, 0, 1, 1, luz);
    armazena_led(1, 0, 1, 1);
    armazena_buzzer(2220);
  } else if (luz == 12) {
    acende_led(1, 1, 0, 0, luz);
    armazena_led(1, 1, 0, 0);
    armazena_buzzer(2400);
  } else if (luz == 13) {
    acende_led(1, 1, 0, 1, luz);
    armazena_led(1, 1, 0, 1);
    armazena_buzzer(2600);
  } else if (luz == 14) {
    acende_led(1, 1, 1, 0, luz);
    armazena_led(1, 1, 1, 0);
    armazena_buzzer(2800);
  } else if (luz == 15) {
    acende_led(1, 1, 1, 1, luz);
    armazena_led(1, 1, 1, 1);
    armazena_buzzer(3000);
  }
}