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
void criaArestas(int,int);
void novaAresta(int, int);
float distCircular(int,int,int,int);


float d, D;
int n;
int** A;

vector<int>* adj;
vecotr< vector<int> > madj;



int main(int argc, char* argv[])
{


	D = strtof(argv[1], NULL);
	d = strtof(argv[2], NULL);
	n = D/d; /* cuidado com arredondamento */

	A = alocaMatrizQuadrada(n);
    madj.resize(n);
    for(int i = 0; i < n; i++)
    {
        madj[i].resize(n);
        for(int j = 0; j < n; j++)
            madj[i][j] = 0;
    }
	adj =(vector<int>*) malloc(n*sizeof(vector<int>));


	return 0;
}


/*
	Numero os quadrados da matriz de forma crescente,
	da esquerda para a direita
*/

int pontoVertice(int x, int y)
{
	return n*y + x;
}

/*****************

	Retorna a menor distancia entre dois quadradinhos
	no quadrado, dentre todas as distâncias possiveis.

	Ou seja, trata a malha coo algo "circular"

*********************/

float distCircular(int x1, int y1, int x2, int y2)
{
	float dx = x1 -x2, dy = y1 - y2;

	if(dx > n/2 ) // Rever
		dx = n - dx;
	if(dy > n/2) // Rever
		dy = n - dy;

	return (dx*dx + dy*dy)*d;
}



/* Vai criar o grafo onde dois pontos são
	adjacentes <=> dist = 1 (com margem de erro
	devido a aproximação)

	Obs: Ordem n^4, MELHORAR.
*/

void criaGrafo()
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			criaArestas(i,j);
}




void criaArestas(int x, int y)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j <  n; j++)
		{
			float dist = distCircular(x,y,i,j);
			if(dist >= 1 && dist <= 1+d) // REVER
				novaAresta(pontoVertice(x,y),pontoVertice(i,j));

				// Cria aresta entre (x,y) e (i,j)
		}

}


void novoArco(int v1, int v2)
{
	//Falta verificar de v1->v2 ja existe
	ajd[v1].push_back(v2);

    madj[v1][v2] = 1;
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


/***************************************************
 *
 * Algoritimos para achar conjuntos independentes
 *
 *
 *
 *
 * Feitos:
 *  - Força bruta (indepSet1())
 ****************************************************/

//Supomos que v1 e v2 são do mesmo tamanho
// ---> Função usada em indepSet1()
int disjuntos(vector<int> v1, vector<int> v2)
{
    int tam = v1.size();

    for(int i = 0; i < tam; i++)
}


    
void indepSet1()
{
    vector<int> s(n);   
    int j;
    for(int i = 0; i < n; i++)
        s[i] = 0;

    s[j] = 1;
    while(1)
    {
        s[j] = 1;


        // se ainda é conjunto indep, frita

        if(disjuntos(madj[v], s))
        {
        }
    }

}



