#include <stdio.h>
// void main()
// {
//     int a = 10, b = 20, c;

//     //    asm {
//     //       mov ax,a
//     //       mov bx,b
//     //       add ax,bx
//     //       mov c,ax
//     //    }

//     asm("mov %eax, a\n\t"
//         "mov %ebx, b\n\t"
//         "add %ebx, %eax\n\t"
//         "mov %ebx, c\n\t");

//     printf("c= %d", c);
// }

int main()
{
    int x = 1;

    asm("movl %1, %%eax;"
        "movl %%eax, %0;"
        : "=r"(x)  /* x is output operand and it's related to %0 */
        : "r"(11)  /* 11 is input operand and it's related to %1 */
        : "%eax"); /* %eax is clobbered register */

    int res = 0;
    int a = 20;
    int b = 30;

    asm("addl %1,%0;" : "+r"(b) : "r"(a));
    asm("movl %1,%0;" : "=r"(res) : "r"(b));


    printf("Hello x = %d\nres=%d\n", x, res);
}