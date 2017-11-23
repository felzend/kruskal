#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

#define debug

/*

A matriz mostrará a relação dos N vértices do grafo.
O valor zero (0) significa que não há ligação entre dois vértices.
Qualquer valor diferente de zero (0) indicará uma ligação entre os dois vértices, onde o valor representado na matriz será o peso da aresta.

*/

struct vertice {
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
				printf("%c ", g->arestas[a]->nome);
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