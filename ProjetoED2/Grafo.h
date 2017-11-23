typedef struct vertice Vertice;
typedef struct aresta Aresta;
typedef struct grafo Grafo;

Grafo* criar(int num_vertices);
Vertice* getVertice(Grafo* g, char nome);
Aresta* getAresta(Grafo* g, char nome);
int getVerticeIndex(Grafo* g, char nome);
int getArestaIndex(Grafo* g, char nome);
void printAdj(Grafo* g);
void printVertices(Grafo* g);
void printArestas(Grafo* g);
void inserirVertice(Grafo* g, char nome);
void inserirAresta(Grafo* g, char nome, char origem, char destino, int peso);
void removerVertice(Grafo* g, char nome);
void removerAresta(Grafo* g, char nome);
void removerAresta(Grafo* g, int orig, int dest);
