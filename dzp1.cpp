#include <iostream>
#include <vector>
#include <list>

using namespace std;

static int current_id = 0;

struct Elem {
	int id;
	int name;
	Elem(int n):id(current_id++), name(n){}
	
};

void  makegraph(vector<list<Elem>>* graph, int N) {
	graph->resize(N);
}

void addNode(vector<list<Elem>>* g, int n) {
	list <Elem> l;
	g->resize(n + 1);
	g->insert(g->end(),l);
}
void disconnect(vector<list<Elem>>* g, int i, int j) {
	if (g->empty()) {
		cout << "Graf je prazan";
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
		cout << "Veza ne postoji" << endl;
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
void removeNode(vector<list<Elem>>* g, int i) {
	list <Elem> ::iterator it;
	list <Elem> ::iterator it2;
	if ((*g)[i].size() != 0) {
		for (it = (*g)[i].begin(); it != (*g)[i].end(); ++it) {
			for (it2 = (*g)[(*it).name].begin(); it2 != (*g)[(*it).name].end();) {
				if ((*it2).name == i) {
					(*g)[(*it).name].erase(it2);
					break;
				}
				else {
					it2++;
				}
			}
		}
		g->erase(g->begin() + i);
	}
}
bool compareName(Elem e1, Elem e2) {
	return (e1.name < e2.name);
}

void connect(vector<list<Elem>>* g, int i, int j) {
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
			cout << "Vec su povezani";
			return;
		}
	}
	(*g)[i].push_back(Elem(j));
	(*g)[j].push_back(Elem(i));
	(*g)[i].sort(compareName);
	(*g)[j].sort(compareName);
}

bool compare(Elem& e, int j) {
	return e.name == j;
}

void printlist(list <Elem> l)
{
	list <Elem> ::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << "\t" << (*it).name<< "-" <<(*it).id;
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
int main() {

	vector<list<Elem>> graph(0);
	cout << "Unesite redni broj odgovarajuc funkcije a zatim i odredjene vrednosti ako su potrebne" << endl;
	cout << "1. Pravljenje praznog grafa velicin n?" << endl;
	cout << "2. Dodati cvor u graf" << endl;
	cout << "3. Ukloniti cvor iz grafa sa mesta i?" << endl;
	cout << "4. Povezati cvorove i? i j?" << endl;
	cout << "5. Prekinuti vezu izmedju cvorova i? i j?" << endl;
	cout << "6. Ispisati graf" << endl;
	cout << "7. Obrisati graf" << endl;
	cout << "-1. Exit" << endl;
	int k;
	int n = 0;
	cin >> k;
	while (k != -1) {
		switch (k)
		{
		case 1: {
			cout << "n?";
			cin >> n;
			if (n <= 0) { cout << "Neodgovarajuci broj cvorova"; break; }
			makegraph(&graph, n);
			break;
		}
		case 2: {
			addNode(&graph, n);
			break;
		}
		case 3: {
			cout << "i?";
			int i;
			cin >> i;
			if (i > n) { cout << "Nepostojeci cvor"; break; }
			removeNode(&graph, i);
			break;
		}
		case 4: {
			cout << "i,j?";
			int i, j;
			cin >> i >> j;
			if (i > n || j > n) {
				cout << "Nepostojuci cvor";
				i > n ? cout << "i" : cout << "j";
				break;
			}
			connect(&graph, i, j);
			break;
		}
		case 5: {
			cout << "i,j?";
			int i, j;
			cin >> i >> j;
			if (i > n || j > n) {
				cout << "Nepostojuci cvor";
				i > n ? cout << "i" : cout << "j";
				break;
			}
			disconnect(&graph, i, j);
			break;
		}
		case 6: {
			printGraph(graph);
			break;
		}
		case 7: {
			deleteGraph(&graph);
			break;
		}
		}
		cout << "Unesite redni broj odgovarajuc funkcije a zatim i odredjene vrednosti ako su potrebne" << endl;
		cout << "1. Pravljenje praznog grafa velicin n?" << endl;
		cout << "2. Dodati cvor u graf" << endl;
		cout << "3. Ukloniti cvor iz grafa sa mesta i?" << endl;
		cout << "4. Povezati cvorove i? i j?" << endl;
		cout << "5. Prekinuti vezu izmedju cvorova i? i j?" << endl;
		cout << "6. Ispisati graf" << endl;
		cout << "7. Obrisati graf" << endl;
		cout << "-1. Exit" << endl;
		cin >> k;
	}
}