#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class tree_t
{
private:
	struct node_t {
		node_t * left;
		node_t * right;
		T key;

		node_t() {
			left = nullptr;
			right = nullptr;
			key = 0;
		}

		void print_(ostream & stream, int size) const {
			if (right != nullptr) right->print_(stream, size + 4);
			for (int i = 0; i < size + 4; i++) 
				stream << '-';
			stream << key << endl;
			if (left != nullptr) left->print_(stream, size + 4);
		}

		~node_t() {
			if (left != nullptr) delete left;
			if (right != nullptr) delete right;
		}

	};
private:
	node_t * root_;

public:
	tree_t() {
		root_ = nullptr;
	}

	bool compare(node_t * one, node_t * other, bool & result) const {
		if (one == nullptr && other == nullptr) return result;
		else if (one == nullptr || other == nullptr) {
			result = false;
			return result;
		}
		else if (one->key != other->key) {
			result = false;
			return result;
		}
		else{
			return(compare(one->left,other->left, result) && compare(one->right,other->right, result));
		}
	}

	auto operator ==(tree_t<T> const & other)  {
		bool result = true;
		compare(root_, other.root_, result);
		return result;
	}

	bool remove(T key) {
		if (find(key) == false) return false;
		else {
			node_t * tmp = root_;
			node_t * ptmp = nullptr;
			while (tmp != nullptr) {
				if (tmp->key == key) break;
				else if (tmp->key > key && tmp->left != nullptr) {
					ptmp = tmp;
					tmp = tmp->left; 
				}
				else if (tmp->key < key && tmp->right != nullptr) {
					ptmp = tmp;
					tmp = tmp->right;
				}
			}

			if (tmp->left == nullptr && tmp->right == nullptr) {
				if (ptmp->left == tmp) {
					ptmp->left = nullptr;
					delete tmp;
					return true;
				}
				else if (ptmp->right == tmp) {
					ptmp->right = nullptr;
					delete tmp;
					return true;
				}
			}
			else if (tmp->left != nullptr && tmp->right == nullptr) {
				tmp->key = tmp->left->key;
				node_t * t = tmp->left;
				tmp->right = tmp->left->right;
				tmp->left = tmp->left->left;
				t->left = nullptr;
				t->right = nullptr;
				delete t;
				return true;
			}
			else if (tmp->left == nullptr && tmp->right != nullptr) {
				node_t * t = tmp->right;
				tmp->key = tmp->right->key;
				tmp->left = tmp->right->left;
				tmp->right = tmp->right->right;
				t->left = nullptr;
				t->right = nullptr;
				delete t;
				return true;
			}
			else if (tmp->left != nullptr && tmp->right != nullptr) {
				node_t * t = tmp->right;
				if (tmp->right->left == nullptr) {
					tmp->key = tmp->right->key;
					tmp->right = tmp->right->right;
					t->left = nullptr;
					t->right = nullptr;
					delete t;
					return true;
				}
				else {
					while (t->left->left != nullptr) t = t->left;
					T n = t->left->key;
					remove(n);
					tmp->key = n;
					return true;
				}
			}
			return false;
		}
	}

	void insert(T key) {

		if (root_ == nullptr) {
			root_ = new node_t;
			root_->key = key;
		}
		else {
			node_t * tmp = root_;

			while (tmp->left != nullptr || tmp->right != nullptr) {
				if (tmp->key > key ) {
					if (tmp->left != nullptr) tmp = tmp->left;
					else break;
				}
				else if (tmp->key < key ) {
					if (tmp->right != nullptr) tmp = tmp->right;
					else break;
				}
				else if (tmp->key == key) return;
			}

			if (tmp->key > key) {
				tmp->left = new node_t;
				tmp->left->key = key;
			}
			else if (tmp->key < key) {
				tmp->right = new node_t;
				tmp->right->key = key;
			}
			
		}
	}

	bool find(T key) const {
		if (root_ == nullptr) return false;
		else {
			node_t * tmp = root_;
			while (tmp != nullptr) {
				if (tmp->key == key) return true;
				else if (tmp->key > key) tmp = tmp->left;
				else if (tmp->key < key) tmp = tmp->right;
			}
			return false;
		}
	}

	void print(ostream & stream) const {
		if (root_ == nullptr) {
		  throw logic_error("ERROR: EMPTY TREE");
		}
		else {
			root_->print_(stream, 0);
		}
	}
	
	tree_t(std::initializer_list<T> keys) {
		root_ = nullptr;
		for (T key : keys) {
			insert(key);
		}
	}

	~tree_t() {
		if (root_ != nullptr) delete root_;
	}
};
