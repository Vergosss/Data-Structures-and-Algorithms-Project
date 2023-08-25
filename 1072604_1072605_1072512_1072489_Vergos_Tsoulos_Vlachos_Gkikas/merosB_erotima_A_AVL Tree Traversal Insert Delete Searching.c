//Libraries
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*
typedef struct Node_only{
int date;
int Volume;
}NODE_ONLY;
*/
//AVL Tree node definition
struct Node{
int date;
int Volume;
int Ypsos;
struct Node* left;
struct Node* right;
};
//function declarations
int max_date(struct Node* riza);
int min_date(struct Node* riza);
void remove_all_chars(char* str,char c);
struct Node* create_node(int date,int Volume);
int Ypsozigisi(struct Node* node);
int Ypsos(struct Node* node);
int max_of_subtrees(int i1,int i2);
struct Node* eisagogi(struct Node* add,int date,int Volume);
struct Node* aristeri_peristrofi(struct Node* node);
struct Node* deksia_peristrofi(struct Node* node);
void endodiatetagmeni_diasxisi(struct Node* riza);
struct Node* diagrafi(struct Node* add, int date);
struct Node* min_node(struct Node* node); 
int search(struct Node* root,int date);
int Count_file(FILE* fp);
int tropopoihsh_Volume(struct Node* root,int date);
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
Open=High=Low=Close=0.0;// temporary variables to hold each field of a line
int Volume,OpenInt;
Volume=OpenInt=0;
int i=0;
int temp=0;
char date[11];

while(fscanf(f1,"%[^,],%lf,%lf,%lf,%lf,%d,%d",date,&Open,&High,&Low,&Close,&Volume,&OpenInt) == 7)
{//this prevents skipping first character of the file and also prevents reading last line twice
//printf("%s,%f,%f,%f,%f,%d%d\n",date,Open,High,Low,Close,Volume,OpenInt);
remove_all_chars(date,'-');//convert date string to int maintaining dates' order
temp=(int)atoi(date);//cast to int
root=eisagogi(root,temp,Volume);//till the end of the file insert for each line a node in the tree
//z=fgetc(f1); this prevents skipping first character of the file


}
fclose(f1);//close file
int choice;//menu choice
char give_date[11];
int given_date;
while(1){//main menu
printf("1 for inorder traversal 2 for searching 3 for modification 4 for deletion and 5 to exit\n");
scanf("%d",&choice);//user's input choice
switch(choice){
	case 1:
		endodiatetagmeni_diasxisi(root);
		break;
	case 2:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		printf("Volume of %d is : %d\n",given_date,search(root,given_date));
		break;
	case 3:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		printf("Volume of %d is : %d\n",given_date,tropopoihsh_Volume(root,given_date));
		break;
	case 4:
		printf("Give date in format: YYYY-MM-DD \n");
		scanf("%s",give_date);
		remove_all_chars(give_date,'-');
		given_date=atoi(give_date);
		root=diagrafi(root,given_date);
		break;
	case 5:
		exit(0);	
}
}

return 0;
}
//functions definitions
struct Node* create_node(int date,int Volume){
struct Node* create=(struct Node*)malloc(sizeof(struct Node));
create->date=date;
create->Volume=Volume;
create->Ypsos=1;
create->left=NULL;
create->right=NULL;
return (create);//new tree node has given data as its first data height of 1 and no children


}
////
int Ypsozigisi(struct Node* node){
if(node==NULL){
return 0;//if it doesnt exist then return 0
}
return (Ypsos(node->left)-Ypsos(node->right));//node's height is the difference of the heights between its left subtree and right subtree

}
////
////
int Ypsos(struct Node* node){
if(node==NULL){//if it doesnt exist then return 0 height(1 for leaf node)
return 0;
}
return node->Ypsos;//find height of given tree node
}
////
int max_of_subtrees(int i1,int i2){
if(i1>i2){
return i1;
}
return i2;//if i1=i2 or i2>i1 then i2 is the biggest
}
////
struct Node* eisagogi(struct Node* add,int date,int Volume){
if(add==NULL){
return create_node(date,Volume);//if the tree is empty then create the node as its root
}
if(date<add->date){
add->left=eisagogi(add->left,date,Volume);//if inserted node's data is smaller than current node's data then go to left subtree
}
else if(date>add->date){
add->right=eisagogi(add->right,date,Volume);//if inserted node's data is bigger than current node's data then go to right subtree
}
else{
return add;//stixeia me idia timh volume de boroun na yparxoun se dyadiko dentro anazitisis
}
add->Ypsos=max_of_subtrees(Ypsos(add->left),Ypsos(add->right))+1;//since we insert a new node to the tree the current node's height is increased by //1
int ipsozygisi=Ypsozigisi(add);//however now the tree may be unbalanced due to the new insertion. Thus we 'weigh' the node
//we have 4 cases to balance the tree
if (ipsozygisi > 1 && date < add->left->date){
return deksia_peristrofi(add);
}
if (ipsozygisi <-1  && date > add->right->date){
return aristeri_peristrofi(add);
}
if (ipsozygisi > 1 && date > add->left->date)
{
add->left = aristeri_peristrofi(add->left);
return deksia_peristrofi(add);
}
if (ipsozygisi < -1 && date < add->right->date)
{
add->right = deksia_peristrofi(add->right);
return aristeri_peristrofi(add);
}

return add;
}
////
struct Node* aristeri_peristrofi(struct Node* node){
//left rotation
struct Node* y=node->right;
struct Node* sub=y->left;
// Perform rotation
y->left=node;
node->right=sub;
 //  Update heights
node->Ypsos=max_of_subtrees(Ypsos(node->left),Ypsos(node->right))+1;
y->Ypsos=max_of_subtrees(Ypsos(y->left),Ypsos(y->right))+1;
//return new root
return y;
}
////
struct Node* deksia_peristrofi(struct Node* node){
//right rotation
struct Node* x=node->left;
struct Node* sub=x->right;
// Perform rotation
x->right=node;
node->left=sub;
//Update heights
node->Ypsos=max_of_subtrees(Ypsos(node->left),Ypsos(node->right))+1;
x->Ypsos=max_of_subtrees(Ypsos(x->left),Ypsos(x->right))+1;
//return new root
return x;
}
////



