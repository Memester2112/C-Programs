#include <stdio.h>
#include <stdlib.h>
#define MAX(x,y) x>y?x:y

int* heapify(int* a,int n)
{
    int rc,lc,mc;//max child index
    int temp,z;
    for(int i=n; i>=1; i--)
    {
        z=i;
        lc=2*z;
        rc=2*z+1;
        while(lc<=n)//implies at least left child exists
        {

            if( (rc<=n) && (a[rc]>a[lc]) )//rc exists and is greater than lc
                mc=rc;
            else
                mc=lc;
            if(a[z]<a[mc])
            {
                temp=a[z];//swap
                a[z]=a[mc];
                a[mc]=temp;
                z=mc;//update current node going down
                lc=2*z; rc=lc+1;
            }
            else
                break;
        }
    }
    return (a);

}
int* insertheap(int* b,int elem)
{
    int temp;
    int c=sizeof(b)-1;//current element index number
    int p=c/2;//parent index
    b[c]=elem;//insert elem at the end of heap first
    while(p>=1)//move up if necessary
    {
        if(b[p]<b[c])
        {
            temp=b[p];
            b[p]=b[c];
            b[c]=temp;

            c=p;
            p=c/2;
        }
        else
            break;
    }
    printf("INSERTED\n");
    return(b);

}

int* makeheap()
{
    int elem;
    int n=2;
    printf("\nEnter 1st element\n");
    int* b=(int *)malloc(n*sizeof(int));
    scanf("%d",&b[1]);//not using b[0]
    printf("\nEnter -1 to exit, otherwise enter element\n");
    scanf("%d",&elem);
    while(elem!=-1)
    {
        n++;
        b=realloc(b,n*sizeof(int));
        b[n-1]=elem;
        for(int i=1;i<n;i++)
            printf("%d ",b[i]);
        printf("\n");
        b=insertheap(b,elem);
        scanf("%d",&elem);

    }
    printf("\nsize of b = %d\n",n);
    return(b);
}

int main()
{
    /*
    int n;

    printf("Enter value of n\n");
    scanf("%d",&n);
    printf("Enter values in array  :\n");
    int a[n+1];//not gonna use index 0
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    int* z=(int* )malloc((n+1)*sizeof(int));
    z=heapify(a,n);
    printf("Heapified :\n");
    for(int i=1; i<=n; i++)
        printf("%d ",a[i]);
    /*
    Now to dynamically allocate and increase array size as the input comes
    along. We have makeheap,deleteheap,insert
    */
    //testing calloc and malloc
    int* b;
    b=makeheap();
    int n=sizeof(b);
    n=n-1;
    printf("Heapified : %d\n",n);
    for(int i=1; i<=n; i++)
        printf("%d ",b[i]);

    return 0;
}
