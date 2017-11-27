#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define debug

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

/*

A matriz mostrará a relação dos N vértices do grafo.
O valor zero (0) significa que não há ligação entre dois vértices.
Qualquer valor diferente de zero (0) indicará uma ligação entre os dois vértices, onde o valor representado na matriz será o peso da aresta.

*/

struct vertice {
	Vertice* ant;
	char nome;
	int valor;
};

struct aresta {
	char nome;
	int peso;
	int orig;
	int dest;
};

struct grafo {
	Vertice** vertices;
	Aresta** arestas;
	int **adj;
	int num_vertices;
	int num_arestas;
	int ocup_vertices;
	int ocup_arestas;
};

Grafo* carregar(char* arquivo)
{
	Grafo* g = NULL;
	FILE* file = fopen(arquivo, "r+");
	if (file == NULL) {
		printf("Arquivo invalido.\n");
		return NULL;
	}

	int lineIndex = 0;
	char* paramSeparator = ",";
	char* objectSeparator = ";";
	char line[1000];	

	int ocup_vertices = 0, ocup_arestas = 0, num_vertices = 0, num_arestas = 0;

	while (fgets(line, sizeof(line), file) != NULL)
	{
		switch (lineIndex)
		{
			case 0: // Linha 1: dados do grafo.
			{
				char* content = strtok(line, paramSeparator);
				int strtokIndex = 0;				
				while (content != NULL)
				{					
					if (strtokIndex == 0) ocup_vertices = atoi(content);
					else if (strtokIndex == 1) ocup_arestas = atoi(content);
					else if (strtokIndex == 2) num_vertices = atoi(content);
					else if (strtokIndex == 3) num_arestas = atoi(content);
					content = strtok(NULL, paramSeparator);
					strtokIndex++;
				}				
				g = criar(num_vertices);
				g->ocup_vertices = ocup_vertices;
				g->ocup_arestas = ocup_arestas;
				g->num_vertices = num_vertices;
				g->num_arestas = num_arestas;				
				g->arestas = (Aresta**)malloc(sizeof(Aresta*) * num_arestas);
				for (int a = 0; a < num_arestas; a++)
				{
					g->arestas[a] = (Aresta*)malloc(sizeof(Aresta));
					g->arestas[a] = NULL;
				}
				break;
			}
			case 1: // Linha 2: dados dos vértices.
			{
				g->vertices = (Vertice**)malloc(sizeof(Vertice*) * num_vertices);
				int vindex = 0;
				char* objectContext = NULL;
				char* paramContext = NULL;
				char* verticeData = strtok_s(line, objectSeparator, &objectContext);
				while (verticeData != NULL)
				{
					char identificador = '0';
					char* verticeObject = strtok_s(verticeData, paramSeparator, &paramContext);
					int peso = 0;
					int verticeDataIndex = 0;
					
					while (verticeObject != NULL) // Identificador , Peso.
					{						
						if (verticeDataIndex == 0)
						{
							identificador = verticeObject[0];
						}
						else if (verticeDataIndex == 1)
						{
							peso = atoi(verticeObject);
						}
						verticeDataIndex++;
						verticeObject = strtok_s(NULL, paramSeparator, &paramContext);
					}					
					g->vertices[vindex] = (Vertice*)malloc(sizeof(Vertice));
					g->vertices[vindex]->nome = identificador;
					g->vertices[vindex]->valor = peso;
					verticeData = strtok_s(NULL, objectSeparator, &objectContext);					
					vindex++;
				}				
				break;
			}
			case 2: // Linha 3: dados das arestas.
			{
				char identificador = '0';
				int aindex = 0;
				int peso = 0;
				int origem = 0;
				int destino = 0;
				char* objectContext = NULL;
				char* paramContext = NULL;
				char* arestaData = strtok_s(line, objectSeparator, &objectContext);
				
				while (arestaData != NULL)
				{
					char* arestaObject = strtok_s(arestaData, paramSeparator, &paramContext);
					int arestaDataIndex = 0;
					while (arestaObject != NULL)
					{
						if (arestaDataIndex == 0) identificador = arestaObject[0];
						else if (arestaDataIndex == 1) peso = atoi(arestaObject);
						else if (arestaDataIndex == 2) origem = atoi(arestaObject);
						else if (arestaDataIndex == 3) destino = atoi(arestaObject);
						arestaObject = strtok_s(NULL, paramSeparator, &paramContext);
						arestaDataIndex++;
					}
					g->arestas[aindex] = (Aresta*)malloc(sizeof(Aresta));
					g->arestas[aindex]->nome = identificador;
					g->arestas[aindex]->peso = peso;
					g->arestas[aindex]->orig = origem;
					g->arestas[aindex]->dest = destino;
					arestaData = strtok_s(NULL, objectSeparator, &objectContext);
					aindex++;
				}
				
				for (int a = 0; a < num_arestas; a++)
				{					
					if (g->arestas[a] != NULL)
					{
						int orig = g->arestas[a]->orig;
						int dest = g->arestas[a]->dest;
						int peso = g->arestas[a]->peso;
						g->adj[orig][dest] = peso;						
					}
				}
				break;
			}
		}
		lineIndex++;
	}

	fclose(file);
	return g;
}

