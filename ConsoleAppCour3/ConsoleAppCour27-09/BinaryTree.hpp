
template<typename T>
struct Leaf {
public:
	T key = {};
	Leaf* left = nullptr;
	Leaf* right = nullptr;

	Leaf(T val) {
		key = val;
	}

	Leaf<T>* Insert(T val) {
		if (key < val) {
			if (left)
				left = left->Insert(val);
			else {
				left = new Leaf<T>(val);
			}
		}
		else {
			if (right)
				right = right->Insert(val);
			else {
				right = new Leaf<T>(val);
			}
		}
		return this;
	}

	Leaf<T>* Remove(T val) {
		//temp
		auto tempLeft = left;
		auto tempRight = right;

		//cas trouve
		if (val == key) {
			//pas l r
			if (!left && !right) {
				delete this;
				return nullptr;
			}
			//pas l
			if (!left) {
				delete this;
				return tempRight;
			}
			//pas r
			if (!right) {
				delete this;
				return tempLeft;
			}
			//les 2
			if (left && right) {
				while (left) {
					auto tempKey = left->key;
					right = right->Insert(tempKey);
					left = left->Remove(tempKey);
				}
				delete this;
				return tempRight;
			}
		}

		//si l
		if (left)
			if (key < val)
				left = left->Remove(val);

		//si r
		if (right)
			if (key > val)
				right = right->Remove(val);

		return this;
	}

	Merge(T val, Leaf<T>* right) {
		//cas d'arret

		auto tempKey = key
	}

	Leaf<T>* Search(T val) {
		if (val == key) {
			return this;
		}
		if(key < val)
			if (left)
				return left->Search(val);
		if(key > val)
			if (right)
				return right->Search(val);
	}

	int Size() {
		int sz = 1;
		if (left)
			sz += left->Size();
		if (right)
			sz += right->Size();
		return sz;
	}

	void print();
};

template<>
void Leaf<std::string>::print() {
	if (left)
		left->print();
	cout << key << " ";
	if (right)
		right->print();
}

template< typename T>
void Leaf<T>::print() {
	if (left)
		left->print();
	cout << std::to_string(key) << " ";
	if (right)
		right->print();
}

template<typename T>
class BinaryTree {
public:
	Leaf<T>* root = nullptr;

	void Insert(T val) {
		if (!root) {
			root = new Leaf<T>(val);
		}
		else
			root->Insert(val);
	}

	void Remove(T val) {
		if (root)
			root = root->Remove(val);
	}

	Leaf<T>* Search(T val) {
		if (root)
			root = root->Search(val);
	}

	int Size() {
		if (!root)
			return 0;
		return root->Size();
	}

	void print() {
		if (root)
			root->print();
		cout << "\n";
	}
};

typedef BinaryTree<int> IntBinaryTree;
typedef BinaryTree<float> floatBinaryTree;
typedef BinaryTree<string> stringBinaryTree;