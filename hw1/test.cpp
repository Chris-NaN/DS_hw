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
        cout << "new ʧ��" << endl;
        return;
    }
    this->Top = node;
    this->Buttom = node;
    this->size = 1;
    node->pNext = NULL;
    node->data = data;
    return;

}

// ��ջ
bool STACK::Push(Item data)
{

    pNode node = new Node;
    if (node == 0)
    {
        cout << "new ʧ��" << endl;
        return false;
    }
    node->pNext = this->Top;
    node->data = data;
    this->size++;
    this->Top = node;
    return true;
}

// ��ջ
bool STACK::Pop()
{
    if (!this->size)
    {
        cout << "ջ������" << endl;
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
// ����վ�ڵ�����Ԫ��
bool STACK::visit()
{
    int size = this->size;
    if (size == 0)
        cout << "���Ǹ���ջ" << endl;
    pNode node = this->Top;
    while (size--)
    {
        cout << node->data << endl;
        node = node->pNext;
    }
    return true;
}

// ����ջ�Ĵ�С
int STACK:: Stack_size()
{
    return this->size;
}

//Ϊ�շ���true
bool STACK::IsEmpty()
{
    if (this->size ==0)
        return true;
    else
        return false;
}
// ���ջ��Ԫ��
Item STACK::GetTOpData()
{
    return this->Top->data;
}

// ���ջ
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
    cout << "�Ѿ��ݻ�ջ"<<endl;
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
//�������ʽ���ɴ��룬num��2-5
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
//doubleתstr
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
