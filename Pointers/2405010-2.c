#include <stdio.h>
#include <stdlib.h>//for malloc
#include <string.h>//for strings
void swap(char **a1,char **a2);
int compare(char *a,char *b);
int main()
{
    int i,j,n;
    scanf("%d",&n);
    char **array=(char **)malloc(n*sizeof(char *));//char** is the pointer to the elements of the string array
    for(i=0;i<n;i++)
    {
        *(array+i)=(char *)malloc(26*(sizeof(char)));//char* is the pointer to the each characters of the string(defined in loop,otherwise all input pointing to single buffer)
        scanf("%s",*(array+i));
    }
    //bubble sort algorithm setup
    for(i=0;i<n-1;i++)
        {
            for(j=0;j<n-i-1;j++)
                {
                    if(compare(*(array+j),*(array+j+1))>0)
                        swap(array+j,array+j+1);
                }
        }
    for(i=0;i<n;i++)
        printf("%s\n",*(array+i));
    for(i=0;i<n;i++)
        free(*(array+i));//clearing string elements
    free(array);//cleaning array
    return 0;
}
//swap function for swapping the array elements if necessary
void swap(char **a1,char **a2)//a1,a2 are the pointer to the pointer of string elements
{
    char *t=*a1;
    *a1= *a2;
    *a2=t;
}
//compare function for array elements
int compare(char *a,char *b)
{
    int i=0;
    while(*(a+i)!='.'&&*(b+i)!='.')//. is the terminating character
        {
            if(*(a+i)>*(b+i))
                return 1;//word 1 comes last
            else if(*(a+i)<*(b+i))
                return -1;//word 1 comes first
                i++;//otherwise it will be in infinite loop
        }
    if((*(a+i)!='.')&&(*(b+i)=='.'))
        return 1;//word 2 is shorter
    else if((*(a+i)=='.')&&(*(b+i)!='.'))
        return -1;//word 1 is shorter
    else return 0;//if equal then swapping no need.
}




