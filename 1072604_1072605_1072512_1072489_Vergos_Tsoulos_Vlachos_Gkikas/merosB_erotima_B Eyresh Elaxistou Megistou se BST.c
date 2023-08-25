//Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//AVL Tree node definition
struct Node{
int date;
int Volume;
int Ypsos;
struct Node* left;
struct Node* right;
};
//function declarations
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
//main menu
int main(){
struct Node* root=(struct Node*)malloc(sizeof(struct Node));
root=NULL;//memory allocation and initialization of AVL tree root
FILE* f1;
f1=fopen("agn.us.txt","r");//opening file
if(f1==NULL){
exit(1);
}
int count=Count_file(f1);
printf("Count is :%d\n",count);
fclose(f1);
f1=fopen("agn.us.txt","r+");
double Open,High,Low,Close;
Open=High=Low=Close=0.0;
int Volume,OpenInt;
Volume=OpenInt=0;// temporary variables to hold each field of a line
int i=0;
int temp=0;
char date[11];
while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{
//printf("%s,%lf,%lf,%lf,%lf,%d,%d\n",date,Open,High,Low,Close,Volume,OpenInt);
remove_all_chars(date,'-');//convert date string to int maintaining dates' order
temp=(int)atoi(date);//cast to int
root=eisagogi(root,temp,Volume);//till the end of the file insert for each line a node in the tree

}
int choice;//menu choice
fclose(f1);//finish reading file
while(1){//main menu
printf("1 for max Volume 2 for min volume 3 for exit\n");
scanf("%d",&choice);//user's input choice
switch(choice){
	case 1:
		printf("Max Volume is : %d\n",max_Volume(root));//max volume of AVL tree
		break;
	case 2:
		printf("Min  Volume is : %d\n",min_Volume(root));//min volume of AVL tree
		break;
	case 3:
		exit(0);
}
	
return 0;
}
}
//functions definitions
int max_of_subtrees(int i1,int i2){
if(i1>i2){
return i1;
}
return i2;//if i1=i2 or i2>i1 then i2 is the biggest
}
////
int Ypsos(struct Node* node){
if(node==NULL){//if it doesnt exist then return 0 height(1 for leaf node)
return 0;
}
return node->Ypsos;//find height of given tree node
}
////
int Ypsozigisi(struct Node* node){//find balance of a node in the tree
if(node==NULL){
return 0;//if it doesnt exist then return 0
}
return (Ypsos(node->left)-Ypsos(node->right));//node's height is the difference of the heights between its left subtree and right subtree

}
////
struct Node* create_node(int date,int Volume){
struct Node* create=(struct Node*)malloc(sizeof(struct Node));
create->date;
create->Volume=Volume;
create->Ypsos=1;
create->left=NULL;
create->right=NULL;
return (create);//new tree node has given data as its first data height of 1 and no children

}
////
struct Node* eisagogi(struct Node* add,int date,int Volume){
if(add==NULL){
return create_node(date,Volume);//if the tree is empty then create the node as its root
}
if(Volume<add->Volume){
add->left=eisagogi(add->left,date,Volume);//if inserted node's data is smaller than current node's data then go to left subtree
}
else if(Volume>add->Volume){
add->right=eisagogi(add->right,date,Volume);//if inserted node's data is bigger than current node's data then go to right subtree
}
else{
return add;//stixeia me idia timh volume de boroun na yparxoun se dyadiko dentro anazitisis
}
add->Ypsos=max_of_subtrees(Ypsos(add->left),Ypsos(add->right))+1;//since we insert a new node to the tree the current node's height is increased by //1
int ipsozygisi=Ypsozigisi(add);//however now the tree may be unbalanced due to the new insertion. Thus we 'weigh' the node
//we have 4 cases to balance the tree
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
{//left rotation
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
struct Node* deksia_peristrofi(struct Node* node){//right rotation
struct Node* x=node->left;
struct Node* sub=x->right;
//perform rotation
x->right=node;
node->left=sub;
//update heights
node->Ypsos=max_of_subtrees(Ypsos(node->left),Ypsos(node->right))+1;
x->Ypsos=max_of_subtrees(Ypsos(x->left),Ypsos(x->right))+1;
//return new root
return x;
}
////


////

int max_Volume(struct Node* riza){
struct Node* temp=riza;
while(temp->right!=NULL){
temp=temp->right;// AVL tree is a binary search tree sto Volume(left-subtree)<Volume(current root)<Volume(right-subtree) recursively
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

int Count_file(FILE* fp){//function to count a file's lines
char c=getc(fp);
int count=0;
for (c = getc(fp); c != EOF; c = getc(fp)){
if (c == '\n'){//if we encounter a new line increase count by one , i.e one more line
count = count + 1;}
}
return count;
}
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {//while we have not finished scanning the string
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