void salvar(Grafo* g, char* arquivo) // OK
{
	if (g != NULL)
	{
		char* grafoData = (char*)malloc(sizeof(char) * 300);
		char* verticeData = (char*)malloc(sizeof(char) * 1000);
		char* arestaData = (char*)malloc(sizeof(char) * 1000);

		// Formato: OCUP_VERT, OCUP_ARES, CAPACIDADE_VERTICES, CAPACIDADE_ARESTAS.
		sprintf(grafoData, "%d,%d,%d,%d\n", g->ocup_vertices, g->ocup_arestas, g->num_vertices, g->num_arestas);	
		
		// Inicializando linhas de dados.
		strcpy(verticeData, "");
		strcpy(arestaData, "");

		// Formato: IDENTIFICADOR,VALOR;
		for (int a = 0; a < g->num_vertices; a++)
		{
			if (g->vertices[a] != NULL)
			{
				printf("%d to %d\n", a, g->num_vertices);
				if (a == g->num_arestas - 2)
					sprintf(verticeData, "%s%c,%d", verticeData, g->vertices[a]->nome, g->vertices[a]->valor);				
				else
					sprintf(verticeData, "%s%c,%d;", verticeData, g->vertices[a]->nome, g->vertices[a]->valor);				
			}
		}

		// Formato: IDENTIFICADOR,PESO,ORIGEM,DESTINO;
		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] != NULL)
			{
				if (a == g->num_arestas - 1)
					sprintf(arestaData, "%s%c,%d,%d,%d", arestaData, g->arestas[a]->nome, g->arestas[a]->peso, g->arestas[a]->orig, g->arestas[a]->dest);
				else
					sprintf(arestaData, "%s%c,%d,%d,%d;", arestaData, g->arestas[a]->nome, g->arestas[a]->peso, g->arestas[a]->orig, g->arestas[a]->dest);
			}
		}

		sprintf(verticeData, "%s\n", verticeData);
		sprintf(arestaData, "%s", arestaData);
		
		FILE* file = fopen(arquivo, "a");
		fprintf(file, "%s%s%s", grafoData, verticeData, arestaData);
		fclose(file);
	}
}

void finalizar(Grafo* g)
{
	if (g != NULL)
	{
		// Desalocar tudo.
	}
}

Grafo* criar(int num_vertices) // OK.
{
	Grafo* g = (Grafo*)malloc(sizeof(Grafo));
	g->adj = (int**)malloc(sizeof(int*) * num_vertices);
	g->num_vertices = num_vertices;
	g->num_arestas = num_vertices;
	g->ocup_vertices = 0;
	g->ocup_arestas = 0;
	g->vertices = (Vertice**)malloc(sizeof(Vertice*) * num_vertices);
	g->arestas = (Aresta**)malloc(sizeof(Aresta*) * num_vertices);

	for (int a = 0; a < num_vertices; a++)
	{
		g->adj[a] = (int*)malloc(sizeof(int) * num_vertices);
		g->vertices[a] = NULL;
		g->arestas[a] = NULL;

		for (int b = 0; b < g->num_vertices; b++) {
			g->adj[a][b] = 0;
		}
	}

	#ifdef debug
	printf("Criou um grafo com %d slots.\n\n", num_vertices);
	#endif
	return g;
}

Vertice* getVertice(Grafo* g, char nome) // OK.
{
	if (g != NULL)
	{
		for (int a = 0; a < g->num_vertices; a++)
		{
			if (g->vertices[a]->nome == nome) return g->vertices[a];
		}
	}

	return NULL;
}

int getVerticeIndex(Grafo* g, char nome) // OK.
{
	if (g != NULL)
	{
		for (int a = 0; a < g->num_vertices; a++)
		{
			if (g->vertices[a] != NULL) {
				if (g->vertices[a]->nome == nome) return a;
			}
		}
	}

	return -1;
}

int getArestaIndex(Grafo* g, char nome)
{
	if (g != NULL)
	{
		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] != NULL) {
				if (g->arestas[a]->nome == nome) return a;
			}
		}
	}

	return -1;
}

Aresta* getAresta(Grafo* g, char nome)
{
	if (g != NULL)
	{
		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] != NULL) {
				if (g->arestas[a]->nome == nome) return g->arestas[a];
			}
		}
	}
	return NULL;
}

void printAdj(Grafo* g) // OK.
{
	if (g != NULL)
	{
		printf("\n---------\n\n");
		for (int a = 0; a < g->num_vertices; a++)
		{
			for (int b = 0; b < g->num_vertices; b++)
			{
				int cell = g->adj[a][b];
				printf("%d ", cell);
			}

			printf("\n");
		}
		printf("\n---------\n\n");
	}
}

