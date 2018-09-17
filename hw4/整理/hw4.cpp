#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
typedef string Eletype;

struct ListNode{
  int value;
  Eletype key;
  struct ListNode *pre;
  struct ListNode *next;
};
typedef struct ListNode Node,*pnode;

class LinkList{
public:
  pnode header;
  LinkList();
  Node* head();
  bool empty();
  int size();
  bool insertNode(Eletype key,int value);
  bool delNode(Eletype key);
  Node* FindKey(Eletype key);
};
Node* LinkList::head(){
  return this -> header;
}

LinkList::LinkList(){
  this -> header = NULL;
}
bool LinkList::empty(){
  return (this -> header == NULL);
}

bool LinkList::insertNode(Eletype key,int value){
  pnode tmpNode = new Node;
  tmpNode -> key = key;
  tmpNode -> value = value;
  tmpNode -> pre = NULL;
  tmpNode -> next = this -> header;

  if (this -> header == NULL){
    this -> header = tmpNode;
  }else{
    this -> header = tmpNode;
    tmpNode->next->pre = tmpNode;
  }
  return true;
}
Node* LinkList::FindKey(Eletype key){
  if (this -> empty()){
    return NULL;
  }
  pnode node = this -> head();

  while (node -> next != NULL) {
    if (node -> key == key)  return node;
    node = node -> next;
  }
  if (node -> key == key)  return node;
  return NULL;
}
bool LinkList::delNode(Eletype key){
  if (this -> empty())  return false;
  pnode tmp = this -> FindKey(key);

  if (tmp != NULL){
    if (!(tmp->pre) && !(tmp->next)){  /*del only header*/
      this->header = NULL;
    }else if (!(tmp->pre) && tmp->next){  /*del header*/
      this -> header = tmp -> next;
      tmp -> next -> pre = NULL;

    }else if (tmp -> pre && !(tmp -> next)){  /*del the last node*/
      tmp -> pre ->next = NULL;

    }else{  /* del middle node */

      tmp -> pre -> next = tmp -> next;
      tmp -> next -> pre = tmp -> pre;
    }
    delete tmp;
    tmp = NULL;
    return true;
  }else{
    return false;
  }
}

class HashTable{
public:
  LinkList** table;
  unsigned int size;
  unsigned int loadfac;
  unsigned int TableSize;
  HashTable(unsigned int lf,unsigned int TableSize);
  unsigned int Hash(Eletype key);
  bool enlarge();
  bool insertNode(Eletype key,int value);
  bool delNode(Eletype key);
};


HashTable::HashTable(unsigned int lf,unsigned int TableSize){
  this -> loadfac = lf;
  this -> TableSize = TableSize;
  this -> table = new LinkList*[TableSize];
  for (unsigned int i=0;i<TableSize;i++){
    this -> table[i] = new LinkList;
  }
}
unsigned int HashTable::Hash(Eletype key){
  unsigned int ui,i,j,hash_val;
  unsigned char alp;
  char *stop = NULL;
  ui = strtoul(key.c_str(), &stop, 10);
  if (*stop == 0){  /*key is num*/
    return ui%this -> TableSize;
  }else{
    hash_val = 0;
    for(i=0;i<key.length();i++){
      alp = key[i];
      ui = (unsigned int)alp;
      for (j=1;j<key.length()-i;j++){
        ui = ui % this -> TableSize;
        ui = ui * 256%this -> TableSize;
        ui = ui % this -> TableSize;
      }
      if (i==key.length()-1){
        ui = ui % this -> TableSize;
      }
      hash_val += ui;
    }
    return hash_val%this -> TableSize;
  }
}
bool HashTable::enlarge(){
  unsigned int i,tmpSize;
  tmpSize = this -> TableSize;
  this -> TableSize = this -> TableSize *2 +1;
  this -> size = 0;
  LinkList** tmp_table;
  pnode rel_node;
  tmp_table = this -> table;
  this -> table = new LinkList*[TableSize];
  for (unsigned int i=0;i<TableSize;i++){
    this -> table[i] = new LinkList;
  }

  for (i=0;i<tmpSize;i++ ){
    rel_node = tmp_table[i] -> header;
    if (tmp_table[i] -> header != NULL){
      while (rel_node -> next !=NULL) {
        this -> insertNode(rel_node -> key,rel_node->value);
        rel_node = rel_node -> next;
      }
      this -> insertNode(rel_node -> key,rel_node->value); /* the last node*/
    }
  }

  return true;
}
bool HashTable::insertNode(Eletype key,int value){
  unsigned int hash;
  pnode tmpNode;
  hash = this -> Hash(key);
  tmpNode =this -> table[hash] -> FindKey(key);
  if (tmpNode == NULL){  /* do not find node */
    this -> table[hash] -> insertNode(key,value);
    this -> size += 1;
    if (this -> size*100>this->TableSize*this-> loadfac){
      this -> enlarge();
    }
    return true;
  }else{
    tmpNode -> value += value;
    return true;
  }
}
bool HashTable::delNode(Eletype key){
  unsigned int hash;
  pnode tmpNode;
  hash = this -> Hash(key);
  tmpNode =this -> table[hash] -> head();
  if (this -> table[hash] -> FindKey(key)==NULL){
    return false;
  }else{
    this -> table[hash] -> delNode(key);
    this -> size -= 1;
    return true;
  }
}
void output(HashTable* table){
  unsigned int i;
  cout<<"["<<endl;
  for (i=0;i<table -> TableSize;i++){
    cout<<"{";
    if (table -> table[i] -> header!=NULL){
      pnode node;
      node = table -> table[i] -> header;
      while (node -> next!=NULL) {
        cout<<"\""<<node -> key<<"\""<<":"<<node-> value<<",";
        node = node -> next;
      }
      cout<<"\""<<node -> key<<"\""<<":"<<node-> value;
    }
    if (i==table -> TableSize-1){
      cout<<"}"<<endl;
    }else{
      cout<<"}"<<","<<endl;
    }

  }
  cout<<"]"<<endl;
}
int main(){
  // freopen("test.in","r",stdin);//读入文件
  // freopen("test.out","w",stdout);//输出文件
   unsigned int lf,len;
   int is_del;
   string input;
   HashTable* table;
   is_del = 0;
   cin>>lf>>len;

   table = new HashTable(lf,len);
   while (cin>>input) {  /*input*/
     if (input=="************************"){
       is_del = 1;
       continue;
     }
     if (is_del==1 && input!="************************"){
       table -> delNode(input);
       continue;
     }
     table -> insertNode(input,1);

   }
   output(table);

   return 0;
}
