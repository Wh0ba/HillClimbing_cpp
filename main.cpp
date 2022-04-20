#include <iostream>
#include <stack>
using namespace std;
struct Node {
	char state;
	int value;
};
void readGraph(Node parents[], Node children[], int size);
void printGraph(Node parents[], Node children[], int size);
string HillClimb(Node parents[], Node children[], char goal, int size);

int main() {
	int edgeCount;
	cout << "Hill Climbing Search" << endl;
	cout << "How many Edges in the Graph: ";
	cin >> edgeCount;
	Node parentNodes[edgeCount];
	Node childNodes[edgeCount];
	readGraph(parentNodes, childNodes, edgeCount);
	printGraph(parentNodes, childNodes, edgeCount);
	return 0;
}

Node getNode(char state, Node p[], Node c[], int size) {
	for (int i = 0; i < size; i++) {
		if(state == p[i].state) return p[i];
		if(state == c[i].state) return c[i];
	}
	Node t;
	t.state = state;
	cout << "\tValue: ";
	cin >> t.value;
	return t;
}

void readGraph(Node parents[], Node children[], int size) {
	for (int i = 0; i < size; i++) {
		Node p;
		Node c;
		cout << "Parent Node: ";
		cin >> p.state;
		p = getNode(p.state, parents, children, size);
		cout << "Child Node: ";
		cin >> c.state;
		c = getNode(c.state, parents, children, size);
		parents[i] = p;
		children[i] = c;
	}
}


void printGraph(Node parents[], Node children[], int size) {
	for (int i = 0; i < size; i++) {
		Node p = parents[i];
		cout << "(" << p.state << ")[" << p.value<< "]" << endl;
		cout << " | " << endl;
		for (int j = 0; j < size; j++) {
			if(parents[i].state == parents[j].state) {
				Node c = children[j];
				cout << "(" << c.state << ")["<<c.value <<"]  ";
			}
		}
		cout << endl;
	}
}