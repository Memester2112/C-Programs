#include <stdio.h>
#include <stdlib.h>
#define INF 999999
typedef struct graph
{
    int n;
    char** c;
    int** t;
} graph;

graph readgraph()
{
    struct graph G;
    int x;
    scanf("%d",&x);
    G.n=x;
    G.c=(char**)malloc(G.n*sizeof(char*));
    G.t=(int**)malloc(G.n*sizeof(int*));

    for(int i=0; i<x; i++)
    {
        G.c[i]=(char*)malloc(x*sizeof(char));
        G.t[i]=(int*)malloc(x*sizeof(int));
    }
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<x; j++)
        {
            if(i==j)
            {
                G.c[i][j]='s';
                G.t[i][j]=0;
            }
            else
            {
                G.c[i][j]='-';
                G.t[i][j]=INF;
            }
        }
    }
    //user input
    int a,b,c;
    char d;//a->b ticket cost=c and airline=d
    while(1)
    {
        scanf("%d",&a);
        if(a==-1)
            break;
        scanf("%d %d %c",&b,&c,&d);
        G.c[a][b]=d;
        G.t[a][b]=c;
    }
    return(G);
}
void prngraph(graph G)
{
    printf("\n");
    for(int i=0; i<G.n; i++)
    {
        printf("\n%d -> ",i);
        for(int j=0; j<G.n; j++)
        {
            if(i!=j&&G.c[i][j]!='-')
            {
                printf(" %d (%d , %c)  ",j,G.t[i][j],G.c[i][j]);
            }
        }

    }
}
void prncost(int** cost,int n)
{
    printf("\n          ");
    for(int i=0; i<n; i++)
        printf("%8d",i);
    for(int i=0; i<n; i++)
    {
        printf("\n%d   ->    ",i);
        for(int j=0; j<n; j++)
        {
            if(cost[i][j]!=INF)
                printf("\t%d ",cost[i][j]);
            else
                printf("\t-");
        }
    }
}

graph getAIGraph(graph G)
{
    graph H;
    H.n=G.n;
    H.c=(char**)malloc(H.n*sizeof(char*));
    H.t=(int**)malloc(H.n*sizeof(int*));
    for(int i=0; i<H.n; i++)
    {
        H.c[i]=(char*)malloc(H.n*sizeof(char));
        H.t[i]=(int*)malloc(H.n*sizeof(int));
    }
    for(int i=0; i<H.n; i++)
    {
        for(int j=0; j<H.n; j++)
        {
            if(i==j)
            {
                H.c[i][j]='s';
                H.t[i][j]=0;
            }
            else
            {
                H.c[i][j]='-';
                H.t[i][j]=INF;
            }
        }
    }
    for(int i=0; i<G.n; i++)
    {
        for(int j=0; j<G.n; j++)
        {
            if(i!=j&&G.c[i][j]=='a')
            {
                H.c[i][j]='a';
                H.t[i][j]=G.t[i][j];
            }
        }
    }

    return(H);
}
int** APSP(graph G)
{
    int** cost=(int**)malloc(G.n*sizeof(int*));
    for(int i=0; i<G.n; i++)
    {
        cost[i]=(int*)malloc(G.n*(sizeof(int)));
    }
    for(int i=0; i<G.n; i++)
    {
        for(int j=0; j<G.n; j++)
        {
            cost[i][j]=G.t[i][j];
        }
    }
    for(int k=0; k<G.n; k++)
    {
        for(int i=0; i<G.n; i++)
        {
            for(int j=0; j<G.n; j++)
            {
                if(cost[i][k]+cost[k][j]<cost[i][j])
                    cost[i][j]=cost[i][k]+cost[k][j];
            }
        }
    }

    return(cost);
}

int** APSPany(graph G,int** cost1)
{
    int** cost3=(int**)malloc(G.n*sizeof(int*));
    for(int i=0; i<G.n; i++)
    {
        cost3[i]=(int*)malloc(G.n*(sizeof(int)));
    }

    for(int i=0; i<G.n; i++)
    {
        for(int j=0; j<G.n; j++)
        {
            cost3[i][j]=G.t[i][j];
        }
    }

    for(int k=0; k<G.n; k++)
    {
        printf("\nF[%d]\n",k);
        prncost(cost3,G.n);
        for(int i=0; i<G.n; i++)
        {
            for(int j=0; j<G.n; j++)
            {
                if(cost3[i][k]+cost3[k][j]<cost3[i][j])
                    cost3[i][j]=cost3[i][k]+cost3[k][j];

            }
        }
    }
    printf("\n\nF[6]\n");
    prncost(cost3,G.n);

//
//    for(int i=0;i<G.n;i++)
//    {
//        for(int j=0;j<G.n;j++)
//        {
//            if(cost1[i][j]!=INF)
//            {
//                cost3[i][j]=cost1[i][j];
//            }
//        }
//    }
    return(cost3);

}
int** APSPone(graph G,int** cost1)
{
    int** cost2=(int**)malloc(G.n*sizeof(int*));
    for(int i=0; i<G.n; i++)
    {
        cost2[i]=(int*)malloc(G.n*(sizeof(int)));
    }
    for(int i=0; i<G.n; i++)
    {
        for(int j=0; j<G.n; j++)
        {
            cost2[i][j]=G.t[i][j];
        }
    }
    //first minimize all routes using a single non ai path
    //then in the end correct for ai paths available
    for(int k=0;k<G.n;k++)
    {
        for(int l=0;l<G.n;l++)
        {
            if(G.c[k][l]=='n')//proceed only if it is a non AI flight
            {
                for(int i=0;i<G.n;i++)
                {
                    for(int j=0;j<G.n;j++)
                    {
                        if(cost1[i][k]+G.t[k][l]+cost1[l][j]<cost2[i][j])
                            cost2[i][j]=cost1[i][k]+G.t[k][l]+cost1[l][j];
                    }
                }
            }
        }
    }

    for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            if(cost1[i][j]!=INF)
            {
                cost2[i][j]=cost1[i][j];
            }
        }
    }

    return(cost2);

}

int main()
{
    printf("Enter graph data\n");
    graph G=readgraph();
    printf("Original Graph\n");
    prngraph(G);//all routes
    printf("AI Graph\n");
    graph H=getAIGraph(G);//only AI routes
    prngraph(H);
    int** cost1=APSP(H);
    //printf("Cheapest Flights AI only\n");
    //prncost(cost1,H.n);

    //int** cost2=APSPone(G,cost1);
    //printf("\nCheapest Flights with only one non AI leg\n");
    //prncost(cost2,H.n);

    int** cost3=APSPany(G,cost1);
//    printf("\nCheapest Flights with any number of non AI leg\n");
//    prncost(cost3,H.n);
    return 0;
}
