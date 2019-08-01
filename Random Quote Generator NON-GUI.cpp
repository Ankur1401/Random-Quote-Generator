#include <stdio.h>
#include <stdlib.h> // For exit() function
#include<time.h>
char b[500];
void quote(int choice)
{   char a;
    int i=0,n,j=0;
    FILE *fptr;
    srand(time(NULL));
    switch(choice)
    {
        case 1: fptr = fopen(".\\data\\books.txt", "r");
                n=(rand()%2932)+1;
                break;
        case 2: fptr = fopen(".\\data\\inspiration.txt", "r");
                n=(rand()%2973)+1;
                break;
        case 3: fptr = fopen(".\\data\\knowledge.txt", "r");
                n=(rand()%2965)+1;
                break;
        case 4: fptr = fopen(".\\data\\life.txt", "r");
                n=(rand()%2963)+1;
                break;
        case 5: fptr = fopen(".\\data\\love.txt", "r");
                n=(rand()%2972)+1;
                break;
        case 6: fptr = fopen(".\\data\\relationships.txt", "r");
                n=(rand()%2950)+1;
                break;
        case 7: fptr = fopen(".\\data\\science.txt", "r");
                n=(rand()%2911)+1;
                break;
        case 8: fptr = fopen(".\\data\\success.txt", "r");
                n=(rand()%2973)+1;
                break;
        case 9: quote((rand()%8)+1);
                return ;
        default:    printf("\nInvalid Input.\n");
                    break;
    }
    while(1)
    {   a=(char)fgetc(fptr);
        if(i==n-1)
        {   b[j]=a;
            ++j;
        }
        if (a=='\n')
            ++i;
        if(i==n)
        {
            b[j]='\0';
            break;
        }

    }
    fclose(fptr);
}
int main()
{   int n;

    scanf("%d",&n);
    quote(n);
    printf("%s",b);

    return 0;
}
