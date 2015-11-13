
//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε03 - Θέμα 1                ***
//***                                                       ***
//***                   Ακ.έτος 2015-16                     ***
//***                                                       ***
//*************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct data node_data;
typedef struct binary_tree binary_tree;

//Data of a Binary Tree Node
struct data{
    char identity[9];
    char name[15];
    char sirname[20];
    float avg_grade;
};

//Binary Tree Node
struct node{
    node_data *data;
    node *parent;
    node *left;
    node *right;
};


//Binary Tree
struct binary_tree{
    node *root;
};

binary_tree* init_bt();
node *findMax(node* root);
node* bt_search(char *query, node *root);
node* create_btree();
void print_node(node* n);
void add(node* leaf, node* root);
void delete_element(char *query, node *root);
void inorder(node* bt);
void overwrite(node* A, node* B);
void add_node(char *identity, char *name, char *sirname, float avg_grade, binary_tree* bt);
void read_db_to_tree(binary_tree *);
void print_preorder(node* bt);

int identity(){
    binary_tree *tree = init_bt();
    read_db_to_tree(tree);
    node* tmp;
    char buffer[50];
    float fbuff;
    int cmd;
    FILE *f;


    while(1){
        printf("########################\n");
        printf("# 1. Print In-Order    #\n");
        printf("# 2. Search            #\n");
        printf("# 3. Modify            #\n");
        printf("# 4. Delete            #\n");
        printf("# 5. Exit              #\n");
        printf("########################\n");
        printf("Enter your choice: ");
        scanf("%d",&cmd);
        switch (cmd){
            case 1:
                inorder(tree->root);
                break;
            case 2:
                printf("Enter IDENTITY NUMBER: ");
                scanf("%s",&buffer);
                tmp = bt_search(buffer, tree->root);
                if (tmp != NULL) {
                    printf("\nResult: ");
                    print_node(tmp);
                    printf("\n");
                }
                break;
            case 3:
                printf("Enter IDENTITY: ");
                scanf("%s", &buffer);
                tmp = bt_search(buffer, tree->root);
                if (tmp != NULL){
                    printf("Enter Name: ");
                    scanf("%s",&buffer);
                    strcpy(tmp->data->name, buffer);
                    printf("Enter Sirname: ");
                    scanf("%s",&buffer);
                    strcpy(tmp->data->sirname, buffer);
                    printf("Enter Average Grade: ");
                    scanf("%f",&fbuff);
                    tmp->data->avg_grade = fbuff;
                    printf("\n\n");
                    print_node(tmp);
                }
                fflush(stdin);
                break;
            case 4:
                printf("Enter IDENTITY: ");
                scanf("%s",&buffer);
                delete_element(buffer, tree->root);
                break;

            case 5:
                // Clear the previous database file
                f = fopen("student_database.txt", "w");
                fclose(f);
                print_preorder(tree->root);
                return 0;
            default:
                printf("Bad Command\n");
                break;
        }
    }

}

//Binary Tree Initialization
binary_tree* init_bt(){
    binary_tree* bt = (binary_tree*)malloc(sizeof(binary_tree));
    bt->root = NULL;
    return bt;
}

//Binary Tree Print Method
void inorder(node* bt){
    if (bt != NULL){
        inorder(bt->left);
        print_node(bt);
        inorder(bt->right);
    }
}

//Add Node to Binary Tree (Client Side)
void add_node(char *identity, char *name, char *sirname,
    float avg_grade, binary_tree* bt)
    {

    //Node Initialization
    node* leaf = (node*)malloc(sizeof(node));
    leaf->left = NULL;
    leaf->right= NULL;

    //Set Node Data
    leaf->data = (node_data*)malloc(sizeof(node_data));
    strcpy(leaf->data->identity, identity);
    strcpy(leaf->data->name, name);
    strcpy(leaf->data->sirname, sirname);
    leaf->data->avg_grade = avg_grade;

    if (bt->root == NULL){
        bt->root = leaf;

    }
    else add(leaf, bt->root);
}

