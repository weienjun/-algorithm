#include<iostream>
using namespace std;
#include<vector>

struct AVLNode {
	int _key;
	int _value;
	int _hr;
	AVLNode* _left;
	AVLNode* _right;

	AVLNode(int key = 0, int value = 0)
		:_key(key)
		, _value(value)
		, _hr(1)
		, _left(NULL)
		, _right(NULL)
	{}
};

class AVLTree {
public:
	typedef AVLNode Node;
	AVLTree()
		:_root(NULL)
	{}

	int getHr(Node* node) {
		if (node) {
			return node->_hr;
		}
		return 0;
	}

	void upHr(Node* &node) {
		if (node) {
			int lhr = getHr(node->_left);
			int rhr = getHr(node->_right);
			node->_hr = (lhr > rhr? lhr : rhr) + 1;
		}
	}
	void put(int key, int value) {
		_root = _put(_root, key, value);
	}
	Node* _put(Node* root, int key, int value) {
		if (root == NULL) {
			return new Node(key,value);
		}
		
		//���Ҳ���λ��
		if (root->_key > key) {
			root->_left = _put(root->_left, key, value);
		}
		else if (root->_key < key) {
			root->_right = _put(root->_right, key, value);
		}
		else {
			root->_value = value;
		}

		//�ݹ����ÿ���ڵ�ĸߺ���ת��ƽ
		//�������ĸ߶�
		upHr(root);
		//��ת�ڵ�
		if (getHr(root->_right)-getHr(root->_left) == -2) {  //���������������߳���1
			Node* child = root->_left;
			if (getHr(child->_right)-getHr(child->_left) == 1) {  //˫��
				root->_left = rotateLeft(child);  //����
			}
			root = rotateRight(root);//����
		}
		if (getHr(root->_right) - getHr(root->_left) == 2) {  //���������������߳���1
			Node* child = root->_right;
			if (getHr(child->_right) - getHr(child->_left) == -1) {  //˫��
				root->_right = rotateRight(child);//����
			}
			root = rotateLeft(root); //����
		}
		return root;
	}

	Node* rotateLeft(Node* node) {
		Node* node_right = node->_right;
		Node* node_rleft = node_right->_left;

		//�����ڵ��λ��
		node_right->_left = node;
		node->_right = node_rleft;
		
		//������ת�����ڵ�ĸ�
		upHr(node); 
		upHr(node_right);

		return node_right;
		
	}

	Node* rotateRight(Node* node) {
		Node* node_left = node->_left;
		Node* node_lright = node_left->_right;
		//�����ڵ��λ��
		node_left->_right = node;
		node->_left = node_lright;
		//���½ڵ�ĸ�
		upHr(node);
		upHr(node_left);

		return node_left;
	}

	int get(int key) {
		Node* node = _get(_root, key);
		if (node) {
			return node->_value;
		}
		return -1;
	}
	Node* _get(Node* root, int key) {
		if (root == NULL) return NULL;
		if (root->_key > key) {
			return _get(root->_left, key);
		}
		else if(root->_key < key){
			return _get(root->_right, key);
		}else{
			return root;
		}
	}

	Node* getMin(Node* node) {
		if (node == NULL) return NULL;
		if (node->_left == NULL) return node;
		return getMin(node->_left);
	}

	//ɾ���ڵ�
	void erase(int key) {
		_root = _erase(_root, key);
	}
	Node* _erase(Node* root, int key) {
		if (root == NULL) return NULL;
		if (root->_key > key) {
			root->_left = _erase(root->_left, key);
		}
		else if (root->_key < key) {
			root->_right = _erase(root->_right, key);
		}
		else {
			Node* del = root;
			if (del->_left == NULL) {
				root = del->_right;
				delete del;
				return root;
			}
			if (del->_right == NULL) {
				root = del->_left;
				delete del;
				return root;
			}
			//1��Ѱ���滻�ڵ㣬ɾ���滻�ڵ�
			Node* min_right = getMin(root->_right);
			swap(root->_key, min_right->_key);
			swap(root->_value, min_right->_value);
			root->_right = _erase(root->_right, key);
			return root;
		}
		//ƽ�⴦��
		//1�����¼���hr
		upHr(root);
		//2����ת����
		if (getHr(root->_right) - getHr(root->_left) == -2) {  //���������������߳���1
			Node* child = root->_left;
			if (getHr(child->_right) - getHr(child->_left) == 1) {  //˫��
				root->_left = rotateLeft(child);  //����
			}
			root = rotateRight(root);//����
		}
		if (getHr(root->_right) - getHr(root->_left) == 2) {  //���������������߳���1
			Node* child = root->_right;
			if (getHr(child->_right) - getHr(child->_left) == -1) {  //˫��
				root->_right = rotateRight(child);//����
			}
			root = rotateLeft(root); //����
		}
		return root;
	}

	//ƽ���ж�
	bool isBlance() {
		return _isBlance(_root);
	}
	bool _isBlance(Node* root) {
		if (root == NULL) {
			return true;
		}
		int left_hr = getHr(root->_left);
		int right_hr = getHr(root->_right);
		if (right_hr - left_hr > -2 && right_hr - left_hr < 2) {  //�������������ĸ߶Ȳ��ж�
			return true;
		}
		return _isBlance(root->_left) && _isBlance(root->_right);
	}

private:
	Node *_root;
};

void test_AVL() {
	AVLTree avl;
	
	avl.put(1, 1);
	avl.put(2, 2);
	avl.put(3,3);
	
	avl.put(4, 4);
	avl.put(5, 5);
	avl.put(6, 6);
	avl.put(8, 8);
	avl.put(7, 7);

	avl.erase(8);
	avl.erase(4);

	cout << avl.get(3) << endl;
	cout << avl.get(6) << endl;
	cout << avl.get(8) << endl;

	if (avl.isBlance()) {
		cout << "ƽ��" << endl;
	}
}

int main() {
	test_AVL();
	return 0;
}