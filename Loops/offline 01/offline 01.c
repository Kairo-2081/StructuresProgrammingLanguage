#include <stdio.h>
int main()
{
    int i,j,n,numbers,rows,total_energy=0;
    scanf("%d",&rows);/*input of the number of rows we want*/
      for (i=1;i<=rows;i++)
      {
        scanf("%d",&n);/*input of the number of numbers in rows we want*/
        int sum=0,alternate_sum=0,odd_sum=0,even_sum=0;
        int sum1=0,sum2=0;
        int prime=1;
        int reverse=0;
        int remainder=0;
        int p;
        int energy_level=0;
        int palindrome_active=0,prime_active=0,harmonic=0,balanced=0;/*Introduced for easier calculation*/
        for (j=1;j<=n;j++)
            {
                scanf("%d",&numbers);/*input of the numbers in each row we want*/
                sum=sum+numbers;/*determines the sum*/
                if(j%2==1)
                {
                   sum1=sum1+numbers;
                }
                if(j%2==0)
                {
                    sum2=sum2-numbers;
                }
                alternate_sum=sum1+sum2;/*determines the alternate sum*/
                if(j%2==0)
                {
                    even_sum=even_sum+numbers;/*determines the even sum*/
                }
                if(j%2==1)
                {
                    odd_sum=odd_sum+numbers;/*determines the odd sum*/
                }
           }
            /*All sums are determined.Now we need to check palindromic,prime,balanced,harmonic*/

            //prime check

            for(int k = 1 ; k < sum ; k++)
            {
                if(sum%k==0 && k!=1)/*logic find*/
                    {
                    prime = 0;
                    break;
                    }
            }
            if(prime==1)
                prime_active=1;

            //palindromic check

            p=sum;
            while(p!=0)
            {
                remainder=p%10;
                reverse=reverse*10+remainder;
                p=p/10;
            }
            if (sum==reverse)
                palindrome_active=1;

            //harmonic check

            if (alternate_sum%7==0)
                harmonic=1;

            //balanced check

            if (odd_sum==even_sum)
                balanced=1;

            //calculation of energy level

            if ( prime_active==1)
            {
                energy_level=energy_level+5;
            }
            if ( palindrome_active==1)
            {
                energy_level=energy_level+3;
            }
            if ( harmonic==1)
            {
                energy_level=energy_level+4;
            }
            if ( balanced==1)
            {
                energy_level=energy_level+2;
            }

            //calculation of status

            int count=prime_active+palindrome_active+harmonic+balanced;
            printf("Row %d: ",i);
            if (count==4)
                printf("ULTRA - Energy Level %d\n",energy_level);
            else if (count==3)
                printf("HIGH - Energy level %d\n",energy_level);
            else if (count==2)
                printf("MEDIUM - Energy level %d\n",energy_level);
            else if (count==1)
                printf("LOW - Energy level %d\n",energy_level);
            else if (count==0)
                printf("INACTIVE - Energy level %d\n",energy_level);

                //total energy calculation
                total_energy=total_energy+energy_level;

      }
       printf("Total Energy: %d",total_energy);
       return 0;
}
