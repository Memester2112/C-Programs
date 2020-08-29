#include <iostream>

using namespace std;

int main()
{
    cout << "Enter Number of Barriers " << endl;
    int n,h,y1,y2,l;
    cin >> n;
    cout << "Enter Number of height of ed " << endl;
    cin >> h;
    cout << "Enter units he can duck from his initial height " << endl;
    cin >> y1;
    cout << "Enter units he can jump " << endl;
    cin >> y2;
    cout << "Enter Number of life force units he has " << endl;
    cin >> l;
    int t[n];//type of barrier
    int x[n];//height of barrier
    cout << "Enter type + Barrier height " << endl;
    for(int i=0;i<n;i++)
    {
        cin >> t[i];
        cin >> x[i];
        //cout << endl;
    }
    cout <<"Printing Input " << endl;
    for(int i=0;i<n;i++)
    {
        cout << t[i] << " " << x[i] << endl;

        //cout << endl;
    }

    int b=0;//no. of barriers that can be passed by ed.
    for(int i=0;i<n;i++)
    {
        if (l<0)//&& i!=0)
        {
            break;
        }

        else//l!=0
        {
            if(t[i]==1)//ducking
            {
                if((h-y1)<= x[i])
                    b++;
                else
                {
                    l--;
                    if(l!=0) b++;
                }

            }

            else// barrier type 2, jumping
            {
                if(y2>=x[i])
                    b++;
                else
                {
                    l--;
                    if(l!=0) b++;
                }

            }
        }
    }

    cout << "Number of barriers : " << b ;
    return 0;
}
