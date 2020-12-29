#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <limits>
#include <queue>
#include <stack> 

using namespace std;

static int current_id = 0;

/*struct Elem {
	int id;	
	int weight;
	int name;
	int road = 0;
	bool done = false;
	Elem(int n, int w = 0) :id(current_id++), name(n), weight(w) {}
};*/
class Elem {
public:
	int id;
	int weight;
	int name;
	int road = 0;
	bool done = false;
	Elem(int n, int w = 0) :id(current_id++), name(n), weight(w) {}
	Elem(int n, int r, bool b):id(current_id++), name(n), road(r), done (b), weight(0) {}
};
struct Pre {
	int name;
	int notfinished;
	Pre(int n = -1, int no = 0) : name(n), notfinished(no) {}
};
void  makegraph(vector<list<Elem>>* graph, int N) {
	graph->resize(N);
}

void addNode(vector<list<Elem>>* g, int n) {
	list <Elem> l;
	g->resize(n + 1);
	g->insert(g->end(), l);
}

void removeNode(vector<list<Elem>>* g, int i) {
	g->erase(g->begin() + i);
}

bool compareName(Elem e1, Elem e2) {
	return (e1.name < e2.name);
}

void connect(vector<list<Elem>>* g, int i, int j, int w) {
	if (g->empty()) {
		cout << "Graf je prazan";
		return;
	}
	if ((unsigned int) i >= g->size() || (unsigned int)j >= g->size()) {
		cout << "Cvor " << ((unsigned int)i >= g->size() ? i : j) << " ne postoji";
		return;
	}
	list <Elem> ::iterator it;
	for (it = (*g)[i].begin(); it != (*g)[i].end(); ++it) {
		if ((*it).name == j) {
			cout << "Vec su povezani";
			return;
		}
	}
	(*g)[i].push_back(Elem(j,w));
	(*g)[j].push_back(Elem(i,w));
	(*g)[i].sort(compareName);
	(*g)[j].sort(compareName);
}

bool compare(Elem& e, int j) {
	return e.name == j;
}
void disconnect(vector<list<Elem>>* g, int i, int j) {
	if (g->empty()) {
		cout << "Graf je prazan";
		return;
	}
	if ((unsigned int)i >= g->size() || (unsigned int)j >= g->size()) {
		cout << "Cvor " << ((unsigned int)i >= g->size() ? i : j) << " ne postoji";
		return;
	}
	list <Elem> ::iterator it;
	bool f = false;
	for (it = (*g)[i].begin(); it != (*g)[i].end();) {
		if ((*it).name == j) {
			(*g)[i].erase(it);
			f = true;
			break;
		}
		else {
			it++;
		}
	}
	if (!f) {
		cout << "Veza ne postoji";
		return;
	}
	for (it = (*g)[j].begin(); it != (*g)[j].end();) {
		if ((*it).name == i) {
			(*g)[j].erase(it);

			break;
		}
		else {
			it++;
		}
	}

}
void printlist(list <Elem> l)
{
	list <Elem> ::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << "\t" << (*it).name << "-" << (*it).weight;
	cout << endl;
}
void deleteGraph(vector<list<Elem>>* g) {
	for (unsigned int i = 0; i < g->size(); i++) {
		g[i].clear();
	}
	g->clear();
}
void printGraph(vector<list<Elem>> graph) {
	cout << "\nThe vector elements are: ";
	cout << endl;
	for (unsigned int i = 0; i < graph.size(); i++) {
		cout << i << ":";
		printlist(graph[i]);
	}
}
void setVectors(vector<int>* dist, vector<int>* parent, vector<bool > * mst, int n, int rooth, vector<int>* key) {
	fill((*dist).begin(), (*dist).end(), numeric_limits<int>::max());
	fill((*parent).begin(), (*parent).end(), -1);
	(*dist)[rooth] = 0;
	fill((*mst).begin(), (*mst).end(), false);
	(*mst)[rooth] = true;
}
void printMST(vector<int> dist, vector<int> parent, int rooth) {
	for (unsigned int i = 0; i < dist.size(); i++) {
		if (i != rooth) {
			cout << parent[i] << "-" << i << "=" << dist[i] << endl;
		}
	}
}

typedef pair<int, int> iPair;

