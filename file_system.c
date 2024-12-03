/*file system simulator in C*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_SIZE 50
typedef struct node{
    char name[30];
    int childCount;
    struct node** ptr;
}node;
node* stack[STACK_SIZE];
int top = -1;
node* prev_node();
node* create_node(void);
node* change_directory(node** temp);
void create_directory(node** temp);//internal node
void display(node* root,int level);
void create_file();//leaf node
void push(node* directory);
node* pop();
int main(void){
    node* root = create_node();
    strcpy(root->name,"root");
    root->childCount = 0;
    root->ptr = NULL;
    node* currentDirectory = root;
    
    while(1){
        /*menu*/
        int choice;
        printf("\n--------------------------\n----------FILES----------\n--------------------------\n");
        printf("1.create a directory\n2.display files\n3.Change directory\n4.Exit\n");
        printf("----------------------------\n");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
            case 1: create_directory(&currentDirectory);
                    break;
            case 2: printf("\n");
                    display(currentDirectory,0);
                    break;
            case 3: currentDirectory = change_directory(&currentDirectory);
                    break; 
            case 4: exit(0);
            default:printf("Invalid input!\n");
                    break;
        }
    }
}

node* create_node(){
    node* n;
    n = malloc(sizeof(node));
    n -> ptr = NULL;
    n -> childCount = 0;
    return n;
}

void create_directory(node** temp){
    node* root = *temp;
    char name[30];
    printf("Type name: ");
    scanf("%s",name);
    node* newNode = create_node();
    root->ptr = realloc(root->ptr,sizeof(node*)*(root->childCount + 1));
    root -> ptr[root->childCount++] = newNode;
    strcpy(newNode->name,name);
    printf("directory created!\n"); 
}

void display(node* root,int level){
    
    if(root == NULL)
        return;
        
    
    for(int i=0;i<level;i++){
        printf(" ");
    }
    if(level!=0)
        printf(" |_");
    printf("%s\n",root->name);
    
    int count = root -> childCount;
    for(int i = 0;i<count;i++){
        display(root->ptr[i],level+1);
    }

}

node* change_directory(node** temp){
    node* root = *temp;
    char name[15];
    printf("Choose directory(Type '..' to return to previous directory): ");
    scanf("%s",name);
    if(strcmp(name,"..")==0){
        root = pop();
        return root;
    }
    for(int i =0;i<root->childCount;i++){
        if(strcmp(name,(root->ptr[i])->name)==0){
            printf("Directory changed to %s\n",(root->ptr[i])->name);
            push(root);
            return root->ptr[i];
        }
    }
}

void push(node* directory){
    stack[++top] = directory;
}

node* pop(){
    return stack[top--];
}