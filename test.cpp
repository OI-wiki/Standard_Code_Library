/**
 * @name TEMPLATE.cpp
 * @subject Segment Tree
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a segment tree implemented with pointers.(kidding)
 */

// I used DocBlockr to make this comment!
// Simply type '/**' in the first line
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)

char buf[100033], tee[1033];
int id = 0;
int main() {
  system("bash generate_cpp_list.sh > file.list");
  // return 0;
  freopen("file.list", "r", stdin);
  gets(buf);
  // printf("%d\n",id);
  // f(i,0,id)puts(buf[i]);
  // return 0;
  // freopen("test_log.txt","w",stdout);
  system(buf);
  freopen("files.log", "r", stdin);
  while (gets(tee)) {
    if (strstr(tee, "Total")) {
      if (strcmp(tee, "Total errors found: 0")) {
        fprintf(stderr, "%s\n", tee);
        return 1;
      } else {
        return 0;
      }
    }
    // puts(tee);
  }
  return 0;
}
