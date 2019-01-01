//三相单词查找树
//三相单词查找树是单词查找树的该进，当R（字符表）很大时可节省空间
//三相单词查找树结构：
//由键值key(字符)，value（注释），三个指针域构成（left,mid,right）
//left--比key值小，mid--等于key值，right--大于key值
//时间复杂度：O（1.39logN)
//空间复杂度：64N-64NW
//适用于非随机的键值

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

	//三相进行逐位递归查找插入位置，
	//节点为空则创建节点，并将该位字符插入其中
	//到达最后一个字符时，将注释插入在该节点中
	//如果字符小于节点字符，则节点左 = 左递归
	//如果字符大于节点字符，则节点右 = 右递归
	//如果当前位不为最后位（小于当前字符串长），节点mid = 递归中间分支同时位+1（查找下一个字符）
	void put(string str, string value) {
		_root = _put(_root, str, value,0);
	}
	Node* _put(Node* root, string str, string value, int bit) {
		if (root == NULL) {
			root = new Node(str[bit]);
		}
		if (root->_key > str[bit])      root->_left = _put(root->_left, str, value, bit);
		else if (root->_key < str[bit]) root->_right = _put(root->_right, str, value, bit);
		else if (bit < str.size()-1)   //注-1是由于树不含头节点，bit从0算起
			root->_mid = _put(root->_mid, str, value, bit + 1);  
		else root->_value = value;  //表示已插入最后一个字符，则将注释插入在最后一个字符处
		return root;
	}

	//查找字符串
	//1、逐个字符查找，并每找个一个字符将字符拼接在一起，找到最后一个字符则返回该节点
	//2、节点为空，则未找到
	//长度达到末尾时，如果节点的value值不为空，则返NULL。
	//3、小于节点字符，则左递归
	//4、大于节点字符，则右递归
	//5、等于节点字符，则递归中间分支，同时字符位置+1（查找下个字符）
	//注：每个位置递归都加return

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
		else return root;  //长度相同，返回该节点
	}

	//删除单词
	//1、递归查找，并且接收返回值（更新指针域）
	//1、先找到删除节点，即到达最后一个字符位置，将该节点的value置为“”
	//2、如果删除节点的左右中指针域为空，则删除该节点，并返回NULL否则返回该节点
 
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

	//三相单词树的其它操作与普通单词树操作类似，此处不再实现。

private:
	Node* _root;
};

void test_TST() {
	TSTree tst;
	tst.put("ok", "你好");
	tst.put("oky", "成功");
	tst.put("osk", "错误");
	tst.put("shell", "编程");
	tst.put("all","所有");

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
