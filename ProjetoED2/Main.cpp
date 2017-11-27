#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

void testes()
{
	/*Grafo* g = criar(4);

	inserirVertice(g, 'A');
	inserirVertice(g, 'B');
	inserirVertice(g, 'C');
	inserirVertice(g, 'D');

	inserirAresta(g, '1', 'A', 'A', 1);
	inserirAresta(g, '2', 'B', 'B', 2);
	inserirAresta(g, '3', 'C', 'C', 3);
	inserirAresta(g, '4', 'D', 'D', 4);
	inserirAresta(g, '5', 'A', 'C', 5);

	salvar(g, "arquivo.txt");*/

	Grafo* g = carregar("arquivo.txt");

	printVertices(g);
	printArestas(g);
	printAdj(g);
}

void menu()
{
	printf("1. CV v -- Cria um vertice com o identificador v.\n\n");
	printf("2. RV v -- Remove o vertice identificado por v.\n\n");
	printf("3. CA a v1 v2 p -- Cria uma aresta de peso 'p' com o identificador 'a' ligando v1 e v2.\n\n");
	printf("4. RA a -- Remove a aresta identificada por a.\n\n");
	printf("5. SVG -- Salva o grafo em arquivo texto. (Formato livre)\n\n");
	printf("6. CRG -- Carrega o grafo do arquivo texto.\n\n");
	printf("7. AM v -- Determina a arvore espalha minima a partir de v.\n\n");
	printf("8. FM -- Termina a execução do seu programa.\n\n");	
}

int main()
{
	menu();
	//testes();

	Grafo* g = criar(5);
	char command[100];	
	while (true)
	{
		//menu();
		system("CLS");
		printf("Digite o comando: ");
		scanf_s("%s", command, 100);

		if (!strcmp(command, "CV")) // OK
		{	
			char id;
			printf("Digite o identificador do vertice: ");			
			scanf_s(" %c", &id, 1);			
			inserirVertice(g, id);
			printVertices(g);
		}
		else if (!strcmp(command, "RV")) // OK
		{
			char id;
			printf("Digite o identificador do vertice: ");
			scanf_s(" %c", &id, 1);
			removerVertice(g, id);
			printVertices(g);
		}
		else if (!strcmp(command, "CA")) // OK
		{
			char id, v1, v2;
			int peso;
			printf("Digite o identificador da aresta: ");
			scanf_s(" %c", &id, 1);
			printf("Digite o identificador do vertice de origem: ");
			scanf_s(" %c", &v1, 1);
			printf("Digite o identificador do vertice de destino: ");
			scanf_s(" %c", &v2, 1);
			printf("Digite o peso da aresta: ");
			scanf("%d", &peso);
			inserirAresta(g, id, v1, v2, peso);
			printArestas(g);
		}
		else if (!strcmp(command, "RA")) // OK
		{
			char id;			
			printf("Digite o identificador da aresta: ");
			scanf_s(" %c", &id, 1);
			removerAresta(g, id);
			printArestas(g);
		}
		else if (!strcmp(command, "SVG")) // OK
		{
			char filename[100];
			printf("Digite o nome do arquivo para salvar o grafo atual: ");
			scanf_s("%s", filename, 100);
			salvar(g, filename);
		}
		else if (!strcmp(command, "CRG")) // OK
		{
			char filename[100];
			printf("Digite o nome do arquivo para carregar o grafo: ");
			scanf_s("%s", filename, 100);
			
			g = carregar(filename);

			if (g != NULL) {
				printVertices(g);
				printArestas(g);
				printAdj(g);
			}
		}
		else if (!strcmp(command, "AM")) // ALGORITMO DE PRIM/KRUSKAL
		{

		}
		else if (!strcmp(command, "FM")) // OK
		{
			finalizar(g);
		}
		else
		{
			printf("Opcao Invalida.\n");
		}

		printf("\n\n");
		system("PAUSE");
	}

	printf("\n\n");
	system("PAUSE");
}
