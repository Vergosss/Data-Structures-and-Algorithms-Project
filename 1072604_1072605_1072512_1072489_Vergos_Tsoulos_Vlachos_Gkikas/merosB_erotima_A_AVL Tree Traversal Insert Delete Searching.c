#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*
typedef struct Node_only{
int date;
int Volume;
}NODE_ONLY;
*/
struct Node{
int date;
int Volume;
int Ypsos;
struct Node* left;
struct Node* right;
};
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
char give_date[11];
int given_date;
while(1){
printf("1 for inorder traversal 2 for searching 3 for modification 4 for deletion and 5 to exit\n");
scanf("%d",&choice);
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
struct Node* create_node(int date,int Volume){
struct Node* create=(struct Node*)malloc(sizeof(struct Node));
create->date=date;
create->Volume=Volume;
create->Ypsos=1;
create->left=NULL;
create->right=NULL;
return (create);

}
////
int Ypsozigisi(struct Node* node){
if(node==NULL){
return 0;
}
return (Ypsos(node->left)-Ypsos(node->right));

}
////
////
int Ypsos(struct Node* node){
if(node==NULL){
return 0;
}
return node->Ypsos;
}
////
int max_of_subtrees(int i1,int i2){
if(i1>i2){
return i1;
}
return i2;
}
////
struct Node* eisagogi(struct Node* add,int date,int Volume){
if(add==NULL){
return create_node(date,Volume);
}
if(date<add->date){
add->left=eisagogi(add->left,date,Volume);
}
else if(date>add->date){
add->right=eisagogi(add->right,date,Volume);
}
else{
return add;
}
add->Ypsos=max_of_subtrees(Ypsos(add->left),Ypsos(add->right))+1;
int ipsozygisi=Ypsozigisi(add);
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
struct Node* y=node->right;
struct Node* sub=y->left;
y->left=node;
node->right=sub;
node->Ypsos=max_of_subtrees(Ypsos(node->left),Ypsos(node->right))+1;
y->Ypsos=max_of_subtrees(Ypsos(y->left),Ypsos(y->right))+1;
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
void endodiatetagmeni_diasxisi(struct Node* riza){
if(riza==NULL){
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
temp=temp->right; //an h hmeromhnia pou dosame einai megalyterh apo to komvo pou vriskomaste epeidh einai dyadiko dentro anazitisis pame sto deksi pedi
}
else{
temp=temp->left; //an h hmeromhnia pou dosame einai mikroterh apo to komvo pou vriskomaste epeidh einai dyadiko dentro anazitisis pame sto aristero pedi
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
{ 
    struct Node* temp= node; 
    while (temp->left != NULL) {
	
        temp= temp->left; 
}
    return temp; 
} 
