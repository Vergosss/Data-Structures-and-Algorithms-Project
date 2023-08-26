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
int date,Close;
}STOCK_;
//function declarations
void remove_all_chars(char* str, char c);
int Count_file(FILE* fp);
void HeapSort(STOCK* array,int size);
void Counting_Sort(STOCK_* A,int megethos);
void Print(STOCK* arr,int megethos);
void Print_(STOCK_* arr,int megethos);//synarthsh Print_ typonei stixia enos pinaka STOCK_. epeidh o counting sort leitourgei se akeraious //strogylopoioume ston plisiestero akeraio
void swap(int* a,int* b);
void swap1(double* a,double* b);
void Sorted(STOCK* arr, int megethos);
int Find_Max(STOCK_* arr,int megethos);
void Sorted_(STOCK_* arr, int megethos);
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
STOCK* Open_array=(STOCK*)malloc(count*sizeof(STOCK));
STOCK_* Open_array2=(STOCK_*)malloc(count*sizeof(STOCK_));

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
//int k=Find_Max(Open_array2,count);//to megisto ton timon pou xeirizomaste xrhsimopoietai apo ton counting sort opote prepei na ypologistei
//printf("Max is : %d\n",k);
int choice;//menu choice
while(1){//main menu
printf("1 for Counting sort table printing, 2 for Counting Sort, 3 to check if it is sorted with counting sort, 4 for Heap Sort table printing, 5 for HeapSort, 6 to check if sorted with HeapSort and 7 to exit\n");
scanf("%d",&choice);//user's input choice
switch(choice){
	case 1:
		Print_(Open_array2,count);
		break;
	case 2:
		Counting_Sort(Open_array2,count);
		break;
	case 3:
		Sorted_(Open_array2,count);
		break;
	case 4:
		Print(Open_array,count);
		break;
	case 5:
		HeapSort(Open_array,count);
		break;
	case 6:
		Sorted(Open_array,count);
		break;
	case 7:
		exit(0);
		break;
	}

}


return 0;
}

//algorithmos heapsort vasismenos sto vivlio tou kyriou tsakalidh
void HeapSort(STOCK* array,int size){
int low=(int)floor(size/2)-1;
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
swap(&array[0].date,&array[rear].date);

rear=rear-1;
j=0;//
}
s.Close=array[j].Close;
s.Open=array[j].Open;
s.High=array[j].High;
s.OpenInt=array[j].OpenInt;
s.Low=array[j].Low;
s.Volume=array[j].Volume;
s.date=array[j].date;

while(2*j<=rear){
k=2*j;
if(k<rear && array[k].Close<array[k+1].Close){
k++;
}
if(s.Close<array[k].Close){
array[j].Close=array[k].Close;
array[j].Open=array[k].Open;
array[j].High=array[k].High;
array[j].Low=array[k].Low;
array[j].Volume=array[k].Volume;
array[j].OpenInt=array[k].OpenInt;
array[j].date=array[k].date;
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
   	array[j].date=s.date;
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
printf("%d,%d\n",arr[i].date,arr[i].Close);
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
void Counting_Sort(STOCK_* A,int megethos){
int i;
int max;
max=(A[0].Close);
for(i=1;i<megethos;i++){
if((A[i].Close)>max){
max=(A[i].Close);
}
}
//
STOCK_* B=(STOCK_*)malloc(megethos*sizeof(STOCK_));//output array-- FIXED HERE WRONG SIZE
int* C=(int*)malloc((max+1)*sizeof(int));//k is the max
int j;
for(i=0;i<=max;i++){
C[i]=0;//count initialization with zeros
}
for(j=0;j<megethos;j++){
C[A[j].Close]++;//store count of each element
}
for(i=1;i<=max;i++){
C[i]+=C[i-1];//apothikeysh tou 'syssoreytikou' plithous tou array
}
for(j=megethos-1;j>=0;j--){// vres th thesh tou kathe stixiou tou Open_array2 sto C(Count array)
  // topothetise ta ston pinaka eksodou
B[C[A[j].Close]-1].Close=A[j].Close;
B[C[A[j].Close]-1].date=A[j].date;
C[A[j].Close]--;
}
for(i=0;i<megethos;i++){
A[i].Close=B[i].Close;//apothikeyse ta taxinomimena stixia sto arxiko array
A[i].date=B[i].date;

}
}
/*
o algorithmos counting sort apaitei apo ton pseydokodika tou enan arithmo k o opoios einai to megisto stixio tou pinaka pou kanoume sorting opote meso ths find max ton vriskoume
*/
int Find_Max(STOCK_* arr,int megethos){
int i;
int max;
max=arr[0].Close;
for(i=1;i<megethos;i++){
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
//
void Sorted_(STOCK_* arr, int megethos)
{//prerequisite for a sorted array is array(i)<=array(i+1) for i=0,...,megethos-2
int i;
    for (int i = 1; i < megethos; i++) {
        
        if (arr[i - 1].Close > arr[i].Close){
        	printf("Array not sorted\n");
        	return;
        }
    }
 
   printf("Array sorted\n");
   return;
}
//
void remove_all_chars(char* str, char c) {//function that accepts a string and a character. it removes this character and deletes the space in the
//deleted position.
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}
