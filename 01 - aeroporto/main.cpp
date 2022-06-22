#include <iostream>
#include <vector>
using namespace std;


void test_case(int aeroportos, int voos, int teste) {
  int grau_de_entrada[aeroportos];
  int grau_de_saida[aeroportos];

  for (int i = 0; i < aeroportos; i++) {
    grau_de_saida[i] =0;
    grau_de_entrada[i] = 0;
  }
  int origem;
  int destino;
  for (int i = 0; i < voos; i++) {
    cin >> origem >> destino;
    grau_de_entrada[origem-1]++;
    grau_de_saida[destino-1]++;
  }

  int maior = -1;
  int pos_maior[aeroportos];
  int j = 0;
  for (int i = 0; i <aeroportos; i++) {
    if (grau_de_entrada[i] + grau_de_saida[i] > maior) {
      pos_maior[0] = i + 1;
      j = 1;
      maior = grau_de_entrada[i] + grau_de_saida[i];
    } else if(grau_de_entrada[i] + grau_de_saida[i] == maior) {
      pos_maior[j] = i + 1;
      j++;
    }
  }


  cout << "Teste " << teste << endl;
  for (int i = 0; i < j; i++) {
    cout << pos_maior[i];
    if (i < j -1 ) cout << " ";
  }
}


int main() {
  int aeroporto, voos;
  int teste = 1;
  do {
    cin >> aeroporto >> voos;
    if (aeroporto && voos) {
      if (teste > 1)  cout << "\n\n";
      test_case(aeroporto, voos, teste);
      teste++;
    }
  } while (aeroporto && voos);


  return 0;
}