#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct Stock{
int date,Volume,OpenInt;
double Open,High,Low,Close;
}STOCK;
void remove_all_chars(char* str,char c);
int Count_file(FILE* fp);
void Print(int* arr,int megethos);
int binary_interpolation_search(STOCK* array,int date,int megethos);
int LinearSearch(STOCK* array,int left,int right,int date);
void checkAlgorithmValidity(STOCK* array,int megethos);
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
//dhlonoume pinaka pou tha apothikeysei tis hmeromhnies pano stis opoies kanoume searching
int Volume,OpenInt; //prosorines metavlites pou apothikeyoyn ta antistixa pedia apo to arxeio
Volume=OpenInt=0;
double Open,High,Low,Close;
Open=High=Low=Close=0.0;
int i=0;
int temp=0;
char date[11];
//
while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{
remove_all_chars(date,'-');//convert date string to int maintaining dates' order
temp=(int)atoi(date);//cast to int
Open_array[i].Open=Open;
//Open_array[i].Close=(int)round(Close);
Open_array[i].Close=Close;
Open_array[i].date=temp;
Open_array[i].High=High;
Open_array[i].Low=Low;
Open_array[i].Volume=Volume;
Open_array[i].OpenInt=OpenInt;

++i;

}
fclose(f1);
/*
char give_date[11]; //Dhlonoume th metavliti hmeromhnias anazitisis
int given_date;
printf("Give date in format: YYYY-MM-DD \n");
scanf("%s",give_date);
remove_all_chars(give_date,'-');
given_date=(int)atoi(give_date);
//printf("Volume of the date you provided is : %d \n",interpolationSearch(new_array,Open_array,0,count-1,given_date));
printf("Volume of the date you provided is : %d \n",binary_interpolation_search(Open_array,given_date,count));
*/
checkAlgorithmValidity(Open_array,count);
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
int binary_interpolation_search(STOCK* array,int date,int megethos){
int i;
int left=0;//in C first index is 0
int right=megethos-1;//in C last index is size-1
int size=right-left+1;//array size
int next=(int)(ceil(size*(date-array[left].date)/(array[right].date-array[left].date)))+1;
while(date!=array[next].date){
i=0;
size=right-left+1;//regardless of subarray the formula for the size is always this
if(size<=3){
return LinearSearch(array,left,right,date);
}
if(date>=array[next].date){
while(date>array[next+i*(int)(floor(sqrt(size)))-1].date){
i++; //sth veltiosh xeirisths periptosis tha exoume i=2*i;
}
right=next+i*(int)(floor(sqrt(size)));
left=next+(i-1)*(int)(floor(sqrt(size)));
}
else if(date<array[next].date){
while(date<array[next-i*(int)(floor(sqrt(size)))+1].date){
i++; //sth veltiosh xeirisths periptosis tha exoume i=2*i;
}
right=next-(i-1)*(int)(floor(sqrt(size)));
left=next-i*(int)(floor(sqrt(size)));
}
next=left+(int)(ceil((right-left+1)*(date-array[left].date)/(array[right].date-array[left].date))) -1;

}
if(date==array[next].date){
return array[next].Volume;
}
else{
return -1;
}
}

/*
algorithmos grammikhs anazhthshs ton opoion kaloume kata thn ektelesh tou binary interpolation search otan to diastima mesa sto opoio psaxnoume to stixio einai mikro arketa(p.x <=3).
*/
int LinearSearch(STOCK* array, int left, int right, int date)
{
	int i = left;
	while (i <= right){
		if (array[i].date == date){
		return array[i].Volume;
		}
		i++;
	}
	return -1;
}
void checkAlgorithmValidity(STOCK* array,int megethos){
int i;
for(i=0;i<megethos;i++){
if(array[i].Volume != binary_interpolation_search(array,array[i].date,megethos)){
printf("The algorithm doesnt work\n");
return;
}

}
printf("The algorithm works\n");
return;
}
