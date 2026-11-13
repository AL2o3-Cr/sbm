#include <stdlib.h>
#include "LList.h"
#include "llistf.h"


LList* crllvoid(){
    LList * newn = (LList*)malloc(sizeof(LList));
    newn->isnend=false;
    newn->next = newn;
    return newn;
}
LList* crll(char d){
    LList * newn = (LList*)malloc(sizeof(LList));
    newn->isnend=true;
    newn->data = d;
    newn->next=crllvoid();
    newn->next->next=newn;
    return newn;
}
LList* lladd(char d, LList *lhead){
    LList *work=lhead;
    while(work->isnend){
        work=work->next;
    }
    work->data = d;
    work->isnend=true;
    work->next=crllvoid();
    work->next->next=lhead;
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
    while(work->isnend){
        work=work->next;
        count++;
    }
    return count;
}
int indexofll(char d, LList *lhead){
    LList *work=lhead;
    int count =0;
    while(work->isnend){
        if(work->data==d){
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
LList* llremoveAt(int i, LList *lhead){
    if (i<0){
        i=(-i)%llsize(lhead);
    }
    LList *out=lhead;
    LList *work=lhead;
    if(i==0){
        out=work->next;
        for(LList *el=work;el->isnend;el=el->next){
            work=el;
        }
        work=work->next;
    }
    else if(i>1){
        if(i>llsize(lhead)){i=i%llsize(lhead);}
        for(int j=0;j<i-1;j++){
            work=work->next;
        }
    }
    LList *tofree=work->next;
    work->next = work->next->next;
    free(tofree);
    return out;
}
LList* copyll(LList *from){
    LList *workf=from;
    LList *to = crll(workf->data);
    to->times=workf->times;
    workf=workf->next;
    while(workf->isnend){
        lladd(workf->data,to)->times=workf->times;
        workf=workf->next;
    }
    return to;
}
int ll2arr(LList *lhead, char (*result)[]){
    LList *work=lhead;
    int i=0;
    while(work->isnend){
        (*result)[i]=work->data;
        work=work->next; i++;
    }
}
LList* mintimes(LList *lhead){
    LList *min =lhead;
    for(LList *el=lhead;el->isnend;el=el->next){
        if(el->times < min->times){min=el;}
    }
    return min;
}
LList* maxtimes(LList *lhead){
    LList *max =lhead;
    for(LList *el=lhead;el->isnend;el=el->next){
        if(el->times > max->times){max=el;}
    }
    return max;
}
LList* balancellmax2minCopy(LList *lhead){
    LList *copyin =copyll(lhead);
    LList *llout =crllvoid();
    LList *max;
    for(int i=0;i<llsize(lhead);i++){
        max=maxtimes(copyin);
        lladd(max->data,llout)->times=max->times;
        copyin =llremoveAt(indexofll(max->data,copyin),copyin);
    }
    return llout;
}
LList* llreverse(LList *lhead){
    int size = llsize(lhead);
    LList *ptrs[size];
    LList *end = ptrs[size-1]->next;
    for (int i = 0; i < size; i++){
        ptrs[i] = llat(i,lhead);
    }
    for(int i=size-1;i>=0;i--){
        ptrs[i]->next->next=ptrs[i];
    }
    ptrs[0]->next = end;
    return ptrs[size-1];
}