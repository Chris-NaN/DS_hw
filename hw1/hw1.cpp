#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//节点node
typedef struct node{
	string val;
	double number;
	struct node *next;
	struct node *above;
}Node,*pnode;
//栈
class stack{
public:
	int size;
	pnode top;
	pnode bottom;
	/*后来额外加的double num是为了计算的时候转完double不再去转回string*/
	stack(string val,double num);//create stack
	bool Push(string val,double num);//push node
	bool Pop();
	bool Isempty();
	int Stack_size();
	string Get_top();/*没用到*/
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
	header -> next = NULL;//栈的下一层
	header -> above = NULL;//栈的上一层
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


//判断string里是否是数字
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
//判断string里是否是操作符
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
//判断是否是点，没用到好像？
bool isdot(string str){
	return str==".";
}
//string 转 double
double str_to_db(string str){
	double rst = atof(str.c_str());
	return rst;
}
//操作符优先级
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
	stack* op;//存操作符
	stack* suf;//存后缀表达式
	pnode node = ins -> bottom;//节点从栈头（底）开始
	int loop_count = ins->size;
	//这边初始化为了之后能new。。emm是个triky的地方
	op = new stack("0",0);
	suf = new stack("0",0);
	op->Pop();
	suf->Pop();


	int i;
	for (i=loop_count;i>0; i--){//从第三个节点开始循环
		if (isdigit(node->val)){//数字直接push到后缀stack
			//以下所有涉及push相关操作都要判断是否为空栈，空栈要重新new一个
			if (suf->Isempty()){
				suf = new stack(node->val,0);
			}else{
				suf->Push(node->val,0);
			}
			node = node->above;
			continue;
		}
		if (isoperator(node -> val)){
			if (op->Isempty()){//操作符栈空直接push
				op = new stack(node->val,0);
				node = node -> above;
				continue;
			}

			if (node->val == ")"){//如果是")"将"("之后的操作符都push到后缀stack
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
			//node->val 优先级小于等于 op栈顶操作符优先级，push op栈顶操作符
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
			//node->val 优先级大于 op栈顶操作符优先级，直接push
			}else{
				if (op->Isempty()){
					op = new stack(node->val,0);
				}else{
					op -> Push(node->val,0);
				}
				node = node->above;
			}
			// //正常情况直接push到op栈
			// if (op->Isempty()){
			// 	op = new stack(node->val);
			// }else{
			// 	op -> Push(node->val);
			// }
			// node = node->above;
		}
	}
	//最后清空一下op栈
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
	//遍历栈
	for (int i = count;i>0;i--){
		//是数字push到num栈
		if (isdigit(node->val)){
			if (num->Isempty()){
				num = new stack("",str_to_db(node->val));
			}else{
				num->Push("",str_to_db(node->val));
			}
			node = node -> above;
			continue;
		}else{//是操作符计算num栈最上层两个，并将其pop掉，把结果push到num栈
			if (node -> val == "+"){//a+b
				double b = num->top->number;
				double a = num->top->next->number;
				num->Pop();
				num->Pop();
				double rst = a+b;
				//结果算完直接push到栈里
				if (num->Isempty()){
					num = new stack("",rst);
				}else{
					num->Push("",rst);
				}
				node = node -> above;
				continue;//continue直接进行下次循环，加快点速度
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
		/*在stack里存储第一个操作符之前的数字*/
		tmp_str = str[count];
		while (!isoperator(tmp_str)){
			if (tmp_str!=" "){//过滤空格
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
		/*在stack里存储第一个操作到最后一个操作符之间的数字和操作符*/
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
		/*存储最后一个操作符之后的数字*/
		if (number!=""){
			s->Push(number,0);
			number="";
		}
		count = 0;
		/*↑手撕字符串，遇到操作符push并把之前收集的数字类型push，最后把最后一个操作符后的数字push*/
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
