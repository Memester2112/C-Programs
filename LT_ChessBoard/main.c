#include <stdio.h>
#include <stdlib.h>
#define MIN(x,y) (((x)<(y))?(x):(y))

#define MAX(x,y) (((x)>=(y))?(x):(y))
int ischessboard(int A[][50],int i,int j, int l,int b)//(i,j)starting coordinates l*b is size to be checked
{
    int counter=0,x,r,c,k=0;
    if(A[i][j]==0)//Starting tile is white
        x=-1;
    else//starting tile is black
        x=1;
    for(r=i; r<i+l; r++)
    {
        if(k%2==0)//traverse the row from column 1 to n
        {
            for(c=j; c<j+b; c++)
            {
                if(A[r][c]==0)
                    counter--;
                else
                    counter++;
                if(counter!=x&&counter!=0)
                    return 0;
            }
        }
        else//traverse the the row in reverse, from column n to 1
        {
            for(c=j+b-1; c>=j; c--)
            {
                if(A[r][c]==0)
                    counter--;
                else
                    counter++;
                if(counter!=x&&counter!=0)
                    return 0;

            }
        }
        k++;
    }
    return(1);

}

void printfloor(int A[][50],int m,int n,int i,int j,int l,int b)//(i,j) starting index l*b=size
{
    int r,c;
    printf("\n");
    for(r=0; r<m; r++)
    {
        for(c=0; c<n; c++)
        {
            if(r>=i&&r<(i+l)&&c>=j&&c<(j+b))
            {
                if(A[r][c]==0)
                    printf("W ");
                else
                    printf("B ");
            }
            else
                printf(". ");
        }
        printf("\n");
    }
}

int essquare(int A[][50],int m,int n)
{
    int i,j,r,c,size,k,p,w;
    i=j=size=0;//size is the side length
    //(i,j) stores the position where maximality is obtained
    for(r=0; r<m; r++)
    {
        for(c=0; c<n; c++)
        {
            //starting position being checked is (r,c)
            k=MIN((n-c),(m-r));
            for(p=k; p>=1; p--)
            {
                w=ischessboard(A,r,c,p,p);
                if(w)//chessboard pattern of length p found at (r,c)
                {
                    if(p>=size)
                    {
                        size=p;
                        i=r;
                        j=c;
                    }
                    break;
                }


            }

        }
    }

    printf("(i,j)= (%d,%d)\n",i,j);
    printf("\n+++Exhaustive Search: Square\n");
    printfloor(A,m,n,i,j,size,size);
    return(size*size);
}

int esrectangle(int A[][50],int m,int n)
{
    int i,j,r,c,sizel,sizeb,k,l,w;
    i=j=sizel=sizeb=0;//sizel,sizeb are the length and breadth
    //(i,j) stores the position where maximality is obtained
    for(r=0; r<m; r++)
    {
        for(c=0; c<n; c++)
        {
            //starting position being checked is (r,c)
            for(k=n-c; k>=1; k--)
            {
                for(l=m-r; l>=1; l--)
                {
                    w=ischessboard(A,r,c,l,k);
                    if(w)
                    {
                        if((k*l)>=(sizel*sizeb))
                        {
                            sizel=l;
                            sizeb=k;
                            i=r;
                            j=c;
                        }
                    }
                }
            }
        }
    }

    printf("(i,j)= (%d,%d)\n",i,j);
    printf("\n+++Exhaustive Search: Rectangle\n");
    printfloor(A,m,n,i,j,sizel,sizeb);
    return(sizel*sizeb);
}

