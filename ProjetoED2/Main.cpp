#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

void testes()
{
	Grafo* g = criar(4);

	inserirVertice(g, 'A');
	inserirVertice(g, 'B');
	inserirVertice(g, 'C');
	inserirVertice(g, 'D');

	inserirAresta(g, '1', 'A', 'A', 1);
	inserirAresta(g, '2', 'B', 'B', 2);
	inserirAresta(g, '3', 'C', 'C', 3);
	inserirAresta(g, '4', 'D', 'D', 4);
	inserirAresta(g, '5', 'A', 'C', 5);
	inserirAresta(g, '6', 'X', 'Y', 9);
	
	removerAresta(g, 0, 0);

	inserirAresta(g, '8', 'A', 'A', 6);

	printAdj(g);

	printVertices(g);	
	printArestas(g);

	
}

void menu()
{
	printf("1. CV v -- Cria um vertice com o identificador v.\n\n");
	printf("2. RV v -- Remove o vertice identificado por v.\n\n");
	printf("3. CA a v1 v2 -- Cria uma aresta de peso 'p' com o identificador 'a' ligando v1 e v2.\n\n");
	printf("4. RA a -- Remove a aresta identificada por a.\n\n");
	printf("5. SVG -- Salva o grafo em arquivo texto. (Formato livre)\n\n");
	printf("6. CRG -- Carrega o grafo do arquivo texto.\n\n");
	printf("7. AM v -- Determina a arvore espalha minima a partir de v.\n\n");
	printf("8. FM -- Termina a execução do seu programa.\n\n");
}

int main()
{
	//menu();
	testes();

	printf("\n\n");
	system("PAUSE");
}
