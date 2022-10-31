#include <iostream>
using namespace std;

int main() {
  int i = 0;
  int j = 0;
  char para = 'a';
  int num_palavras = 0;
  // int caminho[3] = {};
  int valor_dir[3] = {};
  char direcao[3] = {};

  while(i<4)
  {
    cout << "Digite a direção para o robô (d, e, t, f)" << endl;
    cin >> direcao[i];
    cout << "Digite a distância percorrida" <<endl;
    cin >> valor_dir[i];
    cout << "Deseja parar? (s / n)" <<endl;
    cin >> para;
    i++;
    num_palavras++;
    if (para == 's')
    {
      return 0;
    }
  }

  for (j=0; j<num_palavras; j++)
    {
      cout << "Posição: " << direcao[j] <<endl;
      cout << "Valor da posição: " << valor_dir[j] <<endl;
    }
}