int dpsquare(int A[][50],int m,int n)
{
    int r,c,q,size,i,j;
    int T[m][n];
    for(r=0; r<m; r++)
        T[r][n-1]=1;
    for(c=0; c<n; c++)
        T[m-1][c]=1;

    for(r=m-2; r>=0; r--)
    {
        for(c=n-2; c>=0; c--)
        {
            if(A[r][c]==A[r+1][c]||A[r][c]==A[r][c+1])
                T[r][c]=1;
            else
            {
                if(T[r+1][c]>T[r][c+1])
                    T[r][c]=T[r][c+1]+1;

                else if(T[r+1][c]<T[r][c+1])
                    T[r][c]=T[r+1][c]+1;
                else
                {
                    q=T[r+1][c];
                    if(A[r][c]==A[r+q][c+q])
                        T[r][c]=q+1;
                    else
                        T[r][c]=q;

                }
            }
        }
    }
    i=j=size=0;
    for(r=0; r<m; r++)
    {
        for(c=0; c<n; c++)
        {
            if(T[r][c]>=size)
            {
                size=T[r][c];
                i=r;
                j=c;
            }
        }
    }
    printf("\n+++Dynamic Programming: Square\n");
    printfloor(A,m,n,i,j,size,size);
    return(size*size);

}
int dprectangle(int A[][50],int m,int n)
{
    int R[m][n],D[m][n],Area[m][n];
    //R stores the value of the length of the rectangle from(i,j) moving to the right
    //D stores the value of the length of the rectangles from(i,j) moving down
    //Area stores the area of the rectangle at(i,j)
    //first sill up R and D in N^2 time
    //then fill up Area in N^3 time using R and D for linear lookup
    int r,c,p,k;
    for(r=0; r<m; r++)
        R[r][n-1]=1;
    for(c=0; c<n; c++)
        D[m-1][c]=1;
    //R and D initialized
    for(r=0; r<m; r++)
    {
        for(c=n-2; c>=0; c--)
        {
            if(A[r][c+1]==A[r][c])
                R[r][c]=1;
            else
                R[r][c]=R[r][c+1]+1;
        }
    }
    for(c=0; c<n; c++)
    {
        for(r=m-2; r>=0; r--)
        {
            if(A[r+1][c]==A[r][c])
                D[r][c]=1;
            else
                D[r][c]=D[r+1][c]+1;
        }
    }
    //R and D filled
    //Area Fill corner elements first as Area[r][c] = MAX(R[r][c],D[r][c])
    for(r=0; r<m; r++)
    {
        Area[r][n-1]=MAX((D[r][n-1]),(R[r][n-1]));
    }
    for(c=0; c<n; c++)
    {
        Area[m-1][c]=MAX(D[m-1][c],R[m-1][c]);
    }


    //now to fill up the rest of the entries in reverse row major fashion

    for(r=m-2; r>=0; r--)
    {
        for(c=n-2; c>=0; c--)
        {
//            //if(D[r][c]!=R[r][c])
//            {
//                if(D[r][c]>R[r][c])
//                {
//                    //max found in D, now traverse D rightwards as long as we find D[r][c] repeating
//                    p=D[r][c];
//                    for(k=c+1; k<n; k++)
//                    {
//                        if(D[r][k]==p)
//                            continue;
//                        else
//                            break;
//
//                    }
//                    k=k-c;
//                    Area[r][c]=p*k;
//                }
//                else
//                {
//                    p=R[r][c];
//                    //max found in R,traverse R downwards as long as we find R[r][c] repeating
//                    for(k=r+1; k<m; k++)
//                    {
//                        if(R[k][c]==p)
//                            continue;
//                        else
//                            break;
//                    }
//                    k=k-r;
//                    Area[r][c]=p*k;
//                }
//            }
            //else//R[r][c]==D[r][c]
            {
                //have to check both D and R store
                p=D[r][c];
                for(k=c+1; k<n; k++)
                {
                    if(D[r][k]==p)
                        continue;
                    else
                        break;

                }
                k=k-c;
                Area[r][c]=p*k;
                //D done
                for(k=r+1; c<m; k++)
                {
                    if(R[k][c]==p)
                        continue;
                    else
                        break;
                }
                k=k-r;
                if((p*k)>Area[r][c])
                    Area[r][c]=p*k;

            }


        }
    }
    int i=0,j=0,area=0;
    for(r=0; r<m; r++)
    {
        for(c=0; c<n; c++)
        {
            if(Area[r][c]>area)
            {
                area=Area[r][c];
                i=r;
                j=c;
            }
        }
    }
    int sizeb=R[i][j];
    int sizel=area/sizeb;

    printf("\n+++Dynamic Programming: Rectangle\n");
    printfloor(A,m,n,i,j,sizel,sizeb);

    return area;
}

int main()
{
    int m,n,i,j;
    scanf("%d %d",&m,&n);
    int A[50][50];
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d",&A[i][j]);
        }
    }
    printfloor(A,m,n,0,0,m,n);
    printf("\n");
    int z=essquare(A,m,n);
    printf("Largest square of area : %d \n",z);
    z=esrectangle(A,m,n);
    printf("Largest rectangle of area : %d \n",z);
    z=dpsquare(A,m,n);
    printf("Largest square of area : %d \n",z);
    z=dprectangle(A,m,n);
    printf("Largest rectangle of area : %d \n",z);

    return 0;
}
