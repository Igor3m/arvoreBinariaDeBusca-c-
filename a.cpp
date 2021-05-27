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
int main(){
	return 0;
}
