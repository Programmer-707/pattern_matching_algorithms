#ifndef BRUTE_FORCE_H_INCLUDED
#define BRUTE_FORCE_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

void search(string T, string P)
{
    int i, n=T.size();
    int j, m = P.size();
    for (i=0, j=0; i<n; i++)
    {

        if(T[i]==P[j])
            j++;
        else
        {
            i-=j;
            j=0;
        }
        if(j==m){
                //cout << " ";
            //cout << "found at: " << i-m << endl;
        }
    }

}


#endif // BRUTE_FORCE_H_INCLUDED
