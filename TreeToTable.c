#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Tree* Ptr;
typedef struct Tree {
    int data;
    Ptr left;
    Ptr right;
} Tree; /* This stucture called "Enregistrement", is realy important to me
            Because I hate the ..*.. uses!
*/

int Count_nodes(Ptr, int*); //For counting and return the size.
void Convert_to_array(Ptr, int* , int*);// The main foncution.
void Disp_Tr(Ptr, int); // For visualize the tree.
void create_tree(Ptr*, int); // For any addition of values!
//void create_tree(Ptr*);
Ptr new_node(int); // craet new space for a node and storing a value on it!

int main() {
    Ptr Our_Tr = NULL;
    int Size, Data;
    printf("Pls insert the size of tree.. ");
    scanf("%d",&Size);
    for (int i = 1; i <= Size; i++) {
        printf("Pls insert the valeu nbr %d: ",i);
        scanf("%d",&Data);
        create_tree(&Our_Tr, Data);
        sleep(1);
        system("cls");
    } 
 /* Ptr root = NULL;
    create_tree(&root); */

// Print the tree as a visual tree!
    printf("\n** Tree representation before conversion..\n");
    Disp_Tr(Our_Tr, 0);
    //Disp_Tr(root, 0);
    printf("\n");

// Count elements NEMBER in the tree
    int treeSize = 0;
    Count_nodes(Our_Tr, &treeSize);
    //Count_nodes(root, &treeSize);

// Create a table sufficient to store tree values
    int* Araay = (int*)malloc(treeSize*sizeof(int));
    
// Tree to table    
    int index = 0;
    Convert_to_array(Our_Tr, Araay, &index);
    //Convert_to_array(root, Araay, &index);

// Print our new table
    printf("\n** Table after conversion:");
    for (int i = 0; i < treeSize;i++){
        printf("|%i", Araay[i]);
    }
    printf("|\n\n");

    return 0;
}

Ptr new_node( int data){
    Ptr p=malloc(sizeof(Tree) );
    p->data= data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void create_tree(Ptr* root, int data) {
    if (*root == NULL) {
        *root = new_node(data);
        return;
    }
    if ((*root)->data >= data) {
        create_tree(&(*root)->left, data);
    } else {
        create_tree(&(*root)->right, data);
    }
}

/* void create_tree(Ptr *root){
    *root = new_node(59);
    (*root)->left = new_node(16);
    (*root)->right = new_node(89);
    (*root)->left->left = new_node(11);
    (*root)->left->right = new_node(30);
    (*root)->right->left = new_node(77);
    (*root)->right->right = new_node(90);
    (*root)->left->left->left= new_node(10);
    (*root)->left->left->right = new_node(12);
    (*root)->left->right->left = new_node(22);
    (*root)->left->right->right = new_node(44);
} */

void Disp_Tr (Ptr root,int space) {
    if (root == NULL) return;
    space += 6;
    Disp_Tr(root->right, space);
    
    printf("\n");
    for (int i = 6; i < space; i++) printf(" ");
    if (root->left!= NULL || root->right != NULL) {
        printf("|-- %d|", root->data);
    }else printf("|-- %d *", root->data);
    //printf("%d", root->data);
    
    Disp_Tr(root->left, space);
}

void Convert_to_array (Ptr root, int* array,int* index) {
    if (root != NULL){
        Convert_to_array(root->left, array, index);
        array[*index] = root->data;
        (*index)++; // (*i)++ --> the idea comes from the "TP" lesson!
        Convert_to_array(root->right, array, index);
    }
}

int Count_nodes(Ptr root, int* treeSize){
    if (root != NULL) {
        Count_nodes(root->left, treeSize);
        (*treeSize)++;
        Count_nodes(root->right, treeSize);
    }
}