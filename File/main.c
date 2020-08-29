#include<stdio.h>
#include<stdlib.h>
struct node
{
    int date;
    struct node *right;
    struct node *down;
};


struct node* initcal()
{
    printf("INITCAL\n");
    struct node* h;//head
    struct node* temp;
    int i;
    h=(struct node*) malloc(sizeof(struct node));
    for(i=1; i<=419; i++)
    {
        struct node* new_node=(struct node*) malloc(sizeof(struct node));
        if(i==1)
        {
            h->right=new_node;
            h->date=0;//
        }
        else
        {
            temp->date=0;
            temp->right=new_node;
        }
        temp=new_node;
    }
    temp->date=0;
    temp->right=NULL;//#419 is terminating
    temp->down=NULL;//#419 is terminating
//all rights are connected \\ now to connect the downs
//Joining the first 2 rows to begin with;
    struct node* h2;//to store the beginning of THE ROW FROMN WHICH THE ADDRESS IS BEING TAKEN TO ASSIGN
    struct node* h1;//STORES THE BEGINNNING OF THE ROW TO WHICH ADDRESSES ARE BEING ASSIGNED
    h2=h;
    h1=h;
    int j;
    for(i=1; i<=21; i++)
    {
        h2=h2->right;
    }//now h2 is pointing to index 21, (indexing from 0)
    for(i=1; i<=399; i++)
    {
        h1->down=h2;
        h1=h1->right;
        h2=h2->right;
    }//h2 will become NULL and h1 will become the beginning of the last row
    for(i=1; i<=21; i++)
    {
        h1->down=NULL;
        h1=h1->right;
    }
    return(h);
}

void calendar(struct node* p)
{
    for(int i=1; i<=20; i++)
    {
        for(int j=1; j<=21; j++)
        {
            printf("%4d",p->date);
            p=p->right;
        }
        printf("\n");
    }
}//printing in the format

void storemonth(struct node* p,int m,int d,int l)//l=1, if it is a leap year
{
    struct node* t;//pointer, t will hold the address of the starting of the 5*7 grid of the particular month
    struct node* r;
    //now to get t to its correct value

    t=p;
    int m1=m/3;
    for(int i=1; i<=(5*m1); i++)
    {
        t=t->down;
    }

    for(int i=1; i<=(7*(m%3)); i++)
    {
        t=t->right;
    }
    r=t;//r stores the top left of the corner
    for(int i=0; i<d; i++)
    {
        t=t->right;
    }
    //t is now at the day of the month which is 1st
    int c=0;
    d=(7-d)%7;
    if(m==0||m==2||m==4||m==6||m==7||m==9||m==11)//31 days
    {
        for(int i=1; i<=31; i++)
        {

            t->date=i;
            t=t->right;
            if(i%7==d)
            {
                c=c+1;
                t=r;
                for(int j=0; j<c; j++)
                {
                    t=t->down;
                }
                if(c==5)
                {
                    t=r;
                }
            }
        }
    }
    else if(m==1)
    {
        int z=28;
        if(l==1)
        {
            z=29;
        }
        for(int i=1; i<=z; i++)
        {

            t->date=i;
            t=t->right;
            if(i%7==d)
            {
                c=c+1;
                t=r;
                for(int j=0; j<c; j++)
                {
                    t=t->down;
                }
                if(c==5)
                {
                    t=r;
                }
            }

        }
    }
    else
    {
        for(int i=1; i<=30; i++)
        {

            t->date=i;
            t=t->right;
            if(i%7==d)
            {
                c=c+1;
                t=r;
                for(int j=0; j<c; j++)
                {
                    t=t->down;
                }
                if(c==5)
                {
                    t=r;
                }
            }

        }
    }
}
//
    int main()
    {
        struct node* head=initcal();
//printf("%d\n",head);
        struct node* p;
        p=head;
        int i;
        calendar(p);
        //Now to fill in the calendar
        //Inputs being Month[0-11],and Day[0-6]

        printf("\nEnter day of 1st Jan [0-6] ");
        int d;
        scanf("%d",&d);
        printf("\nIf it is a leap year, enter 1, else enter 0\n");
        int l;
        scanf("%d",&l);
        int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(l==1)
        {
            a[1]=29;
        }
        int fd[12];//first day
        fd[0]=d;
        storemonth(head,0,fd[0],l);//Jan Call

        for(int i=1;i<=11;i++)
        {
            fd[i]=(a[i-1]+fd[i-1])%7;
            storemonth(head,i,fd[i],l);
        }

        printf("\nModified Calendar is as follows:\n");

        calendar(p);
        return 0;
    }
