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
	readGraph(parentNodes, childNodes);
	cout << "Enter The Start State: "
	char start;cin >> start;
	cout << "Enter the Goal State: "
	char goal;cin >> goal;

	//printGraph(parentNodes, childNodes, edgeCount);
	string result = HillClimb(parentNodes, childNodes, start, goal)
	return 0;
}

Node getNode(Node p[], Node c[]) {
	char s;
	cin >> s;
	for (int i = 0; i < edgeCount; i++) { // search for the node in both arrays
		if(s == p[i].state) return p[i];
		if(s == c[i].state) return c[i];
	}
	Node t;
	t.state = s;
	cout << "\tValue: ";
	cin >> t.value;
	return t;
}

void readGraph(Node parents[], Node children[]) {
	for (int i = 0; i < edgeCount; i++) {
		Node p;
		Node c;
		cout << "Parent Node: ";
		p = getNode(parents, children);
		cout << "Child Node: ";
		c = getNode(parents, children);
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
string HillClimb(Node parents[], Node children[],char start, char goal){
	stack<char> open;
	stack<char> close;
	open.push(start);
	while(!open.empty()){
		for(int i=0;i<edgeCount;i++){
			if(parents[i].state != open.top()) {
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
				if(c.state == parents[i].state){
					if(children[j].value < minNode.value) minNode = children[j];
				}		
			}
			open.push(minNode.state)
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
