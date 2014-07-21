#include <cstdio>
#include <cstdlib>

#include <list>
#include <vector>
#include <algorithm>
#include <cmath>

#include "EasyBMP.h"




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
	ponto(int xt,int yt,int it)
	{
		x = xt;
		y = yt;
		i = it;
	}
	ponto()
	{
		x = y = i = 0;
	}
} *Ponto;


int pontoVertice(Ponto p);
int** alocaMatrizQuadrada(int n);
void criaGrafo();
void criaArestas(Ponto);
void novaAresta(int, int);
double distCircular(Ponto, Ponto);
void indepSet1();
int criaCircR1( double D, double d);
void annealing(double T, double coolR, int iter);
int novasArestas(int v, vector<bool>& s);
void tabuSearch(int nt2, int nI, int k);
double distE(Ponto p1, Ponto p2);

double d, D;
int n, N, maxTamanho;
//int** A;


vector< vector<int> > A, Amax;

vector< vector<Ponto>  > MatrizP;
vector<int> dgr;


vector< list<int> > adj;
vector<Ponto> vertices;





int main(int argc, char* argv[])
{


	if(argc < 4)
	{
		printf("Modo de uso: ./ep <tipo> D d ");
	}


	D = strtof(argv[2], NULL);
	d = strtof(argv[3], NULL);
	n = D/d; /* cuidado com arredondamento */

    N = n*n;
    A.resize(n);
    Amax.resize(n);
    MatrizP.resize(n);
    dgr.resize(N);
    adj.resize(N);

	vertices.resize(N);

  
    for(int i =0; i < n; i++)
    {
        A[i].resize(n);
        Amax[i].resize(n);
        MatrizP[i].resize(n);

    }

    for(int i = 0; i < n; i++)
    	for(int j = 0; j < n; j++)
    		A[i][j] = Amax[i][j] = 0;

//////////////////////////////////////////////////////////////////////////////////////////
	if(*argv[1] == 'c')
	{
		printf("Criando Grafo...\n");

		int N2 = criaCircR1(D,d);
		printf("Achando conjunto independente...\n");
		int temp = N;
		N = N2;
		//annealing(100000,0.001,500);
		tabuSearch(20,500,70);
		N = temp;
		/*
		Ponto ph1 = vertices[130];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
			{
				Ponto ph2 = MatrizP[i][j];
				float disth = distE(ph1,ph2);
				if(disth >= 1-d && disth <= 1+d) Amax[i][j] = 1;
				else Amax[i][j] = 0;
				if(ph2 == ph1) Amax[i][j] = 1;

			}	
		*/
		printf("Criando imagem....\n");

		BMP img;
	
		img.SetSize(1000,1000);
		// Set its color depth to 32-bits
		img.SetBitDepth(32);

		// Set one of the pixels
		img(14,18)->Red = 255;
		img(14,18)->Green = 255;
		img(14,18)->Blue = 255;
		img(14,18)->Alpha = 0;

		int tam = 1000*(d/D);

		

		int cor;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(!Amax[i][j])
					if(MatrizP[i][j]->i < N2) cor = 255;
					else cor = 100;
				else 
					if(MatrizP[i][j]->i < N2) cor = 0;
					else cor = 10;


				// printf("[%d]",Amax[i][j]);

				for(int i2 = i*tam; i2 < i*tam + tam; i2++)
					for(int j2 = tam*j; j2 < tam*j + tam; j2++)
					{
						img(i2,j2)->Red = cor;
						img(i2,j2)->Green = cor;
						img(i2,j2)->Blue = cor;
						img(i2,j2)->Alpha = 0;
					}

			}
		}

		img.WriteToFile("Output.bmp");
		return 0;
		
		//printf("\n");
	}

	

///////////////////////////////////////////////////////////////////////////////////////////////////	

	
	


	//adj = new list<int>[n];

