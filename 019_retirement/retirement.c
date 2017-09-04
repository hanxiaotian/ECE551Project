#include<stdio.h>
#include<stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void balanceCompute(int* startAge, double* initial, retire_info info){
  for(int i=0;i<info.months;i++,(*startAge)++){
    printf("Age %3d month %2d you have $%.2lf\n",*startAge/12, *startAge%12, *initial);
    (*initial)+=(*initial)*info.rate_of_return/12+info.contribution;
  }
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
  balanceCompute(&startAge, &initial, working);
  balanceCompute(&startAge, &initial, retired);
}

int main(){
  int startAge=327;
  double initial=21345;
  retire_info working={489,1000,0.045};
  retire_info retired={384,-4000,0.01};
  retirement(startAge, initial, working, retired);
  return 0;
}
