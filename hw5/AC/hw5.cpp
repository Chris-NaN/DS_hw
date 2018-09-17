#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef struct edge{
  int s;   /*start_city*/
  int t;   /*target_city*/
  int len;
  edge(int s,int t,int len){
    this -> s = s;
    this -> t = t;
    this -> len = len;
  };
}edge,*pedge;
typedef edge* Eletype;

class Min_heap{
public:
  Min_heap();
  int size; //number of nod es
  int cap; //capacity of array
  Eletype *arr; //array to store node
  void insert(Eletype num);
  Eletype remove_root();
  bool empty();
};
bool Min_heap::empty(){
  return this -> size == 0;
}

Min_heap::Min_heap(){
  this -> size = 0;
  this -> cap =70000;
  this->arr = new Eletype[this -> cap];
  this->arr[0] = 0;
  return;
}

int min_num(int a,int b){
  if (a>b) return b;
  if (a<b) return a;
  return -1;
}
int max_num(int a,int b){
  if (a>b) return a;
  if (a<b) return b;
  return -1;
}
int cmp_(Eletype a,Eletype b){
  /*To break the tie when two roads e1=(s1, t1) and e2=(s2, t2)
  have the same length, consider e1 to be shorter than e2 if and only if
  min(s1, t1) < min(s2, t2), or
  min(s1, t1) == min(s2, t2) and max(s1, t1) < max(s2, t2)*/
  if (a->len<b->len){
    return -1;
  }else if(a->len==b->len&&min_num(a->s,a->t)<min_num(b->s,b->t)){
    return -1;
  }else if (a->len==b->len&&min_num(a->s,a->t)==min_num(b->s,b->t)&&max_num(a->s,a->t)<
  max_num(b->s,b->t)){
    return -1;
  }else{
    return 1;
  }
}

void minheap_insert(Min_heap* min,Eletype edg){
  int index;
  min -> size+=1;
  index = min->size;
  /*this->arr[index>>1]>num*/
  while ((index>>1!=0) &&(cmp_(edg,min->arr[index>>1])==-1)){
    min->arr[index] = min->arr[index>>1];
    index = index>>1;
  }
  min->arr[index] = edg;
}
void Min_heap::insert(Eletype edg){
  if (this -> size+1==this -> cap){
    Eletype *new_arr = new Eletype[this->cap*2];
    this -> cap *= 2;
    for (int i=0;i<=this->size;i++){
      new_arr[i] = this->arr[i];
    }
    this -> arr = new_arr;
    minheap_insert(this,edg);
  }else{
    minheap_insert(this,edg);
  }
}

