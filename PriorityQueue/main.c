#include <stdio.h>
#include <stdlib.h>
//minheap

int* heapify(int* a,int c)
{
    int size=a[0];//last index
    int l,smallest,r,temp;
    l=2*c;
    r=c*2+1;

    while(l<=size)
    {

        if(a[c]>a[l])
        {
            smallest=l;
        }

        if(r<=size)//right child also exists
        {
            if(a[smallest]>a[r])
            {
                smallest=r;
            }

        }
        if(smallest!=c)//need to swap
        {
            temp=a[smallest];
            a[smallest]=a[c];
            a[c]=temp;
            c=smallest;
            l=2*c;
            r=l+1;
        }
        else
        {
            break;
        }
    }
    return(a);
}

int deletemin(int* a)
{
    int x=a[1];
    int size=a[0];
    a[0]=a[0]-1;//reduce size
    a[1]=a[size];
    a[size]=0;
    a=heapify(a,1);
    return(x);
}
int* insertq(int* a,int n)
{

    a[0]=a[0]+1;//increase size
    a=(int*)realloc(a,(a[0]+1)*sizeof(int));
    a[a[0]]=n;
    //inserted at the last position
    //now correct for position
    //switch with parent as long as necessary
    int c=a[0];//current node
    int p=c/2;//parent loc
    int temp;
    while(p>0)
    {
        if(a[p]>a[c])
        {
            temp=a[c];
            a[c]=a[p];
            a[p]=temp;
            c=p;
            p=c/2;
        }
        else
        {
            break;
        }
    }

    return(a);
}

int main()
{
    printf("Insert elements\nEnter -1 to stop\n");
    int* a=(int*)malloc(1*sizeof(int));
    a[0]=0;//a[0] will store the size of the array
    int n;
    scanf("%d",&n);
    while(n!=-1)
    {
        a=insertq(a,n);



        scanf("%d",&n);

    }
    printf("The array is :\n");

    for(int i=1; i<=a[0]; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\nSorted:\n");
    int size=a[0];
    for(int i=1;i<=size;i++)
    {
        int z=deletemin(a);
        printf("%d ",z);
    }
    return 0;
}
