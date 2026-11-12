#include <stdlib.h>
#include "LList.h"


LList* crllvoid(){
    LList * newn = (LList*)malloc(sizeof(LList));
    newn->data = NULL;
    newn->next = newn;
    return newn;
}
LList* crll(char d){
    LList * newn = (LList*)malloc(sizeof(LList));
    *(newn->data) = d;
    newn->next = (LList*)malloc(sizeof(LList));
    newn->next->data = NULL;
    newn->next->next = newn;
    return newn;
}
LList* lladd(char d, LList *lhead){
    LList *work=lhead;
    while(work->data != NULL){
        work=work->next;
    }
    *(work->data) = d;
    work->next =(LList*)malloc(sizeof(LList));
    work->next->data = NULL;
    work->next->next = lhead;
    return work;
}
LList* llat(int i, LList *lhead){
    LList *work=lhead;
    for(int j;j<i;j++){
        work=work->next;
    }
    return work;
}
int llsize(LList *lhead){
    LList *work=lhead;
    int count =0;
    while(work->data != NULL){
        work=work->next;
        count++;
    }
    return count;
}
int indexofll(char d, LList *lhead){
    LList *work=lhead;
    int count =0;
    while(work->data != NULL){
        if(*(work->data)==d){
            return count;
        }
        work=work->next;
        count++;
    }
    return -1;
}
bool includell(char d, LList *lhead){
    if(indexofll(d,lhead) != -1){return true;}
    return false;
}
int llremoveAt(int i, LList *lhead){
    LList *work=lhead;
    for(int j;j<i-1;j++){
        work=work->next;
    }
    LList *tofree=work->next;
    work->next = work->next->next;
    free(tofree);
    return 0;
}
LList* copyll(LList *from){
    LList *workf=from;
    LList *to = crll(*(workf->data));
    to->times=workf->times;
    workf=workf->next;
    while(workf->data != NULL){
        lladd(*(workf->data),to)->times=workf->times;
        workf=workf->next;
    }
    return to;
}
int ll2arr(LList *lhead, char (*result)[]){
    LList *work=lhead;
    int i=0;
    while(work->data != NULL){
        (*result)[i]=*(work->data);
        work=work->next; i++;
    }
}
LList* mintimes(LList *lhead){
    LList *min =lhead;
    for(LList *el=lhead;el->data != NULL;el=el->next){
        if(el->times < min->times){min=el;}
    }
    return min;
}
LList* maxtimes(LList *lhead){
    LList *max =lhead;
    for(LList *el=lhead;el->data != NULL;el=el->next){
        if(el->times > max->times){max=el;}
    }
    return max;
}