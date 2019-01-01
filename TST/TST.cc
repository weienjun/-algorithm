//���൥�ʲ�����
//���൥�ʲ������ǵ��ʲ������ĸý�����R���ַ����ܴ�ʱ�ɽ�ʡ�ռ�
//���൥�ʲ������ṹ��
//�ɼ�ֵkey(�ַ�)��value��ע�ͣ�������ָ���򹹳ɣ�left,mid,right��
//left--��keyֵС��mid--����keyֵ��right--����keyֵ
//ʱ�临�Ӷȣ�O��1.39logN)
//�ռ临�Ӷȣ�64N-64NW
//�����ڷ�����ļ�ֵ

#include<iostream>
using namespace std;
#include<string>
#include<vector>

struct TSTNode {
	char _key;
	string _value;
	TSTNode* _left;
	TSTNode* _mid;
	TSTNode* _right;

	TSTNode(char key = '0',string value = "")
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_mid(NULL)
		,_right(NULL)
	{}
};

class TSTree {
public:
	typedef TSTNode Node;
	TSTree()
		:_root(NULL)
	{}

	//���������λ�ݹ���Ҳ���λ�ã�
	//�ڵ�Ϊ���򴴽��ڵ㣬������λ�ַ���������
	//�������һ���ַ�ʱ����ע�Ͳ����ڸýڵ���
	//����ַ�С�ڽڵ��ַ�����ڵ��� = ��ݹ�
	//����ַ����ڽڵ��ַ�����ڵ��� = �ҵݹ�
	//�����ǰλ��Ϊ���λ��С�ڵ�ǰ�ַ����������ڵ�mid = �ݹ��м��֧ͬʱλ+1��������һ���ַ���
	void put(string str, string value) {
		_root = _put(_root, str, value,0);
	}
	Node* _put(Node* root, string str, string value, int bit) {
		if (root == NULL) {
			root = new Node(str[bit]);
		}
		if (root->_key > str[bit])      root->_left = _put(root->_left, str, value, bit);
		else if (root->_key < str[bit]) root->_right = _put(root->_right, str, value, bit);
		else if (bit < str.size()-1)   //ע-1������������ͷ�ڵ㣬bit��0����
			root->_mid = _put(root->_mid, str, value, bit + 1);  
		else root->_value = value;  //��ʾ�Ѳ������һ���ַ�����ע�Ͳ��������һ���ַ���
		return root;
	}

	//�����ַ���
	//1������ַ����ң���ÿ�Ҹ�һ���ַ����ַ�ƴ����һ���ҵ����һ���ַ��򷵻ظýڵ�
	//2���ڵ�Ϊ�գ���δ�ҵ�
	//���ȴﵽĩβʱ������ڵ��valueֵ��Ϊ�գ���NULL��
	//3��С�ڽڵ��ַ�������ݹ�
	//4�����ڽڵ��ַ������ҵݹ�
	//5�����ڽڵ��ַ�����ݹ��м��֧��ͬʱ�ַ�λ��+1�������¸��ַ���
	//ע��ÿ��λ�õݹ鶼��return

	string get(string str) {
		Node* cur = _get(_root, str, 0);
		if (cur) {
			return cur->_value;
		}
		return "";
	}
	Node* _get(Node* root, string str, int bit) {
		if (root == NULL) return NULL;
		if (str[bit] < root->_key) 
			return _get(root->_left, str, bit);
		else if (str[bit] > root->_key) 
			return _get(root->_right, str, bit);
		else if (bit < str.size() - 1) 
			return _get(root->_mid, str, bit + 1);
		else return root;  //������ͬ�����ظýڵ�
	}

	//ɾ������
	//1���ݹ���ң����ҽ��շ���ֵ������ָ����
	//1�����ҵ�ɾ���ڵ㣬���������һ���ַ�λ�ã����ýڵ��value��Ϊ����
	//2�����ɾ���ڵ��������ָ����Ϊ�գ���ɾ���ýڵ㣬������NULL���򷵻ظýڵ�
 
	void deleteKye(string str) {
		_deleteKey(_root, str,0);
	}
	Node* _deleteKey(Node* root, string str,int bit) {
		if (root == NULL) return NULL;
		if (root->_key > str[bit]) {
			root->_left = _deleteKey(root->_left, str, bit);
		}
		else if (root->_key < str[bit]) {
			root->_right = _deleteKey(root->_right, str, bit);
		}
		else if (bit < str.size()-1) {
			root->_mid = _deleteKey(root->_mid, str, bit+1);
		}
		else {
			root->_value = "";
		}
		if (root->_value.size() > 0) return root;
		if (root->_left == NULL &&
			root->_mid == NULL &&
			root->_right == NULL) {
			delete root;
			return NULL;
		}
		return root;
	}

	//���൥������������������ͨ�������������ƣ��˴�����ʵ�֡�

private:
	Node* _root;
};

void test_TST() {
	TSTree tst;
	tst.put("ok", "���");
	tst.put("oky", "�ɹ�");
	tst.put("osk", "����");
	tst.put("shell", "���");
	tst.put("all","����");

	cout << tst.get("ok") << endl;
	cout << tst.get("oky") << endl;
	cout << tst.get("sk") << endl;
	cout << tst.get("shell") << endl;
	cout << tst.get("all") << endl;
	cout << tst.get("osk") << endl;

	cout << "delete" << endl;
	tst.deleteKye("shell");
	cout << tst.get("shell") << endl;
	tst.deleteKye("osk");
	tst.deleteKye("oky");

	cout << "get" << endl;
	cout << tst.get("ok") << endl;
	cout << tst.get("oky") << endl;
	cout << tst.get("sk") << endl;
	cout << tst.get("shell") << endl;
	cout << tst.get("all") << endl;
	cout << tst.get("osk") << endl;

}

int main() {
	test_TST();
	return 0;
}
