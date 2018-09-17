#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
using namespace std;

typedef struct info_s{
  int num;
}info_t;

typedef std::list<int> list_t;

string replace_blank(string str){
  string new_str;
  for (string::iterator it = str.begin();it!=str.end();it++){
    if (*it != ' ')  new_str+=*it;
  }
  return new_str;
}
string tolowercase(string str){
  string new_str;
  for (string::iterator it = str.begin();it!=str.end();it++){
    new_str+=tolower(*it);
  }
  return new_str;
}

int main(int argc, char const *argv[]) {
  freopen("test.in","r",stdin);//读入文件
  freopen("test.out","w",stdout);//输出文件
  int num,i,j,valid;
  string name1,name2,output;
  list_t List[26]; // initialize Link-list

  int in_degree[26];
  for (i=0;i<26;i++){
    in_degree[i] = 0;
  }
  scanf("%d\n",&num );
  getline(cin,name1);
  name1 = replace_blank(name1);
  name1 = tolowercase(name1);
  //num == 1 的情况
  while (getline(cin,name2)) {
    name2 = replace_blank(name2);
    name2 = tolowercase(name2);
    for (i=0;i<name1.length();i++){
      if(name1[i]==name2[i]){
        if (i==name1.length()-1||i==name2.length()-1){
          if (name1.length()>name2.length()){
            std::cout << "另请高明吧" << '\n';
            return 0;
          }
        }
        continue;
      }else{// ex, exchange b, e
        List[name1[i]-97].push_back(name2[i]-97);
        in_degree[name2[i]-97] += 1;
        break;
      }
    }
    name1 = name2;
  }
  //output
  valid = 1;
  while (true) {

    for (i=0;i<26;i++){
      if (in_degree[i]==0){

        valid = 0;
        output += char(i+97);
        in_degree[i] = -1;  // visited
        if (!List[i].empty()){
          for (list_t::iterator iter = List[i].begin();iter!=List[i].end();iter++){
            in_degree[*iter]--;
          }
          List[i].clear();
          i = -1;
        }
      }
    }
    if (valid == 1){
      std::cout << "另请高明吧" << '\n';
      return 0;
    }
    if (output.length()==26){
      std::cout << output << '\n';
      return 0;
    }
    valid = 1;
  }
  return 0;
}