////
void endodiatetagmeni_diasxisi(struct Node* riza){
if(riza==NULL){//inorder traversal in AVL Tree and BST's in general
return;
}
endodiatetagmeni_diasxisi(riza->left);
printf("%d-%d\n",riza->date,riza->Volume);
endodiatetagmeni_diasxisi(riza->right);
return;
}

int search(struct Node* root,int date){
struct Node* temp=root;
while(temp->date!=date){

if(temp!=NULL){
if(date>temp->date){
temp=temp->right;
}
else{
temp=temp->left;
}
if(temp==NULL){
return -1;
}
}


}
return temp->Volume;
}
////
int tropopoihsh_Volume(struct Node* root,int date){
struct Node* temp=root;
while(temp->date!=date){

if(temp!=NULL){
if(date>temp->date){
temp=temp->right; //an h hmeromhnia pou dosame einai megalyterh apo to komvo pou vriskomaste epeidh einai dyadiko dentro anazitisis pame sto deksi //pedi
}
else{
temp=temp->left; //an h hmeromhnia pou dosame einai mikroterh apo to komvo pou vriskomaste epeidh einai dyadiko dentro anazitisis pame sto aristero //pedi
}
if(temp==NULL){
return -1;
}
}

}
printf("Please give the new Volume:\n"); //molis ftasoume sto komvo pou theloume tote meso scanf alazoume to pedio volume
scanf("%d",&temp->Volume);
return temp->Volume;
}
int Count_file(FILE* fp){//count number of lines in file
char c=getc(fp);
int count=0;
for (c = getc(fp); c != EOF; c = getc(fp)){
if (c == '\n'){
count = count + 1;}
}
return count;
}
void remove_all_chars(char* str, char c) {//remove given character from string and delete the produced space
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}
int min_date(struct Node* riza){
struct Node* temp=riza;
while(temp->left!=NULL){
temp=temp->left;
} // AVL tree is a binary search tree sto Volume(left-subtree)<Volume(current root)<Volume(right-subtree) recursively
return temp->date;
}
int max_date(struct Node* riza){
struct Node* temp=riza;
while(temp->right!=NULL){
temp=temp->right;
} // AVL tree is a binary search tree sto Volume(left-subtree)<Volume(current root)<Volume(right-subtree) recursively
return temp->date;
}
struct Node* diagrafi(struct Node* add, int date) 
{ 
      
    // STEP 1: PERFORM STANDARD BST DELETE 
    if (add == NULL){
	
        return add; 
}
  
    if ( date < add->date ) 
        add->left = diagrafi(add->left, date); 
  
    else if( date > add->date ) 
        add->right = diagrafi(add->right, date); 
  
    // if key is same as root's key, then 
    // This is the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (add->left == NULL) ||
            (add->right == NULL) ) 
        { 
            struct Node* temp = add->left ? 
                         add->left : 
                         add->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = add; 
                add = NULL; 
            } 
            else{ // One child case 
            *add = *temp; // Copy the contents of 
                 }          // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct Node* temp = min_node(add->right); 
  
            // Copy the inorder successor's 
            // data to this node 
            add->date = temp->date; 
  
            // Delete the inorder successor 
            add->right = diagrafi(add->right,temp->date); 
        } 
    } 
  
    // If the tree had only one node
    // then return 
    if (add == NULL) {
	
    return add; 
}
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    add->Ypsos = 1 + max_of_subtrees(Ypsos(add->left), Ypsos(add->right)); 

    // STEP 3: GET THE BALANCE FACTOR OF 
    // THIS NODE (to check whether this 
    // node became unbalanced) 
    int balance = Ypsozigisi(add); 
  
    // If this node becomes unbalanced, 
    // then there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && Ypsozigisi(add->left) >= 0) 
        return deksia_peristrofi(add); 
  
    // Left Right Case 
    if (balance > 1 && Ypsozigisi(add->left) < 0) 
    { 
        add->left = aristeri_peristrofi(add->left); 
        return deksia_peristrofi(add); 
    } 
  
    // Right Right Case 
    if (balance < -1 && Ypsozigisi(add->right) <= 0) 
        return aristeri_peristrofi(add); 
  
    // Right Left Case 
    if (balance < -1 && Ypsozigisi(add->right) > 0) 
    { 
        add->right = deksia_peristrofi(add->right); 
        return aristeri_peristrofi(add); 
    } 
  
    return add; 
} 

struct Node* min_node(struct Node* node) 
{ //node with min value in AVL tree and BStrees in general is that the leftmost leaf has the smallest value
    struct Node* temp= node; 
    while (temp->left != NULL) {
	
        temp= temp->left; 
}
    return temp; 
} 
