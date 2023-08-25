//libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Stock data type
typedef struct Stock{
int date,Volume,OpenInt;
double Open,High,Low,Close;
}STOCK;
//function declarations
int Count_file(FILE* fp);
void merge(STOCK* arr,int low,int mid,int rear);
void mergeSort(STOCK* arr,int low,int rear);
void Print(STOCK* arr,int megethos);
void QuickSort(STOCK* array,int left,int right);
void swap(int* a,int* b);
void swap1(double* a,double* b);
void remove_all_chars(char* str, char c);
void Sorted(STOCK* arr, int megethos);
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
int Volume,OpenInt;
Volume=OpenInt=0;
double Open,High,Low,Close;
Open=High=Low=Close=0.0;//assistant variables to hold each field of the file
int i=0;
int temp=0;
char date[11];
while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{
remove_all_chars(date,'-');//convert date string to int maintaining dates' order
temp=(int)atoi(date);//cast to int
Open_array[i].Open=Open;
Open_array[i].Close=Close;
Open_array[i].date=temp;
Open_array[i].High=High;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt;
++i;

}
fclose(f1);

int choice;//menu choice
while(1){//main menu
printf("1 for table printing 2 for MergeSort 3 for QuickSort 4 to check if it is sorted 5 to exit\n");
scanf("%d",&choice);//user's input choice
switch(choice){
	case 1:
		Print(Open_array,count);
		break;
	case 2:
		mergeSort(Open_array,0,count-1);
		break;
	case 3:
		QuickSort(Open_array,0,count-1);
		break;
	case 4:
		Sorted(Open_array,count);
		break;
	case 5:
		exit(0);
		break;
	}

}



return 0;
}
/*
voithitikh synarthsh merge pou enonei pinakes oste na petyxoume thn enosh pou thelei o mergesort
*/
void merge(STOCK* arr, int low, int mid, int rear)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = rear - mid;

    STOCK L[n1], R[n2];

    for (i = 0; i < n1; i++){
        L[i].Open = arr[low + i].Open;
        L[i].Close = arr[low + i].Close;
        L[i].High = arr[low + i].High;
        L[i].Low = arr[low + i].Low;
        L[i].date = arr[low+i].date;
        L[i].Volume = arr[low + i].Volume;
        L[i].OpenInt = arr[low + i].OpenInt;
    }
    for (j = 0; j < n2; j++){
        R[j].Open =arr[mid + 1 + j].Open;
        R[j].Close =arr[mid + 1 + j].Close;
        R[j].High =arr[mid + 1 + j].High;
        R[j].Low =arr[mid + 1 + j].Low;
       	R[j].date = arr[mid+1+j].date;
        R[j].Volume =arr[mid + 1 + j].Volume;
        R[j].OpenInt =arr[mid + 1 + j].OpenInt;
    }
    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if ((double)L[i].Open <=(double) R[j].Open) {
        arr[k].Open =L[i].Open;
        arr[k].Close =L[i].Close;
        arr[k].High =L[i].High;
        arr[k].Low =L[i].Low;
        arr[k].date =L[i].date;
        arr[k].OpenInt =L[i].OpenInt;
        arr[k].Volume =L[i].Volume;
            i++;
        }
        else {
            arr[k].Open = (double)R[j].Open;
            arr[k].Close=R[j].Close;
            arr[k].High=R[j].High;
            arr[k].Low=R[j].Low;
            arr[k].date=R[j].date;
            arr[k].OpenInt=R[j].OpenInt;
            arr[k].Volume=R[j].Volume;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k].Open =L[i].Open;
        arr[k].Close =L[i].Close;
        arr[k].High =L[i].High;
        arr[k].Low =L[i].Low;
        arr[k].date =L[i].date;
        arr[k].OpenInt =L[i].OpenInt;
        arr[k].Volume =L[i].Volume;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k].Open = (double)R[j].Open;
            arr[k].Close=R[j].Close;
            arr[k].High=R[j].High;
            arr[k].Low=R[j].Low;
            arr[k].date=R[j].date;
            arr[k].OpenInt=R[j].OpenInt;
            arr[k].Volume=R[j].Volume;
        j++;
        k++;
    }
}
//algorithmos mergesort pou spaei kathe ypopinaka sth mesh kai otan ftasoume se pinakes 1 mono stixiou tote kanei merge 
void mergeSort(STOCK* arr, int low, int rear)
{
    if (low < rear) {
        int mid = low + (rear - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, rear);
        merge(arr, low, mid, rear);
    }
}
/*
algorithmos QuickSort ylopoihmenos basei diafaneivn kyriou siouta apo to eclass
*/
void QuickSort(STOCK* array,int left,int right){
int leftarrow,rightarrow;
double pivot;// check here for bugs - Propably not
leftarrow=left;
rightarrow=right;
pivot=array[(left+right)/2].Open;
do{
while(array[rightarrow].Open>pivot){
--rightarrow;
}
while(array[leftarrow].Open<pivot){
++leftarrow;
}
if(leftarrow<=rightarrow){
swap1(&array[leftarrow].Low,&array[rightarrow].Low);
swap1(&array[leftarrow].High,&array[rightarrow].High);
swap1(&array[leftarrow].Open,&array[rightarrow].Open);
swap1(&array[leftarrow].Close,&array[rightarrow].Close);
swap(&array[leftarrow].date,&array[rightarrow].date);
swap(&array[leftarrow].Volume,&array[rightarrow].Volume);
swap(&array[leftarrow].OpenInt,&array[rightarrow].OpenInt);
++leftarrow;
--rightarrow;
}
}while(rightarrow>=leftarrow);
if(left<rightarrow){
QuickSort(array,left,rightarrow);
}
if(leftarrow<right){
QuickSort(array,leftarrow,right);
}

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
/*
synarthsh pou pernei os orisma pinaka akeraion kai typonei ta stixia tou
*/
void Print(STOCK* arr,int megethos){
int i;
for(i=0;i<megethos;i++){
printf("%d,%lf\n",arr[i].date,(double)arr[i].Open);
}
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