int Prims(vector<list<Elem>> *g, vector<int> *dist, vector<int> *parent, vector <bool> *mst, int rooth, priority_queue< iPair, vector <iPair>, greater<iPair> > pq){ //mozak ti je kasa moras da se snadjes oko indeksa zato sto je koren random a ne 0
	int n = g->size();
	for (int i = 0; i < n; i++) {
		pq.push(make_pair((*dist)[i], i));
	}
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		(*mst)[u] = true;
		list <Elem> ::iterator it;
		for (it = (*g)[u].begin(); it != (*g)[u].end(); it++) {
			if ((*it).weight < (*dist)[(*it).name] && (*mst)[(*it).name] == false) {
				int v = (*it).name;
				int weight = (*it).weight;
				(*dist)[v] = weight;
				pq.push(make_pair((*dist)[v], v));
				(*parent)[v] = u;
			}
		}
	}
		int c = 0;
		for (unsigned int k = 0; k < (*dist).size(); k++) {
			if (k != rooth) { c += (*dist)[k]; }
		}
		return c;
}
void setRoad (vector<list<Elem>>* g, int i, int j, int l , bool b){
	if (g->empty()) {
		cout << "Graf je prazan";
		return;
	}
	if ((unsigned int)i >= g->size() || (unsigned int)j >= g->size()) {
		cout << "Cvor " << ((unsigned int)i >= g->size() ? i : j) << " ne postoji";
		return;
	}
	list <Elem> ::iterator it;
	for (it = (*g)[i].begin(); it != (*g)[i].end(); ++it) {
		if ((*it).name == j) {
			(*it).road = l;
			(*it).done = b;
		}
	}
	for (it = (*g)[j].begin(); it != (*g)[j].end(); ++it) {
		if ((*it).name == i) {
			(*it).road = l;
			(*it).done = b;
			return;
		}
	}
	(*g)[i].push_back(Elem(j, l, b));
	(*g)[j].push_back(Elem(i, l, b));
	(*g)[i].sort(compareName);
	(*g)[j].sort(compareName);
}
struct CompareNotFinished {
	bool operator()(Pre const& p1, Pre const& p2)
	{
		return p1.notfinished > p2.notfinished; 
	}
};
void printMin(vector<priority_queue<Pre, vector <Pre>, CompareNotFinished>> parent, vector<int> dist, int rooth) {
	stack <int> s;
	for (unsigned int i = 0; i < dist.size(); i++) {
		if (parent[i].top().name == -1) { continue; }
		cout << "Za lokaciju  " << i << " postoje  " << parent[i].size() << " puteva duzine  " << dist[i] << endl;
		while (!parent[i].empty()) {
			int p = parent[i].top().name;
			while (p != -1) {
				s.push(p);
				if (!parent[p].empty()) {
					p = parent[p].top().name;
				}
				else {
					break;
				}
			}
			cout << endl;
			cout << "V-";
			int k;
			while (!s.empty()) {
				k = s.top();
				s.pop();
				if (k != rooth) {
					cout << k;
				}
				if (!s.empty()) { cout << " - "; }
			}
			cout << "-"<<i<<endl;
			cout << "Put sadrzi " << parent[i].top().notfinished << " neigradjenih puteva";
			parent[i].pop();
			cout << endl;
		}
	}
}
void minPath(vector<list<Elem>>* g, int rooth) {

	int n = (*g).size();
	int i = 0, j = 0, l = 0;
	while (true) {
		cout << "Uneti parove lokacija i? i j? izmedju kojih vec postoji drumski saobracaj i njegovu duzinu" << endl;
		cout << "i? j?  l?" << endl;
		cin >> i;
		cin >> j;
		cin >> l;
		setRoad(g, i, j, l, true);
		cout << "Za prekid unosa unesite -1, ako zelite da nastavite bilo koji drugi int" << endl;
		int c;
		cin >> c;
		if (c == -1) { break; }
	}
	while (true) {
		cout << "Uneti parove lokacija i? i j? izmedju kojih je moguce napraviti drumski saobracaj i njegovu duzinu" << endl;
		cout << "i? j? i l?" << endl;
		cin >> i;
		cin >> j;
		cin >> l;
		setRoad(g, i, j, l, false);
		cout << "Za prekid unosa unesite -1, ako zelite da nastavite bilo koji drugi int" << endl;
		int c;
		cin >> c;
		if (c == -1) { break; }
	}

	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
	vector<priority_queue<Pre, vector <Pre>, CompareNotFinished>> parent((*g).size());
	vector<int> dist((*g).size(), numeric_limits<int>::max());
	//vector <bool> visited((*g).size(), false);
	//visited[rooth] = true;
	pq.push(make_pair(0, rooth));
	dist[rooth] = 0;
	parent[rooth].push(Pre(-1));
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		list< Elem >::iterator it;
		for (it = (*g)[u].begin(); it != (*g)[u].end(); ++it)
		{
			int v = (*it).name;
			int weight = (*it).road;
			bool finished = (*it).done;
			//if (!visited[v]) {
					if (dist[v] >= dist[u] + weight)
					{
						int c = 0;
						if (dist[v] == (dist[u] + weight)) {
							if (parent[u].size() != 0) {
								if (finished == false) { c = parent[u].top().notfinished + 1; }
								else {
									c = parent[u].top().notfinished;
								}
							}
							parent[v].push(Pre(u, c));
						}
						else {
							while (!parent[v].empty()) {
								parent[v].pop();
							}
							if (parent[u].size() != 0) {
								if (finished == false) { c = parent[u].top().notfinished + 1; }
								else {
									c = parent[u].top().notfinished;
								}
							}
							parent[v].push(Pre(u, c));
						}
						dist[v] = dist[u] + weight;
						pq.push(make_pair(dist[v], v));
					}
			//}
		}
		//visited[u] = true;
	}
	printMin(parent,dist, rooth);
}
int main() {
	vector<list<Elem>> graph(0);
	int n;
	while (true) {
		cout << "Broj kljucnih lokacija u gradu?";
		cin >> n;
		if (n >= 0) { break; }
		cout << "Nedozvoljena vrednost za n molim vas pokusajte ponovo" << endl;
	}
	int rooth = rand() % n; 
	cout << "rooth: " << rooth;
	makegraph(&graph, n);
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
	vector<int>  parent(n), key(n);
	vector <int> dist(n);
	vector <bool> mst(n);
	setVectors(&dist, &parent, &mst, n, rooth, &key);
	int i, j, w;
	while (true) {
		cout << "Unesite izmedju kojih mesta i? i j? postoji veza i njenu cenu w? "<<endl;
		cout << "i?, j?, w?"<<endl;
		cin >> i >> j >> w;
		connect(&graph, i, j, w);
		cout << "Ako zelite da prekinete unos, unesite -1" << endl;
		int k;
		cin >> k;
		if (k == -1) { break; }
	}
	int cena = Prims(&graph, &dist, &parent, &mst, rooth, pq);
	cout << "Cena je: " << cena << endl;
	//printGraph(graph);
	//cout << endl << rooth;
	//printMST(dist, parent, rooth);
	int v;
	cout << "Unesite index lokacije V?";
	cin >> v;
	minPath(&graph, v);
}