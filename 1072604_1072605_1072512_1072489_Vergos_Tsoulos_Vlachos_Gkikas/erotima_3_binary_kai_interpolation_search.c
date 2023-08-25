//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Stock structure represents each line of the file
typedef struct Stock{
int date,Volume,OpenInt;
double Open,High,Low,Close;
}STOCK;
//function definitions
void Print(STOCK* arr,int megethos);
void remove_all_chars(char* str,char c);
int Count_file(FILE* fp);
int interpolationSearch(STOCK* array, int l, int h, int date);
int Binary_search(STOCK* array,int date,int left,int right);
//main menu
int main(){
FILE* f1;
f1=fopen("agn.us.txt","r");
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);//number of lines in file
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("agn.us.txt","r+");
STOCK Open_array[count];
int Volume,OpenInt;
Volume=OpenInt=0;
double Open,High,Low,Close;
Open=High=Low=Close=0.0;//assistant variables to hold each field of the file
int temp=0;
int i=0;
char date[11];
//
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
//Needs change
char give_date[11];
int given_date;
printf("Give date in format: YYYY-MM-DD \n");
scanf("%s",give_date);
remove_all_chars(give_date,'-');
given_date=(int)atoi(give_date);
printf("Volume of %d is %d\n",given_date,Binary_search(Open_array,given_date,0,count-1));
//
printf("Please give a new date:\n");

printf("Give date in format: YYYY-MM-DD \n");
scanf("%s",give_date);
remove_all_chars(give_date,'-');
given_date=(int)atoi(give_date);
printf("Volume of %d you gave is : %d\n",given_date,interpolationSearch(Open_array,0,count-1,given_date));
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
if(array[mid].date == date){
return array[mid].Volume;
}
else if(array[mid].date>date){
return Binary_search(array,date,left,mid-1);
}
else{
return Binary_search(array,date,mid+1,right);
}
//Updated binary search to use the trick with the 'combined date' to reduce code volume.
}
//algorithmos anazitisis me paremvoli

int interpolationSearch(STOCK* array, int l, int h, int date)
{
int low=l;
int high=h;
while((array[high].date>=date) && (date>array[low].date)){
int next = low + ((date-array[low].date)/(array[high].date-array[low].date))*(high-low);
if(date>array[next].date){
low=next+1;
}
else if(date<array[next].date){
high=next-1;
}
else{
low=next; //ypologizoume thn timh tou next kai analoga th sxesh tou stixiou tou pinaka me ayto os deikth kai aytou pou psaxnoume metakinoumaste eite kato h pano sto pinaka
}
}
if(date==array[low].date){
return array[low].Volume;
}
else{
return -1;
}
}

int Count_file(FILE* fp){//function that counts the lines of a text file
char c=getc(fp);
int count=0;
for (c = getc(fp); c != EOF; c = getc(fp)){
if (c == '\n'){
count = count + 1;}//if we change line count is increased by one(new line).
}
return count;
}

/*
synarhthsh pou pernei os orisma ena string kai to xaraktira pou theloume na afairesoume kai afairei ton xaraktira ayton apo to string kai kolaei ta xorismena metaxy tous ypo-strings
*/
void remove_all_chars(char* str, char c) {//function that accepts a string and a character. it removes this character and deletes the space in the
//deleted position.
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}


