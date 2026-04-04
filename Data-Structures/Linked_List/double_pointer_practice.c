#include <stdio.h>

void change(int **pptr, int *b) {// 주소를 받겠다
    *pptr = b; 

int main() {
    int a = 10;
    int b = 99;
    int *p = &a;
   
    change(&p, &b); //주소를 넘겨줄게

    printf("%d\n", *p);

    // change 함수 정의하고
    // change 호출하고
    // printf로 *p 출력해봐
}