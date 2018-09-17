#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void insertsort(int* arr,int n){
  int i,j;
  for (i=1;i<n;i++){
    int tmp = arr[i];
    for (j=i;j>0;j--){
      if (arr[j-1]>tmp){
        arr[j] = arr[j-1];
      }else{
        arr[j] = tmp;
        break;
      }
    }
    if (j==0){
      arr[0] = tmp;
    }

  }
}


int main(int argc, char const *argv[]) {
  int i;
  int arr[4] = {1,5,4,3};
  insertsort(arr,4);
  for(i = 0;i<10;i++){
    if (i==4){
      i=0;
    }
    std::cout << i << '\n';
  }
  return 0;
}
