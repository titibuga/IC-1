#include <cstdio>
#include <cstdlib>

#include <list>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

/*
 D := Tamanho do quadrado.
 d := tamanho das subdivisões
 n := Tamanho da matriz;


*/




typedef struct ponto{
	int x;
	int y;
	int i; // INDICE NO VETOR DE VERTICES
} *Ponto;


int pontoVertice(Ponto p);
int** alocaMatrizQuadrada(int n);
void criaGrafo();
void criaArestas(Ponto);
void novaAresta(int, int);
float distCircular(Ponto, Ponto);
void indepSet1();
void criaCircR1( float D, float d);

float d, D;
int n, N, maxTamanho;
//int** A;


vector< vector<int> > madj, A, Amax;


vector< list<int> > adj;
Ponto* vertices;





int main(int argc, char* argv[])
{


	if(argc < 4)
	{
		printf("Modo de uso: ./ep <tipo> D d ");
	}


	D = strtof(argv[2], NULL);
	d = strtof(argv[3], NULL);
	n = D/d; /* cuidado com arredondamento */

    N = n << 1;

	if(*argv[1] == 'c')
	{
		criaCircR1(D,d);
		return 0;
	}

	
	


    A.resize(n);
    Amax.resize(n);
    madj.resize(N);
    for(int i = 0; i < N; i++) madj[i].resize(N);
    
	//adj = new list<int>[n];

	//A = alocaMatrizQuadrada(n);

    for(int i =0; i < n; i++)
    {
        A[i].resize(n);
        Amax[i].resize(n);

    }
	//adj = new list<int>[n];

//	A = alocaMatrizQuadrada(n);


	//adj = new vector<int>[n];
	adj.resize(N);

	vertices = new Ponto[n*n];

	Ponto pteste;

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			A[i][j] = 0;
			Ponto p = new ponto();
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n-1 && j == 0) pteste = p;
			vertices[p->i] = p;
		}

//	criaGrafo();
    //indepSet1();
	criaArestas(pteste);
	

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			if(!Amax[i][j])printf("\033[1;31m[%d]\033[0m",Amax[i][j]);
			else printf("[%d]",Amax[i][j]);
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
	Ponto pteste;

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			A[i][j] = 0;
			Ponto p = new ponto();
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n-1 && j == 0) pteste = p;
			vertices[p->i] = p;
		}
}





float distE(Ponto p1, Ponto p2)
{
	int x1 = p1->x, y1 = p1->y, x2 = p2->x, y2 = p2->y;
	float dx = x1 -x2, dy = y1 - y2;

	return sqrt(dx*dx + dy*dy)*d;
}


void grafoR1(Ponto pc)
{
	Ponto p;
	for(int i = 0; i < N; i++)
	{
		p = vertices[i];
		A[p->x][p->y] = 1;
		float distR = distE(pc,p);
		if(distR >= 1) continue;
		for(int j = 0; j < N; i++)
		{
			Ponto p2 = vertices[j];
			float dist = distE(p,p2);
			float distR = distE(pc,p2);        
			if(distR < 1 && dist > 1-d && dist < 1+d){ //distR < 1, será?
				novaAresta(p->i,p2->i);
	            A[p2->x][p2->y] = 1;

			}
			
				// Cria aresta entre p1 e p2
		}		
	}
}


void criaCircR1( float D, float d)
{
	/*
	D = 2;
	n = D/d;
	N = n << 1;
	*/

	Ponto pteste;
	madj.resize(N);
    for(int i = 0; i < N; i++) madj[i].resize(N);
	vertices = new Ponto[N];
 	A.resize(n);
	for(int i = 0; i < n; i++) A[i].resize(n);

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			A[i][j] = 0;
			Ponto p = new ponto();
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n/2 && j == n/2) pteste = p;
			vertices[p->i] = p;
		}
	grafoR1(pteste);
	
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

	if(dx > n/2 ) // Certeza?
		dx = n - dx;
	if(dy > n/2) // Certeza?
		dy = n - dy;

	//printf("Dist: %f\n", (dx*dx + dy*dy)*d);
	return sqrt(dx*dx + dy*dy)*d;
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

	A[p->x][p->y] = 1;
	for(int i = 0; i < N; i++)
	{
		Ponto p2 = vertices[i];
		float dist = distCircular(p,p2);        
		if(dist > 1-d && dist < 1+d){ 
			novaAresta(p->i,p2->i);
            A[p2->x][p2->y] = 1;

		}
		
			// Cria aresta entre p1 e p2
	}

}