//	A = alocaMatrizQuadrada(n);


	//adj = new vector<int>[n];
	

	Ponto pteste;
	printf("Criando pontos...\n");

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			A[i][j] = 0;
			Ponto p = new ponto();
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n-1 && j == 0) pteste = p;
			vertices[p->i] = p;
			dgr[p->i] = 0;
			MatrizP[i][j] = p;
		}

	printf("Criando grafo...\n");

	criaGrafo();

	int v = pteste->i;
	int xv = pteste->x, yv = pteste->y;

	for(list<int>::iterator it = adj[0].begin(); it != adj[0].end(); ++it)
	{
		int u = *it;
		Ponto p = vertices[u];
		int xu = p->x, yu = p->y;
		printf("DeltaX: %d | DeltaY: %d \n ", xv-xu, yv-yu);
	}



	printf("Achando conjunto independente....\n");
	annealing(100000,0.001,500);
	//tabuSearch(nt2,ni,k);
	//tabuSearch(20,500,70);
    //indepSet1();

	
	BMP img;
	
	img.SetSize(1000,1000);
	// Set its color depth to 32-bits
	img.SetBitDepth(32);

	// Set one of the pixels
	img(14,18)->Red = 255;
	img(14,18)->Green = 255;
	img(14,18)->Blue = 255;
	img(14,18)->Alpha = 0;

	int tam = 1000*(d/D);

	

	int cor;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(!Amax[i][j]) cor = 255;
				//printf("\033[1;31m[%d]\033[0m",Amax[i][j]);
			else cor = 0;
			// printf("[%d]",Amax[i][j]);

			for(int i2 = i*tam; i2 < i*tam + tam; i2++)
				for(int j2 = tam*j; j2 < tam*j + tam; j2++)
				{
					img(i2,j2)->Red = cor;
					img(i2,j2)->Green = cor;
					img(i2,j2)->Blue = cor;
					img(i2,j2)->Alpha = 0;
				}

		}

		
		//printf("\n");
	}

	
	img.WriteToFile("Output.bmp");

    
	return 0;
}


/*
	Numero os quadrados da matriz de forma crescente,
	da esquerda para a direita
*/

int pontoVertice(Ponto p)
{
	return n*p->y + p->x;
	/*
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
		*/
}





double distE(Ponto p1, Ponto p2)
{
	int x1 = p1->x, y1 = p1->y, x2 = p2->x, y2 = p2->y;
	double dx = x1 -x2, dy = y1 - y2;

	return sqrt(dx*dx + dy*dy)*d;
}

/*
void grafoR1(Ponto pc)
{
	Ponto p;
	for(int i = 0; i < N; i++)
	{
		p = vertices[i];
		A[p->x][p->y] = 1;
		double distR = distE(pc,p);
		if(distR >= 1-d) continue;
		for(int j = 0; j < N; i++)
		{
			Ponto p2 = vertices[j];
			double dist = distE(p,p2);
			double distR = distE(pc,p2);        
			if(distR < 1-d && dist > 1-d && dist < 1+d){ //distR < 1, será?
				novaAresta(p->i,p2->i);
	            A[p2->x][p2->y] = 1;

			}
			
				// Cria aresta entre p1 e p2
		}		
	}
}
*/


void criaArestas2(Ponto p)
{

	A[p->x][p->y] = 1;
	for(int i = 0; i < N; i++)
	{
		Ponto p2 = vertices[i];
		double dist = distE(p,p2);        
		if(dist > 1-d && dist < 1+d){ 
			novaAresta(p->i,p2->i);
            A[p2->x][p2->y] = 1;

		}
		
			// Cria aresta entre p1 e p2
	}

}


void grafoR1(Ponto pc)
{
	list<Ponto> deltas;
	for(int i = 0; i < N; i++)
		criaArestas2(vertices[i]);
	
	
}



