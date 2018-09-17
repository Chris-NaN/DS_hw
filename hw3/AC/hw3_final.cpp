#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class HuffNode{
public:
  HuffNode();
  unsigned char mychar;  /*or char data?*/
  int weight;
  int min_weight;
  HuffNode *lchild,*rchild;
};
typedef HuffNode* Eletype;

class Min_heap{
public:
  Min_heap();
  int size; //number of nodes
  int cap; //capacity of array
  Eletype *arr; //array to store node
  bool insert(Eletype node);
  Eletype remove_root();
};

HuffNode::HuffNode(){
  this->mychar = '\0';
  this->lchild = NULL;
  this->rchild = NULL;
}


Min_heap::Min_heap(){
  this -> size = 0;
  this -> cap =1;
  this->arr = new Eletype[1];
  this->arr[0] = 0;
  return;
}
int cmp_(int a,int b){
  if (a>b) return 1;
  if (a<b) return -1;
  return 0;
}
int Min(int a,int b){
  if(a>b){
    return b;
  }else{
    return a;
  }
}
int32_t swapInt32(int32_t value)
{
     return ((value & 0x000000FF) << 24) |
               ((value & 0x0000FF00) << 8) |
               ((value & 0x00FF0000) >> 8) |
               ((value & 0xFF000000) >> 24) ;
}
bool Min_heap::insert(Eletype node){
  int index;
  if (this -> size+1==this -> cap){
    Eletype *new_arr = new Eletype[this->cap*2];
    this -> cap *= 2;
    for (int i=0;i<=this->size;i++){
      new_arr[i] = this->arr[i];
    }
    delete this->arr;
    this -> arr = new_arr;
    //内存扩展完毕
    this -> size+=1;
    index = this->size;
    //跟父节点交换
    /*先比权重，权重相同但ASCII码权重小优先级高，上浮*/
    while ((index>>1!=0) &&(cmp_(this->arr[index>>1]->weight,node->weight)==1||
    (cmp_(this->arr[index>>1]->weight,node->weight)==0&&cmp_(this->arr[index>>1]->min_weight,node->min_weight)==1))){
      this->arr[index] = this->arr[index>>1];
      index = index>>1;
    }
    this->arr[index] = node;
    return true;
  }else{
    this -> size+=1;
    index = this->size;
    while ((index>>1!=0) &&(cmp_(this->arr[index>>1]->weight,node->weight)==1||
    (cmp_(this->arr[index>>1]->weight,node->weight)==0&&cmp_(this->arr[index>>1]->min_weight,node->min_weight)==1))){
      this->arr[index] = this->arr[index>>1];
      index = index>>1;
    }
    this->arr[index] = node;
    return true;
  }
  return false;
}
Eletype Min_heap::remove_root(){
  if (this->size==0){
    return 0;
  }
  Eletype root = this->arr[1];
  Eletype element = this -> arr[this->size];
  this -> size -= 1;
  int index;
  int new_index;
  //跟子节点比较
  for (index=1;index<=this->size/2;index=new_index){
    //右子节点不存在或右子节点大于左子节点，改index
    HuffNode* lnode = this->arr[2*index];
    HuffNode* rnode = this->arr[2*index+1];
    if ((2*index+1>this->size) || cmp_(lnode->weight,rnode->weight)==-1 ||
    (cmp_(lnode->weight,rnode->weight)==0&&cmp_(lnode->min_weight,rnode->min_weight)==-1)){
      new_index=2*index;
    }else{
      new_index = 2*index+1;
    }

    if (cmp_(this->arr[new_index]->weight,element->weight)==-1||
    (cmp_(this->arr[new_index]->weight,element->weight)==0&&cmp_(this->arr[new_index]->min_weight,element->min_weight)==-1)){
      this->arr[index] = this->arr[new_index];
    }else{
      break;
    }
  }
  this->arr[index] = element;
  //如果数组过大，缩小数组
  if (this->cap/2>this->size+1){
    Eletype *new_arr = new Eletype[this->cap/2];
    this -> cap /= 2;
    for (int i=0;i<=this->size;i++){
      new_arr[i] = this->arr[i];
    }
    delete this->arr;
    this -> arr = new_arr;
  }
  return root;

}

