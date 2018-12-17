#include<iostream>
using namespace std;
#include<string>
#include<vector>

//低位优先字符串排序
//方法：采用计数排序的方法，逐位排序
//低位优先排序，适用于排序相同固定长短的字符串
//时间复杂度：NW
//空间复杂度：N
//稳定性：稳定

void string_sort(vector<string>& str) {
	int size = str.size();
	if (size < 1) return;
	int len = str[0].size(); //计算一个字符串长度，假设所有字符串长相同
	vector<string> tmp;
	tmp.resize(size);

	int i = 0;
	//根据长度循环排每个位，先排低位
	for (i = len-1; i >= 0; i--) {
		int arr[257] = { 0 };  //用于统计某个字符出现的次数
		int j = 0;
		//统计第j个字符出现某字符的个数
		for (j = 0; j < size; j++) {
			arr[str[j][i]+1]++;
		}
		//根据出现的频率，判断该字符结束的起始下标位置
		for (j = '0'; j <= '9'; j++) {  //注：由于i+1导致，下标取到256造成越界，所以空间要256+1
			arr[j+1] += arr[j];  //第一个下标，从0开始，不处理,数字字符从‘0’--‘9’所以直接从此范围统计即可，减少赋值操作
		}
		//根据统计的结果进行排序
		for (j = 0; j < size; j++) {
			tmp[arr[str[j][i]]++] = str[j];  //取某个字符串的某个字符，根据起始位置进行赋值
		
		}
		//将排序的tmp放回原数组

		for (j = 0; j < size; j++) {
			str[j] = tmp[j];
		}
	}

}

int getChar(string str,int bit) {
	if (str.size() > bit) {  //注size为下标
		return str[bit];
	}
	return -1;
}

//解析：
//1、先将最高位进行排序，排序后等到的是一个分组状态，即最高位相同的字符在一起，并且有序
//2、递归排序最除高位的其它位，并且按组进行递归排序（排字符相同的一部分）
//最终得到的为一个有序的字符串。递归出口就是区间范围
//（1）、先统计某个字符的个数
//（2）、获取字符的结束下标
//（3）、排序，分组
//（4）、放回原数组
//（5）、递归处理分组中的下一个位
//当字符个数小于某值时，使用插入排序剩余的位，可以提高效率

//高位优先的效率高于低位优先，当遇到空格时不会进行处理，并且可以排任意不同长度的字符串
//时间复杂度：O（N)~NW  w--字符串长度，R--字符对应的总个数 N--字符串个数
//空间复杂度：O(N+WR)
//稳定性：稳定

bool greater(string str1,string str2,int bit) {
	//已知前bit位字符串相同，不用比较
	if((int)str1.size() > bit+1 && (int)str2.size() > bit+1)
	return strcmp(str1.c_str()+bit, str2.c_str()+bit) > 0;
}

//插入排序
void insertSort(vector<string> &str, int left, int right,int bit) {
	if (right <= left) return;
	int i = 0;
	for (i = left; i <= right; i++) {  //从前向后排序
		int j = i;  //假设前i个有序，否则从i向前调整
		for (; j > left && greater(str[j - 1], str[j],bit); j--) {
			//交换数据顺序
			swap(str[j], str[j - 1]);
		}

	}
}

void _sort(vector<string>& str,int left,int right,int bit) {
	int k = 10; //跳转插入排序阀值
	if(right <= left+k) {
		insertSort(str, left, right,bit);  //插入排序
		return;
	}
	int count[258] = { 0 };
	vector<string> tmp;
	tmp.resize(right+1);
	//设置阀值，小于w进行插入排序

	//统计字符次数
	int j = 0;
	for (j = left; j <= right; j++) {
		count[getChar(str[j],bit)+2]++;  //数组下标从0开始+1保证字符与下标对应，超出字符长度返回-1，所以再+1
	}
	//统计字符的结束下标
	for (j = 0; j < 256; j++) {
		count[j + 1] += count[j];
	}
	//进行排序,分类
	for (j = left; j <= right; j++) {
		tmp[count[getChar(str[j], bit) + 1]++] = str[j];
	}
	//放回原数组
	for (j = left; j <= right; j++) {  
		str[j] = tmp[j-left];  //注：此处-left,是由于从left开始排序的放到tmp中，tmp存数据时未加left
	}
	//递归排序下一位,递归排同一区间的字符的字符串（字符相同的字符串）
	for (j = 0; j < 256; j++) {
		_sort(str, left+count[j], left+count[j+1]-1, bit+1);
	}
}
//高位优先字符串排序
void stringSortHigh(vector<string>& str) {
	int size = str.size();
	_sort(str, 0, size-1, 0);
}

//三相切分快速排序
//数组划分成三部分：小于key 等于key，大于key
//数组分为：已排序(start,end)和未排序部分（left,right）
//方法：
//循环：start < right
//数值start < key(left)，则进行交换(start,left)，start++,left++;
//数值start > key(left)，则进行交换(start,right)，right--;
//数值start = key(left)，则start++;

//三相切分法适用与具有大量相同重复数据部分的处理。
//对于相同的数据将其排序放在一起，下次处理时不在处理相同的数据部分，因此可以提高排序的速率
//对于排字符串时，先从某个位进行排序，将数组划分成三部分，在对各个部分进行递归排序，
//注：对于相等字符的部分还要进行递归比较下个位（其它数字排序无此部分）
//时间复杂度：N~WN   N--字符串个数，W--字符串长度
//空间复杂度：W+logN
//稳定性：由快排知，不稳定

void threeCutSort(vector<string>& str,int L,int R,int bit) {
	int start = L+1;
	int end = R;
	int left = L;
	int right = R;

	if (L >= R) return;
	//根据第bit位进行排序，即数组划分
	int key = getChar(str[left], bit);  //获取第bit位字符
	while (start <= right) {
		int i = getChar(str[start], bit);
		if (i < key) swap(str[start++], str[left++]);
		else if (i > key) swap(str[start], str[right--]);
		else  start++;
	}
	//bit位字符排序完,数组根据bit划分成三部分
	//小于key ,等于key ,大于key
	//递归在处理各个部分
	threeCutSort(str, L, left-1, bit);  //处理小于部分
	if (key >= 0)  threeCutSort(str, left, right, bit+1);  //处理等于部分的下个位，注：bit存在时进行再处理
	threeCutSort(str,right+1,R,bit);  //处理大于部分
}

void threeCutSort(vector<string> &str) {
	threeCutSort(str, 0, str.size()-1, 0);  //左闭右闭区间
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