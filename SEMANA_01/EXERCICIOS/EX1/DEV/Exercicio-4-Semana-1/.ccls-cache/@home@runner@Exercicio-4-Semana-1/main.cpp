#include <iostream>
using namespace std;

int main() {
  float vetor[4] = {}; 
  cout << "Descubra qual a maior distância: " <<endl;
  cout << "Distância para direita:" <<endl;
  cin >> vetor[0];
  cout << "Distância para esquerda:" <<endl;
  cin >> vetor[1];
  cout << "Distância para frente:" <<endl;
  cin >> vetor[2];
  cout << "Distância para trás:" <<endl;
  cin >> vetor[3];

  if (vetor[0] > vetor[1] && vetor[0] > vetor[2] && vetor[0] > vetor[3])
  {
    cout << "A maior distância é a da direita, sendo" << " " <<  vetor[0] << endl; 
  }
  else if (vetor[1] > vetor[0] && vetor[1] > vetor[2] && vetor[1] > vetor[3])
  {
    cout << "A maior distância é a da esquerda, sendo" << " " <<  vetor[1] << endl; 
  }
  else if (vetor[2] > vetor[0] && vetor[2] > vetor[1] && vetor[2] > vetor[3])
  {
    cout << "A maior distância é a da frente, sendo" << " " <<  vetor[2] << endl;
  }
  else if (vetor[3] > vetor[0] && vetor[3] > vetor[1] && vetor[3] > vetor[2])
  {
    cout << "A maior distância é a de trás, sendo" << " " <<  vetor[3] << endl;
  }
}