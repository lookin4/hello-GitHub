#include<stdio.h>
#include<stdlib.h>


typedef struct _Tree Tree;

struct _Tree{
    int n;
    Tree *left;
    Tree *right;
};

Tree *Tree_new(int n){
    Tree *p = malloc(sizeof(Tree));
    p->n = n;
    p->left = p->right = NULL;

    return p;
}

static void indent(int level){
    int i;
    for(i = 0;i<level;i++){
        printf("  ");
    }
}

static void Tree_print_wIndent(Tree *p,int level){
    indent(level);printf("n = %d\n",p->n);
    indent(level);printf("left = %p\n",p->left);
    if( p->left){
        Tree_print_wIndent(p->left,level + 1);
    }
    indent(level);printf("right = %p\n",p->right);
    if( p->right){
        Tree_print_wIndent(p->right,level + 1);
    }
}

void Tree_print(Tree *p){
    Tree_print_wIndent(p,0);
}

int main()
{
    Tree *root = Tree_new(0);
    Tree *left = Tree_new(1);
    Tree *right = Tree_new(-1);
    root->left = left;
    root->right = right;
    
    Tree_print(root);

    return 0;
}
