#include <iostream>
using namespace std;

int main() {
  char resposta;
  cout << "Deseja continuar com o mapeamento? ~s ou n" <<endl;
  cin >> resposta;
  if (resposta == 's'){
    return true;
  }
  else if (resposta =='n'){
    return false;
  }
}
