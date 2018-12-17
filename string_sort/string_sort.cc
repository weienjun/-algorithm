#include<iostream>
using namespace std;
#include<string>
#include<vector>

//��λ�����ַ�������
//���������ü�������ķ�������λ����
//��λ��������������������ͬ�̶����̵��ַ���
//ʱ�临�Ӷȣ�NW
//�ռ临�Ӷȣ�N
//�ȶ��ԣ��ȶ�

void string_sort(vector<string>& str) {
	int size = str.size();
	if (size < 1) return;
	int len = str[0].size(); //����һ���ַ������ȣ����������ַ�������ͬ
	vector<string> tmp;
	tmp.resize(size);

	int i = 0;
	//���ݳ���ѭ����ÿ��λ�����ŵ�λ
	for (i = len-1; i >= 0; i--) {
		int arr[257] = { 0 };  //����ͳ��ĳ���ַ����ֵĴ���
		int j = 0;
		//ͳ�Ƶ�j���ַ�����ĳ�ַ��ĸ���
		for (j = 0; j < size; j++) {
			arr[str[j][i]+1]++;
		}
		//���ݳ��ֵ�Ƶ�ʣ��жϸ��ַ���������ʼ�±�λ��
		for (j = '0'; j <= '9'; j++) {  //ע������i+1���£��±�ȡ��256���Խ�磬���Կռ�Ҫ256+1
			arr[j+1] += arr[j];  //��һ���±꣬��0��ʼ��������,�����ַ��ӡ�0��--��9������ֱ�ӴӴ˷�Χͳ�Ƽ��ɣ����ٸ�ֵ����
		}
		//����ͳ�ƵĽ����������
		for (j = 0; j < size; j++) {
			tmp[arr[str[j][i]]++] = str[j];  //ȡĳ���ַ�����ĳ���ַ���������ʼλ�ý��и�ֵ
		
		}
		//�������tmp�Ż�ԭ����

		for (j = 0; j < size; j++) {
			str[j] = tmp[j];
		}
	}

}

int getChar(string str,int bit) {
	if (str.size() > bit) {  //עsizeΪ�±�
		return str[bit];
	}
	return -1;
}

//������
//1���Ƚ����λ�������������ȵ�����һ������״̬�������λ��ͬ���ַ���һ�𣬲�������
//2���ݹ����������λ������λ�����Ұ�����еݹ��������ַ���ͬ��һ���֣�
//���յõ���Ϊһ��������ַ������ݹ���ھ������䷶Χ
//��1������ͳ��ĳ���ַ��ĸ���
//��2������ȡ�ַ��Ľ����±�
//��3�������򣬷���
//��4�����Ż�ԭ����
//��5�����ݹ鴦������е���һ��λ
//���ַ�����С��ĳֵʱ��ʹ�ò�������ʣ���λ���������Ч��

//��λ���ȵ�Ч�ʸ��ڵ�λ���ȣ��������ո�ʱ������д������ҿ��������ⲻͬ���ȵ��ַ���
//ʱ�临�Ӷȣ�O��N)~NW  w--�ַ������ȣ�R--�ַ���Ӧ���ܸ��� N--�ַ�������
//�ռ临�Ӷȣ�O(N+WR)
//�ȶ��ԣ��ȶ�

bool greater(string str1,string str2,int bit) {
	//��֪ǰbitλ�ַ�����ͬ�����ñȽ�
	if((int)str1.size() > bit+1 && (int)str2.size() > bit+1)
	return strcmp(str1.c_str()+bit, str2.c_str()+bit) > 0;
}

//��������
void insertSort(vector<string> &str, int left, int right,int bit) {
	if (right <= left) return;
	int i = 0;
	for (i = left; i <= right; i++) {  //��ǰ�������
		int j = i;  //����ǰi�����򣬷����i��ǰ����
		for (; j > left && greater(str[j - 1], str[j],bit); j--) {
			//��������˳��
			swap(str[j], str[j - 1]);
		}

	}
}

