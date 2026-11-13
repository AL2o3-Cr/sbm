#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llistf.h"

bool force = false;
FILE * Read = NULL;
FILE * Write = NULL;
int a;
const char help[]="*add*";

enum Choice{
    isencode,
    isdecode
};


typedef struct NodeTree{
    char data;
    bool isvoidroot;
    struct NodeTree * left;
    struct NodeTree * right;
} BinTree;

BinTree* crtree(char d){
    BinTree* newn = (BinTree*)malloc(sizeof(BinTree));
    newn->data=d;
    newn->isvoidroot=false;
    newn->left=newn->right=NULL;
    return newn;
}
BinTree* crtreeVoidroot(){
    BinTree *newn = (BinTree*)malloc(sizeof(BinTree));
    newn->isvoidroot=true;
    newn->left=newn->right=NULL;
    return newn;
}
BinTree* mergetreeWithVRoot(BinTree *left,BinTree *right){
    BinTree *newn = crtreeVoidroot();
    newn->left=left; newn->right=right;
    return newn;
}
int countvrootinarr(int size,BinTree *(ptrs)[]){
    int j=0;
    for(int i=0;i<size;i++){
        if(ptrs[i]->isvoidroot){
            j++;
        }
    }
    return j;
}
int excludefromArrByisvoidroot(BinTree *(**arr)[],int size){
    BinTree *(*newarr)[countvrootinarr(size,(**arr))]; (*newarr)[0]=(**arr)[0];
    int j=1;
    for(int i=1;i<size;i++){
        if((**arr)[i]->isvoidroot){
            (*newarr)[j++] = (**arr)[i];
        }
    }
    (*arr)=newarr;
    return j;
}

enum Choice arghandler(int argc, char const *argv[]){
    bool next=false;
    int encordec=-1;
    for (size_t i = 0; i < argc; i++)
    {
        if(next){
            next=false;
            continue;
        }
        if(strcmp(argv[i],"--help")==0){
            printf(help);
            break;
        }
        else if(strcmp(argv[i],"--force")==0 && force==false){
            force=true;
        }
        else if (strcmp(argv[i],"--encode") && encordec != isdecode==0){
            next=true;
            Read = fopen(argv[i+1],"rb");
            encordec=isencode;
        }
        else if (strcmp(argv[i],"--decode")==0 && encordec != isencode){
            next=true;
            Read = fopen(argv[i+1],"rb");
            encordec=isdecode;
        }
        else if (strcmp(argv[i],"--save")==0){
            next=true;
            Write = fopen(argv[i+1],"wb");
        }
    }
    if(Read==NULL || Write==NULL){perror("file not exist");}
    return encordec;
}


BinTree* balancell2tree(LList *ll){
    LList *balanced = balancellmax2minCopy(ll);
    BinTree *_nodes[llsize(balanced)];
    BinTree *(*nodes)[llsize(balanced)] = _nodes;
    int i=0;
    for(LList *el=balanced;el->isnend;el=el->next){
        (*nodes)[i++]=crtree(el->data);
    }
    while(true){
        int size=i--;
        int j=i;
        while (i>1){
            BinTree *left=nodes[i--];
            BinTree *right=nodes[i--];
            BinTree *merged = mergetreeWithVRoot(left,right);
            (*nodes)[j--]=merged;
        }
        int newsize=countvrootinarr(size,*nodes);
        excludefromArrByisvoidroot(&nodes,size);
        if(newsize==1){break;}
        i=newsize+1;
    }
    BinTree *fin=mergetreeWithVRoot((*nodes)[0],(*nodes)[1]);
    return fin;
}

void decode(){
    return;
}

void encode(){
    LList *uniq = crllvoid();
    int i = 0;
    char work;
    while (fseek(Read,i,SEEK_SET) == 0){
        fread(&work,sizeof(work),1,Read);
        if(! includell(work,uniq)){lladd(work,uniq);}
        llat(indexofll(work,uniq),uniq)->times++;
        i++;
    }
    /**/
    BinTree *ntree = balancell2tree(uniq);
}

int main(int argc, char const *argv[])
{
    switch(arghandler(argc,argv)){
        case isencode:
            encode();
            break;
        case isdecode:
            decode();
            break;
        default:
            break;
    }

    return 0;
}






