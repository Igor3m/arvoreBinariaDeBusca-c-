#include <iostream>
#include <cstdlib>

using namespace std;
class No{
	friend class ArvoreB;
	private:
		int valor;
		No esquerdo;
		No direito;
		No pai;
	public:
		No(int v);
		No(int v, No esq, No dir, No p);
};
No::No(int v){
	valor = v;
	esquerdo = NULL;
	direito = NULL;
	pai = NULL;
}
No::No(int v, No esq, No dir, No p){
	valor = v;
	esquerdo = esq;
	direito = dir;
	pai = p;
}


class ArvoreB{
	private:
		No* raiz;
	public:
		ArvoreB();
		void inserirValor(int umValor);
		int minimo();
		No minimoAux(No* raizSubarvore);
		int maximo();
		No maximoAux(No* raizSubarvore);
		No buscaAux(int umValor);
		void percorreEmOrdem();
		void percorreEmOrdemAux(No* umNo);
		void percorrePreOrdem();
		void percorrePreOrdemAux(No* umNo);
		void percorrePosOrdem();
		void percorrePosOrdemAux(No* umNo);
		void transplanta(No* antigo, No* novo);
		void remove(int umValor);
};
ArvoreB::ArvoreB(){
	raiz = NULL;
}
void ArvoreB::inserirValor(int umValor){
	No* novo = new No(umValor);
	No* atual;
	No* anterior;
	if (raiz == NULL){
		raiz = novo;
	}
	else{
		atual = raiz;
		while (atual != NULL){
			anterior = atual;
			if (atual->valor > umValor){
				atual = atual->esquerdo;
			}
			else{
				atual = atual->direito;
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
}
No ArvoreB::minimoAux(No* raizSubarvore){
	No* aux = raizSubarvore;
	while(aux->esquerdo != NULL){
		aux = aux->esquerdo;
	}
	return* aux;
}
int ArvoreB::minimo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No minimoNo = minimoAux(raiz);
		return minimoNo.valor;
	}
}
No ArvoreB::maximoAux(No* raizSubarvore){
	while(raizSubarvore->direito != NULL){
		raizSubarvore = raizSubarvore->direito;
	}
	return* raizSubarvore;
}
int ArvoreB::maximo(){
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		No maximoNo = maximoAux(raiz);
		return maximoNo.valor;
	}
}
No ArvoreB::buscaAux(int umValor){
	No* atual = raiz;
	while (atual != NULL){
		if (atual->valor == umValor){
			return* atual;
		}
		else if (atual->valor > umValor){
			atual = atual->esquerdo;
		}
		else{
			atual = atual->direito;
		}
	}
	atual->valor = 0;
	return* atual;
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
	No* remove = new No();
}
int main (){
	ArvoreB A1;
	int valor;
	for (int i=0; i<6; i++){
		cin >> valor;
		A1.inserirValor(valor);
	}
	cout << A1.minimo() << endl;
	cout << A1.maximo() << endl;
	A1.percorreEmOrdem();
	cout << endl;
	A1.percorrePreOrdem();
	cout << endl;
	A1.percorrePosOrdem();
	cout << endl;
	A1.remove(18);
	A1.percorreEmOrdem();
	return 0;
}