void _sort(vector<string>& str,int left,int right,int bit) {
	int k = 10; //��ת��������ֵ
	if(right <= left+k) {
		insertSort(str, left, right,bit);  //��������
		return;
	}
	int count[258] = { 0 };
	vector<string> tmp;
	tmp.resize(right+1);
	//���÷�ֵ��С��w���в�������

	//ͳ���ַ�����
	int j = 0;
	for (j = left; j <= right; j++) {
		count[getChar(str[j],bit)+2]++;  //�����±��0��ʼ+1��֤�ַ����±��Ӧ�������ַ����ȷ���-1��������+1
	}
	//ͳ���ַ��Ľ����±�
	for (j = 0; j < 256; j++) {
		count[j + 1] += count[j];
	}
	//��������,����
	for (j = left; j <= right; j++) {
		tmp[count[getChar(str[j], bit) + 1]++] = str[j];
	}
	//�Ż�ԭ����
	for (j = left; j <= right; j++) {  
		str[j] = tmp[j-left];  //ע���˴�-left,�����ڴ�left��ʼ����ķŵ�tmp�У�tmp������ʱδ��left
	}
	//�ݹ�������һλ,�ݹ���ͬһ������ַ����ַ������ַ���ͬ���ַ�����
	for (j = 0; j < 256; j++) {
		_sort(str, left+count[j], left+count[j+1]-1, bit+1);
	}
}
//��λ�����ַ�������
void stringSortHigh(vector<string>& str) {
	int size = str.size();
	_sort(str, 0, size-1, 0);
}

//�����зֿ�������
//���黮�ֳ������֣�С��key ����key������key
//�����Ϊ��������(start,end)��δ���򲿷֣�left,right��
//������
//ѭ����start < right
//��ֵstart < key(left)������н���(start,left)��start++,left++;
//��ֵstart > key(left)������н���(start,right)��right--;
//��ֵstart = key(left)����start++;

//�����зַ���������д�����ͬ�ظ����ݲ��ֵĴ���
//������ͬ�����ݽ����������һ���´δ���ʱ���ڴ�����ͬ�����ݲ��֣���˿���������������
//�������ַ���ʱ���ȴ�ĳ��λ�������򣬽����黮�ֳ������֣��ڶԸ������ֽ��еݹ�����
//ע����������ַ��Ĳ��ֻ�Ҫ���еݹ�Ƚ��¸�λ���������������޴˲��֣�
//ʱ�临�Ӷȣ�N~WN   N--�ַ���������W--�ַ�������
//�ռ临�Ӷȣ�W+logN
//�ȶ��ԣ��ɿ���֪�����ȶ�

void threeCutSort(vector<string>& str,int L,int R,int bit) {
	int start = L+1;
	int end = R;
	int left = L;
	int right = R;

	if (L >= R) return;
	//���ݵ�bitλ�������򣬼����黮��
	int key = getChar(str[left], bit);  //��ȡ��bitλ�ַ�
	while (start <= right) {
		int i = getChar(str[start], bit);
		if (i < key) swap(str[start++], str[left++]);
		else if (i > key) swap(str[start], str[right--]);
		else  start++;
	}
	//bitλ�ַ�������,�������bit���ֳ�������
	//С��key ,����key ,����key
	//�ݹ��ڴ����������
	threeCutSort(str, L, left-1, bit);  //����С�ڲ���
	if (key >= 0)  threeCutSort(str, left, right, bit+1);  //������ڲ��ֵ��¸�λ��ע��bit����ʱ�����ٴ���
	threeCutSort(str,right+1,R,bit);  //������ڲ���
}

void threeCutSort(vector<string> &str) {
	threeCutSort(str, 0, str.size()-1, 0);  //����ұ�����
}

void Print(vector<string>& str) {
	int len = str.size();
	int i = 0;
	while (i < len) {
		cout << str[i++] << " ";
	}
	cout << endl;
}

int main() {
	vector<string> str = {
		"123",
		"334",
		"456",
		"524",
		"33",
		"74",
		"680111",
		"947"
	};

	//Print(str);
	//string_sort(str);
	//Print(str);

	Print(str);
	stringSortHigh(str);
	Print(str);

	//Print(str);
	//threeCutSort(str);
	//Print(str);

	return 0; 
}