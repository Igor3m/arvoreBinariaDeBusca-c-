#include <iostream>
#include <cstdlib>

using namespace std;
class No{
	friend class ArvoreB;
	private:
		int valor;
		No* esquerdo;
		No* direito;
		No* pai;
	public:
		No(int v);
};
No::No(int v){
	valor = v;
	esquerdo = NULL;
	direito = NULL;
	pai = NULL;
}

class ArvoreB{
	private:
		No* raiz;
	public:
		ArvoreB();
		void inserirValor(int umValor);
		int minimo();
		No* minimoAux(No* raizSubarvore);
		int maximo();
		No* maximoAux(No* raizSubarvore);
		No* buscaAux(int umValor);
		void percorreEmOrdem();
		void percorreEmOrdemAux(No* umNo);
		void percorrePreOrdem();
		void percorrePreOrdemAux(No* umNo);
		void percorrePosOrdem();
		void percorrePosOrdemAux(No* umNo);
		void transplanta(No* antigo, No* novo);
		void removeRecusiva(int umValor);
		void removeRecAux(No umNo, int umValor);
		void remove(int umValor);
		void busca(int v);
		int contaNo (int umValor);
};
ArvoreB::ArvoreB(){
	raiz = NULL;
}
void ArvoreB::inserirValor(int umValor){
	No* novo = new No(umValor);
	No* atual;
	No* anterior;
	int cont = 1;
	if (raiz == NULL){
		raiz = novo;
	}
	else{
		atual = raiz;
		while (atual != NULL){
			anterior = atual;
			if (atual->valor > umValor){
				atual = atual->esquerdo;
				cont++;
			}
			else{
				atual = atual->direito;
				cont++;
			}
		}
		novo->pai = anterior;
		if (anterior->valor > novo->valor){
			anterior->esquerdo = novo;
		}
		else{
			anterior->direito = novo;
		}
	}
	cout << "O numero de nos percorridos nessa isnercao foi:" << " " << cont << endl;
}
No* ArvoreB::minimoAux(No* raizSubarvore){
	No* aux = raizSubarvore;
	while(aux->esquerdo != NULL){
		aux = aux->esquerdo;
	}
	return aux;
}
int ArvoreB::minimo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No* minimoNo = minimoAux(raiz);
		return minimoNo->valor;
	}
}
No* ArvoreB::maximoAux(No* raizSubarvore){
	while(raizSubarvore->direito != NULL){
		raizSubarvore = raizSubarvore->direito;
	}
	return raizSubarvore;
}
int ArvoreB::maximo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No* maximoNo = maximoAux(raiz);
		return maximoNo->valor;
	}
}
int ArvoreB::contaNo(int umValor){
	No* atual = raiz;
	int cont = 1;
	while (atual != NULL){
		if (atual->valor == umValor){
			return cont;
		}
		else if (atual->valor > umValor){
			atual = atual->esquerdo;
			cont++;
		}
		else{
			atual = atual->direito;
			cont++;
		}
	}
	return cont;
}
No* ArvoreB::buscaAux(int umValor){
	No* atual = raiz;
	while (atual != NULL){
		if (atual->valor == umValor){
			return atual;
		}
		else if (atual->valor > umValor){
			atual = atual->esquerdo;
		}
		else{
			atual = atual->direito;
		}
	}
	return atual;
}
void ArvoreB::busca(int v){
	No* resultado = buscaAux(v);
	int numeroDeNos = contaNo(v);
	if (resultado != NULL){
		cout << "Elemento encontrado:" << " " << resultado->valor << " " << "Numero de nos acessados:" << " " << numeroDeNos << endl;
	}
	else{
		cout << "Elemento nao encontrado" << " " << "Numero de nos acessados:" << " " << numeroDeNos-1 << endl;
	}
}
void ArvoreB::percorreEmOrdemAux(No* umNo){
	if (umNo != NULL){
		percorreEmOrdemAux(umNo->esquerdo);
		cout << umNo->valor << " ";
		percorreEmOrdemAux(umNo->direito);
	}
}
void ArvoreB::percorreEmOrdem(){
	percorreEmOrdemAux(raiz);
}
void ArvoreB::percorrePreOrdemAux(No* umNo){
	if (umNo != NULL){
		cout << umNo->valor << " ";
		percorrePreOrdemAux(umNo->esquerdo);
		percorrePreOrdemAux(umNo->direito);
	}
}
void ArvoreB::percorrePreOrdem(){
	percorrePreOrdemAux(raiz);
}
void ArvoreB::percorrePosOrdemAux(No* umNo){
	if (umNo != NULL){
		percorrePosOrdemAux(umNo->esquerdo);
		percorrePosOrdemAux(umNo->direito);
		cout << umNo->valor << " ";
	}
}
void ArvoreB::percorrePosOrdem(){
	percorrePosOrdemAux(raiz);
}
void ArvoreB::transplanta(No* antigo, No* novo){
	if (raiz == antigo){
		raiz = novo;
	}
	else if (antigo == antigo->pai->esquerdo){
		antigo->pai->esquerdo = novo;
	}
	else{
		antigo->pai->direito = novo;
	}
	if (novo != NULL){
		novo->pai = antigo->pai;
	}
}
void ArvoreB::remove(int umValor){
	No *remover = buscaAux(umValor);
	No *sucessor;
	if (remover == NULL){
		cerr << "No nao encontrado!" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		if (remover->esquerdo == NULL){
			transplanta(remover, remover->direito);
		}
		else if(remover->direito == NULL){
			transplanta(remover, remover->esquerdo);
		}
		else{
			sucessor = minimoAux(remover->direito);
			if (sucessor->pai != remover){
				transplanta(sucessor, sucessor->direito);
				sucessor->direito = remover->direito;
				sucessor->direito->pai = sucessor;
			}
			transplanta(remover,sucessor);
			sucessor->esquerdo = remover->esquerdo;
			sucessor->esquerdo->pai = sucessor;
		}
		delete remover;
	}
}
int main (){
	ArvoreB A1;
	int quant, valor;
	cout << "Quantos elementos deseja inserir na arvore?" << endl;
	cin >> quant;
	cout << "Insira os elementos abaixo:" << endl;
	for (int i=0; i<quant; i++){
		cin >> valor;
		A1.inserirValor(valor);
	}
	A1.percorreEmOrdem();
	cout << endl;
	cout << "Quantos valores deseja buscar na arvore?" << endl; 
	cin >> quant;
	cout << "Insira os valores que deseja buscar" << endl;
	for (int i=0; i<quant; i++){
		cin >> valor;
		A1.busca(valor);
	}


	return 0;
}