void preOrder(HuffNode* node,string strarr[],string str){
  if (node->rchild==NULL && node->lchild==NULL){
    strarr[(int) node->mychar] = str;
    return;
  }
  str += "0";
  preOrder(node->lchild,strarr,str);
  str = str.substr(0,str.length()-1);
  str += "1";
  preOrder(node->rchild,strarr,str);
  str = str.substr(0,str.length()-1);
}
string num2str(int i){
  stringstream ss;
  ss<<i;
  return ss.str();
}

int binstr_to_bin(string str){  /*二进制字符串转int十进制*/
  int j;
  int oct_ecd,mul;
  oct_ecd=0;
  mul=1;
  for (j=str.length()-1;j>=0;j--){
    if (str[j]=='1'){
      oct_ecd+=mul;
    }
    mul*=2;
  }
  return oct_ecd;
}
string reverse(string str){
  char tmp;
  for (int i=0,j=str.length()-1;i<j;i++,j--){
    tmp=str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
  return str;
}
string hex_to_bin(int num){
  string str="";
  ((num&(1<<7))!=0)?str+="1":str+="0";
  ((num&(1<<6))!=0)?str+="1":str+="0";
  ((num&(1<<5))!=0)?str+="1":str+="0";
  ((num&(1<<4))!=0)?str+="1":str+="0";
  ((num&(1<<3))!=0)?str+="1":str+="0";
  ((num&(1<<2))!=0)?str+="1":str+="0";
  ((num&(1<<1))!=0)?str+="1":str+="0";
  ((num&(1))!=0)?str+="1":str+="0";
  return str;
}
int main() {

  // freopen("test.in","r",stdin);//读入文件
  // freopen("test.out","w",stdout);//输出文件
  int i,charAt,num;
  char get_char;
  unsigned char ch,get_unch;
  string str,six_char;

  Min_heap *min= new Min_heap;
  for (i=0;i<6;i++){
    cin.get(get_char);
    six_char+=get_char;
  }

  if (six_char=="ENCODE"){ /*argument is "ENCODE"*/

    int charr[256];
    string oristr; /*用于储存编码顺序*/
    string strarr[256]; //存编码101
    for (i=0;i<256;i++){
      strarr[i] = "";
    }

    while (cin.get(get_char)){
      get_unch = get_char;
      charr[(int)get_unch]++;
    }


    string huf = "HUFFMAN\0";
    for (i=0;i<=huf.length();i++){
      // printf("%c",huf[i]);
      cout<<(unsigned char)huf[i];
    }

    for (i=0;i<256;i++){  /*打印ASCII码数量*//*反着打*/
      int tmp = charr[i];
      int p;
      for (int j=0;j<4;j++){
        if (j==0){
          p = tmp%256;
          // printf("%c",tmp&0x000000FF); /*位运算有bug*/
          cout<<(unsigned char)p;
        }else if (j==1){
          tmp = tmp/256;
          p = tmp%256;
          // printf("%c",tmp&0x0000FF00 );
          cout<<(unsigned char)p;
        }else if (j==2){
          tmp = tmp/256;
          p = tmp%256;
          // printf("%c",tmp&0x00FF0000 );
          cout<<(unsigned char)p;
        }else{
          tmp = tmp/256;
          p = tmp%256;
          // printf("%c",tmp&0xFF000000 );
          cout<<(unsigned char)p;
        }
      }
      // if (charr[i]!=0){ /*打印编码测试，删*/
      //     cout<<dec<<i<<endl;
      //     cout<<strarr[i]<<endl;
      //
      // }
    }

    for (i=0;i<256;i++){ //将节点push到min_heap
      if (charr[i]!=0){
        HuffNode* new_node = new HuffNode;
        new_node->mychar = (unsigned char) i;
        new_node->weight = charr[i];
        new_node->min_weight = i;
        min->insert(new_node);
      }
    }

    if (min->size==0){
      return 0;
    }
    while (min->size>1){  /*建树*/
      HuffNode* parent_node = new HuffNode;
      HuffNode* l_node = new HuffNode;
      HuffNode* r_node = new HuffNode;
      r_node = min->remove_root();
      l_node = min->remove_root();
      parent_node->lchild = l_node;
      parent_node->rchild = r_node;
      parent_node->weight = l_node->weight+r_node->weight;
      parent_node->min_weight = Min(l_node->min_weight,r_node->min_weight);
      min->insert(parent_node);
    }

    string order;
    preOrder(min->arr[1],strarr,order);

    /*以下是打印*/
    cin.clear();
    cin.seekg(6,cin.beg); /*重新读取*/

    string encode;
    while (cin.get(get_char)){
      get_unch = get_char;
      encode += strarr[(int)get_unch];
    }
    while(encode.length()%8!=0){  /*补零*/
      encode+='0';
    }

    /*先将8为字符串反转，再打印*/
    int bit_8=7;
    string print_encode="";
    for (i=0;i<encode.length();i++){
      if (i<=bit_8-4){  /*8位颠倒*/
        print_encode+=encode[bit_8-i%8];
      }else{  /*搞定前四位*/
        print_encode+=encode[bit_8-i%8];
        if (i==bit_8){
          num = binstr_to_bin(print_encode);
          // printf("%c",num );
          cout<<(unsigned char)num;
          print_encode="";
          bit_8+=8;
        }
      }
    }

  }else{  /*argument is "DECODE"*/

    int count=0;
    string strarr[256]; //存编码
    for (i=0;i<256;i++){
      strarr[i] = "";
    }
    for (i=0;i<8;i++){ /*读掉HUFFMAN*/
      cin.get(get_char);
    }
    int charr[256]={0};
    num = 0;
    int trans=0;

    for (i=0;i<1024;i++){
      if (i%4==0){
        get_unch = cin.get();
        trans+=(int)get_unch;
      }else if (i%4==1){
        get_unch = cin.get();
        trans+=(int)get_unch*256;
      }else if (i%4==2){
        get_unch = cin.get();
        trans+=(int)get_unch*256*256;
      }else{
        get_unch = cin.get();
        trans+=(int)get_unch*256*256*256;
        count+=trans;
        charr[num++]+=trans;
        trans=0;
      }
    }

    for (i=0;i<256;i++){ //将节点push到min_heap
      if (charr[i]!=0){
        HuffNode* new_node = new HuffNode;
        new_node->mychar = (unsigned char) i;
        new_node->weight = charr[i];
        new_node->min_weight = i;
        min->insert(new_node);
      }
    }

    if (min->size==0){
      return 0;
    }
    while (min->size>1){  /*建树*/
      HuffNode* parent_node = new HuffNode;
      HuffNode* l_node = new HuffNode;
      HuffNode* r_node = new HuffNode;
      r_node = min->remove_root();
      l_node = min->remove_root();
      parent_node->lchild = l_node;
      parent_node->rchild = r_node;
      parent_node->weight = l_node->weight+r_node->weight;
      parent_node->min_weight = Min(l_node->min_weight,r_node->min_weight);
      min->insert(parent_node);
    }

    string order;
    preOrder(min->arr[1],strarr,order); /*生成编码*/

    /*以下为解码*/
    string decode;

    while (cin.get(get_char)){
      get_unch = get_char;
      string tmp = hex_to_bin((int)get_unch);
      decode+=reverse(tmp);
    }


    HuffNode* denode = min->arr[1];
    for (i=0;i<decode.length();i++){
      if (decode[i]=='1'&&denode->rchild!=NULL){
        denode=denode->rchild;
      }else if(decode[i]=='0'&&denode->lchild!=NULL){
        denode = denode->lchild;
      }
      if (denode->lchild==NULL&&denode->rchild==NULL&&count>0){
        // printf("%c",denode->mychar );
        cout<<(unsigned char)denode->mychar;
        denode = min->arr[1];
        count--;
        continue;
      }
    }


  }

  return 0;
}
