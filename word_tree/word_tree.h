#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>

//��������
//1�����ܣ����ڴ�ŵ��ʵ�һ�����νṹ�����Կ��ٵĲ��ң�ɾ������
//���ṹ�����Ľڵ�����������ɣ���������һ��������
//value---һ�������˼,����Ϊ��(�����ǵ���)��
//key(next)��ŵ�����һ���ڵ�ĵ�ַ�����飬�����СΪ26����ĸ�������������±��Ӧ���ʵ���ĸ��0--a...��
//ʱ�临�Ӷȣ�O(log(R)N); --R=26
//�ռ临�Ӷȣ�O��8R+56)*N--O(8R+56)Nw
//���ʲ���������ʱ��ֱ���¸��ַ�����ƥ�䣬����Ч�ʺܸ�
//��R�ܴ�ʱ���ռ������ʱȽϵ�,�����ڽ϶̼��ͽ�С���ַ���

//�ܽ᣺
//1������ռ��㹻����������Ч����ߣ�����ʱ�临�Ӷ�Ϊ��������
//���ڴ����ַ����ʺ�ʹ�����൥�������Ƚϴ����Ƕ�������ġ�
//����������Ĳ����Ƕ��������

struct WTNode {  
	string _value;  //ע��
	WTNode *_next[26]; //�±��ʾ�ַ���0-25������ŵ�����һ���ڵ�ĵ�ַ

	WTNode(string value = "")
		:_value()
		//, _next(NULL)  //�ֶ����ٿռ�26
	{
		int i = 0;
		for (; i < 26; i++) {
			_next[i] = NULL;
		}
	}
};

class WTree {
public:
	typedef WTNode Node;
	WTree()
		:_root(NULL)
	{}

	int getChar(char ch) {
		return ch - 'a';
	}
	//����
	//1��ע�����жϸ��Ƿ�ΪNULL,Ϊ�մ���һ���ڵ�
	//2���ж��Ƿ�ﵽ�ַ����Ľ�β��bitͳ�Ƶڼ����ַ������ﵽ��β����value�������˳�
	//3���жϽڵ��и��ַ���Ӧ��nextλ���Ƿ�ָ��սڵ㣬Ϊ�����ø�λ��ָ��һ����Ч�ڵ㣨ָ���´����ڵ㣩
	//4���ݹ�ýڵ��е�nextλ�ã�ͬʱָ����һ���ַ�

	void put(string key, string value) {
		//�ȴ���һ��ͷ�ڵ�
		if (_root == NULL) {
			_root = new Node;
		}
		_put(_root, key, value, 0);
		
	}
	void _put(Node* root, string key, string value, int bit) {
		if (bit == key.size()) {  
			root->_value = value;
			return;
		}
		int k = getChar(key[bit]);
		if (root->_next[k] == NULL) {
			root->_next[k] = new Node;
		}
		_put(root->_next[k], key, value, bit + 1);
	}

	string get(string key) {
		if (_root == NULL) {
			return "";
		}
		return _get(_root, key, 0);
	}

	string _get(Node* root, string key, int bit) {
		if (root == NULL) {
			return "";
		}
		if (bit == (int)key.size()) {
			return root->_value;
		}
		int k = getChar(key[bit]);
		if (root->_next[k] == NULL) {
			return "";
		}
		return _get(root->_next[k], key, bit + 1);
	}

	void getAll() {  //��ȡ�����ַ���
		if (_root == NULL) {
			return;
		}
		vector<string> str;
		string ptr = "";
		_getAll(_root, ptr, str);
		Print(str);
	}
	void _getAll(Node* root, string ptr, vector<string>& str) {
		if (root == NULL) return;
		if (root->_value.size() > 0) {
			str.push_back(ptr);
		}
		int i = 0;
		for (i = 0; i < 26; i++) {
			_getAll(root->_next[i], ptr + (char)(i+'a'), str);
		}
	}
	void Print(vector<string>&str) {
		int size = str.size();
		int i = 0;
		for (; i < size; i++) {
			cout << str[i] << " ";
		}
		cout << endl;
	}

	void getMatch(string key) {  //��ȡƥ����ַ���(.��ʾͨ�������ַ�)
		if (_root == NULL) {
			return;
		}
		vector<string> str;
		_getMatch(_root, key, str, "");
		Print(str);
	}

	//1������NULL�ڵ�ʱ�˳�
	//2�������ȴﵽ�����ַ�������ʱ����value��Ϊ�գ����������̼�¼���ַ�������
	//3�������ڵ��е�ÿ��next,�ﵽ�ַ���Ӧ��next�±���ַ�Ϊ'.'ʱ���еݹ��λ�á�
	//4���ݹ���һλ��ʱ��ƴ���ϸ�λ�ö�Ӧ���ַ�
	void _getMatch(Node* root, string key, vector<string>& str, string ptr) {
		if (root == NULL) {
			return;
		}
		int bit = ptr.size();
		if (key.size() == bit && root->_value.size() > 0) {
			str.push_back(ptr);
		}

		int k = getChar(key[bit]);
		int i = 0;
		for (; i < 26; i++) {
			if (i == k || key[bit] == '.') {  //'.'��ʾ����һ���ַ�
				_getMatch(root->_next[i], key, str, ptr+(char)(i+'a'));
			}
		}
	}

