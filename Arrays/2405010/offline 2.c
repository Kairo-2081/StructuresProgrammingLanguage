#include <stdio.h>
#include <math.h>//for sqrt
#include <string.h>//for qsort
#include "utils.c"//for the given codes in the file
#include <stdlib.h>//for size of function

#define MAX_SIZE 1000000
#define MAX_BINS 1000
#define MAX_STARS 50

/*declare all functions*/

void help();
double minimum(double*array,int size);
double maximum(double*array,int size);
double Mean(double*array,int size);
double std(double*array,int size);
double median(double*array,int size);



/*start the code*/

double array [MAX_SIZE];
int size;

int main()
{
    /*declare all commands*/

    char command[10];
    char distribution[10];
    double min,max,mean,stddev;
    int initialized=0;

    help();
    while(1)
    {
        unsigned int seed;
        printf("\nEnter Command:");
        scanf("%s",command);
        if(strcmp(command,"set")==0)
        {
            initialized++;
            printf("Enter number of elements (<= 100000):");
            scanf("%d",&size);
            if(size<=1000000)
            {
                printf("Enter Seed:");
                scanf("%u",&seed);
                printf("Distribution? (uniform/gaussian):");
                scanf("%s",distribution);
                if(strcmp(distribution,"uniform")==0)
                {
                    printf("Enter min and max:");
                    scanf("%lf%lf",&min,&max);
                    populate_array_uniform(array,size,min,max,seed);
                    printf("Array initialized with uniform distribution");
                }
                else if(strcmp(distribution,"gaussian")==0)
                {
                    printf("Enter mean and stddev:");
                    scanf("%lf%lf",&mean,&stddev);
                    populate_array_gaussian(array,size,mean,stddev,seed);
                    printf("Array initialized with gaussian distribution");

                }
            else
                {
                    printf("Invalid distribution");
                    continue;
                }
            }
        else
            {
                printf("Invalid number of elements.Please enter number of elements (<= 100000)");
                continue;
            }
        }
        //all other commands cases
        else if(strcmp(command,"min")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                        double k = minimum(array,size);
                        printf("Min     :   %.4lf",k);
                }
        else if(strcmp(command,"max")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                        double k1 = maximum(array,size);
                        printf("Max     :   %.4lf",k1);
                }
        else if(strcmp(command,"mean")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                        double k3 = Mean(array,size);
                        printf("Mean     :   %.4lf",k3);
                }
        else if(strcmp(command,"stddev")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                        double k4 = std(array,size);
                        printf("Std dev     :   %.4lf",k4);
                }
        else if(strcmp(command,"summary")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                        double k = minimum(array,size);
                        double k1 = maximum(array,size);
                        double k3 = Mean(array,size);
                        double k4 = std(array,size);
                        printf("Min     :   %.4lf\n",k);
                        printf("Max     :   %.4lf\n",k1);
                        printf("Mean    :   %.4lf\n",k3);
                        printf("Std dev :   %.4lf\n",k4);
                }
        else if(strcmp(command,"hist")==0)
                {
                    if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
/*histogram function:for histogram,at first we will take bin input and then check cases.
Then we will check the bin width.
then we will count bin and then assume max bin.
We have max stars.So we can take proportion to print stars so that the graph is not dismantled.
then we will take maxima and minima each cases and print stars*/

/*Bin count:*/

    int bins;
    int i,j;
    printf("Enter the number of bins:");
    scanf("%d",&bins);
    if ((bins<=0)||(bins>MAX_BINS))
        {
            printf("Invalid number of bins.Must be between 1 and 1000\n");

        }
            //bcnt means bin count
            int bcnt[MAX_BINS]={0};
            double k = minimum(array,size);
            double k1 = maximum(array,size);
            double bin_width=(k1-k)/bins;//return issue korle eine dibo
            for(i=0;i<size;i++)
                {
                    //bin counts
                    int bin_index=(int)((array[i]-k)/bin_width);
                    if(bin_index>=bins)
                        bin_index=bins-1;//so that index doesnt cross bounds.can occur in case of max and nearby ones only.Then counted in the last bin.
                    bcnt[bin_index]++;
                }
            int mcnt=0;

            for(i=0;i<bins;i++)
                {
                    if(mcnt<bcnt[i])
                    {
                        mcnt=bcnt[i];
                    }
                }
                for(i=0;i<bins;i++)
                 {
                     int stars=(bcnt[i]*MAX_STARS)/(mcnt!=0?mcnt:1);
                     double low=k+i*bin_width;
                     double high=k+(i+1)*bin_width;
                     printf("[%.2lf]  -  [%.2lf]:",low,high);
                     for(j=0;j<stars;j++)
                        printf("*");
                     printf("\n");
                 }
            }
        else if(strcmp(command,"median")==0)
        {
             if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
                    double k5=median(array,size);
                    printf("Median  :     %.4lf\n",k5);



        }
        else if(strcmp(command,"exit")==0)
        {
             if(initialized==0)
                    {
                        printf("Array not initialized. Use 'set' command first\n");
                        continue;
                    }
            break;
        }

        else if(strcmp(command,"help")==0)
                {
                    help();
                }
        else
        {
            printf("Unknown Command.Type 'help' for list of commands\n");
            //FOR ARRAY NOT INOITIALIZED INTRODUCE A VARIABLE WHICH IS 1
        }
   }
}

//all functions

void help()
{
    printf("Commands:\n");
    printf(" set \t-Set array size, seed, and distribution(uniform or gaussian)\n");
    printf(" min \t-Print minimum value\n");
    printf(" max \t-Print maximum value\n");
    printf(" mean \t-Print mean value\n");
    printf(" stddev\t-Print standard deviation\n");
    printf(" hist \t-Plot histogram\n");
    printf(" summary-Print min, max, mean, stddev \n");
    printf(" median\t-finds the median\n");
    printf(" help \t-Show this help message\n");
    printf(" exit \t-Exit the program\n");
}

//counts minimum

double minimum(double*array,int size)
{
    int i;
    double mini=array[0];
    for (i=1;i<size;i++)
    {
        if(mini>array[i])
        mini=array[i];

    }
    return mini;
}

//counts maximum

double maximum(double*array,int size)
{
    int i;
    double maxi=array[0];
    for (i=1;i<size;i++)
    {
        if(maxi<array[i])
        maxi=array[i];

    }
    return maxi;
}

//counts average

double Mean(double*array,int size)
{
    int i;
    double sum=array[0];
    for (i=1;i<size;i++)
        {
            sum=sum+array[i];
        }
     double meani=sum/size;
        return meani;
}

//counts std Dev

double std(double*array,int size)
{
    int i;
        double sum=array[0];
    for (i=1;i<size;i++)
        {
            sum=sum+array[i];
        }
     double meani=sum/size;
     double p=0;
     double t;
     for (i=0;i<size;i++)
        {
            t=(array[i]-meani)*(array[i]-meani);
            p=p+t;
        }
        p=p/size;
        double std_Dev=sqrt(p);
        return std_Dev;
}

//counts median

double median(double*array,int size)
{
    int i;
    double medin;
    int compare(const void *a, const void *b)//compare function between two strings a and b
    {
    double diff = *(double*)a - *(double*)b;//two void pointers converted into doubles
    if (diff < 0)
          return -1;
    if (diff > 0)
          return 1;
    return 0;
    }
    qsort(array, size, sizeof(double), compare);//basic library function of qsort
    if (size % 2 == 0)
    {
        medin = (array[size/2 - 1] + array[size/2]) / 2.0;
    }
    else
    {
        medin = array[size/2];
    }
    return medin;
}
























