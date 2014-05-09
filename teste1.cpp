#include <cstdio>
#include <cstdlib>

#include <list>
#include <vector>
#include <algorithm>


using namespace std;

/*
 D := Tamanho do quadrado.
 d := tamanho das subdivisões
 n := Tamanho da matriz;


*/




typedef struct ponto{
	int x;
	int y;
	int i;
} *Ponto;


int pontoVertice(Ponto p);
int** alocaMatrizQuadrada(int n);
void criaGrafo();
void criaArestas(Ponto);
void novaAresta(int, int);
float distCircular(Ponto, Ponto);


float d, D;
int n, N;
int** A;

list<int> adj[1000];
Ponto* vertices;


int main(int argc, char* argv[])
{



	D = strtof(argv[1], NULL);
	d = strtof(argv[2], NULL);
	n = D/d; /* cuidado com arredondamento */

	//adj = new list<int>[n];

	A = alocaMatrizQuadrada(n);
	N = n*n;

	//adj = new vector<int>[n];
	vertices = new Ponto[n*n];

	Ponto pteste;

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			A[i][j] = 1;
			Ponto p = (Ponto) malloc(sizeof(ponto));
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n/2 && j == n/2) pteste = p;
			vertices[p->i] = p;
		}

	criaArestas(pteste);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			printf("[%d]",A[i][j]);
		printf("\n");
	}


	return 0;
}


/*
	Numero os quadrados da matriz de forma crescente,
	da esquerda para a direita
*/

int pontoVertice(Ponto p)
{
	return n*p->y + p->x;
}

/*****************

	Retorna a menor distancia entre dois quadradinhos
	no quadrado, dentre todas as distâncias possiveis.

	Ou seja, trata a malha coo algo "circular"

*********************/

float distCircular(Ponto p1, Ponto p2)
{
	int x1 = p1->x, y1 = p1->y, x2 = p2->x, y2 = p2->y;
	float dx = x1 -x2, dy = y1 - y2;

	if(dx < 0) dx*=-1;
	if(dy < 0) dy*=-1;

	if(dx > n/2 ) // Rever
		dx = n - dx;
	if(dy > n/2) // Rever
		dy = n - dy;

	//printf("Dist: %f\n", (dx*dx + dy*dy)*d);
	return (dx*dx + dy*dy)*d;
}



/* Vai criar o grafo onde dois pontos são
	adjacentes <=> dist = 1 (com margem de erro
	devido a aproximação)

	Obs: Ordem n^4, MELHORAR.
*/

void criaGrafo()
{
	for(int i = 0; i < N; i++)
		criaArestas(vertices[i]);
}




void criaArestas(Ponto p)
{
	A[p->x][p->y] = 0;
	for(int i = 0; i < N; i++)
	{
		Ponto p2 = vertices[i];
		float dist = distCircular(p,p2);
		if(dist >= 1-d && dist <= 1+d){ // REVER
			novaAresta(p->i,p2->i);
			A[p2->x][p2->y] = 0;
		}
			// Cria aresta entre p1 e p2
	}

}


void novoArco(int v1, int v2)
{

	for (list<int>::iterator it = adj[v1].begin() ; it != adj[v1].end(); ++it)
	{
		if(*it == v2) return;
	}
	//if(find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end())
	printf("HUE\n");
	adj[v1].push_back(v2);
}



void novaAresta(int v1, int v2)
{
	novoArco(v1,v2);
	novoArco(v2,v1);
}






int** alocaMatrizQuadrada(int n)
{
	int** m;

	m =(int**) malloc(n*sizeof(int*));
	for(int i = 0; i < n; i++)
		m[i] =(int*) malloc(n*sizeof(int));

	return m;
}