#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t;
    scanf("%d",&t);//test cases
    for(int r=1; r<=t; r++)
    {


        //printf("Enter size of matrix\n");
        int n;
        scanf("%d",&n);
        int A[n][n];

        //printf("Enter values in the Array\n");


        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                scanf("%d",&A[i][j]);

            }
        }
        /*

        for(int i=0; i<n; i++)
        {
            printf("\n");
            for(int j=0; j<n; j++)
            {
               if(A[i][j]>trace)
               {
                   trace=A[i][j];
               }

            }
        }
        //now  trace has the biggest element.
        */
        int max=0;
        int trace=A[0][0];//initial max value
        int k=0;// temp trace sum
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                k=A[i][j];
                if(k>trace)
                {
                    trace=k;
                }
                max=(i>=j)?i:j;
                max=n-max-1;
                for(int m=1; m<=max; m++)
                {
                    k=k+A[i+m][j+m];
                    if(k>trace)
                        trace=k;
                }
            }
        }

        printf("%d",trace);
    }
    return 0;

}
