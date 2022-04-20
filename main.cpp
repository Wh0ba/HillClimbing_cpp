#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;
struct Node {
	char state;
	int value;
};
int edgeCount=0;

void readGraph(Node parents[], Node children[]);
void printGraph(Node parents[], Node children[]);
string HillClimb(Node parents[], Node children[],char start, char goal);

int main() {
	int e;
	cout << "Hill Climbing Search" << endl;
	cout << "How many Edges in the Graph: ";
	cin >> e;
	edgeCount = e;
	Node parentNodes[edgeCount];
	Node childNodes[edgeCount];
	readGraph(parentNodes, childNodes, edgeCount);
	printGraph(parentNodes, childNodes, edgeCount);
	return 0;
}

Node getNode(char state, Node p[], Node c[]) {
	for (int i = 0; i < edgeCount; i++) {
		if(state == p[i].state) return p[i];
		if(state == c[i].state) return c[i];
	}
	Node t;
	t.state = state;
	cout << "\tValue: ";
	cin >> t.value;
	return t;
}

void readGraph(Node parents[], Node children[]) {
	for (int i = 0; i < edgeCount; i++) {
		Node p;
		Node c;
		cout << "Parent Node: ";
		cin >> p.state;
		p = getNode(p.state, parents, children);
		cout << "Child Node: ";
		cin >> c.state;
		c = getNode(c.state, parents, children);
		parents[i] = p;
		children[i] = c;
	}
}


void printGraph(Node parents[], Node children[]) {
	for (int i = 0; i < edgeCount; i++) {
		Node p = parents[i];
		cout << "(" << p.state << ")[" << p.value<< "]" << endl;
		cout << " | " << endl;
		for (int j = 0; j < edgeCount; j++) {
			if(parents[i].state == parents[j].state) {
				Node c = children[j];
				cout << "(" << c.state << ")["<<c.value <<"]  ";
			}
		}
		cout << endl;
	}
}

// 0 1 2 3 4
// A A B C C
// B C D E F
string HillClimb(Node parents[], Node children[],Node start, Node goal){
	stack<Node> open;
	stack<Node> close;
	open.push(start);
	while(!open.empty()){
		for(int i=0;i<edgeCount;i++){
			if(parents[i].state != open.top().state) {
				if(i == edgeCount - 1){
					close.push(open.top());
					open.pop();
					break;
				}
				continue;
			}
			Node c = parents[i];
			close.push(open.top());
			open.pop();
			Node minNode = children[i];
			for(int j=i+1;j<edgeCount){
				if(c.state == parents[i]){
					if(children[j].value < minNode.value) minNode = children[j];
				}		
			}
			open.push(minNode)
			break;
		}
	}
	string path = "";
	while(!close.empty()){
		path += close.top();
		close.pop();
	}
	reverse(path.begin(), path.end());
	return path;
}
