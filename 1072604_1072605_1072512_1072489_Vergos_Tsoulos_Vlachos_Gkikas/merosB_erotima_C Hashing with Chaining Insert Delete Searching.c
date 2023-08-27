//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 3239#
//Hash table node data type
struct Node{
int date;
int key; //kleidi
int Volume;
struct Node* next; // deikth se tetoia domh etsi oste na ylopoihthei to chaining-linked list implementing chaining
};
//function definitions
int anazitisi(struct Node** table,int date,int key);
void diagrafi(struct Node** table ,int date,int key);
void tropopoihsh(struct Node** table,int date,int key);
void Print(struct Node** table);
void remove_all_chars(char* str, char c);
int Count_file(FILE* fp);
int ascii_values(char* s,int len);
void eisagogi(struct Node** table,int date ,int key,int Volume);
////////
//main menu
//
int main(){
FILE* f1=fopen("agn.us.txt","r");
if(f1==NULL){
exit(-1);
}
struct Node* Hash_Table[SIZE];//creating hash table 
int j=0;
for(j=0;j<SIZE;j++){
Hash_Table[j]=NULL;
}//arxikopoihsh ton next deikton- initialization of hash table
int count=Count_file(f1);
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("agn.us.txt","r+");
int Volume,OpenInt;
Volume=OpenInt=0;
double Open,High,Low,Close;
Open=High=Low=Close=0.0;//assistant variables to store file's lines' fields
char date[11];
int temp=0;
int key=0;
//reading file
while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{
key=ascii_values(date,strlen(date));
//hash thn timh toy key kai apotelesma->thesi sto array
remove_all_chars(date,'-');
temp=(int)atoi(date);
eisagogi(Hash_Table,temp,key,Volume);

}
fclose(f1);//close file
char give_date[11];
int given_date;
int choice;//variables to hold user's date input
while(1){//user interface
printf("1 for date search  2 for date volume modification  3 for date deletion 4 to print the hash table and 5 to exit\n");
scanf("%d",&choice);
switch(choice){
	case 1:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		key=ascii_values(give_date,strlen(give_date));
		printf("Volume of %d is : %d\n",given_date,anazitisi(Hash_Table,given_date,key));
		break;
	case 2:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		key=ascii_values(give_date,strlen(give_date));
		tropopoihsh(Hash_Table,given_date,key);
		break;
	case 3:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		key=ascii_values(give_date,strlen(give_date));
		diagrafi(Hash_Table,given_date,key);
		break;
	case 4:
		Print(Hash_Table);
		break;
	case 5:
		exit(0);
		break;
}
}



return 0;
}
//function definitions
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
//
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

////
/*

synarthsh h opoia prosthetei tis times ascii ton xaraktiron enos string ths morfhs "YYYY-MM-DD" .Xrhsimeyei gia na ypologisoume pou tha apothikeytei kathe egrafh sto pinaka katakermatismou
*/
int ascii_values(char* s,int len){
int sum=0;
int i;
for (i = 0; i < len; i++)
{

sum = sum + s[i];//in a string s, s(i) means its ascii value

}
return sum;
}
////
void eisagogi(struct Node** table,int date,int key,int Volume){
struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));//desmeysi mnimis gia to neo komvo
struct Node* temp_node=(struct Node*)malloc(sizeof(struct Node));//desmeysi mnimis gia to temp komvo sthn alysida
////
new_node->date=date;  //dimiourgia tou komvou
new_node->key=key;
new_node->Volume=Volume;
new_node->next=NULL;//efoson einai neos komvos tote den tha exei epomeno
////
int index=key%SIZE;//execute hash 'function'
////
if(table[index]==NULL){//here
table[index]=new_node;
} // an to keli tou pinaka einai adeio vale to neo komvo ekei
else{
//alios arxikopoihse metrhth me th koryfh ths listas dietrexe thn mexri to telos ths kai prosthese ekei to neo komvo
temp_node=table[index];//here
while(temp_node->next!=NULL){
temp_node=temp_node->next;
}
////
temp_node->next=new_node;
}
}
////
/*
synarthsh pou typonei to hash table
*/
//print the hash table bucket by bucket
void Print(struct Node** table){
struct Node* temp_node=(struct Node*)malloc(sizeof(struct Node));//represent a list's node in hash table
int i=0;
for(i=0;i<SIZE;i++){//Traversing all the buckets
if(table[i]==NULL){//here
printf("Table %d-th is empty!\n",i);
continue;//afou einai adeia pigene ston epomeno kouva
}
temp_node=table[i];//arxikopoihsh tou protou stixiou ths alysidas-//here
while(temp_node!=NULL){//mexri na diasxisoume olh th lista
printf(" ->%d-%d-> ",temp_node->date,temp_node->Volume);//typonoume kathe stixio ths listas tou kathe kouva
temp_node=temp_node->next;//diasxizoume th lista
}
printf("\n");
}
return;
}
////
//search a given date in the hash table and if it exists return its volume 
int anazitisi(struct Node** table,int date,int key){
int index=key%SIZE;//location in the table where we will search
struct Node* cur=(struct Node*)malloc(sizeof(struct Node));//node to begin traversal from to search
cur=table[index];//here
//vriskoume me th synarthsh katakermatismou pou vriskomaste ston pianaka.meta diatrexoume th lista mexri to telos ths kai an taytistoun oi hmeromhnies tote epistrefei to volume pou psaxnoume
while(cur!=NULL){
if(cur->date==date){//if current's node date is equal to the search date then we found the element
return cur->Volume;
}
cur=cur->next;
}
return -10;//if it is not found then return a negative value to signify search failure
}
////change volume of a given date
void tropopoihsh(struct Node** table,int date,int key){
int index=key%SIZE;
struct Node* cur=(struct Node*)malloc(sizeof(struct Node));
cur=table[index]; //vriskoume me th synarthsh katakermatismou pou vriskomaste ston pianaka.meta diatrexoume th lista mexri to telos ths kai an taytistoun oi hmeromhnies tote me th scanf alazoume to volume ekeinou tou komvoy
while(cur!=NULL){
if(cur->date==date){
printf("Please enter volume\n");
scanf("%d",&cur->Volume);
return;
}
cur=cur->next;
}
return;
}
////
//Delete a date in the hash table
void diagrafi(struct Node** table,int date,int key){
int index=key%SIZE;
struct Node* cur=table[index];
if(cur!=NULL){
if(cur->date==date){
cur=cur->next;//diagrafi an h lista exei 1 mono stixio
}
else
{
while(cur->next!=NULL){
if(cur->next->date==date){
cur->next=cur->next->next;//syndeoume ton proigoumeno komvo aytou pou theloume na diagrapsoume me ton epomeno aytou pou theloume na diagrapsoume etsi petyxainoume ti diagrafi
}
cur=cur->next; //diatrexoume th lista
}
}
}	
}

