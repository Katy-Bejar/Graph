#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <math.h>
#include <queue>
#include <stack>
#include <string>
using namespace std;

template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge;

template <typename V, typename E>
class Graph;

typedef map<string, vector<string>> MAPA;
MAPA mapa;

priority_queue<string> q;
template <typename V, typename E>
class Vertex {
    public:
        V m_Dato;
        list<Edge<V, E>> member_list_edges;
        list<Vertex<V, E>> member_list_Vertex_ady;
    public:
        // constructor
        Vertex(V dato) {
            m_Dato = dato;
        }
};

template <typename V, typename E>
class Edge{
    public:
        E m_Dato;
        Vertex<V, E>* member_pointer_to_next_Vertex;
    public:
        // constructor
        Edge(E dato, Vertex<V, E>* pointer = NULL) {
            m_Dato = dato;
            member_pointer_to_next_Vertex = pointer;
        }
};

template <typename V, typename E>
class Graph{
    private:
        list<Vertex<V, E>> member_list_of_Vertex;
        //V origen_ = "A"; // element of type Vertex
    public:
        // constructor
        Graph() {}
	
        // function Find Vertex
        bool find_Vertex(V data_vertex) {
            list<Vertex<string, int>> :: iterator it = member_list_of_Vertex.begin();
            for (; it != member_list_of_Vertex.end(); it++) 
                if (it -> m_Dato == data_vertex)  return true;
            return false;
        }

        // function Insert Vertex
        void insertVertex(V data_vertex) {
            member_list_of_Vertex.push_back(Vertex<V, E> (data_vertex));
        }

        // function Insert Edge
        void InsertEdge(string data_vertex1, int data_edge, string data_vertex2) {
            Vertex<V, E> V1(data_vertex1);
            Vertex<V, E> V2(data_vertex2); 

            if (find_Vertex(data_vertex1) == true && find_Vertex(data_vertex2) == true) {
                V1.member_list_edges.push_back(Edge<V, E> (data_edge, &V2));
                V1.member_list_Vertex_ady.push_back(Vertex<V, E> (V2));
                mapa[data_vertex1].push_back(data_vertex2);
                string num_str1(to_string(data_edge));
                mapa[data_vertex1].push_back(num_str1);
            }
        }

        bool isNumber(const string& str) {
            for (char const &c : str) 
                if (std::isdigit(c) == 0) return false;
            return true;
        }

        void print_graph(ostream& output){
            output << "graph {" << endl;
            output << "rankdir = LR" << endl;
            for (auto &vertice: mapa) {
                    for (size_t i = 0; i < vertice.second.size(); i++) {
                        if (isNumber(vertice.second[i]) == true) {
                            output << "[label = " << vertice.second[i] <<", weight = " << vertice.second[i] <<"];" << endl;
                            continue;
                        }
                        output << vertice.first << "--";
                        output << vertice.second[i];
                    }	
                    output << endl;
            }
            output << "}";
        }

        vector<string> returned_ady_key(string data_vertex) {
            auto iter = mapa.begin();
            vector<string> vect;
            while (iter != mapa.end()) {
                if (mapa.find(data_vertex) != mapa.end()) {
                    if (iter -> first == data_vertex) {
                        for (size_t i = 0; i < iter -> second.size(); i += 2) {
                            vect.push_back(iter -> second[i]);
                        }
                        break;
                    } 
                    else {
                        iter++;
                    }
                } 
            }
            //print_vector(vect);
            return vect;
        }

        void print_vector(vector<string> v) {
            for (size_t i = 0; i < v.size(); i++) {
                cout << v[i] << " ";
            }
        }

        bool Visitados(vector<string> vect, string element) {
            for (size_t i = 0; i < vect.size(); i++) {
                if (vect[i] == element) {
                    return true;
                }
            }
            return false;
        }

        void DFS(V datavertexOrigen) { // profundidad
            vector<string> visitados;
            vector<string> adyacentes;
            stack<string> pila;
            
            pila.push(datavertexOrigen);
            visitados.push_back(datavertexOrigen);
            while(!pila.empty()) {
                auto aux = pila.top();
                adyacentes = returned_ady_key(aux);
                cout << aux << " ";
                pila.pop();
                for(size_t i = 0; i < adyacentes.size(); i++) {
                    if (Visitados(visitados, adyacentes[i]) == false) {
                        pila.push(adyacentes[i]);
                        visitados.push_back(adyacentes[i]);
                    }
                }
            }

        }

        void BFS(V datavertexOrigen) { // anchura
            vector<string> visitados;
            vector<string> adyacentes;
            queue<string> pila;
            
            pila.push(datavertexOrigen);
            visitados.push_back(datavertexOrigen);
            while(!pila.empty()) {
                auto aux = pila.front();
                adyacentes = returned_ady_key(aux);
                cout << aux << " ";
                pila.pop();
                for(size_t i = 0; i < adyacentes.size(); i++) {
                    if (Visitados(visitados, adyacentes[i]) == false) {
                        pila.push(adyacentes[i]);
                        visitados.push_back(adyacentes[i]);
                    }
                }
            }

        }

        template<typename T>
        void print_vector(vector<T> vec) {
            for (size_t i = 0; i < vec.size(); i++){
                    cout << vec[i] << " ";
            }
            cout << endl;
        }
};

int main() {
    Graph<string, int> graph;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");
    graph.insertVertex("F");
    graph.insertVertex("G");
    graph.insertVertex("H");
    graph.InsertEdge("A", 9, "B");
    graph.InsertEdge("B", 9, "A");
    graph.InsertEdge("A", 1, "D");
    graph.InsertEdge("D", 1, "A");
    graph.InsertEdge("B", 8, "C");
    graph.InsertEdge("C", 8, "B");
    graph.InsertEdge("C", 3, "H");
    graph.InsertEdge("H", 3, "C");
    graph.InsertEdge("H", 7, "F");
    graph.InsertEdge("F", 7, "H");
    graph.InsertEdge("F", 5, "G");
    graph.InsertEdge("G", 5, "F");
    graph.InsertEdge("D", 4, "F");
    graph.InsertEdge("F", 4, "D");
    graph.InsertEdge("B", 12, "D");
    graph.InsertEdge("D", 12, "B");
    graph.InsertEdge("D", 6, "E");
    graph.InsertEdge("E", 6, "D");
    
    ofstream file("graph.dot");
    graph.print_graph(file);

    cout << "Recorrido BFS: " << endl;
    graph.BFS("A");

    cout << "\n\nRecorrido DFS: " << endl;
    graph.DFS("A");


    return 0;
}