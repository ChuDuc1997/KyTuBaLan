#include<iostream>
#include<string>
using namespace std;

template<class T>
struct Node {
	T Key;
	Node<T>* pNext;
};

template<class T>
Node<T>* createNode(T Data) {
	Node<T>* result = new Node<T>;
	if (result == NULL) {
		return NULL;
	}

	result->Key = Data;
	result->pNext = NULL;
	return result;
}

template<class T>
class Stack {
public:
	Node<T>* pHead;
public:
	Stack() {
		pHead = NULL;
	}

	bool isEmpty() {
		if (pHead == NULL) {
			return true;
		}
		return false;
	}

	bool push(T Data) {
		Node<T>* pNode = createNode(Data);
		if (pNode == NULL) {
			return false;
		}

		if (isEmpty()) {
			pHead = pNode;
			return true;
		}

		for (Node<T>* p = pHead; p != NULL; p = p->pNext) {
			if (p->pNext == NULL) {
				p->pNext = pNode;
				break;
			}
		}
		return true;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}

		if (pHead->pNext == NULL) {
			delete pHead;
			pHead = NULL;
		}
		else {
			for (Node<T>* p = pHead; p != NULL; p = p->pNext) {
				if (p->pNext->pNext == NULL) {
					delete p->pNext;
					p->pNext = NULL;
					break;
				}
			}
		}
		return;
	}

	T top() {
		T result = T();
		for (Node<T>* p = pHead; p != NULL; p = p->pNext) {
			if (p->pNext == NULL) {
				result = p->Key;
				break;
			}
		}
		return result;
	}

	void clear() {
		while (pHead != NULL) {
			Node<T>* pNode = pHead;
			pHead = pHead->pNext;
			delete pNode;
		}
	}

	friend ostream& operator<<(ostream& osDev, const Stack& stack) {
		if (stack.pHead == NULL) {
			osDev << "Stack is empty!";
		}
		else {
			for (Node<T>* p = stack.pHead; p != NULL; p = p->pNext) {
				if (p->pNext == NULL) {
					osDev << p->Key << endl;
				}
				else {
					osDev << p->Key << " ";
				}
			}
		}
		return osDev;
	}
};

bool operatorPrecedence(char operator1, char operator2) {
	if (operator1 == '^')
		return true;
	else if (operator2 == '^') {
		return false;
	}
	else if (operator1 == '*' || operator1 == '/') {
		return true;
	}
	else if (operator2 == '*' || operator2 == '/') {
		return false;
	}
	else if(operator1 == '+' || operator1 == '-'){
		return true;
	}
	else {
		return false;
	}
}


int main() {
	
	Stack<char> stack_char = Stack<char>();
	Stack<float> stack_float = Stack<float>();
	string P = string();
	string Q = string();
	
	stack_char.push('(');
	
	getline(cin, P);
	char delim[2] = ")";
	char data[2] = " ";
	P.append(delim);
	
	for (int i = 0; i < P.length(); i++) {
		delim[0] = P[i];
		if (delim[0] >= '0' && delim[0] <= '9') {
			Q.append(delim);
			delim[0] = P[i + 1];
			if (!(delim[0] >= '0' && delim[0] <= '9')) {
				Q.append(" ");
			}
		}
		else if (delim[0] == '(') {
			stack_char.push(delim[0]);
		}
		else if (delim[0] == '+' || delim[0] == '-' || delim[0] == '*' || delim[0] == '/' || delim[0] == '^') {
			while (operatorPrecedence((data[0] = stack_char.top()), delim[0])) {
				Q.append(data);
				Q.append(" ");
				stack_char.pop();
			}
			stack_char.push(delim[0]);
		}
		else if (delim[0] == ')') {
			while ((data[0] = stack_char.top()) != '(') {
				Q.append(data);
				Q.append(" ");
				stack_char.pop();
			}
			stack_char.pop();
		}
	}


	for (int i = 0; i < Q.length(); i++) {
		if (Q[i] == ' ') {
			continue;
		}
		else if (Q[i] >= '0' && Q[i] <= '9') {
			float number = 0;
			number = number * 10 + (int(Q[i]) - 48);
			while (Q[i + 1] >= '0' && Q[i + 1] <= '9') {
				i = i + 1;
				number = number * 10 + (int(Q[i]) - 48);
			}
			stack_float.push(number);
		}
		else if (Q[i] == '+' || Q[i] == '-' || Q[i] == '*' || Q[i] == '/' || Q[i] == '^') {
			float num2 = stack_float.top();
			stack_float.pop();
			float num1 = stack_float.top();
			stack_float.pop();
			switch (Q[i]) {
			case '+':
				stack_float.push(num1 + num2);
				break;
			case '-':
				stack_float.push(num1 - num2);
				break;
			case '*':
				stack_float.push(num1 * num2);
				break;
			case '/':
				stack_float.push(num1 / num2);
				break;
			case '^':
				stack_float.push(pow(num1, num2));
				break;
			}
		}
	}
	
	cout << stack_float.top();
	
	return 0;
}