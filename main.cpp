#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>

//as partes do codigo que estiverem em comentario são as utilizadas na p3 que nao foram necessarias nessa;

using namespace std;

struct tNo{
  float info;
  tNo* proximo;
};

tNo* criaNo(int item){
  tNo* no = new tNo;

  no->info = item;
  no->proximo = NULL;

  return no;
}

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho;
};

void inicializaLista(tLista* pLista){
  pLista->primeiro = NULL;
  pLista->ultimo = NULL;
  pLista->marcador = NULL;
  pLista->tamanho = 0;
}

int obterTamanho(tLista* pLista){
  return (pLista->tamanho);
}

bool listaVazia(tLista* pLista){ 
  return (pLista->tamanho==0);
}

bool finalLista(tLista* pLista){
  return (pLista->marcador == NULL);
}

void incluirNoFim(tLista* pLista, float info){
  tNo* no;
  no = criaNo(info);

  if (listaVazia(pLista)){
    pLista->primeiro = no;
  }
  else{
    pLista->ultimo->proximo = no;
  }

  pLista->ultimo = no;
  pLista->marcador = no;
  pLista->tamanho++;
}

void imprimirLista(tLista* pLista){
  pLista->marcador = pLista->primeiro;

  while(!finalLista(pLista)){
      float informacao = pLista->marcador->info;
      cout << informacao << " ";
      pLista->marcador = pLista->marcador->proximo;
  }
  cout << endl;
}

void excluirPosicao(tLista* pLista, int pos){
    tNo* anterior;
    tNo* aux;
    tNo* apagado;

    if(!listaVazia(pLista)){
        pLista->marcador = pLista->primeiro;

        if(pos < obterTamanho(pLista)){

            if (pos==0){
              pLista->primeiro = pLista->marcador->proximo;
            }
            else{
                for(int i = 0; i < pos; i++){
                    anterior = pLista->marcador;
                    pLista->marcador = pLista->marcador->proximo;
                    aux = pLista->marcador->proximo;
                }
            anterior->proximo = aux;
            }
            apagado = pLista->marcador;
            free(apagado);
            pLista->tamanho--;
        }
    }
}

/*
struct tInvest{ 
  
  void jSimples(float capital, float taxa, float tempo){
    float montante = capital * (1 + (taxa) * tempo);
    cout << "\n\n  Montante aplicado a juros simples: R$" << montante << endl;
  }

  void jComposto(float capital, float taxa, float tempo){
    float montante = capital * pow(1+(taxa),(tempo));
    cout << "Montante aplicado a juros compostos: R$" << montante << endl;
  }

  void Converte(float taxa){
    float taxaMensal = ((pow((1+(taxa)), 1.0/12)) - 1)*100;
    cout << "\t\tTaxa convertida para mensal: " << taxaMensal  << "%" << endl;
  }
};
*/

void receberEntradas(tLista* valores, int nEntradas){
  float capital, taxa, tempo;
  for (int i=0; i<nEntradas; i++){ 
    cout << "\n\n\n";
    cout << "Informe o valor inicial da aplicacao: "; 
    cin >> capital;
    cout << "Informe a taxa anual em porcentagem: "; 
    cin >> taxa;
    cout << "Informe por quantos anos o valor ficara aplicado: "; 
    cin >> tempo;
    incluirNoFim(valores, capital);
    incluirNoFim(valores, taxa);
    incluirNoFim(valores, tempo);
  }

  ofstream gravarNoArq; 
  gravarNoArq.open("arquivo.txt", ios::out);

  valores->marcador = valores->primeiro;
  int cont=1;
  while(!finalLista(valores)){ 
    float informacao = valores->marcador->info;

    if (cont % 3 == 0){
      gravarNoArq << "\n";
    }
    gravarNoArq << " " << informacao ;


    valores->marcador = valores->marcador->proximo;
    cont++;
  }
  gravarNoArq.close();

  int tamanho = obterTamanho(valores)-1;
  for (int i=tamanho; i>0; i--){ 
    excluirPosicao(valores, i);
  }
  inicializaLista(valores);

}

void LerArquivo(tLista* valores){
  float num;

  ifstream lerDoArq;
  lerDoArq.open("arquivo.txt", ios::in);
  valores->marcador = valores->primeiro; 

  while(!lerDoArq.eof()){ 
    lerDoArq >> num;
    incluirNoFim(valores, num);
  }

  lerDoArq.close();

  imprimirLista(valores);
  cout << "Tam: " << obterTamanho(valores) << endl;

  int tamanho = obterTamanho(valores)-1;
  for (int i=tamanho; i>0; i--){
    excluirPosicao(valores, i); 
  }
  inicializaLista(valores);
}


int main() {

  tLista* valores = new tLista;
  inicializaLista(valores);

  
  //---------------PARTE DO PROGRAMA ANTIGO----------------
  //tInvest invest;

  int nEntradas;
  while(true){

    int opcao1;
    cout << "DIGITE: " << endl;
    cout << " 1) - Gravar em um arquivo" << endl;
    cout << " 2) - Ler de um arquivo" << endl;
    cout << " 3) - Sair" << endl;
    cout << "Opcao: ";
    cin >> opcao1;

    if(opcao1==1){
      cout << "Informe quantas entradas serao executadas: ";
      cin >> nEntradas;
      receberEntradas(valores, nEntradas);
    }else if(opcao1==2){
      LerArquivo(valores);
    }else{
      break;
    }

    
      /*---------------- ANTES AQUI CALCULAVA O JURO SIMPLES, COMPOSTO E A TAXA CONVERTIDA PARA MES------------------
      cout << fixed << setprecision(2);
      taxa = taxa/100;

      if (opcao==0){
        break;
      }else if (opcao == 1){ 
        invest.jSimples(capital, taxa, tempo);
      }
      else if (opcao == 2){
        invest.jComposto(capital, taxa, tempo);
      }
      else if (opcao == 0){
        cout << fixed << setprecision(4);
        invest.Converte(taxa);
      }
      else{
        cout << "OPCAO INCORRETA. PROGRAMA ENCESSADO." << endl;
        break;
      }
    }
    */
  }
}