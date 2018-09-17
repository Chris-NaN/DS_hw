#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//�ڵ�node
typedef struct node{
	string val;
	double number;
	struct node *next;
	struct node *above;
}Node,*pnode;
//ջ
class stack{
public:
	int size;
	pnode top;
	pnode bottom;
	/*��������ӵ�double num��Ϊ�˼����ʱ��ת��double����ȥת��string*/
	stack(string val,double num);//create stack
	bool Push(string val,double num);//push node
	bool Pop();
	bool Isempty();
	int Stack_size();
	string Get_top();/*û�õ�*/
	bool visit();
	// bool del_node();
	bool Destroy_stack();
};
/*create stack*/
stack::stack(string val,double num){
	pnode header = new Node;
	this -> top = header;
	this -> bottom = header;
	this -> size = 1;
	header -> next = NULL;//ջ����һ��
	header -> above = NULL;//ջ����һ��
	header -> val = val;
	header -> number = num;
	return;
};
bool stack::Push(string val,double num){
	pnode node = new Node;
	this -> top ->above = node;
	node -> next = this -> top;
	node -> above = NULL;
	node -> val = val;
	node -> number = num;
	this -> size++;
	this -> top = node;
	return true;
}

bool stack::Pop(){
	if (this->size<=0){
		this -> top = NULL;
		return false;
	}
	pnode node;
	node = this -> top;
	this -> top = this -> top ->next;
	this -> size--;
	delete node;
	return true;
}
bool stack::Isempty(){
	if (this -> size == 0){
		return true;
	}else{
		return false;
	}
};
int stack::Stack_size(){
	return this -> size;
};
string stack::Get_top(){
	return this -> top ->val;
};
bool stack::Destroy_stack(){
	pnode node;
	if (this -> Isempty() == false){
		node = this -> top;
		this -> top = this -> top -> next;
		delete node;
	}
	return true;
};
bool stack::visit(){
	if (this -> size ==0){
		cout<<"empty"<<endl;
	}
	pnode node = this -> top;
	while (size--){
		cout<<node -> val<<endl;
		node = node -> next;
	}
	return true;
}


//�ж�string���Ƿ�������
bool isdigit(string str){
	double num;
	char c;
	stringstream ss(str);
	if (!(ss >> num)){
		return false;
	}
	if (ss >> c){
		return false;
	}
	return true;
}
//�ж�string���Ƿ��ǲ�����
bool isoperator(string str){
	string op = "()+-*/";
	if (str=="(" || str==")"){
		return true;
	}else if(str=="+" || str=="-"){
		return true;
	}else if(str=="*" || str=="/"){
		return true;
	}else{
		return false;
	}
}
//�ж��Ƿ��ǵ㣬û�õ�����
bool isdot(string str){
	return str==".";
}
//string ת double
double str_to_db(string str){
	double rst = atof(str.c_str());
	return rst;
}
//���������ȼ�
bool priority(string s1,string s2){
	if (s1=="(" || s2 == "("){
		return false;
	}
	if ((s1=="-"||s1=="+")&&(s2=="*"||s2=="/")){
		return false;
	}
	return true;
}

stack *infix_to_suffix(stack* ins){
	stack* op;//�������
	stack* suf;//���׺���ʽ
	pnode node = ins -> bottom;//�ڵ��ջͷ���ף���ʼ
	int loop_count = ins->size;
	//��߳�ʼ��Ϊ��֮����new����emm�Ǹ�triky�ĵط�
	op = new stack("0",0);
	suf = new stack("0",0);
	op->Pop();
	suf->Pop();


	int i;
	for (i=loop_count;i>0; i--){//�ӵ������ڵ㿪ʼѭ��
		if (isdigit(node->val)){//����ֱ��push����׺stack
			//���������漰push��ز�����Ҫ�ж��Ƿ�Ϊ��ջ����ջҪ����newһ��
			if (suf->Isempty()){
				suf = new stack(node->val,0);
			}else{
				suf->Push(node->val,0);
			}
			node = node->above;
			continue;
		}
		if (isoperator(node -> val)){
			if (op->Isempty()){//������ջ��ֱ��push
				op = new stack(node->val,0);
				node = node -> above;
				continue;
			}

			if (node->val == ")"){//�����")"��"("֮��Ĳ�������push����׺stack
				for (int j = 500;j>=0;j--){
					if (op->top->val == "("){
						op -> Pop();
						break;
					}
					suf -> Push(op->top->val,0);
					op->Pop();
				}
				node = node->above;
				continue;
			}
			//node->val ���ȼ�С�ڵ��� opջ�����������ȼ���push opջ��������
			if (priority(op->top->val,node->val)){
				suf->Push(op->top->val,0);
				op->Pop();
				int size = op->size;
				for (int k = 0;k<size;k++){
					if (!priority(op->top->val,node->val)){
						break;
					}
					suf->Push(op->top->val,0);
					op->Pop();
				}
				if (op->Isempty()){
					op = new stack(node->val,0);
				}else{
					op -> Push(node->val,0);
				}
				node = node->above;
			//node->val ���ȼ����� opջ�����������ȼ���ֱ��push
			}else{
				if (op->Isempty()){
					op = new stack(node->val,0);
				}else{
					op -> Push(node->val,0);
				}
				node = node->above;
			}
			// //�������ֱ��push��opջ
			// if (op->Isempty()){
			// 	op = new stack(node->val);
			// }else{
			// 	op -> Push(node->val);
			// }
			// node = node->above;
		}
	}
	//������һ��opջ
	while (!op->Isempty()){
		suf -> Push(op->top->val,0);
		op -> Pop();
	}
	return suf;
}