void novoArco(int v1, int v2)
{

    madj[v1][v2] = 1;
	for (list<int>::iterator it = adj[v1].begin() ; it != adj[v1].end(); ++it)
	{
		if(*it == v2) return;
	}
	//if(find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end())
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


/***************************************************
 *
 * Algoritimos para achar conjuntos independentes
 *
 *
 *
 *
 * Feitos:
 *  - Força bruta (indepSet1())
 *  - Simulates Annealing (annealing())
 ****************************************************/

//Supomos que v1 e v2 são do mesmo tamanho
// ---> Função usada em indepSet1()
int disjuntos(vector<int> v1, vector<int> v2)
{
    int tam = v1.size();

    for(int i = 0; i < tam; i++)
        if(v1[i] && v1[i] == v2[i]) return 0;
    return 1;
}


    
void indepSet1()
{
    int tam;
    Ponto p;

    p = vertices[0];
    A[p->x][p->y] = 1;
    vector<int> s(n*n);  
    vector<int> maxS(n*n);
    int j;
    for(int i = 0; i < n; i++)
        s[i] = 0;
    int N = n*n;
    maxS[0] = s[0] = 1;
    maxTamanho = 1;
    tam = 1;
    j = 1;
    while(1)
    {
//        printf("j = %d\n", j);

        if(j >= N)
        {
            while(j!=0 && !s[--j]);
            if(!j) break; // ACABOU!
            p = vertices[j];
            A[p->x][p->y] = 0;
            s[j++] = 0;
            tam--;
            continue;
        }
        p = vertices[j];
        A[p->x][p->y] = s[j] = 1;
        
        tam++;

        // Se não é mais conjunto indep, continue

        if(!disjuntos(madj[j], s))
        {
            p = vertices[j];
            A[p->x][p->y] = s[j++] = 0;
            
            tam--;
            continue;
        }

        // Se ainda é conj indep, frita
        

        if(tam > maxTamanho)
        {
            printf("NOVO TAMANHO %d\n", tam);
            maxTamanho = tam;
            maxS = s;
            Amax = A;
        }
        j++;


        

    }

    printf("%d\n", maxTamanho);

}


void solInicial(vector<int>& s)
{
	for(int i = 0; i < N; i++) s[i] = 0;

	for(int i = 0; i < N; i++)
	{
		s[i] = 1;
		if(!disjuntos(madj[i], s)) s[i] = 0;	
	}
}

int novasArestas(int v, vector<int>& s)
{
	int qtd = 0;

	for(vector<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		int u = *it;
		if(s[u]) qtd++;
	}

	return qtd;

}


void annealing(int T, float coolR)
{
	vector<int> s(N);
	vector<int> sT(N);
	int nV = 0, nVtemp = 0;
	int nA = 0, nAtemp = 0;
	int c, cTemp;

    solInicial(s);
    for(int i = 0; i < N; i++) nV += s[i];
    nVtemp = c = nV;

    while(T>1)
    {
    	int rv =  ((double) rand() / (RAND_MAX))*N;
    	sT = s; // Quanto tempo isso demora?

    	if(s[rv])
    	{
    		sT[rv] = 0; nVtemp--;
    		nAtemp -= novasArestas(rv,sT);
    	}
    	else
    	{
    		nAtemp += novasArestas(rv,sT);
    		sT[rv] = 1;
    		nVtemp++;
    	}

    	cTemp = nVtemp - nAtemp/T;
    	c = nV - nA/T;

    	if(c < cTemp || exp(((c - cTemp)*1.0)/T) > rand()/(RAND_MAX))
    	{
    		s = sT;
    		nV = nVtemp;
    		nA = nAtemp;
    	}


       	T *= 1-coolR;
    }

}


