#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int vertex;
    struct node* next;
} node;

typedef struct graph
{
    int n;//number of vertices
    char* color;
    int* vn;//vertex number
    node* adjlist;//array of lists,n in number


} graph;

graph readgraph(int v,int* vertexno)
{
    int p,q;//edges scanning
    graph G;
    G.n=v;
    G.vn=(int*)malloc(v*sizeof(int));
    for(int i=0; i<v; i++)
        G.vn[i]=vertexno[i];

    G.color=(char*)malloc(v*sizeof(char));
    for(int i=0; i<v; i++)
    {
        scanf(" %c",&G.color[i]);
    }
    G.adjlist=(node*)malloc(v*sizeof(node));//initialize the array of nodes
    for(int i=0; i<v; i++)
    {
        G.adjlist[i].vertex=-1;//beginning of the list is useless
        node* newnode=(node*)malloc(sizeof(node));
        G.adjlist[i].next=newnode;
        newnode->vertex=i;
        newnode->next=NULL;

    }
    printf("\nEnter edges\n");
    p=0;
    q=0;
    scanf("%d %d",&p,&q);
    while(p!=(-1))
    {
        node* temp;
        //now go to adjlist[p] and adjlist[q] and add another node to these lists and update there values
        //create new nulls. Will find where to add by tracking NULL; first create 2 new node types
        node* newnodep=(node*)malloc(sizeof(node));
        newnodep->next=NULL;
        newnodep->vertex=q;
        temp=G.adjlist[p].next;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newnodep;

        node* newnodeq=(node*)malloc(sizeof(node));
        newnodeq->vertex=p;
        newnodeq->next=NULL;
        temp=G.adjlist[q].next;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newnodeq;
//        free(newnodep);
//        free(newnodeq);

        scanf("%d",&p);
        if(p==-1)
            break;
        scanf("%d",&q);
    }
    return(G);


}
void prngraph(graph G)
{
    for(int i=0; i<G.n; i++)
    {
        printf("[%c]   ",G.color[i]);
        printf("%d -> ",G.vn[i]);
        node* temp;
        temp=G.adjlist[i].next;
        temp=temp->next;
        while(temp!=NULL)
        {
            printf("%d,",G.vn[temp->vertex]);
            temp=temp->next;
        }
        printf("\n");

    }
}
graph getcolgraph(graph G,char col)
{
    graph H;
    int v=0;//number of vertex of color col
    int a[G.n];
    for(int i=0; i<G.n; i++)
    {
        if(G.color[i]==col)
        {
            a[v]=i;//vertex number filled
            v++;
        }
    }
    H.n=v;
    H.vn=(int*)malloc(v*sizeof(int));
    for(int i=0; i<v; i++)
    {
        H.vn[i]=a[i];
    }
    H.color=(char*)malloc(v*sizeof(char));
    for(int i=0; i<v; i++)
    {
        H.color[i]=col;
    }
    //********************
    H.adjlist=(node*)malloc(v*sizeof(node));//initialize the array of nodes
    for(int i=0; i<v; i++)
    {
        H.adjlist[i].vertex=-1;//beginning of the list is useless
        node* newnode=(node*)malloc(sizeof(node));
        H.adjlist[i].next=newnode;
        newnode->vertex=i;
        newnode->next=NULL;

    }
    int r;
    for(int i=0; i<v; i++)
    {
        r=H.vn[i];//look at G.adjlist[r], these are the nodes with the same colour
        //we go over the lists and add any node which of the same colour
        //do so until end of list is reached.
        node* temp;
        int w=0;
        node* ptr;
        temp=G.adjlist[r].next;
        temp=temp->next;
        while(temp!=NULL)
        {
            if(G.color[(temp->vertex)]==col)//add this vertex to the end of the list of H.adjlist[i]
            {
                //need to find the end of the list H.adjlist[i] first though

                node* newnode=(node*)malloc(sizeof(node));//new node to be added
                newnode->next=NULL;
                for(int j=0; j<v; j++)
                {
                    if(temp->vertex==H.vn[j])
                        w=j;

                }
                newnode->vertex=w;
                ptr=H.adjlist[i].next;
                while(ptr->next!=NULL)
                    ptr=ptr->next;
                //found
                ptr->next=newnode;


            }
            temp=temp->next;

        }

    }
    return(H);


}

