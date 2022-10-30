#include <iostream>
using namespace std;

int main() {
  int i = 0;
  int input[3] = {};
  
  while(i<3)
  {
    cout << "Digite o valor a ser inserido: " <<endl;
    cin >> input[i];
    i++;
  }
  
  for(i=0; i<3; i++)
  {
    cout << "O valor armazenado no local " << i << " é: " << input[i] <<endl;
  }
}