#include <iostream>

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
		int minimoAux(No* raizSubarvore);
		int maximo();
		int maximoAux(No* raizSubarvore);
		int buscaAux(int umValor);
		void percorreEmOrdem();
		void percorreEmOrdemAux(No* umNo);
		void percorrePreOrdem();
		void percorrePreOrdemAux(No* umNo);
		void percorrePosOrdem();
		void percorrePosOrdemAux(No* umNo);
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
int ArvoreB::minimoAux(No* raizSubarvore){
	while(raizSubarvore->esquerdo != NULL){
		raizSubarvore = raizSubarvore->esquerdo;
	}
	return raizSubarvore->valor;
}
int ArvoreB::minimo(){
	int minimoNo;
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		minimoNo = minimoAux(raiz);
		return minimoNo;
	}
}
int ArvoreB::maximoAux(No* raizSubarvore){
	while(raizSubarvore->direito != NULL){
		raizSubarvore = raizSubarvore->direito;
	}
	return raizSubarvore->valor;
}
int ArvoreB::maximo(){
	int maximoNo;
	if (raiz == NULL){
		cerr << "Arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		maximoNo = maximoAux(raiz);
		return maximoNo;
	}
}
int ArvoreB::buscaAux(int umValor){
	No* atual = raiz;
	while (atual != NULL){
		if (atual->valor == umValor){
			return atual->valor;
		}
		else if (atual->valor > umValor){
			atual = atual->esquerdo;
		}
		else{
			atual = atual->direito;
		}
	}
	return atual->valor;
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
	return 0;
}
