#include "LList.h"

#ifndef LLISTF_H
#define LLISTF_H

LList* crllvoid();
LList* crll(char d);
LList* lladd(char d, LList *lhead);
LList* llat(int i, LList *lhead);
int llsize(LList *lhead);
int indexofll(char d, LList *lhead);
bool includell(char d, LList *lhead);
LList* llremoveAt(int i, LList *lhead);
LList* copyll(LList *from);
int ll2arr(LList *lhead, char (*result)[]);
LList* mintimes(LList *lhead);
LList* maxtimes(LList *lhead);
LList* balancellmax2minCopy(LList *lhead);
#endif