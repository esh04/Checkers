#ifndef __STACK_H
#define __STACK_H

#include<stdio.h>


typedef struct StackContents StackContents;

struct StackContents{
    coordinates start;
    coordinates final;
    char turn;
};

void push(StackContents s[10000], StackContents c);
void pop(StackContents s[10000]);

#endif


// int main()
// {
//     top=-1;
//     printf("\n Enter the size of STACK[MAX=100]:");
//     scanf("%d",&n);
//     printf("\n\t STACK OPERATIONS USING ARRAY");
//     printf("\n\t--------------------------------");
//     printf("\n\t 1.PUSH\n\t 2.POP\n\t 3.DISPLAY\n\t 4.EXIT");
//     do
//     {
//         printf("\n Enter the Choice:");
//         scanf("%d",&choice);
//         switch(choice)
//         {
//             case 1:
//             {
//                 push();
//                 break;
//             }
//             case 2:
//             {
//                 pop();
//                 break;
//             }
//             case 3:
//             {
//                 display();
//                 break;
//             }
//             case 4:
//             {
//                 printf("\n\t EXIT POINT ");
//                 break;
//             }
//             default:
//             {
//                 printf ("\n\t Please Enter a Valid Choice(1/2/3/4)");
//             }
                
//         }
//     }
//     while(choice!=4);
//     return 0;
// }

