/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    v.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (v[elem] < 0) {
    return elem;
  } else {
    return find(v[elem]);
  }
}

void DisjointSets::setunion(int a, int b) {
  int f1 = find(a);
  int f2 = find(b);
  int s1 = size(f1);
  int s2 = size(f2);
  int newSize = s1 + s2;
  if (s1 < s2) {
    v[f1] = f2;
    v[f2] = newSize*-1;
  } else {
    v[f2] = f1;
    v[f1] = newSize*-1;
  }
}

int DisjointSets::size(int elem) {
  int retval = find(elem);
  return v[retval]*-1;
}
