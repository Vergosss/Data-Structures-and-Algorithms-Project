//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Stock and Stock_ custom data type
typedef struct Stock{
int date,Volume,OpenInt;
double Open,High,Low,Close;
}STOCK;
typedef struct Stock_{
int date;
int Close;
}STOCK_;
//function declarations
void remove_all_chars(char* str, char c);
int Count_file(FILE* fp);
void HeapSort(STOCK* array,int size);
void Counting_Sort(STOCK_* A,STOCK_* B,int k,int megethos);
void Print(STOCK* arr,int megethos);
void Print_(STOCK_* arr,int megethos);//synarthsh Print_ typonei stixia enos pinaka STOCK_. epeidh o counting sort leitourgei se akeraious //strogylopoioume ston plisiestero akeraio
void swap(int* a,int* b);
void swap1(double* a,double* b);
void Sorted(STOCK* arr, int megethos);
int Find_Max(STOCK_* arr,int megethos);
/////
//main menu
int main(){
FILE* f1;
f1=fopen("ale.us.txt","r");
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("ale.us.txt","r+");//needed to avoid garbage
STOCK Open_array[count];
STOCK_ Open_array2[count];
STOCK_ Open_array3[count];
int Volume,OpenInt;
Volume=OpenInt=0;
double Open,High,Low,Close;
Open=High=Low=Close=0.0;
int i=0;
int temp=0;
char date[11];
while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{
remove_all_chars(date,'-');//convert date string to int maintaining dates' order
temp=(int)atoi(date);//cast to int
Open_array[i].Open=Open;
Open_array[i].Close=Close;
Open_array[i].High=High;
Open_array[i].date=temp;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt;
//
Open_array2[i].date=temp;
Open_array2[i].Close=(int)(round(Close));//strogylopoihsh ston plisiestero akeraio

++i;

}
fclose(f1);
Print(Open_array,count);
HeapSort(Open_array,count);
printf("After heapsort...\n");
Print(Open_array,count);
int k=Find_Max(Open_array2,count);//to megisto ton timon pou xeirizomaste xrhsimopoietai apo ton counting sort opote prepei na ypologistei
//Counting_Sort(Open_array3,Open_array2,k,count);
//Print_(Open_array3,count);
return 0;
}

//algorithmos heapsort vasismenos sto vivlio tou kyriou tsakalidh
void HeapSort(STOCK* array,int size){
int low=floor(size/2)-1;
int rear=size-1;
int j,k;
STOCK s;
while(rear>=1){
if(low>0){
low=low-1;
j=low;
}
else{
swap1(&array[0].Open,&array[rear].Open);
swap1(&array[0].Close,&array[rear].Close);
swap1(&array[0].High,&array[rear].High);
swap1(&array[0].Low,&array[rear].Low);
swap(&array[0].Volume,&array[rear].Volume);
swap(&array[0].OpenInt,&array[rear].OpenInt);
swap(&array[0].year,&array[rear].year);
swap(&array[0].month,&array[rear].month);
swap(&array[0].day,&array[rear].day);
rear=rear-1;
j=0;
}
s.Close=array[j].Close;
s.Open=array[j].Open;
s.High=array[j].High;
s.OpenInt=array[j].OpenInt;
s.Low=array[j].Low;
s.Volume=array[j].Volume;
s.day=array[j].day;
s.month=array[j].month;
s.year=array[j].year;

while(2*j<=rear){
k=2*j;
if(k<rear&& array[k].Close<array[k+1].Close){
k++;
}
if(s.Close<array[k].Close){
array[j].Close=array[k].Close;
array[j].Open=array[k].Open;
array[j].High=array[k].High;
array[j].Low=array[k].Low;
array[j].Volume=array[k].Volume;
array[j].OpenInt=array[k].OpenInt;
array[j].year=array[k].year;
array[j].month=array[k].month;
array[j].day=array[k].day;
j=k;
}
else{
goto E;
}
}
E:
    array[j].Close=s.Close;
    array[j].Open=s.Open;
    array[j].High=s.High;
    array[j].Low=s.Low;
    array[j].year=s.year;
    array[j].month=s.month;
    array[j].day=s.day;
    array[j].Volume=s.Volume;
    array[j].OpenInt=s.OpenInt;
}
//return array;
}
/*

synarthsh pou metra tis grames tou arxeiou.xrisimi giana vroume to megethos tou pinaka
*/
int Count_file(FILE* fp){
char c=getc(fp);
int count=0;
for (c = getc(fp); c != EOF; c = getc(fp)){
if (c == '\n'){
count = count + 1;}
}
return count;
}

/*
voithitikes synartiseis swap kai swap1 h swap enalasei akeraious eno h swap1 enalasei doubles
*/
void swap(int* a,int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void swap1(double* a,double* b){
double t= *a;
*a= *b;
*b= t;
}
void Print_(STOCK_* arr,int megethos){
int i;
for(i=0;i<megethos;i++){
printf("%d,%lf\n",arr[i].date,arr[i].Close);
}
return;

}
/*
synarthsh pou pernei os orisma pinaka akeraion kai typonei ta stixia tou
*/
void Print(STOCK* arr,int megethos){
int i;
for(i=0;i<megethos;i++){
printf("%d,%f\n",arr[i].date,(double)arr[i].Open);
}
return;

}
/*
algorithmos counting sort ylopoihmenos me th voitheia tou pseydokodika apo to vivlio tou kiriou tsakalidi
*/
void Counting_Sort(STOCK_* A,STOCK_* B,int k,int megethos){
int C[k+1];
int i,j;
for(i=0;i<=k;i++){
C[i]=0;
}
for(j=1;j<megethos;j++){
C[A[j].Close]+=1;
}
for(i=1;i<=k;i++){
C[i]+=C[i-1];
}
for(j=megethos-1;j>=0;j--){
B[C[A[j].Close]-1].Close=A[j].Close;
B[C[A[j].Close]-1].year=A[j].year;
B[C[A[j].Close]-1].month=A[j].month;
B[C[A[j].Close]-1].day=A[j].day;
C[A[j].Close]--;
}
for(i=0;i<megethos;i++){
A[i].Close=B[i].Close;
A[i].day=B[i].day;
A[i].month=B[i].month;
A[i].year=B[i].year;
}
}
/*
o algorithmos counting sort apaitei apo ton pseydokodika tou enan arithmo k o opoios einai to megisto stixio tou pinaka pou kanoume sorting opote meso ths find max ton vriskoume
*/
int Find_Max(STOCK_* arr,int megethos){
int i;
int max;
max=arr[0].Close;
for(i=0;i<megethos;i++){
if(arr[i].Close>max){
max=arr[i].Close;
}
}
return max;
}
//helper function to check if array is sorted or not
void Sorted(STOCK* arr, int megethos)
{//prerequisite for a sorted array is array(i)<=array(i+1) for i=0,...,megethos-2
int i;
    for (int i = 1; i < megethos; i++) {
        
        if (arr[i - 1].Open > arr[i].Open){
        	printf("Array not sorted\n");
        	return;
        }
    }
 
   printf("Array sorted\n");
   return;
}
void remove_all_chars(char* str, char c) {//function that accepts a string and a character. it removes this character and deletes the space in the
//deleted position.
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}
