#ifndef KMP_H_INCLUDED
#define KMP_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

void CreateLPS(string, int, int*);

void KMP(string txt, string pat)
{
    int M = pat.size();
    int N = txt.size();

    int* lps = new int[M];
    CreateLPS(pat, M, lps);

    int i=0, j=0;

    while(i<N)
    {
        if(txt[i]==pat[j])
        {
            i++;
            j++;
        }

        if(j==M)
        {
            //cout << " ";
            //cout << "found at: " << i-j << endl;
            j= lps[j-1];
        }
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

}
void CreateLPS(string pat, int m, int* lps)
{
    lps[0] = 0; // the first value of lps always starts with 0
    int value = 0, i=1; // i for starting 2nd element to compare with 1st

    while(i<m) // loop till to reach the size of pattern
    {
        if(pat[i]==pat[value])
        {
            value++;
            pat[i] = value;
            i++;
        }
        else
        {
            if(value!=0)
            {
                value = lps[value-1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


#endif // KMP_H_INCLUDED
