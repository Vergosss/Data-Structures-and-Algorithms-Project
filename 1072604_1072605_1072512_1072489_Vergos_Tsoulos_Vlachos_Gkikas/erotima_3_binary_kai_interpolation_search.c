#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Stock{
int year,month,day,Volume,OpenInt;
float Open,High,Low,Close;
}STOCK;
void Print(STOCK* arr,int megethos);
void remove_all_chars(char* str,char c);
int main(){
FILE* f1;
f1=fopen("agn.us.txt","r");
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("agn.us.txt","r+");
STOCK Open_array[count];
int year,Volume,OpenInt,month,day;
year=month=day=Volume=OpenInt=0;
float Open,High,Low,Close;
Open=High=Low=Close=0.0;
int new_array[count];
int i=0;
char c=fgetc(f1);
while(c!=EOF)
{
fscanf(f1,"%d-%d-%d,%f,%f,%f,%f,%d,%d",&year,&month,&day,&Open,&High,&Low,&Close,&Volume,&OpenInt);
Open_array[i].Open=Open;
//Open_array[i].Close=(int)round(Close);
Open_array[i].Close=Close;
Open_array[i].year=year;
Open_array[i].month=month;
Open_array[i].day=day;
Open_array[i].High=High;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt;
c=fgetc(f1);
if(c=='\n'){
i++;
}
}
//Needs change
printf("Please give a date:\n");
printf("Give year:\n");
scanf("%d",&year);
printf("Give month:\n");
scanf("%d",&month);
printf("Give day:\n");
scanf("%d",&day);
printf("Volume of %d is %d\n",date,Binary_search(Open_array,date,0,count-1));
printf("Please give a new date:\n");
char give_date[11];
int given_date;
printf("Give date in format: YYYY-MM-DD \n");
scanf("%s",give_date);
remove_all_chars(give_date,'-');
given_date=atoi(give_date);
printf("Volume of %d you gave is : %d\n",given_date,interpolationSearch(new_array,Open_array,0,count-1,given_date));
//dinoume hmeromhnies kai tis kanoume searching
return 0;
}
//algorithmos dyadikhs anazhthshs.spame to pinaka se misa synexomena eos otou to stixio a[mid] na einai iso me ayto pou psaxnoume (an einai megalytero apo to a[mid] kitazoume deksi ypopinaka an mikrotero ston aristero
int Binary_search(STOCK* array,int date,int left,int right){
if(left>right){
return -1;
}
int mid=(right+left)/2;
//metatropi date sto stock* array
//
if(array[mid] == date){
return array[mid].Volume;
}
else if(array[mid]>date){
return Binary_search(array,date,left,mid-1);
}
else{
return Binary_search(array,date,mid+1,right);
}
//Updated binary search to use the trick with the 'combined date' to reduce code volume.
}
//algorithmos anazitisis me paremvoli

int interpolationSearch(int* arr,STOCK* array, int l, int h, int date)
{
int low=l;
int high=h;
while((arr[high]>=date) && (date>arr[low])){
int next = low + ((date-arr[low])/(arr[high]-arr[low]))*(high-low);
if(date>arr[next]){
low=next+1;
}
else if(date<arr[next]){
high=next-1;
}
else{
low=next; //ypologizoume thn timh tou next kai analoga th sxesh tou stixiou tou pinaka me ayto os deikth kai aytou pou psaxnoume metakinoumaste eite kato h pano sto pinaka
}
}
if(date==arr[low]){
return array[low].Volume;
}
else{
return -1;
}
}

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
synarhthsh pou pernei os orisma ena string kai to xaraktira pou theloume na afairesoume kai afairei ton xaraktira ayton apo to string kai kolaei ta xorismena metaxy tous ypo-strings
*/
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}