graph dfs(graph G,int* parent,int* visited,int* level,int p,int i)//p=parent i is node on which dfs is called
{
    //need to delete the back edges after detecting them
    node* temp;
    node* ptr;
    node* adr;
    int x,y,a;

    temp=G.adjlist[i].next;//refers to vertex number G.vn[i]
    ptr=G.adjlist[i].next;
    while(temp!=NULL)//for all the successors of the node i
    {
        if(visited[temp->vertex]==1&&temp->vertex!=p&&level[temp->vertex]<level[i])
        {
            printf("Cycle detected: by joining at vertex %2d and vertex %2d\n",G.vn[temp->vertex],G.vn[ptr->vertex]);
            x=ptr->vertex;
            a=x;
            while(x!=temp->vertex)
            {
                printf("%d ",G.vn[x]);
                x=parent[x];
            }
            printf("%d ",G.vn[temp->vertex]);
            printf("\n");
            y=temp->vertex;
            //after printing of the cycle 2 deletions need to be made in 2 linked list
            //the 2 vertex which on joining form the cycle are temp->vertex and ptr->vertex
            //these indexes are within bounds:(x and y) Remove connection x->y and y->x
            //need a pointer can use ptr as it is reset after entering this loop anyway
            //ptr is already set of the list starting with x, so iterate over it to delete y
            while((ptr->next)->vertex!=y)
            {
                ptr=ptr->next;
            }
            adr=ptr->next->next;
            ptr->next=adr;
            //x->y deleted
            //now to delete the y->x terminal we need to set ptr to the linked list begining with y
            //That can be :( note that x has remained unchanged)
            ptr=G.adjlist[y].next;

            while((ptr->next)->vertex!=a)
            {
                ptr=ptr->next;
            }
            adr=ptr->next->next;
            ptr->next=adr;

        }

        if(visited[temp->vertex]==0)//if not visited
        {
            //printf("Vertex visited = %d\n",G.vn[temp->vertex]);
            visited[temp->vertex]=1;//marked visited
            if(temp->vertex!=i)
            {
                parent[temp->vertex]=i;//mark parent
                level[temp->vertex]=level[i]+1;
            }
            G=dfs(G,parent,visited,level,i,temp->vertex);
        }
        ptr=G.adjlist[i].next;
        temp=temp->next;
    }
    return(G);
}


graph multidfs(graph G)
{
    int* visited=(int*)malloc(G.n*sizeof(int));
    int* parent=(int*)malloc(G.n*sizeof(int));
    int* level=(int*)malloc(G.n*sizeof(int));
    for(int i=0; i<G.n; i++)
    {
        visited[i]=0;
        parent[i]=-1;
        level[i]=0;
    }

    for(int i=0; i<G.n; i++)
    {
        if(visited[i]==0)
        {

            G=dfs(G,parent,visited,level,parent[i],i);
        }
    }
    return(G);
}


