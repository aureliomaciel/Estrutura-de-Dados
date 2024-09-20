#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

class Grafo {
private:
    int V; 
    vector<vector<int>> matrizAdjacencia; 
    vector<list<int>> listaAdjacencia;    
public:

    Grafo(int V) : V(V) {
        matrizAdjacencia.resize(V, vector<int>(V, 0));
        listaAdjacencia.resize(V);
    }

   
    void adicionarAresta(int v1, int v2) {
 
        matrizAdjacencia[v1][v2] = 1;
        matrizAdjacencia[v2][v1] = 1;

        listaAdjacencia[v1].push_back(v2);
        listaAdjacencia[v2].push_back(v1);
    }

   
    void carregarGrafo(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        if (!arquivo) {
            cerr << "Erro ao abrir o arquivo" << endl;
            return;
        }

        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            int v1, v2;
            ss >> v1 >> v2;
            adicionarAresta(v1, v2);
        }
    }

    void BFS(int s, int t) {
        vector<bool> visitado(V, false);
        vector<int> pai(V, -1);
        queue<int> fila;

        visitado[s] = true;
        fila.push(s);

        while (!fila.empty()) {
            int v = fila.front();
            fila.pop();

            if (v == t) {
                imprimirCaminho(s, t, pai);
                return;
            }

            for (int vizinho : listaAdjacencia[v]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    pai[vizinho] = v;
                    fila.push(vizinho);
                }
            }
        }
        cout << "Não há caminho entre os vértices " << s << " e " << t << endl;
    }

    void imprimirCaminho(int s, int t, const vector<int>& pai) {
        if (t == -1) {
            cout << "Não há caminho entre os vértices " << s << " e " << t << endl;
            return;
        }

        stack<int> caminho;
        for (int v = t; v != -1; v = pai[v]) {
            caminho.push(v);
        }

        cout << "Caminho: ";
        while (!caminho.empty()) {
            cout << caminho.top() << " ";
            caminho.pop();
        }
        cout << endl;
    }

    void DFS(int s) {
        vector<bool> visitado(V, false);
        stack<int> pilha;
        pilha.push(s);

        while (!pilha.empty()) {
            int v = pilha.top();
            pilha.pop();

            if (!visitado[v]) {
                cout << v << " ";
                visitado[v] = true;
            }

            for (int vizinho : listaAdjacencia[v]) {
                if (!visitado[vizinho]) {
                    pilha.push(vizinho);
                }
            }
        }
        cout << endl;
    }

    void exibirMatrizAdjacencia() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << matrizAdjacencia[i][j] << " ";
            }
            cout << endl;
        }
    }

    void exibirListaAdjacencia() {
        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            for (int vizinho : listaAdjacencia[i]) {
                cout << vizinho << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Grafo g(5); 

    g.carregarGrafo("grafo.txt");

    cout << "Matriz de Adjacência:" << endl;
    g.exibirMatrizAdjacencia();

    cout << "Lista de Adjacência:" << endl;
    g.exibirListaAdjacencia();

    cout << "BFS (Caminho entre 0 e 3):" << endl;
    g.BFS(0, 3);

    cout << "DFS a partir do vértice 0:" << endl;
    g.DFS(0);

    return 0;
}
