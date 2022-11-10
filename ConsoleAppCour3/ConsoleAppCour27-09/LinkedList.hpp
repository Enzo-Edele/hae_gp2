
template<typename T>
struct Node {
public:
	T key = {}; //objet vide universelle
	Node* next = nullptr;
	Node* prev = nullptr;

	Node(T val) {
		key = val;
	}

	Node<T>* RemoveAll(T val) {
		if (val == key) {
			Node<T>* chain = next;
			delete this;
			return chain->RemoveAll(val);
		}
		else {
			if (next)
				next = next->RemoveAll(val);
		}
		return this;
	}

	Node<T>* RemoveOne(T val) {
		if (val == key) {
			Node<T>* chain = next;
			delete this;
			return chain;
		}
		else {
			if (next)
				next = next->RemoveOne(val);
		}
		return this;
	}

	Node<T>* PushBack(T val) {
		if(next)
			next = next->PushBack(val);
		else {
			Node<T>* ptr = new Node<T>(val);
			next = ptr;
		}

		return this;
	}
};

template<typename T>
class LinkedList {
public:
	Node<T>* head = nullptr;

	void PushFront(T val) {
		Node<T>* ptr = new Node<T>(val);
		if (!head) {
			head = ptr;
			return;
		}
		auto oldhead = head;
		head = ptr;
		head->next = oldhead;
		oldhead->prev = head;
	};

	void RemovePrev(T val) {
		Node<T>* ptr = head;
		while (ptr) {
			auto prev = ptr->prev;
			auto next = ptr->next;
			if (ptr->key == val) {
				if (prev) prev->next = next;
				if (next) next->prev = prev;
				if (ptr == head) {
					head = next;
				}
				delete ptr;
				ptr = nullptr;
			}
			ptr = next;
		}
		delete ptr;
	}

	void RemoveAll(T val) {
		if (!head)
			return;
		head = head->RemoveAll(val);
	};
	void RemoveOne(T val) {
		if (!head)
			return;
		head = head->RemoveOne(val);
	};

	void PushBack(T val) {
		Node<T>* ptr = new Node<T>(val);
		if (!head) {
			head = ptr;
			return;
		}
		head = head->PushBack(val);
	}

	void print() {
		auto ptr = head;
		cout << "[";
		while (ptr) {
			cout << to_string(ptr->key);
			ptr = ptr->next;
			cout << " ";
		}
		cout <<"] \n";
	}
};

typedef LinkedList<int> IntList;
typedef LinkedList<float> FloatList;