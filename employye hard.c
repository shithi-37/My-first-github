#include<stdio.h>
int main(){
int salary,service;
float bonus,final,tax;
scanf("%d %d ",&salary,&service);
if(salary<0 ){
    printf("Invalid");
}
else if(salary<=20000)
{
    bonus=0;
}
else if(salary<=50000)
{
bonus=salary*0.1;
final=salary+bonus;
}
else if(salary<=80000){
    bonus=salary*0.15;
}
else{
    bonus=salary*0.25;
}

if(service>=15){
    final=final+20000;
}

if(salary>150000){
    tax=final*0.12;
    printf("tax");
final=final-tax;

}

else{
        final=salary+bonus;
    printf("bonus=%.2f",bonus);
    printf("final=%.2f",final);
}






return 0;

}
