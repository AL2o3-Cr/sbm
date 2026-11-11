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
    struct NodeTree * left;
    struct NodeTree * right;
} BinTreeNode;

BinTreeNode* crn(char d){
    BinTreeNode* newn = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    newn->data=d;
    newn->left=newn->right=NULL;
    return newn;
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
    LList *balanced = llbalance(uniq);
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