graph getrbgraph(graph G,graph Gr,graph Gb)
{
    graph H;
    H.n=G.n;
    H.vn=(int*)malloc(H.n*sizeof(int));
    H.color=(char*)malloc(H.n*sizeof(char));
    for(int i=0; i<H.n; i++)
    {
        H.vn[i]=i;
        H.color[i]=G.color[i];
        printf("%c %d \n",H.color[i],H.vn[i]);
    }
    H.adjlist=(node*)malloc(H.n*sizeof(node));
    for(int i=0; i<H.n; i++)
    {
        H.adjlist[i].vertex=-1;//beginning of the list is useless
        node* newnode=(node*)malloc(sizeof(node));
        H.adjlist[i].next=newnode;
        newnode->vertex=i;
        newnode->next=NULL;
    }
    //node* temp;
    node* ptr;
    node* adr;
    char cc;//current color
    //need to find out the nodes which have different coloured nodes attached
    for(int i=0; i<H.n; i++) //all nodes need to be checked
    {
        cc=H.color[i];
        ptr=G.adjlist[i].next;//temp has the address of node=i
        ptr=ptr->next;//ptr has address of the next node in the adjacency list
        while(ptr!=NULL)
        {
            if(G.color[ptr->vertex]!=cc)
            {
                //add the node to the list ending of H.adjlist[i], first find the ending of this list
                adr=H.adjlist[i].next;
                while(adr->next!=NULL)
                {
                    adr=adr->next;
                }
                node* newnode=(node*)malloc(sizeof(node));
                newnode->vertex=ptr->vertex;
                newnode->next=NULL;
                adr->next=newnode;
            }
            ptr=ptr->next;
        }
    }
    //now to add the dfs tree edges: First blue
    int r;
    for(int i=0; i<Gb.n; i++)
    {
        r=Gb.vn[i];//have to add nodes at the nide no. r in H
        //first reach the end of this list
        adr=H.adjlist[r].next;
        while(adr->next!=NULL)
        {
            adr=adr->next;
        }
        // now to iterate over the list of dfs tree edges in Gb we use ptr
        ptr=Gb.adjlist[i].next;
        ptr=ptr->next;//ptr now points to the first node that needs to be added.
        //add Gb.vn[ptr->vertex], not ptr->vertex
        while(ptr!=NULL)
        {
            node* newnode=(node*)malloc(sizeof(node));
            newnode->next=NULL;
            newnode->vertex=Gb.vn[ptr->vertex];
            adr->next=newnode;
            adr=newnode;
            ptr=ptr->next;
        }
    }
    //now to add red dfs edges
    for(int i=0; i<Gr.n; i++)
    {
        r=Gr.vn[i];//have to add nodes at the nide no. r in H
        //first reach the end of this list
        adr=H.adjlist[r].next;
        while(adr->next!=NULL)
        {
            adr=adr->next;
        }
        // now to iterate over the list of dfs tree edges in Gb we use ptr
        ptr=Gr.adjlist[i].next;
        ptr=ptr->next;//ptr now points to the first node that needs to be added.
        //add Gb.vn[ptr->vertex], not ptr->vertex
        while(ptr!=NULL)
        {
            node* newnode=(node*)malloc(sizeof(node));
            newnode->next=NULL;
            newnode->vertex=Gr.vn[ptr->vertex];
            adr->next=newnode;
            adr=newnode;
            ptr=ptr->next;
        }
    }
    return(H);
}


int main()
{
    int v;
    printf("No. of vertices:\n");
    scanf("%d",&v);
    int* vertexno=(int*)malloc(v*sizeof(int));
    for(int i=0; i<v; i++)
        vertexno[i]=i;//for the initial graph vertex numbers are same as natural ordering
    graph H,Gr,Gb;
    graph G=readgraph(v,vertexno);
    printf("\nOriginal Graph\n");
    prngraph(G);
    free(vertexno);

    H=getcolgraph(G,'r');
    printf("\nRed Graph\n");
    prngraph(H);

    printf("\nRed Cycles\n");
    Gr=multidfs(H);
    printf("After deletion Red Graph:\n");
    prngraph(Gr);


    H=getcolgraph(G,'b');
    printf("\nBlue graph\n");
    prngraph(H);

    printf("\nBlue Cycles\n");
    Gb=multidfs(H);
    printf("After deletion Blue graph:\n");
    prngraph(Gb);
    printf("*****************************************\n");
    graph X=getrbgraph(G,Gr,Gb);
    printf("Multi-Colored Graph\n");
    prngraph(X);
    printf("\nMulti-Colored Cycles\n");
    X=multidfs(X);

    return 0;
}
