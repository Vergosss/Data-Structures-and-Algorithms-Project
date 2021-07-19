#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Stock{
int year,month,day,Volume,OpenInt;
float Open,High,Low,Close;
}STOCK;
void remove_all_chars(char* str,char c);
int Count_file(FILE* fp);
void Print(int* arr,int megethos);
int binary_interpolation_search(int* arr,STOCK* array,int date,int megethos);
int LinearSearch(int* arr,STOCK* array,int left,int right,int date);
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
//STOCK_ Open_array[count];
//STOCK_ Open_array2[count];
STOCK Open_array[count];
int new_array[count];//dhlonoume pinaka pou tha apothikeysei tis hmeromhnies pano stis opoies kanoume searching
int year,Volume,OpenInt,month,day; //prosorines metavlites pou apothikeyoyn ta antistixa pedia apo to arxeio
year=month=day=Volume=OpenInt=0;
float Open,High,Low,Close;
Open=High=Low=Close=0.0;
int i=0;
char c=getc(f1);
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

c=getc(f1);
if(c=='\n'){
i++;
}
}
fclose(f1);
f1=fopen("agn.us.txt","r+");
i=0;
int temp=0;
char date[11];
char z=getc(f1);
/*
skanaroume to arxeio kai apothikeyoume se metavlites thn hmeromhnia os string sth morfh:YYYY-MM-DD kai stis ypoloipes
metavlites tous arithmous pou xorizontai metaxy tous me comma.
*/
while(z!=EOF)
{
fscanf(f1,"%s,%f,%f,%f,%f,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt);
Open_array[i].Open=Open;
//Open_array[i].Close=(int)round(Close);
/*Open_array[i].Close=Close;
Open_array[i].year=year;
Open_array[i].month=month;
Open_array[i].day=day;
Open_array[i].High=High;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt;
*/
remove_all_chars(date,'-');//klhsh synarthshs poy afairei apo thn hmeromhnia tis payles kai svinei ta kena
temp=atoi(date); //metatrepoume thn hmeromhnia pou einai string akoma kai xoris ta kena se akeraio gia na th xeiristoume
new_array[i]=temp;
z=getc(f1);
if(z=='\n'){
i++;
}
}
//Print(new_array,count);
char give_date[11]; //Dhlonoume th metavliti hmeromhnias anazitisis
int given_date;
printf("Give date in format: YYYY-MM-DD \n");
scanf("%s",give_date);
remove_all_chars(give_date,'-');
given_date=atoi(give_date);
//printf("Volume of the date you provided is : %d \n",interpolationSearch(new_array,Open_array,0,count-1,given_date));
printf("Volume of the date you provided is : %d \n",binary_interpolation_search(new_array,Open_array,given_date,count));


return 0;
}
/*
synartisi pou metrame poses grames stixion exei to arxeio.tosa tha einai kai ta stixia ton pinakon pou xeirizomaste
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
synarthsh pou pernei os orisma pinaka akeraion kai typonei ta stixia tou
*/
void Print(int* arr,int megethos){
int i;
for(i=0;i<megethos;i++){
printf("%d\n",arr[i]);
}
return;

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
/*
algorithmos diikis anazitisis paremvolis. Ylopoihmenos basei tou vivliou tou kyrioy tsakalidi.
*/
int binary_interpolation_search(int* arr,STOCK* array,int date,int megethos){
int i;
int left=0;
int right=megethos-1;
int size=right-left;
int next=size*(date-arr[left])/(arr[right]-arr[left])+1;
while(date!=arr[next]){
i=0;
size=right-left;
if(size<=3){
return LinearSearch(arr,array,left,right,date);
}
if(date>=arr[next]){
while(date>arr[next+i*(int)(sqrt(size))-1]){
i++; //sth veltiosh xeirisths periptosis tha exoume i=2*i;
}
right=next+i*sqrt(size);
left=next+(i-1)*sqrt(size);
}
else if(date<arr[next]){
while(date<arr[next-i*(int)(sqrt(size))+1]){
i++; //sth veltiosh xeirisths periptosis tha exoume i=2*i;
}
right=next-(int)((i-1)*sqrt(size));
left=next-(int)(i*sqrt(size));
}
next=left+(right-left+1)*(date-arr[left])/(arr[right]-arr[left]) -1;
}
if(date==arr[next]){
return array[next].Volume;
}
else{
return -1;
}
}
/*
algorithmos grammikhs anazhthshs ton opoion kaloume kata thn ektelesh tou binary interpolation search otan to diastima mesa sto opoio psaxnoume to stixio einai mikro arketa(p.x <=3).
*/
int LinearSearch(int* arr,STOCK* array, int left, int right, int date)
{
	int i = left;
	while (i <= right){
		if (arr[i] == date){
		return array[i].Volume;
		}
		i++;
	}
	return -1;
}