double calculate(stack* suf){
	//start from header
	pnode node = suf -> bottom;
	//to store number
	stack* num = new stack("",str_to_db(node->val));
	node = node->above;
	int count = suf->size-1;
	//����ջ
	for (int i = count;i>0;i--){
		//������push��numջ
		if (isdigit(node->val)){
			if (num->Isempty()){
				num = new stack("",str_to_db(node->val));
			}else{
				num->Push("",str_to_db(node->val));
			}
			node = node -> above;
			continue;
		}else{//�ǲ���������numջ���ϲ�������������pop�����ѽ��push��numջ
			if (node -> val == "+"){//a+b
				double b = num->top->number;
				double a = num->top->next->number;
				num->Pop();
				num->Pop();
				double rst = a+b;
				//�������ֱ��push��ջ��
				if (num->Isempty()){
					num = new stack("",rst);
				}else{
					num->Push("",rst);
				}
				node = node -> above;
				continue;//continueֱ�ӽ����´�ѭ�����ӿ���ٶ�
			}
			if (node -> val == "-"){//a-b
				double b = num->top->number;
				double a = num->top->next->number;
				num->Pop();
				num->Pop();
				double rst = a-b;
				if (num->Isempty()){
					num = new stack("",rst);
				}else{
					num->Push("",rst);
				}
				node = node -> above;
				continue;
			}
			if (node -> val == "*"){//a*b
				double b = num->top->number;
				double a = num->top->next->number;
				num->Pop();
				num->Pop();
				double rst = a*b;
				if (num->Isempty()){
					num = new stack("",rst);
				}else{
					num->Push("",rst);
				}
				node = node -> above;
				continue;
			}
			if (node -> val == "/"){//a/b
				double b = num->top->number;
				double a = num->top->next->number;
				num->Pop();
				num->Pop();
				double rst = a/b;
				if (num->Isempty()){
					num = new stack("",rst);
				}else{
					num->Push("",rst);
				}
				node = node -> above;
			}
		}
	}
	double r = num->top->number;
	num->Destroy_stack();
	return r;
}

int main(){
	string str;
	string tmp_str;
	string number = "";
	int i;
	int count = 0;
	stack* s;

  // getline(cin,str);
	while (getline(cin,str)){
		/*��stack��洢��һ��������֮ǰ������*/
		tmp_str = str[count];
		while (!isoperator(tmp_str)){
			if (tmp_str!=" "){//���˿ո�
				number+=tmp_str;
			}
			count++;
			tmp_str = str[count];
		}
		if (number!=""){
				s = new stack(number,0);
		}else{
				s = new stack(tmp_str,0);
				count++;
		}

		number="";
		/*��stack��洢��һ�����������һ��������֮������ֺͲ�����*/
		for (i=count;i<str.length();i++){
			tmp_str = str[i];
			if (!isoperator(tmp_str)){
				if (tmp_str!=" "){
					number+=tmp_str;
				}
			}else{
				if (number!=""){
					s->Push(number,0);
					number="";
				}
				s->Push(tmp_str,0);
			}
		}
		/*�洢���һ��������֮�������*/
		if (number!=""){
			s->Push(number,0);
			number="";
		}
		count = 0;
		/*����˺�ַ���������������push����֮ǰ�ռ�����������push���������һ���������������push*/
		stack* suf_ = infix_to_suffix(s);
		// suf_->visit();
		double result = calculate(suf_);
		// cout<<"infix:"<<endl;
		// s->visit();
		// str += ",hello!";
		// cout<<result<<endl;
		printf("%f\n",result);
		s->Destroy_stack();
		suf_->Destroy_stack();
	}
	return 0;
}
