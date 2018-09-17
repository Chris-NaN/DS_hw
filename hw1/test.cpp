#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <limits>

using namespace std;
typedef int Item;

typedef struct node{
        Item data;
        struct node *pNext;
} Node, *pNode;
class STACK{
public:
        int size;
        pNode Top;
        pNode Buttom;
public: STACK(Item data);
public: bool Push(Item data);
        bool Pop();
        bool visit();
        bool IsEmpty();
        int Stack_size();
        Item GetTOpData();
        bool ClearStack();
        bool DestroyStack();
};
STACK::STACK(Item data)
{
    pNode node = new Node;
    if (node == 0)
    {
        cout << "new 失败" << endl;
        return;
    }
    this->Top = node;
    this->Buttom = node;
    this->size = 1;
    node->pNext = NULL;
    node->data = data;
    return;

}

// 进栈
bool STACK::Push(Item data)
{

    pNode node = new Node;
    if (node == 0)
    {
        cout << "new 失败" << endl;
        return false;
    }
    node->pNext = this->Top;
    node->data = data;
    this->size++;
    this->Top = node;
    return true;
}

// 出栈
bool STACK::Pop()
{
    if (!this->size)
    {
        cout << "栈到底了" << endl;
        this->Top = NULL;
        return false;
    }
    pNode node;
    Item data;
    data = this->Top->data;
    node = this->Top;
    this->size--;
    this->Top = this->Top->pNext;
    delete node;
    return true;
}
// 遍历站内的所有元素
bool STACK::visit()
{
    int size = this->size;
    if (size == 0)
        cout << "这是个空栈" << endl;
    pNode node = this->Top;
    while (size--)
    {
        cout << node->data << endl;
        node = node->pNext;
    }
    return true;
}

// 返回栈的大小
int STACK:: Stack_size()
{
    return this->size;
}

//为空返回true
bool STACK::IsEmpty()
{
    if (this->size ==0)
        return true;
    else
        return false;
}
// 获得栈顶元素
Item STACK::GetTOpData()
{
    return this->Top->data;
}

// 清除栈
bool STACK::ClearStack()
{
    while (this->IsEmpty() == false)
    {
        this->Pop();
    }
    return true;
}

bool STACK::DestroyStack()
{
    pNode node = NULL;
    if (this->IsEmpty() == false)
    {
        node = this->Top;
        this->Top = this->Top->pNext;
        delete node;
    }
    cout << "已经摧毁栈"<<endl;
    return true;
}

string doubleToString(double num)
{
    char str[256];
    sprintf(str, "%f", num);
    string result = str;
    return result;

    // ostringstream os;
    // if (os << num)
    //   return os.str();
    // return "invalid conversion";
}
//随机计算式生成代码，num填2-5
string generate(int num){
	float rate = 0.65;
	int length = num*2-1;
	float p = (float) rate*(70-length)/(35*(length-1));
	//printf("%f\n",p);
	int max = RAND_MAX*p;
	string op[] = {"+","-","*","/"};
	int length2[] = {2,3,4,5};
	int i;
	string last = "";
	string output = "";
	for (i=1;i<=num;i++){
		if (rand()<=max){
			int index = rand()%4;
			output += "(" + generate(length2[index]) + ")";
		}else{
			if (rand()%2){
				float operand = 100*(rand()/double(RAND_MAX));
				stringstream stream;
				stream << operand;
				output += stream.str().substr(0,rand()%(8-3+1)+3);
			}else{
				float operand = rand()/double(RAND_MAX);
				stringstream stream;
				stream << operand;
				output += stream.str();
			}
		}
		if (i!=num){
			output += op[rand()%4];
		}
	}
	return output;
}
//double转str
string output(double value)
 {
      int prec= numeric_limits<double>::max_digits10;
      ostringstream stream;
      stream.precision(prec);
      stream << value;
      return stream.str();
}


int main(){
  double num = 1234567.121518;
  string str = output(num);
  // num = str_to_db(str);
  cout<<str<<endl;



  return 0;
}
