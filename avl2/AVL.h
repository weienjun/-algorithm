#include<iostream>
#include<assert.h>
#include<math.h>

using namespace std;

template<class T,class V>
struct AvlNode
{
	T _key;//��ֵ
	V _value;//����
	int _bf;//ƽ������
	AvlNode<T,V>* _left;
	AvlNode<T,V>* _right;
	AvlNode<T,V>* _parent;
	AvlNode(const T& key,const V& value)
		:_key(key)
		,_value(value)
		,_bf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};
template<class T,class V>
class AVL
{
	typedef AvlNode<T,V> Node;
public:
	AVL()
		:_root(NULL)
	{}

	bool Push_Back(const T& Key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(Key,value);//���ڵ�
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;

		//�������ҵ��ɲ���λ��
		while(cur)
		{
			if(cur->_key < Key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > Key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//��ֵ��ͬ����
				return false;
		}

		//�����½ڵ�
		cur = new Node(Key,value);
		if(parent->_key < Key)//�������Ҳ�
		{
			parent->_right = cur;
		}
		else//���������
		{
			parent->_left = cur;
		}
		cur->_parent = parent;//��ʼ�½ڵ�ĸ���

		//����ƽ������
		while(parent)  //ѭ������
		{
			//ƽ�����Ӽ���(����˫��(��)�ڵ������)
			if(parent->_left == cur)//������˫�׵���
				parent->_bf--;      //ƽ�����Ӽ�-1
			else                    //������˫�׵���
				parent->_bf++;      //ƽ������+1

			//����ƽ�����ӵ���ֵ�ж��Ƿ������
			if(parent->_bf == 0)//ƽ�ⲻ�õ��������˳�
				break;
			else if(parent->_bf == 1 || parent->_bf == -1)//��ƽ�⣬����Ϊ1--���ϻ���
			{
				cur = parent;
				parent = cur->_parent;
			}
			//��ƽ�������
			else//��ƽ�⣬����Ϊ2��ƽ�⴦��
			{
				if(parent->_bf == 2)//�����Ҳ೤
				{
					if(cur->_bf == -1)//�������������ڵ����
						Lotatel(parent);//����
					else             //�������������ڵ��Ҳ�
						Rotaterl(parent);//������
				}
				else//������೤
				{
					if(cur->_bf == -1)  //�������������ڵ����
						Rotatel(parent);//����
					else                //�������������ڵ����
						Rotatelr(parent);//������
				}
				break;
			}
			//ƽ�⴦��
			//1������ڽϸ����������ҽڵ���(�ҽڵ���һ���)���ұ���---����
			//2������ڽϸ�����������ڵ���(��ڵ�������)������ҳ�---����
			//3������ڽϸ�����������ڵ���(��ڵ�������)--�ұ���---�ң���˫������������1�֣��ڽ�������
			//4������ڽϸ����������ҽڵ���(�ҽڵ�������)--����ҳ�---����˫������������2�֣��ڽ�������
		}
		return true;
	}

	void Rotatelr(Node* parent)//����˫��
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;
		int bf = sublr->_bf;//��¼��ת֮ǰ������ֵ

		Lotatel(parent->_left);//����
		Rotatel(parent);//����
		//��������ֵ
		if(bf == -1)
			subl->_bf = 1;
		else if(bf == 1)
			parent->_bf = -1;
	}

	void Rotaterl(Node* parent)//�ң���˫��
	{
		Node* subr = parent->_right;
		Node* subrl = subr->_left;
		int bf = subrl-> _bf;//��¼��ת֮ǰ��

		Rotatel(parent->_right);//����
		Lotatel(parent);//����

		if(bf == 1)
			parent->_bf = -1;
		else if(bf == -1)
			subr->_bf = 1;
	}

	void Lotatel(Node* parent)//����---���ڵ���ҳ�
	{
		//parent������ֵΪ2�Ľڵ�
		Node* subr = parent->_right;//��ȡ���ڵ��������
		Node* subl = subr->_left;   //��ȡ������������

		//�ı�ָ����ʵ�����ĵ���
		parent->_right = subl;     //���ڵ����ָ��subr������
		if(subl)//��������������
			subl->_parent = parent;//����subr���ӵĸ��ڵ�
		subr->_left = parent;    //����subr����ָ��ָ�򸸽ڵ�
		Node* pparent = parent->_parent;//��ȡԭ���ڵ�ĸ���
		subr->_parent = pparent;//����subr���׽ڵ�ĸ���
		parent->_parent = subr;//subr�����µĸ��׽ڵ�

		if(parent == _root)//���ڵ�Ϊ���ڵ�
			_root = subr;//���ĸ��ڵ�
		else
		{
			if(pparent->_left == parent)//ԭ���׽ڵ������
				pparent->_left = subr;//�¸��׽ڵ���������ࣨԭ���׽ڵ�ĸ��׽ڵ���ࣩ
			else
				pparent->_right = subr;////�¸��׽ڵ��������Ҳ�
		}
		//���½ڵ�����ֵ
		parent->_bf = subr->_bf = 0;
		parent->_parent = NULL;
	}

	void Rotatel(Node* parent)//����
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;

		parent->_left = sublr;
		if(sublr)//���ڸ��ڵ��������������ڵ�
			sublr->_parent = parent;//�����丸�ڵ�
		subl->_right = parent;
		Node* pparent = parent->_parent;//ԭ���ڵ�ĸ���
		subl->_parent = pparent;
		parent->_parent = subl;

		if(parent == _root)//���ڵ�Ϊ���ڵ�
			_root = subl;//���ĸ��ڵ�
		else
		{
			if(pparent->_left == parent)
				pparent->_left = subl;
			else
				pparent->_right = subl;
		}
		//���½ڵ�����
		parent->_bf = subl->_bf = 0;
		parent->_parent = NULL;
	}

	void print()
	{
		print(_root);
	}
	void print(Node* cur)
	{
		if(cur == NULL)
			return ;
		print(cur->_left);
		cout << cur->_key << ' ';
		print(cur->_right);
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}
	bool IsBalance(Node* root)
	{
		if(root == NULL)
			return true;
		int leftH = Height(root->_left);
		int rightH = Height(root->_right);
		if(abs(leftH-rightH) >= 2)//��ֵ����2����Ϊƽ����
			return false;
		return IsBalance(root->_left) && IsBalance(root->_right);//�ݹ���������
	}
	size_t Height(Node* cur)
	{
		if(cur == NULL)
			return 0;

		static size_t n1 = 1;//���ڵ�Ϊ��һ��
		static size_t n2 = 1;

		n1 = Height(cur->_left);
		n2 = Height(cur->_right);
		if(cur->_left || cur->_right)//��������������Ľڵ�Ž��бȽ�
		return (n1 > n2 ? n1 : n2)++;
		return 1;//ֻ�и��ڵ�
	}

private:
    Node* _root;
};

void AVL_test()
{
	int arr[] = {16,3,7,11,9,26,18,14,15};
	AVL<int,int> a;
	int i = 0;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
		a.Push_Back(arr[i],i);
	a.print();
	cout << endl;
	cout << a.IsBalance() << endl;
}