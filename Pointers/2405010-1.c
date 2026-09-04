#include <stdio.h>
#include <stdlib.h>
//function prototypes
void removeNegatives(int *input,int n,int **output,int *newSize);
int main()
{
    int i,N;
    int *output,newSize;
    scanf("%d",&N);//scans number of elements in input array
    int *input=(int *)malloc(N*sizeof(int));//allocates dynamic memory for input array
    for (i=0;i<N;i++)
        scanf("%d",input+i);//(input+i) refers to the location of the elements of the array
    removeNegatives(input,N,&output,&newSize);//output and newSize is the address of output and newSize pointer
    printf("%d\n",newSize);
    for(i=0;i<newSize;i++)
        printf("%d ",*(output+i));
//free the allocated memory
    free(input);
    free(output);
}
//function for removing negatives
void removeNegatives(int *input,int n,int **output,int *newSize)
{
    int i,count=0;
    for(i=0;i<n;i++)
    {
        if(*(input+i)>=0)//counts the number of non negative integers
        count++;
    }
    *newSize=count;//newSize is a pointer to the address of count
    int j;
    *output=(int *)malloc(count*sizeof(int));//output pointer of the size of output array
    for(i=0;i<n;i++)
    {
        if(*(input+i)>=0)
        {
            *(*output+j)=*(input+i);//pointer to pointer of output array where value will be stored
            j++;
        }
    }
}