//Add Node to Binary Tree (Code Side)
void add(node* leaf, node* root){


    if ( strcmp(leaf->data->identity, root->data->identity) == -1 ){

        if (root->left == NULL){
            root->left = leaf;
            leaf->parent = root;
        }
        else{

            add(leaf, root->left);
        }
    }
    else{

        if (root->right == NULL){
            root->right = leaf;
            leaf->parent = root;
        }
        else{

            add(leaf, root->right);
        }
    }

}

//Search in the binary tree
node* bt_search(char *query, node *root){
    if (root == NULL){
        printf("\nStudent Record not found\n\n");
        return NULL;
    }
    if (strcmp(root->data->identity, query) == 0){
        return root;
    }
    else{
        if ( strcmp(query, root->data->identity) == -1 ){
            bt_search(query, root->left);
        }
        else{
            bt_search(query, root->right);
        }
    }
}

//Element deletion
void delete_element(char *query, node *root){
    if (root == NULL){
        printf("Empty Tree\n");
        return;
    }

    node* del = bt_search(query, root);
    node* tmp;

    if (del == NULL) return;

    //The node has two children
    if (del->left!=NULL && del->right!=NULL){
        tmp = findMax(del->left);
        overwrite(del, tmp);

        //Checking if the current node is the left or right parent's child
        if (tmp->parent->left == tmp) tmp->parent->left=NULL;
        else tmp->parent->right = NULL;
        free(tmp->data);
        free(tmp);
    }
    //The node has not any childFILE* fo = fopen( "treedata.txt", "a+" );
    else if (del->left==NULL && del->right==NULL){

        //Checking if the current node is the left or right parent's child
        if (del->parent->left == del) del->parent->left=NULL;
        else del->parent->right = NULL;
        free(del->data);
        free(del);
    }
    //The node has one child
    else{
        if (del->left == NULL){
            tmp = del->right;
            del->right = NULL;
        }
        else if (del->right == NULL){
            tmp = del->left;
            del->left = NULL;
        }
        overwrite(del, tmp);
        del->left = tmp->left;
        del->right = tmp->right;
        free(tmp->data);
        free(tmp);
    }
}

//Find Max Value(ID) in Binary Tree
node *findMax(node* root){
    if (root == NULL){
        return NULL;
    }
    if (root->right == NULL){
        return root;
    }
}

//Ovewrite the node A with the node B
void overwrite(node* A, node* B){
    strcpy(A->data->identity,B->data->identity);
    strcpy(A->data->name, B->data->name);
    strcpy(A->data->sirname, B->data->sirname);
    A->data->avg_grade = B->data->avg_grade;
}

//Full print of the node
void print_node(node* n)
{
    printf("%s -- %s -- %s -- %.2f\n", n->data->identity, n->data->name, n->data->sirname, n->data->avg_grade);
    //printf("%s\n", n->data->identity);
}
//Read text database to in-memory binary tree
void read_db_to_tree(binary_tree* tree){
    FILE *fh, *test;
    fh = fopen("student_database.txt","rw");

    if (fh == NULL){
        printf("NULL");
    }

    size_t line_size = 50;
    char buffer[50];
    char *identity = malloc(9*sizeof(char));
    char *name = malloc(15*sizeof(char));

    char *sirname = malloc(20*sizeof(char));
    float avg_grade;
    int i;
    while(fgets(buffer, line_size, fh)!=NULL){
        identity = strtok(buffer," ");
        printf("%s\n", identity);
        name = strtok(NULL," ");
        sirname = strtok(NULL," ");
        avg_grade = atof(strtok(NULL, " "));
        add_node(identity, name, sirname, avg_grade, tree);
    }

    fclose(fh);
}

//Write back the in-memory binary tree to text database in pre-order traversal
void print_preorder(node* bt )
{
   if( !bt )
    {
        return;
    }
    FILE *fo = fopen("student_database.txt", "a+");

    fprintf(fo, "%s %s %s %.2f\n", bt->data->identity, bt->data->name, bt->data->sirname, bt->data->avg_grade);
    print_preorder(bt->left);
    print_preorder(bt->right);
    fclose(fo);
}

