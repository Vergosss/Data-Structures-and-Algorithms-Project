#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Stock{
int year,month,day,Volume,OpenInt;
float Open,High,Low,Close;
}STOCK;
int Count_file(FILE* fp);
void merge(STOCK* arr,int low,int mid,int rear);
void mergeSort(STOCK* arr,int low,int rear);
void Print(STOCK* arr,int megethos);
void QuickSort(STOCK* array,int left,int right);
void swap(int* a,int* b);
void swap1(float* a,float* b);
/////
int main(){
FILE* f1;
f1=fopen("ale.us.txt","r+");
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);
printf("Count is :%d\n",count);
STOCK Open_array[count];
int year,month,day,Volume,OpenInt;
year,month,day,Volume=OpenInt=0;
float Open,High,Low,Close;
Open=High=Low=Close=0.0;
int i=0;
int temp=0;
char c=fgetc(f1);
while(c!=EOF)
{
fscanf(f1,"%d-%d-%d,%f,%f,%f,%f,%d,%d",&year,&month,&day,&Open,&High,&Low,&Close,&Volume,&OpenInt);
Open_array[i].Open=Open;
Open_array[i].month=month;
Open_array[i].year=year;
Open_array[i].day=day;
Open_array[i].Close=Close;
Open_array[i].High=High;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt; //pername tis metavlites diladi kathe pedio kathe grammis tou arxeiou sta antistixa pedia kathe stixiou tou pinaka
c=getc(f1);
if(c=='\n'){
i++;
}
}
Print(Open_array,count);
mergeSort(Open_array,0,count-1); //sortarisma meso mergesort
printf("After MergeSort...\n");
Print(Open_array,count);//typosi sortarismenou pinaka
QuickSort(Open_array,0,count-1); //sortarisma me quicksort
Print(Open_array,count);//typosi sortarismenou pinaka

fclose(f1);

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
        L[i].year = arr[low + i].year;
        L[i].month = arr[low + i].month;
        L[i].day = arr[low + i].day;
        L[i].Volume = arr[low + i].Volume;
        L[i].OpenInt = arr[low + i].OpenInt;
    }
    for (j = 0; j < n2; j++){
        R[j].Open =arr[mid + 1 + j].Open;
        R[j].Close =arr[mid + 1 + j].Close;
        R[j].High =arr[mid + 1 + j].High;
        R[j].Low =arr[mid + 1 + j].Low;
        R[j].year =arr[mid + 1 + j].year;
        R[j].month =arr[mid + 1 + j].month;
        R[j].day =arr[mid + 1 + j].day;
        R[j].Volume =arr[mid + 1 + j].Volume;
        R[j].OpenInt =arr[mid + 1 + j].OpenInt;
    }
    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if ((float)L[i].Open <=(float) R[j].Open) {
        arr[k].Open =L[i].Open;
        arr[k].Close =L[i].Close;
        arr[k].High =L[i].High;
        arr[k].Low =L[i].Low;
        arr[k].year =L[i].year;
        arr[k].month =L[i].month;
        arr[k].day =L[i].day;
        arr[k].OpenInt =L[i].OpenInt;
        arr[k].Volume =L[i].Volume;
            i++;
        }
        else {
            arr[k].Open = (float)R[j].Open;
            arr[k].Close=R[j].Close;
            arr[k].High=R[j].High;
            arr[k].Low=R[j].Low;
            arr[k].year=R[j].year;
            arr[k].month=R[j].month;
            arr[k].day=R[j].day;
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
        arr[k].year =L[i].year;
        arr[k].month =L[i].month;
        arr[k].day =L[i].day;
        arr[k].OpenInt =L[i].OpenInt;
        arr[k].Volume =L[i].Volume;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k].Open = (float)R[j].Open;
            arr[k].Close=R[j].Close;
            arr[k].High=R[j].High;
            arr[k].Low=R[j].Low;
            arr[k].year=R[j].year;
            arr[k].month=R[j].month;
            arr[k].day=R[j].day;
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
float pivot;
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
//swap(&array[leftarrow].date,&array[rightarrow].date);
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
voithitikes synartiseis swap kai swap1 h swap enalasei akeraious eno h swap1 enalasei floats
*/
void swap(int* a,int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void swap1(float* a,float* b){
float t= *a;
*a= *b;
*b= t;
}
/*
synarthsh pou pernei os orisma pinaka akeraion kai typonei ta stixia tou
*/
void Print(STOCK* arr,int megethos){
int i;
for(i=0;i<megethos;i++){
printf("%d-%d-%d-%f\n",arr[i].year,arr[i].month,arr[i].day,(float)arr[i].Open);
}
return;

}
