#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while(t>0)
    {

        t--;
        //cout << "Hello world!" << endl;
        int M,N,X,Y;
        //cout << "Enter value of M,N,X,Y" << endl;
        cin >> M >> N;
        int g[M][N];//M*N for the whole grid
        // populate it by 0's
        //cout <<"Enter dimension of house"<< endl;
        int s;
        cin >>X >> Y >> s;
        for(int i=0; i<M; i++)
        {
            for(int j=0; j<N; j++)
            {
                g[i][j]=0;
            }
        }
        int x[X];//horizontal rivers
        int y[Y];//vertical rivers
        //populate x
        //cout <<"Enter values for horizontal rivers " <<endl;
        for(int i=0; i<X; i++)
        {
            cin >> x[i];
            x[i]=x[i]-1;
        }
//**********************************************************************************
        //cout <<"Enter values for vertical rivers " <<endl;
        for(int i=0; i<Y; i++)
        {
            cin >> y[i];
            y[i]=y[i]-1;
        }

        //populating horizontal rows
        for(int i=0; i<X; i++)
        {
            int r=x[i];
            for(int j=0; j<N; j++)
            {
                g[r][j]=1;
            }
        }

        //populating vertical columns
        for(int i=0; i<Y; i++)
        {
            int c=y[i];
            for(int j=0; j<M; j++)
            {
                g[j][c]=1;
            }
        }

        //printing the grid
        for(int i=0; i<M; i++)
        {
            for(int j=0; j<N; j++)
            {
                cout << g[i][j] << " ";
            }
            cout<< endl;
        }

        int count=0;// number of houses
        for(int i=0; i<M; i++)
        {

            for(int j=0; j<N; j++)
            {
                if(g[i][j]==1)
                {
                    continue;
                }

                else if(g[i][j]==0)
                {
                    //check for emptiness in the next s-1 grids horizontal, next s-1 grids vertically
                    int t=0;
                    for(int k=1; k<=s-1; k++)
                    {
                        //checking next s-1 columns
                        if(g[i+k][j]!=0)
                        {
                            t=1;
                            break;
                        }
                    }
                    if(t==0)// if the columns are empty,check for emptiness of the rows

                        for(int k=1; k<=s-1; k++)
                        {
                            //checking next s-1 rows
                            if(g[i][j+k]!=0)
                            {
                                t=1;
                                break;
                            }
                        }

                    if(t==0)//implies that a house can be made
                    {
                        count++;
                        for(int k=i; k<i+s; k++)
                        {
                            for(int l=j; l<j+s; l++)
                            {
                                g[k][l]=2;
                            }
                        }

                    }

                }//0 found at pos


            }//j
        }//i
        //cout << "Number of houses :" << count <<endl;
        cout << count << endl;

        //printing the grid
        for(int i=0; i<M; i++)
        {
            for(int j=0; j<N; j++)
            {
                cout << g[i][j] << " ";
            }
            cout<< endl;
        }

    }//while

    return 0;
}
