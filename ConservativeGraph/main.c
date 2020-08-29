#include <stdio.h>
#include <stdlib.h>

int main()
{
    //N nodes M edges
    int N,M;
    scanf("%d %d",&N,&M);
    int u[M],v[M],w[M];//edge from u to v with cost w
    for(int i=0; i<M; i++)
    {
        scanf("%d %d %d",&u[i],&v[i],&w[i]);
    }
    //create an adjacency matrix
    int a[N+1][N+1];
    for(int i=0; i<=N; i++)
    {
        for(int j=0; j<=N; j++)
        {
            a[i][j]=0;
        }

    }
    for(int i=0; i<M; i++)
    {
        a[u[i]][v[i]]=w[i];
        a[v[i]][u[i]]=-w[i];
    }
    printf("\nAdjacency Matrix\n");
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            printf("%4d ",a[i][j]);
        }
        printf("\n");

    }
    //identify the points where the upper half of a is 0, these are the paths that need to be checked.


    return 0;
}
