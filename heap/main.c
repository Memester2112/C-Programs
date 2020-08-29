#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int n;//number of keys stored
    int a[2];

} node;

void bsort(int* a,int n)
{
    //sort in descending
    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
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

node* initheap(int p,int nmax)
{
    typedef struct node
    {
        int n;//number of keys stored
        int a[p];
    } node;
    int m=(nmax+p-1)/p;//number of nodes that need to be formed
    node* z=(node*)malloc((m+1)*sizeof(node));//not using the 0th node
    for(int i=1; i<=m; i++)
    {
        z[i].n=0;
        for(int j=0; j<p; j++)
        {
            z[i].a[j]=0;
        }
    }
    return(z);

}

int findmax(node* root)
{
    int max;
    if(root[0].n==0)//implies that the heap is empty
        return (-1);
    else
    {
        max=root[0].a[0];
        for(int i=1; i<root[0].n; i++)
        {
            if(root[0].a[i]>max)
            {
                max=root[0].a[i];
            }
        }
        return (max);
    }

}

void prnheap(node* root,int nmax,int p)
{
    int m=(nmax+p-1)/p;
    for(int i=1; i<=m; i++)
    {
        printf("\n[ ");
        for(int j=0; j<p; j++)
        {
            if(root[i].a[j]!=0)
                printf("%d ",root[i].a[j]);
            else
                printf("- ");
        }

        printf(" ]");
        printf(" n= %d",root[i].n);
    }
}

heapify(node* root,int c,int m)
{
    //c is the current index
//m is the last index
    int lc=2*c;
    int rc=2*c+1;
    int lmax,rmax,cmax,wc,qmin;//wc keeps record of which child's max is greater
    qmin=root[c].a[0];
    for(int i=1; i<root[c].n; i++)
    {
        if(root[c].a[i]<qmin)
            qmin=root[c].a[i];
    }
    while(lc<=m)//atleast left child exists
    {
        lmax=root[lc].a[0];
        for(int i=1; i<root[lc].n; i++)
            if(root[lc].a[i]>lmax)
                lmax=root[lc].a[i];
        if(rc<=m)//right child also exists
        {
            rmax=root[rc].a[0];
            for(int i=1; i<root[rc].n; i++)
                if(root[rc].a[i]>rmax)
                    rmax=root[rc].a[i];
        }

        if(rc<=m&&rmax>lmax)
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
            int rootelems=root[c].n;
            int childelems=root[wc].n;
            int b[rootelems+childelems];//new array of combined size
            for(int i=0; i<rootelems; i++)
                b[i]=root[c].a[i];
            for(int i=0; i<childelems; i++)
                b[i+rootelems]=root[wc].a[i];
            bsort(b,(rootelems+childelems));//sorted
            for(int i=0; i<rootelems; i++)
                root[c].a[i]=b[i];
            for(int i=0; i<childelems; i++)
                root[wc].a[i]=b[i+rootelems];
                //arrangement over
            //updating current node for going down the heap
            c=wc;
            lc=2*c;
            rc=lc+1;

        }
        else
            break;
    }


}



delmax(node* root,int nmax,int p)
{

    int m=(nmax+p-1)/p;//m is the last node
    //nmax has the number of elements in the heap currently
    int loc=0;
    int loc_max=root[0].a[0];
    for(int i=0; i<root[0].n; i++)
    {
        if(root[0].a[i]>loc_max)
        {
            loc_max=root[0].a[i];
            loc=i;//location of max element in the root
        }
    }
    root[0].a[loc]=root[m].a[0];//replaced max element by elem from last
    heapify(root,0,m);



}
node* insertheap(node* root,int x,int p,int nmax)
{
    int m=(nmax+p-1)/p;
    int loc=0;//loc is the current node location, where insertion is being done
    //have to find the first node which is not full
    for(int i=1; i<=m; i++)
    {


        if(root[i].n!=p)
        {

            loc=i;//node index of insertion
            //printf("\nloc=%d\n",loc);
            root[i].a[root[i].n]=x;
            root[i].n=root[i].n+1;
            //printf("\nroot[i].n= %d\n",root[i].n);
            break;
        }
    }//element inserted in free slot
    //now to move it up.
    int pi=loc/2;//parent node index
    while(pi>=1)
    {
        int pi_min=root[pi].a[0];
        for(int i=1; i<p; i++)
        {
            if(root[pi].a[i]<pi_min)
                pi_min=root[pi].a[i];
        }//pi_min has the min value of parent node
        int loc_max=root[loc].a[0];
        for(int i=0; i<root[loc].n; i++)
        {
            if(root[loc].a[i]>loc_max)
                loc_max=root[loc].a[i];
        }
        if(loc_max>pi_min)
        {
            //need to rearrange
            int b[p+root[loc].n];//for merging elems from parent and current node
            for(int i=0; i<p; i++)
                b[i]=root[pi].a[i];
            for(int i=0; i<root[loc].n; i++)
                b[i+p]=root[loc].a[i];
            bsort(b,(p+root[loc].n));//b is sorted in descending
            for(int i=0; i<p; i++)
                root[pi].a[i]=b[i];//parent is filled with largest p
            for(int i=0; i<root[loc].n; i++) //current node with remaining
                root[loc].a[i]=b[i+p];
            loc=pi;//update current node
            pi=loc/2;
        }
        else
            break;
    }

    return(root);

}

int main()
{
    int p,nmax;
    scanf("%d %d",&p,&nmax);
    node * root;
    root = initheap(p,nmax);
    prnheap(root,nmax,p);
    int q[nmax];
    printf("\nEnter values:\n");
    for(int i=0; i<nmax; i++)
    {
        scanf("%d",&q[i]);
    }
    for(int i=0; i<nmax; i++)
    {
        root=insertheap(root,q[i],p,nmax);

    }
    prnheap(root,nmax,p);

    return 0;
}
