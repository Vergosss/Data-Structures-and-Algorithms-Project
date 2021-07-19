#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct Node{
int date;
int Volume;
int Ypsos;
struct Node* left;
struct Node* right;
};
void remove_all_chars(char* str, char c);
struct Node* create_node(int date,int Volume);
int Ypsozigisi(struct Node* node);
int Ypsos(struct Node* node);
int max_of_subtrees(int i1,int i2);
struct Node* eisagogi(struct Node* add,int date,int Volume);
struct Node* aristeri_peristrofi(struct Node* node);
struct Node* deksia_peristrofi(struct Node* node);
int min_Volume(struct Node* riza);
int max_Volume(struct Node* riza);
int Count_file(FILE* fp);
int main(){
struct Node* root=(struct Node*)malloc(sizeof(struct Node));
root=NULL;
FILE* f1;
f1=fopen("agn.us.txt","r");
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("agn.us.txt","r+");
float Open,High,Low,Close;
Open=High=Low=Close=0.0;
int Volume,OpenInt;
Volume=OpenInt=0;
int i=0;
int temp=0;
char date[11];
char z=fgetc(f1);
while(z!=EOF)
{
fscanf(f1,"%s,%f,%f,%f,%f,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt);
remove_all_chars(date,'-');
temp=(int)atoi(date);
root=eisagogi(root,temp,Volume);
z=fgetc(f1);

if(z=='\n'){
i++;
}
}
int choice;
fclose(f1);
while(1){
printf("1 for max Volume 2 for min volume 3 for exit\n");
scanf("%d",&choice);
switch(choice){
	case 1:
		printf("Max Volume is : %d\n",max_Volume(root));
		break;
	case 2:
		printf("Min  Volume is : %d\n",min_Volume(root));
		break;
	case 3:
		exit(0);
}
	
return 0;
}
}
int max_of_subtrees(int i1,int i2){
if(i1>i2){
return i1;
}
return i2;
}
////
int Ypsos(struct Node* node){
if(node==NULL){
return 0;
}
return node->Ypsos;
}
////
int Ypsozigisi(struct Node* node){
if(node==NULL){
return 0;
}
return (Ypsos(node->left)-Ypsos(node->right));

}
////
struct Node* create_node(int date,int Volume){
struct Node* create=(struct Node*)malloc(sizeof(struct Node));
create->date;
create->Volume=Volume;
create->Ypsos=1;
create->left=NULL;
create->right=NULL;
return (create);

}
////
struct Node* eisagogi(struct Node* add,int date,int Volume){
if(add==NULL){
return create_node(date,Volume);
}
if(Volume<add->Volume){
add->left=eisagogi(add->left,date,Volume);
}
else if(Volume>add->Volume){
add->right=eisagogi(add->right,date,Volume);
}
else{
return add;//stixeia me idia timh volume de boroun na yparxoun se dyadiko dentro anazitisis
}
add->Ypsos=max_of_subtrees(Ypsos(add->left),Ypsos(add->right))+1;
int ipsozygisi=Ypsozigisi(add);

if(ipsozygisi>1 && Volume<add->left->Volume){
return deksia_peristrofi(add);
}
else if(ipsozygisi<-1 && Volume>add->right->Volume){
return aristeri_peristrofi(add);
}
else if(ipsozygisi>1 && Volume>add->left->Volume){
add->left = aristeri_peristrofi(add->left);
return deksia_peristrofi(add);
}
else if(ipsozygisi<-1 && Volume<add->right->Volume){
add->right = deksia_peristrofi(add->right);
return aristeri_peristrofi(add);
}

return add;
}
////
struct Node* aristeri_peristrofi(struct Node* node)
{
    struct Node* y = node->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = node;
    node->right = T2;

    //  Update heights
    node->Ypsos = max_of_subtrees(Ypsos(node->left), Ypsos(node->right))+1;
    y->Ypsos = max_of_subtrees(Ypsos(y->left), Ypsos(y->right))+1;

    // Return new root
    return y;
}
////
struct Node* deksia_peristrofi(struct Node* node){
struct Node* x=node->left;
struct Node* sub=x->right;
x->right=node;
node->left=sub;
node->Ypsos=max_of_subtrees(Ypsos(node->left),Ypsos(node->right))+1;
x->Ypsos=max_of_subtrees(Ypsos(x->left),Ypsos(x->right))+1;

return x;
}
////


////

int max_Volume(struct Node* riza){
struct Node* temp=riza;
while(temp->right!=NULL){
temp=temp->right;
}
return temp->date;


}
////
int min_Volume(struct Node* riza){
struct Node* temp=riza;
while(temp->left!=NULL){
temp=temp->left;
} // AVL tree is a binary search tree sto Volume(left-subtree)<Volume(current root)<Volume(right-subtree) recursively
return temp->date;
}
////

int Count_file(FILE* fp){
char c=getc(fp);
int count=0;
for (c = getc(fp); c != EOF; c = getc(fp)){
if (c == '\n'){
count = count + 1;}
}
return count;
}
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

