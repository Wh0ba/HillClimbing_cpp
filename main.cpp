//نستورد المكاتب اللي نحتاجها 
#include <iostream>
#include <stack>// ومن ضمنها الستاك لان نستخدمه بعملية البحث
#include <string>
#include <algorithm>
using namespace std;

/*
نعرف ستركت (حاوية) يحتوي على اسم الستيت وقيمتها 
حتى يسهل علينا حفظها
*/
struct Node {
	char state;
	int value;
};

//(الخطوط)عدد الوصلات بين الستيتات  
int edgeCount = 0;

void readGraph(Node parents[], Node children[]);

string HillClimb(Node parents[], Node children[], char start, char goal);

int main() {
	int e;
	cout << "Hill Climbing Search" << endl;
	cout << "How many Edges in the Graph: ";
	cin >> e;

	edgeCount = e;//نعين عدد الوصلات بين الستيتات

	Node parentNodes[edgeCount];//مصفوفة تحتوي على الاباء
	Node childNodes[edgeCount];//مصفةفى تحتوي على الأبناء
	readGraph(parentNodes, childNodes);//ندز المصفوفات الفارغة على دالة القرائة
	cout << "Enter The Start State: ";
	char start; cin >> start;//نقرا رمز البداية
	cout << "Enter the Goal State: ";
	char goal; cin >> goal;//نقرا الهدف | الكول

	//ندز المصفوفات اللي انكتبت الها الشجره مع البداية والهدف
	string result = HillClimb(parentNodes, childNodes, start, goal);

	cout << "Result: " << result << endl;//نطبع المسار الناتج
	return 0;
}


//دالة تقرا ستيت من المستخدم
//وتتاكد اذا جنا مدخلين هاي الستيت قبل حتى ما يصير اختلاف بالقيم مالت نفس الستيت
Node getNode(Node p[], Node c[]) {
	char s;
	cin >> s;
	for (int i = 0; i < edgeCount; i++) {//هنا نبحث عن الستيت اللي دخلها المستخدم بداخل القيم اللي دخلها قبل
		// search for the node in both arrays
		if(s == p[i].state) return p[i];
		if(s == c[i].state) return c[i];
		//اذا جانت الستيت موجوده قبل, نرجعها هيه والقيمة مالتها 
	}
	//واذا ما جانت موجوده نسوي حاويه جديدة ونخلي بيها الستيت وقيمة جديدة اله
	Node t;
	t.state = s;
	cout << "\tValue: ";
	cin >> t.value;
	return t;
}

// هاي الدالة تسال المستخدم على كل الستيتات وارتباطاتهم 
//مع التأكيد على عدم تكرار الستيتات بقيم مختلفة
void readGraph(Node parents[], Node children[]) {
	for (int i = 0; i < edgeCount; i++) {
		Node p;
		Node c;
		cout << "Parent Node: ";
		p = getNode(parents, children);//دالة تقرا قيمة وتتحقق من وجودها قبل
		cout << "Child Node: ";
		c = getNode(parents, children);
		parents[i] = p;
		children[i] = c;
	}
}


//الدالة الاساسية لعمل الخوارزمية 
string HillClimb(Node parents[], Node children[], char start, char goal) {
	stack < char > open;//ستاك خاص بالاوبن
	stack < char > close;//ستاك خاص بالكلوز
	open.push(start);//ندفع عنصر البداية للستاك الاوبن
	while(!open.empty()) {//ما دام الاوبن مو فارغ ، نفذ الكود داخل القوسين
		for(int i = 0; i < edgeCount; i++) {// نفتر على عدد جميع الوصلات
			if(parents[i].state != open.top()) {//اذا جان اعلى عنصر بالستاك هو مو الاب الحالي
				if(i == edgeCount - 1) {//اذا حاليا احنا يم اخر عنصر بالمصفوفة احذف العنصر من الاوبن وضيفه للكلوز
					close.push(open.top());
					open.pop();
					if(goal == close.top()) break;//اذا جان العنصر اللي حذفنا هو الكول ، اطلع من اللوب
					else return "Did not find goal, MAX Problem";// واذا مو هو الكول واصلا خلصنا المصفوفة نرجع بمشكلة ماكس
				}
				continue;// واذا احنا مو يم اخر عنصر كمل على العنصر الجاي لما نلكه ستيت اللي نتفرع منه 
			}
			Node c = parents[i];//ناخذ الاب الحالي 
			close.push(open.top());//ندفعه للكلوز
			open.pop();//نحذف العنصر من التوب

			if(goal == close.top()) break;//اذا الكول هو العنصر اللي هسه ضفناه للكلوز اطفر

			Node minNode = children[i];// نبدا عمليه مقارنه وناخذ اول عنصر من الابناء ك اصغر عنصر
			int childCount = 1;//نعين عدد الابناء الى 1 
			bool isEqual = true;//هذا نخلي حتى نتاكد اذا كل العناصر متساويه
			for(int j = i+1; j < edgeCount; j++) {
				if(c.state == parents[j].state) {//اذا جانت الستيت الحالية هيه راجعه للاب
					childCount++;//نزيد عدد الابناء 
					if (minNode.value > c.value) return "Can't find goal, Ridge Problem";//اذا جانت قيمه الابن اكبر من الاب نخرج بمشكله 
					if(!(minNode.value == children[j].value)) isEqual = false;// اذا جان الابن اللي قرينا يختلف يعني ما عدنا مشكله تساوي
					if(children[j].value < minNode.value) minNode = children[j];// ناخذ العنصر الاصغر 
				}
			}
			if(isEqual && !(childCount == 1)) return "Can\'t find goal, Plateau Problem";//ناذا جانت كل الستيتات متساويه نخرج بمشكله 
			open.push(minNode.state);//غيرها ندفع الابن الاصغر الى الاوبن
			break;//ونكسر اللوب
		}
	}
	string path = "";
	while(!close.empty()) {
		path += close.top();//نضيف جميع العناصر الى المسار
		close.pop();
	}
	reverse(path.begin(), path.end());//نقوم بعكس نص المسار لان الية عمل الستاك تخرج مسار معكوس
	return path;
}