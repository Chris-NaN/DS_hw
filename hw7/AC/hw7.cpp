#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>
#include <list>

using namespace std;

class Node{
public:
  int x,y;
  Node* front;
  int type;
  void setXY(int X,int Y){
    this -> x = X;
    this -> y = Y;
  };  /* homework*/
  int getX();
  int getY();
  void setType(int T){
    this->type = T;
  }
};

void output(Node* start,Node* end,int width,int height,int path[200][200]){
  int i=0;
  int count = 0;
  while(i<1500){
    path[end->y][end->x] = 2;  /* 2: . */
    // cout<<"v.t:"<<end->type<<endl;
    // cout<<"v.x:"<<end->x<<endl;
    // cout<<"v.y:"<<end->y<<endl;
    // fprintf(stderr, "%d\n", end->x);
    if (end->y==start->y&&end->x==start->x){
      break;
    }
    end = end->front;
    count++;
    i++;
  }

  for (int j=0;j<height;j++){
    for (int i=0;i<width;i++){
      if (path[j][i]==2){
        printf("%s",".");
      }
      if (path[j][i]==0){
        printf("%s","#");
      }
      if (path[j][i]==1){
        printf("%s"," ");
      }
      if (i==width-1){
        printf("\n");
      }
    }
  }
  // fprintf(stderr, "%d\n",count );
  printf("%d\n",count );
}
int main(int argc, char const *argv[]) {
  // freopen("test.in","r",stdin);
  // freopen("test.out","w",stdout);
  int width,height,i,num_path;
  Node* maze[200][200];
  Node* start = new Node;
  int path[200][200];
  for (i=0;i<200;i++){
    for (int j=0;j<200;j++){
      maze[i][j] = new Node;
    }
  }
  string edg;
  queue<Node*> q;
  bool visited[200][200] = {false};
  int dir[][2] = {
    {0,-1},{0,1},{1,0},{-1,0}
  };
  width = 0; height = 0;

  while (getline(cin,edg)) {
    width = edg.length();

    for (i = 0;i<width;i++){

      /*
      '#'': wall, 0
      ' ' : road, 1
      '*' : start, -1
      '+' : end, -2
      */
      maze[height][i]->setXY(i,height);

      if (edg[i]=='#'){
        maze[height][i]->setType(0);
        path[height][i] = 0;
      }else if(edg[i]==' '){
        maze[height][i]->setType(1);
        path[height][i] = 1;
      }else if(edg[i]=='*'){

        maze[height][i]->setType(-1);
        path[height][i] = -1;
        start->setXY(i,height);
        q.push(maze[height][i]);
      }else{

        maze[height][i]->setType(-2);
        path[height][i] = -2;
      }
    }
    height++;

  }
  while (!q.empty()) {
    Node* head = q.front();

    visited[head->y][head->x] = true;
    q.pop();

    for (i=0;i<4;i++){

      if (i==0 && head->y==0){
        continue;
      }
      if (i==1 && head->y==height-1){
        continue;
      }
      if (i==2 && head->x==width-1){
        continue;
      }
      if (i==3 && head->x==0){
        continue;
      }
      Node* v = maze[head->y + dir[i][1]][head->x+dir[i][0]];
      if (v->type == -2){
        v->front = head;
        output(start,v,width,height,path);
        return 0;
      }
      if ((v->type == 1 || v->type == -2) && !visited[v->y][v->x]){
        v->front = head;
        q.push(v);
        visited[v->y][v->x] = true;

      }

    }
  }
  cout<<"NO SOLUTION"<<endl;

  return 0;

}