int criaCircR1( double D, double d)
{
	/*
	D = 2;
	n = D/d;
	N = n << 1;
	*/

	Ponto pteste;
	/*madj.resize(N);
    for(int i = 0; i < N; i++) madj[i].resize(N);*/
	vertices.resize(N);
 	A.resize(n);
	for(int i = 0; i < n; i++) A[i].resize(n);

	for(int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
		{
			Amax[i][j] = A[i][j] = 0;
			Ponto p = new ponto();
			p->x = j; p->y = i; p->i = pontoVertice(p);
			if(i == n/2 && j == n/2) pteste = p;
			vertices[p->i] = p;
			MatrizP[i][j] = p;			

		}
	
	int i = 0, j = N-1;
	while(i <= j)
	{
		Ponto p = vertices[i];
		if(distE(p,pteste) >= 1-d) // Fora da bola aberta
		{
			vertices[i]->i = j;
			vertices[j]->i = i;
			vertices[i] = vertices[j];
			vertices[j--] = p;
		}
		else i++;
	}
	int Nantigo = N;
	N = j + 1;

	grafoR1(pteste);

	N = Nantigo;
	return j+1;
	
}



/*****************

	Retorna a menor distancia entre dois quadradinhos
	no quadrado, dentre todas as distâncias possiveis.

	Ou seja, trata a malha coo algo "circular"

*********************/

double distCircular(Ponto p1, Ponto p2)
{
	int x1 = p1->x, y1 = p1->y, x2 = p2->x, y2 = p2->y;
	double dx = x1 -x2, dy = y1 - y2;

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


*/

void criaGrafo()
{/*
	for(int i = 0; i < N; i++)
		criaArestas(vertices[i]);*/
	list<Ponto> deltas;

	criaArestas(vertices[0]);
	Ponto p1,p2;
	p1 = vertices[0];
	int v = p1->i;
	int xv = p1->x, yv = p1->y;

	for(list<int>::iterator it = adj[v].begin(); it != adj[v].end(); ++it)
	{
		int u = *it;
		Ponto p2 = vertices[u];
		int xu = p2->x, yu = p2->y;
		deltas.push_back( new ponto(xv-xu, yv-yu, 0));
	}


	printf("Progresso:\n0%%\n");
	int perc = 1;
	for(int i = 1; i < N; i++)
	{
		p1 = vertices[i];
		
		if((i*1.0)/N > (perc*1.0)/100.0){ printf("%d%%\n", perc); perc+=1;}
		//	printf("V: %d n: %d \n", i,N);
		for(list<Ponto>::iterator it = deltas.begin(); it != deltas.end(); ++it)
		{
			Ponto delta = *it;
			xv = p1->x + delta->x;
			yv = p1->y + delta->y;

			if(xv < 0) xv += n;
			if(yv < 0) yv += n;

			p2 = MatrizP[yv][xv];

			novaAresta(p1->i, p2->i);
			double dist = distCircular(p1,p2);
			if(!(dist > 1-d && dist < 1+d)) printf("Problema\n");
		}
	
		
	}
}


   

void criaArestas(Ponto p)
{

	A[p->x][p->y] = 1;
	for(int i = 0; i < N; i++)
	{
		Ponto p2 = vertices[i];
		double dist = distCircular(p,p2);        
		if(dist > 1-d && dist < 1+d){ 
			novaAresta(p->i,p2->i);
            A[p2->x][p2->y] = 1;

		}
		
			// Cria aresta entre p1 e p2
	}

}


void novoArco(int v1, int v2)
{

   // madj[v1][v2] = 1;
	for (list<int>::iterator it = adj[v1].begin() ; it != adj[v1].end(); ++it)
	{
		if(*it == v2) return;
	}
	//if(find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end())
	adj[v1].push_back(v2);
	dgr[v1]++;
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
    vector<bool> s(n*n);  
    vector<bool> maxS(n*n);
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
        if(novasArestas(j,s)) // Se não é mais conjunto indep, pula
        {
        	j++;
        	continue;
        }


        p = vertices[j];
        A[p->x][p->y] = s[j] = 1;
        
        tam++;

        
/*
        if(!disjuntos(madj[j], s))
        {
            p = vertices[j];
            A[p->x][p->y] = s[j++] = 0;
            
            tam--;
            continue;
        }*/

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


void solInicial(vector<bool>& s)
{
	for(int i = 0; i < N; i++) s[i] = 0;
/*
	for(int i = 0; i < N; i++)
		if(!novasArestas(i,s)) s[i] = 1;*/
}

int novasArestas(int v, vector<bool>& s)
{
	int qtd = 0;

	for(list<int>::iterator it = adj[v].begin(); it != adj[v].end(); ++it)
	{
		int u = *it;
		if(s[u]) qtd++;
	}

	return qtd;

}


void annealing(double T, double coolR, int iter)
{
	vector<bool> s(N);
	vector<bool> sT(N);
	vector<bool> sMax(N);
	int nV = 0, nVtemp = 0;
	int nA = 0, nAtemp = 0;
	int tMax = 0;
	int c, cTemp ,cAnt;
	int cMax = -1;
	int nAmax;

    solInicial(s);
    sMax = s;
    for(int i = 0; i < N; i++) nV += s[i];
    nVtemp = c = nV;
	tMax = nV;
	cMax = nV;


   	do
    {
    	cAnt = cMax;
    	for(int i = 0; i < iter; i++)
    	{
	    	int rv =  ((double) 1.0*rand() / (RAND_MAX))*N;
	    	sT = s; // Quanto tempo isso demora?
	    	nVtemp = nV;
	    	nAtemp = nA;

	    //	printf("Vértice: %d || nA = %d\n", rv, nA);

	    	//printf("Calculando....");

	    	if(sT[rv])
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
	    	//printf("Pronto!\n");

	    	double b;
	    	int a;
	    	if(c < cTemp ||  (a = (exp(((cTemp-c)*1.0)/T) > (rand()*1.0)/(RAND_MAX) )) )
	    	{
	    		//printf("%d\n",a);
	    		s = sT;
	    		nV = nVtemp;
	    		nA = nAtemp;
	    		//printf("nV: %d nA: %d c: %d || nVtemp: %d nAtemp: %d c: %d\n",nV,nA,c,nVtemp,nAtemp, cTemp);
	    		//printf("Teste1: %d || Delta:%d a: %f b: %f\n",c < cTemp,c-cTemp,a,b);
	    		cMax = tMax - nAmax/T;
	    		if(/*nA < 1000 && nV > tMax*/c > cMax)
	    		{
	    			
	    			tMax = nV;
	    			sMax = s;
	    			cMax = c;
	    			nAmax = nA;
	    		}
	    	}
	    }




       	T *= (1.0-coolR);
       	//printf("Vai\n");

    } while(T > 1 || nAmax != 0);
    for(int i = 0; i < N; i++)
		if(!novasArestas(i,sMax))
		{
			sMax[i] = 1;
			tMax++;
		}

    printf("tMax: %d nV: %d\n",tMax, nV);

    tMax = 0;
    for(int i = 0; i < N; i++)
    {
    	tMax += sMax[i];
    	Ponto p = vertices[i];
    	if(sMax[i])
       		Amax[p->x][p->y] = 1;
       	else
       		Amax[p->x][p->y] = 0;
   
    }
    printf("tMax: %d || N: %d\n",tMax,N);

}


void tabuSearch(int nt2, int nI, int k)
{
	vector<bool> s(N);
	//vector<bool> sTemp(N);
	vector<bool> sMax(N);

	list<int> sIn;
	int t = 0;

	int tMax = 0;

//	list<vector<bool> > T1; // Lista de soluções Tabu
	list<int> T2; // Lista de adições tabu
	list<int> vS; //Lista dos vértices em S




	for(int itr = 0; itr < nI; itr++)
	{

		//Procura vértice para aumentar o conj indep
		int dgrMin = (1 <<30);
		int v = -1;
		printf("[%d]", t);
		for(int i = 0; i < N; i++)
		{
			if(s[i]) continue;
			list<int>::iterator it = find(T2.begin(), T2.end(), i);
			if(it != T2.end()) continue; //TABU
			if(novasArestas(i,s)) continue;
			if(dgr[i] < dgrMin)
			{
				v = i;
				dgrMin = dgr[i];
			}

		}

		if(v != -1)
		{
			s[v] = 1;
			/****
				No papaer, a ideia original era verificar 
				em uma lista de tabus T1 de soluções ja visitadas
				recentemente. Não vou tentar isso agora por motivos
				de eficiência

			****/

			vS.push_back(v);
			t++;
			
			if(t > tMax)
			{
				sMax = s;
				tMax = t;
				printf("\nMelhorou: %d\n", tMax);
				itr = 0;	
			}
		}
		else
		{

			/*
			int dgrMax = 0;
			for(int i = 0; i < N; i++)
			{
				if(!s[i]) continue;
				if(dgr[i] > dgrMax)
				{
					v = i;
					dgrMax = dgr[i];
				}

			}
			*/

			/****
				No papaer, a ideia original era verificar 
				em uma lista de tabus T1 de soluções ja visitadas
				recentemente. Não vou tentar isso agora por motivos
				de eficiência

				No lugar farei min{k,|S|} deleções aleatórias

			****/

			int k2 = t < k2? t : k2;
			for(int i = 0; i < k2; i++)
			{
				list<int>::iterator it = vS.begin();
				advance(it, vS.size()*((rand()*1.0)/(RAND_MAX)));
				int v = *it;

				s[v] = 0;
				t--;
				T2.push_back(v);
				if(T2.size() > nt2) T2.pop_front();
			}
		}


	}


    printf("tMax: %d",tMax);

    tMax = 0;
    for(int i = 0; i < N; i++)
    {
    	tMax += sMax[i];
    	Ponto p = vertices[i];
    	if(sMax[i])
       		Amax[p->x][p->y] = 1;
       	else
       		Amax[p->x][p->y] = 0;
   
    }
    printf("tMax: %d || N: %d\n",tMax,N);
}