Eletype Min_heap::remove_root(){  /*not include delete operation*/
  if (this->size==0){
    return 0;
  }
  Eletype root = this->arr[1];
  Eletype element = this -> arr[this->size];
  this -> size -= 1;
  int index;
  int new_index;
  for (index=1;index<=this->size/2;index=new_index){
    if ((2*index+1>this->size) || (cmp_(this->arr[2*index],this->arr[2*index+1])==-1)){
      new_index=2*index;
    }else{
      new_index = 2*index+1;
    }
    if (cmp_(this->arr[new_index],element)==-1){
      this->arr[index] = this->arr[new_index];
    }else{
      break;
    }
  }
  this->arr[index] = element;
  return root;
}
class Disjset{
public:
  int *parent;  /*store set*/
  Disjset(int n);
  int find(int num);
  int set_union(int num1,int num2);
};
/*initialize disjoint set*/
Disjset::Disjset(int n){
  int i;
  this -> parent = new int[n];
  for (i = 0;i<n;i++){
    parent[i] = i;
  }
}
/*change the pointer to root when using find()*/
int Disjset::find(int num){
  if (this -> parent[num] == num){
    return num;
  }else{
    this -> parent[num] = this -> find(this -> parent[num]);
    return this -> parent[num];
  }
}
int Disjset::set_union(int num1,int num2){
  num1 = this -> find(num1);
  num2 = this -> find(num2);
  if (num1 != num2){
    this -> parent[num2] = num1;
    return num1;
  }
  return -1;
}
class region{
public:
  int size;
  int cap;
  pedge* arr;   /*used for store edges*/
  int n_cities;    /*number of cities*/
  int label;    /*regions label*/
  int min_mem;  /*minium city of region*/
  region(int label);  /*initialize*/
};
region::region(int label){
  this -> size = 0;
  this -> cap = 2048;
  this -> arr = new pedge[this->cap];
  this -> n_cities = 1;
  this -> label = label;
  this -> min_mem = label;
}
/*
union two regions
reg1<-reg2: reg1.numberof cities<-reg2.numberof cities
*/
bool reg_union(int root,region* reg1,region* reg2,pedge edg){
  if (reg1->label == root){
    if (reg1->min_mem>reg2->min_mem){
      reg1->min_mem=reg2->min_mem;
    }
    reg1->n_cities+=reg2->n_cities;
    reg2->n_cities = 0;
    return true;
  }else{

    if (reg2->min_mem>reg1->min_mem){
      reg2->min_mem=reg1->min_mem;
    }
    reg2->n_cities+=reg1->n_cities;
    reg1->n_cities = 0;
    return true;
  }
}
int cmp_reg(region* a,region* b){
  if (a->n_cities<b->n_cities){
    return -1;
  }else if(a->n_cities==b->n_cities&&a->min_mem<b->min_mem){
    return -1;
  }else{
    return 1;
  }
}
/*used for print each regions*/
class Maxreg_heap{
public:
  Maxreg_heap();
  int size; //number of nodes
  int cap; //capacity of array
  region* *arr; //array to store node
  void insert(region* num);
  region* remove_root();
  bool empty();
};
Maxreg_heap::Maxreg_heap(){
  this -> size = 0;
  this -> cap =70000;
  this->arr = new region*[this -> cap];
  this->arr[0] = 0;
  return;
}
bool Maxreg_heap::empty(){
  return this -> size == 0;
}
void maxregheap_insert(Maxreg_heap* max,region* edg){
  int index;
  max -> size+=1;
  index = max->size;
  /*this->arr[index>>1]>num*/
  while ((index>>1!=0) &&(cmp_reg(edg,max->arr[index>>1])==1)){
    max->arr[index] = max->arr[index>>1];
    index = index>>1;
  }
  max->arr[index] = edg;
}
void Maxreg_heap::insert(region* edg){
  if (this -> size+1==this -> cap){
    region* *new_arr = new region*[this->cap*2];
    this -> cap *= 2;
    for (int i=0;i<=this->size;i++){
      new_arr[i] = this->arr[i];
    }
    this -> arr = new_arr;
    maxregheap_insert(this,edg);
  }else{
    maxregheap_insert(this,edg);
  }
}
region* Maxreg_heap::remove_root(){
  if (this->size==0){
    return 0;
  }
  region* root = this->arr[1];
  region* element = this -> arr[this->size];
  this -> size -= 1;
  int index;
  int new_index;
  for (index=1;index<=this->size/2;index=new_index){
    if ((2*index+1>this->size) || (cmp_reg(this->arr[2*index],this->arr[2*index+1])==1)){
      new_index=2*index;
    }else{
      new_index = 2*index+1;
    }
    if (cmp_reg(this->arr[new_index],element)==1){
      this->arr[index] = this->arr[new_index];
    }else{
      break;
    }
  }
  this->arr[index] = element;
  return root;
}
void output(Maxreg_heap* regheap){
  int i;
  printf("%s\n","[" );
  while (!regheap->empty()) {
    printf("%s\n","[" );
    region* reg = regheap->remove_root();
    for (i=reg->size-1;i>=0;i--){
      pedge tmp_edg = reg->arr[i];
      if (i!=0){
        printf("%s%d,%d,%d%s\n","[", tmp_edg->s,tmp_edg->t,tmp_edg->len,"],");
      }else{
        printf("%s%d,%d,%d%s\n","[", tmp_edg->s,tmp_edg->t,tmp_edg->len,"]");
      }
    }
    if (regheap->size==0){
      printf("%s\n","]" );
    }else{
      printf("%s\n","]," );
    }
  }
  printf("%s\n","]" );
}
int main(int argc, char const *argv[]) {
  // freopen("randomtest/input2","r",stdin);
  // freopen("test.out","w",stdout);
  int n,m,k,i,regions;
  int start,target,length;
  int labels,labelt,root;
  pedge edg;
  Min_heap* graph;   /*used for sort input road*/
  Min_heap* graph1;  /*used for store region's road*/
  Maxreg_heap* reg_heap;   /*used for store regions*/
  Disjset* set;
  /*n:number of cities;
   m:number of old roads
   k:the threshold region number
  */
  scanf("%d%d%d",&n,&m,&k);
  regions = n;
  graph = new Min_heap;
  graph1 = new Min_heap;
  reg_heap = new Maxreg_heap;
  set = new Disjset(n);
  region* region_arr[n];
  for (i=0;i<n;i++){
    region_arr[i] = new region(i);
  }

  for (i=0;i<m;i++){  /*input roads*/
    scanf("%d%d%d",&start,&target,&length);
    edg = (start>target)?new edge(target,start,length):new edge(start,target,length);
    graph -> insert(edg);   /*each is in the min heap now*/
  }

  while (regions>k&&!graph->empty()) {
    pedge edg = graph -> remove_root();
    labels = set->find(edg->s);
    labelt = set->find(edg->t);
    root = set->set_union(edg->s,edg->t);  /*union set*/
    if (root !=-1){  /*if union success*/
      reg_union(root,region_arr[labels],region_arr[labelt],edg); /*union region*/
      graph1 -> insert(edg);  /*store roads of region*/
      regions--;
    }
  }
  while (!graph1->empty()) {
    pedge edg = graph1 -> remove_root();
    labels = set->find(edg->s);
    int size = region_arr[labels]->size;
    region_arr[labels]->arr[size] = edg;
    region_arr[labels]->size+=1;
    /*realloc more memory*/
    if (region_arr[labels]->size==region_arr[labels]->cap){
      region_arr[labels]->cap*=2;
      pedge* new_arr = new pedge[region_arr[labels]->cap];
      for (int i=0;i<region_arr[labels]->size;i++){
        new_arr[i] = region_arr[labels]->arr[i];
      }
      region_arr[labels]->arr = new_arr;
    }
  }
  for (i=0;i<n;i++){  /*store regions to arr*/
    if (region_arr[i]->n_cities!=0){

      reg_heap->insert(region_arr[i]);
    }
    //reg_heap->insert(region_arr[i]);

  }
  output(reg_heap);

  return 0;
}