void printVertices(Grafo* g) // OK.
{
	if (g != NULL)
	{
		printf("Lista de vertices: ");
		for (int a = 0; a < g->num_vertices; a++)
		{			
			if (g->vertices[a] != NULL) {
				printf("%c ", g->vertices[a]->nome);
			}
		}
		printf("\n\n");
	}
}

void printArestas(Grafo* g) // OK.
{
	if (g != NULL)
	{
		printf("Lista de arestas: ");
		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] != NULL) {
				printf("%c (peso: %d) ", g->arestas[a]->nome, g->arestas[a]->peso);
			}
		}
		printf("\n\n");
	}
}

void inserirVertice(Grafo* g, char nome) // OK
{
	if (g != NULL)
	{
		int vi = getVerticeIndex(g, nome);
		if (vi != -1) {
			printf("Vertice ja existente!\n\n");
			return;
		}
		if (g->ocup_vertices >= g->num_vertices) {
			g->vertices = (Vertice**)realloc(g->vertices, (g->num_vertices + 1) * sizeof(Vertice));
			g->vertices[g->num_vertices++] = NULL;
		}
		for (int a = 0; a < g->num_vertices; a++)
		{
			if (g->vertices[a] == NULL)
			{
				g->vertices[a] = (Vertice*)malloc(sizeof(Vertice));
				g->vertices[a]->ant = NULL;
				g->vertices[a]->nome = nome;
				g->vertices[a]->valor = 0;
				g->ocup_vertices++;
				#ifdef debug
				printf("Inseriu vertice %c.\n\n", nome);
				#endif
				return;
			}
		}
	}
}

void inserirAresta(Grafo* g, char nome, char origem, char destino, int peso) // OK.
{
	if (g != NULL)
	{
		int oi = getVerticeIndex(g, origem);
		int di = getVerticeIndex(g, destino);
		Aresta* a = getAresta(g, nome);

		if (a != NULL) {
			printf("Identificador de Aresta ja utilizado.\n\n");
			return;
		}

		if (oi == -1 || di == -1) {
			printf("Vertices invalidos.\n\n");
			return;
		}

		if (g->adj[oi][di] != 0) {
			printf("Aresta ja existente na ligacao entre %c e %c.\n\n", origem, destino);
			return;
		}

		if (g->ocup_arestas >= g->num_arestas)
		{
			g->arestas = (Aresta**)realloc(g->arestas, sizeof(Aresta*) * (g->num_arestas + 1));
			g->arestas[g->num_arestas++] = NULL;
		}

		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] == NULL)
			{
				g->arestas[a] = (Aresta*)malloc(sizeof(Aresta));
				g->arestas[a]->nome = nome;
				g->arestas[a]->peso = peso;
				g->arestas[a]->orig = oi;
				g->arestas[a]->dest = di;
				g->ocup_arestas++;	
				break;
			}
		}
	
		g->adj[oi][di] = peso;
	}
}

void removerVertice(Grafo* g, char nome) // OK.
{
	if (g != NULL)
	{
		int vi = getVerticeIndex(g, nome);
		if (vi == -1) {
			printf("Vertice invalido.\n\n");
			return;
		}

		g->vertices[vi] = NULL;
		g->vertices = (Vertice**)realloc(g->vertices, --g->num_vertices * sizeof(Vertice));

		g->ocup_vertices--;

		for (int a = 0; a < g->num_vertices; a++)
		{
			if (g->adj[vi][a] != 0)
			{
				g->adj[vi][a] = 0;
				removerAresta(g, vi, a);
				g->ocup_arestas--;
			}
		}
	}
}

void removerAresta(Grafo* g, char nome) // OK.
{
	if (g != NULL)
	{
		int ai = getArestaIndex(g, nome);

		if (ai == -1) {
			printf("Aresta invalida.\n\n");
			return;
		}

		char nome = g->arestas[ai]->nome;
		int peso = g->arestas[ai]->peso;
		g->adj[g->arestas[ai]->orig][g->arestas[ai]->dest] = 0;
		g->arestas[ai] = NULL;
		g->arestas = (Aresta**)realloc(g->arestas, --g->num_arestas * sizeof(Aresta));
		g->ocup_arestas--;

		#ifdef debug
		printf("Removeu a aresta %c de peso %d.\n\n", nome, peso);
		#endif
	}
}

void removerAresta(Grafo* g, int orig, int dest)
{
	if (g != NULL)
	{
		for (int a = 0; a < g->num_arestas; a++)
		{
			if (g->arestas[a] != NULL)
			{
				if (g->arestas[a]->orig == orig && g->arestas[a]->dest == dest) {
					removerAresta(g, g->arestas[a]->nome);
					break;
				}
			}
		}
	}
}