#include <iostream>
using namespace std;

int main()
{
float num_min, num_max, num_ref, res_min, res_max = 0.0;
  cout << "Digite um número mínimo: " <<endl;
  cin >> num_min;
  cout << "Digite um número máximo: " <<endl;
  cin >> num_max;
  cout << "Digite um número intermediário: " <<endl;
  cin >> num_ref;

  if(num_ref == num_min)
  {
    cout << "O número intermediário é o próprio número mínimo" <<endl;
  }
  else if(num_ref == num_max)
  {
    cout << "O número intermediário é o próprio número máximo" <<endl;
  }
  else if (num_ref < ((num_max - num_min) /2))
  {
    res_min = 50 - (num_ref * 100) / (num_max - num_min); //essa fórmula mostra o quão longe a variável intermediária está da metade, que simboliza o ponto da virada entre estar mais próximo do mínimo para estar mais próximo do máximo. Então é explicitado um valor em relação a metade (por isso -50)
    cout << "O número intermediário está " << res_min <<"% mais perto do menor número do que do maior" <<endl;
  //cout << num_min <<" "<< num_max << " " <<num_ref; 
  }
  else if (num_ref == ((num_max - num_min) /2)) //se for no meio
  {
    cout << "O número intermediário está exatamente entre o maior e o menor número " <<endl;
  }
  else
  {
    res_max = abs(50 - (num_ref * 100) / (num_max - num_min)); //aqui é colocado o módulo do valor anterior, ou seja, o que seria negativo por ser maior do que a metade entre máx e mín torna-se o valor absoluto
    cout << "O número intermediário está " << res_max <<"% mais perto do maior número do que do menor" <<endl;
  }
}