	//����key��ͬʱ��value��Ϊ�յĳ��ȼ�¼����/���£�len��
	//��������սڵ�ʱ��ʾ�ѱ��������λ�ã����ؼ�¼�ĳ��ȣ�len��
	//����ڵ���ѱ��������һ���ַ������ʾ�������������ؼ�¼�ĳ���(len)��
	//�ݹ�ÿһ��λ��֪������������key�����꣬�����սڵ㣩
	//��ȡkey��ǰlen���ַ�����Ϊ���ǰ׺���ʡ�

	string longestPrefixOf(string key) { //��ȡ���ǰ׺ƥ��ĵ���
		if (_root == NULL) {
			return "";
		}
		int len = 0;
		len = _longestPrefixOf(_root, key, len, 0);
		return key.substr(0, len);  //��ȡ�ַ���������ʼλ�ÿ�ʼ
	}
	int _longestPrefixOf(Node* root, string str, int &len,int bit) {
		if (root == NULL) return len;
		if (root->_value.size() > 0) {  //��ע�͸��³���
			len = bit;
		}
		if (str.size() == bit) {  //�ﵽ��󳤶ȣ����ظó���
			return len;
		}
		//�ݹ���һ���ַ�
		int k = getChar(str[bit]);
		return _longestPrefixOf(root->_next[k], str, len, bit + 1);
	}

	//ɾ����
	//���ҵ�ɾ���ڵ㣬Ȼ�󽫸�λ��value�ÿգ����жϸýڵ��е�next�Ƿ�Ϊ�գ���Ϊ�շ��ظýڵ㣬��Ϊ�ս��ýڵ�ɾ����Ȼ�󷵻�NULL
	//�ϲ�ѭ��/�ݹ�����²�ķ���ֵ�����ڸ��½ڵ��е�next��
	//ͬʱ������valueֵ��Ϊ����˵���ýڵ�����Ч�ģ�ֱ�ӷ��ظýڵ㣬�������жϽڵ��е�next�Ƿ�ΪNULL

	//1�����õݹ�ɾ������0bitλ��ʼ����
	//2���ﵽ���Ⱥ󣬽��ýڵ��value��Ϊ""��
	//3���ݹ���һ��λ���Ҹ�λ�ý��շ��صĵ�ַ
	//4������ڵ��value���ڣ���˵�ýڵ���Ч����ֱ�ӷ��ظýڵ���������ж�next
	//5�������ڵ��next,�в�Ϊ�յĵ�ַ�����ظýڵ��ַ
	//                 ���е�ַΪ�յģ�ɾ���ýڵ㣬������NULL��

	void deleteKey(string key) {
		if (_root == NULL) return;
		_root = deleteKey(_root, key, 0);
	}
	Node* deleteKey(Node* root, string str, int bit) {
		if (root == NULL) return NULL;

		if (bit == str.size()) {
			root->_value = "";
		}
		else {  //δ�ҵ��ýڵ�λ��
			int k = getChar(str[bit]);
			//�ݹ鴦����һ���ַ����������½�����һ���ַ��ĵ�ַ
			root->_next[k] = deleteKey(root->_next[k], str, bit + 1);
		}
		if (root->_value.size() > 0) {  //����value����ʾ�ڵ���Ч������ɾ������ֱ�ӷ��ؽڵ��ַ
			return root;
		}
		int i = 0;
		//����ɾ��nextΪ�յĽڵ�
		for (; i < 26; i++) {
			if (root->_next[i]) {
				return root;
			}
		}
		delete root;
		return  NULL;
	}

private:
	Node *_root;
};


void test_WTree() {
	WTree wr;
	wr.put("ok", "���");
	wr.put("oye", "�ɹ�");
	wr.put("oyell", "�ɹ���");
	wr.put("oyel", "�ɹ���2");
	wr.put("shell", "������");
	cout << wr.get("ok") << endl;
	cout << wr.get("oyell") << endl;
	cout << wr.get("shell") << endl;

	wr.getAll();
	wr.getMatch("shell");
	wr.getMatch("o..");

	cout << "���ǰ׺" << endl;
	cout << wr.longestPrefixOf("shellll") << endl;
	cout << wr.longestPrefixOf("o") << endl;
	cout << wr.longestPrefixOf("oyelllss") << endl;

	wr.deleteKey("oyell");
	//wr.deleteKey("oyel");
	wr.deleteKey("oye");
	wr.getAll();
}