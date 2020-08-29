#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int n;
    int* a;
} node;

void bsort(int* a,int n)//sort in descending order
{
    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=i; j<(n-1); j++)
        {
            if(a[j]<a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

node* initheap(int nmax,int p)
{
    int m=(nmax+p-1)/p;//number of nodes needed.
    node* A =(node*)malloc((m+1)*sizeof(int));//array of nodes
    for(int i=0; i<=m; i++) //not using the 0th node,0th node used to store m
    {
        A[i].a=(int *)malloc(p*sizeof(int));
        A[i].n=0;
    }
    for(int i=1; i<=m; i++)
    {
        for(int j=0; j<p; j++)
        {
            A[i].a[j]=0;

        }

    }

    A[0].n=m;//keeping m
    return(A);
}
////////////////////////////////////////////////////////////////////////////////////

void prnheap(node* H,int p)
{
    int m=H[0].n;

    for(int i=1; i<=m; i++) //nodes
    {
        for(int j=0; j<p; j++) //for array in each node
        {
            if(H[i].a[j]!=0)
                printf("%3d ",H[i].a[j]);
            else
                printf("  - ");
        }
        printf("\n");
    }

}
////////////////////////////////////////////////////////////////////////////////////

void insertheap(node* H,int p,int x)
{
    int loc;//first node which is empty:
    int m=H[0].n;
    int max1,min1;
    for(int i=1; i<=m; i++)
    {
        if(H[i].n!=p)
        {
            loc=i;
            break;
        }
    }//identified node with free space
    int q=H[loc].n;
    H[loc].a[q]=x;
    q++;
    H[loc].n=q;
    //loc is the current node
    //parent node pn
    int pn=loc/2;
    while(pn>0)//if loc != 1
    {

        //find the minimum of parent node
        min1=H[pn].a[0];
        for(int i=1; i<p; i++)
        {
            if(H[pn].a[i]<min1)
                min1=H[pn].a[i];
        }
        max1=H[loc].a[0];
        q=H[loc].n;
        for(int i=1; i<q; i++)
        {
            if(H[loc].a[i]>max1)
                max1=H[loc].a[i];
        }
        int size1=q+p;//total number of elements in the combined array
        int* b=(int *)malloc(size1*sizeof(int));


        if(max1>min1)
        {
            //forming combined array
            for(int i=0; i<p; i++)
                b[i]=H[pn].a[i];
            for(int i=0; i<q; i++)
                b[i+p]=H[loc].a[i];
            //formed
            //sorting

            bsort(b,size1);
            //repopulating the nodes
            for(int i=0; i<p; i++)
            {
                H[pn].a[i]=b[i];
            }
            for(int i=0; i<q; i++)
            {
                H[loc].a[i]=b[i+p];
            }
            //redistribution done
            free(b);
            //now to update the values of current node and pn
            loc=pn;
            pn=loc/2;
        }
        else
            break;

    }
}
/////////////////////////////////////////////////////////////////

void heapify(node* H,int i)
{
    int m=H[0].n;
    int cmax,lmax,rmax,wc;//wc-which child cmax-max of the 2 children
    int lc=i*2;
    int rc=lc+1;
    int qmin=H[i].a[0];//i is the current node
    for(int j=1; j<H[i].n; j++)
    {
        if(H[i].a[j]<qmin)
            qmin=H[i].a[j];
    }
    //qmin has the min of the current node

    int lastnode;//stores the index of the last node
    for(int j=m; j>0; j--)
    {
        if(H[j].n!=0)
        {
            lastnode=j;
            break;
        }
    }
    m=lastnode;
    while(lc<=m)//at least the left child exists.
    {
        lmax=H[lc].a[0];
        for(int j=1; j<H[lc].n; j++)
        {

            if(H[lc].a[j]>lmax)
            {
                lmax=H[lc].a[j];
            }
        }

        if(rc<=m)//right child also exists
        {
            rmax=H[rc].a[0];
            for(int j=1; j<H[rc].n; j++)
            {

                if(H[rc].a[j]>rmax)
                {
                    rmax=H[rc].a[j];
                }
            }
        }

        if(rc<=m&&(rmax>lmax))
        {
            cmax=rmax;
            wc=rc;
        }
        else
        {
            cmax=lmax;
            wc=lc;
        }

        if(cmax>qmin)//need to arrange
        {
            int rootelems=H[i].n;
            int childelems=H[wc].n;
            int size1=rootelems+childelems;
            int* b=(int *)malloc(size1*sizeof(int));//new array of combined size

            for(int j=0; j<rootelems; j++)
                b[j]=H[i].a[j];
            for(int j=0; j<childelems; j++)
                b[j+rootelems]=H[wc].a[j];
            bsort(b,size1);//sorted
            for(int j=0; j<rootelems; j++)
                H[i].a[j]=b[j];
            for(int j=0; j<childelems; j++)
                H[wc].a[j]=b[j+rootelems];
            //arrangement over
            //updating current node for going down the heap
            free(b);
            i=wc;
            lc=2*i;
            rc=lc+1;

        }
        else
            break;

    }
}
////////////////////////////////////////////////////////////////////////////////////

int delmax(node* H,int p)
{
    int m=H[0].n;//extracting the total number of nodes
    int max1;//root
    int maxloc;//stores index in the root of the maximum value
    int q=H[1].n;//no. of keys in root
    max1=H[1].a[0];
    maxloc=0;
    for(int i=1; i<q; i++)
    {
        if(H[1].a[i]>max1)
        {
            max1=H[1].a[i];
            maxloc=i;
        }

    }
    //deleting the max value and replacing it with last value in the heap's last node
    int lastnode;//stores the index of the last node
    for(int j=m; j>0; j--)
    {
        if(H[j].n!=0)
        {
            lastnode=j;
            break;
        }
    }
    //lastnode identified
    int r=H[lastnode].n;//number of keys in the last node.
    r=r-1;//index of key to be shifted. if r=4,a[3] needs to be shifted
    H[1].a[maxloc]=H[lastnode].a[r];//max value replaced
    H[lastnode].a[r]=0;//set that node to 0
    H[lastnode].n=r;//number of keys reduced in the last node.

    /*
    if(r==0&&lastnode!=1)//if number of keys in the lastnode have become 0 and its not the root
    {
        lastnode=lastnode-1;
    }//now to update the storage of 'm' in the H[0].n;
    //H[0].n=lastnode;
    */
    //now to heapify:
    heapify(H,1);
    return(max1);
}

int main()
{
    printf("Enter value of p\n");
    int p,nmax;
    scanf("%d",&p);
    printf("Enter number of entries:\n");
    scanf("%d",&nmax);
    int m=(nmax+p-1)/p;//number of nodes needed.
    node* A=initheap( nmax, p);
    prnheap(A,p);

    printf("Enter array of Elems:\n");
    int val[nmax];
    for(int i=0; i<nmax; i++)
    {
        scanf("%d",&val[i]);
    }
    for(int i=0; i<nmax; i++)
    {
        insertheap(A,p,val[i]);
    }
    printf("\n\n");
    prnheap(A,p);
    int k;
    printf("\n");
    int z=nmax;
    for(int i=1; i<=z; i++)
    {
        k=delmax(A,p);
        printf("%d ",k);

    }


    return 0;

}
