#include <cstdio>
#include <cstdlib>
#include <vector>


using namespace std;

/*
 D := Tamanho do quadrado.
 d := tamanho das subdivisões
 n := Tamanho da matriz;


*/

int** alocaMatrizQuadrada(int n);
void criaGrafo();


float d, D;
int n;
int** A;


int main(int argc, char* argv[])
{


	D = strtof(argv[1]);
	d = strtof(argv[2]);
	n = D/d; /* cuidado com arredondamento */

	A = alocaMatrizQuadrada(n);


	return 0;
}


/*
	Numero os quadrados da matriz de forma crescente,
	da esq

*/

int pontoVertice(int x, int y)
{
	return n*y + x;
}

float distCircular(int x1, int y1, int x2, int y2)
{
	float dx = x1 -x2, dy = y1 - y2;

	if(dx > )

	return dx*dx + dy*dy
}



/* Vai criar o grafo onde dois pontos são
	adjacentes <=> dist = 1 (com margem de erro
	devido a aproximação)
*/

void criaGrafo()
{

}



int** alocaMatrizQuadrada(int n)
{
	int** m;

	m = malloc(n*sizeof(int*));
	for(int i = 0; i < n; i++)
		m = malloc(n*sizeof(int));

	return m;
}