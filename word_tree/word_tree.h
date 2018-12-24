#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>

//单词树：
//1、介绍：用于存放单词的一个树形结构，可以快速的查找，删除单词
//树结构：树的节点由两部分组成，该树不是一个二叉树
//value---一个存放意思,可以为空(代表不是单词)，
//key(next)存放的是下一个节点的地址的数组，数组大小为26（字母个数），数组下标对应单词的字母（0--a...）
//时间复杂度：O(log(R)N); --R=26
//空间复杂度：O（8R+56)*N--O(8R+56)Nw
//单词查找树查找时，直接诼个字符进行匹配，查找效率很高
//当R很大时，空间利用率比较低,适用于较短键和较小的字符表

//总结：
//1、如果空间足够，单词树的效率最高，查找时间复杂度为常数级别，
//对于大型字符表适合使用三相单词树，比较次数是对数级别的。
//二叉查找树的查找是对数级别的

struct WTNode {  
	string _value;  //注释
	WTNode *_next[26]; //下标表示字符（0-25），存放的是下一个节点的地址

	WTNode(string value = "")
		:_value()
		//, _next(NULL)  //手动开辟空间26
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
	//插入
	//1、注：先判断根是否为NULL,为空创建一个节点
	//2、判断是否达到字符串的结尾（bit统计第几个字符），达到结尾更新value，返回退出
	//3、判断节点中该字符对应的next位置是否指向空节点，为空则让该位置指向一个有效节点（指向新创建节点）
	//4、递归该节点中的next位置，同时指向下一个字符

	void put(string key, string value) {
		//先创建一个头节点
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

	void getAll() {  //获取所有字符串
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

	void getMatch(string key) {  //获取匹配的字符串(.表示通配任意字符)
		if (_root == NULL) {
			return;
		}
		vector<string> str;
		_getMatch(_root, key, str, "");
		Print(str);
	}

	//1、遇到NULL节点时退出
	//2、当长度达到给定字符串长度时并且value不为空，将遍历过程记录的字符串保存
	//3、遍历节点中的每个next,达到字符对应的next下标或字符为'.'时进行递归该位置。
	//4、递归下一位置时，拼接上该位置对应的字符
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
			if (i == k || key[bit] == '.') {  //'.'表示任意一个字符
				_getMatch(root->_next[i], key, str, ptr+(char)(i+'a'));
			}
		}
	}

	//遍历key，同时将value不为空的长度记录下来/更新（len）
	//如果遇到空节点时表示已遍历到最大位置，返回记录的长度（len）
	//如果节点的已遍历到最后一个字符，则表示遍历结束，返回记录的长度(len)。
	//递归每一个位，知道遍历结束（key遍历完，遇到空节点）
	//截取key的前len个字符，即为最大前缀单词。

	string longestPrefixOf(string key) { //获取最大前缀匹配的单词
		if (_root == NULL) {
			return "";
		}
		int len = 0;
		len = _longestPrefixOf(_root, key, len, 0);
		return key.substr(0, len);  //截取字符串，从起始位置开始
	}
	int _longestPrefixOf(Node* root, string str, int &len,int bit) {
		if (root == NULL) return len;
		if (root->_value.size() > 0) {  //有注释更新长度
			len = bit;
		}
		if (str.size() == bit) {  //达到最大长度，返回该长度
			return len;
		}
		//递归下一个字符
		int k = getChar(str[bit]);
		return _longestPrefixOf(root->_next[k], str, len, bit + 1);
	}

	//删除：
	//先找到删除节点，然后将该位置value置空，再判断该节点中的next是否为空，不为空返回该节点，若为空将该节点删除。然后返回NULL
	//上层循环/递归接收下层的返回值，用于更新节点中的next。
	//同时若发现value值不为空则说明该节点是有效的，直接返回该节点，不用再判断节点中的next是否为NULL

	//1、采用递归删除，从0bit位开始查找
	//2、达到长度后，将该节点的value置为""。
	//3、递归下一个位并且该位置接收返回的地址
	//4、如果节点的value存在，则说该节点有效，可直接返回该节点而不用再判断next
	//5、遍历节点的next,有不为空的地址，返回该节点地址
	//                 所有地址为空的，删除该节点，并返回NULL。

	void deleteKey(string key) {
		if (_root == NULL) return;
		_root = deleteKey(_root, key, 0);
	}
	Node* deleteKey(Node* root, string str, int bit) {
		if (root == NULL) return NULL;

		if (bit == str.size()) {
			root->_value = "";
		}
		else {  //未找到该节点位置
			int k = getChar(str[bit]);
			//递归处理下一个字符，并且重新接收下一个字符的地址
			root->_next[k] = deleteKey(root->_next[k], str, bit + 1);
		}
		if (root->_value.size() > 0) {  //存在value，表示节点有效，不能删除，可直接返回节点地址
			return root;
		}
		int i = 0;
		//遍历删除next为空的节点
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
	wr.put("ok", "你好");
	wr.put("oye", "成功");
	wr.put("oyell", "成功了");
	wr.put("oyel", "成功了2");
	wr.put("shell", "编译器");
	cout << wr.get("ok") << endl;
	cout << wr.get("oyell") << endl;
	cout << wr.get("shell") << endl;

	wr.getAll();
	wr.getMatch("shell");
	wr.getMatch("o..");

	cout << "最大前缀" << endl;
	cout << wr.longestPrefixOf("shellll") << endl;
	cout << wr.longestPrefixOf("o") << endl;
	cout << wr.longestPrefixOf("oyelllss") << endl;

	wr.deleteKey("oyell");
	//wr.deleteKey("oyel");
	wr.deleteKey("oye");
	wr.getAll();
}