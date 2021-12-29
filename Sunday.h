#ifndef SUNDAY_H_INCLUDED
#define SUNDAY_H_INCLUDED

#include <iostream>
#include<vector>
#include <string>

using namespace std;

void sunday(string text, string pat)
{
    int N = text.length();
    int M = pat.length();

    vector<int> veNext;
    // for the character does not appear in the pattern string, skip the entire, length of movement pattern string length +
    for (int i = 0; i < 256; ++i)
        veNext.push_back(M + 1);

// for characters appear in the pattern string, a length corresponding to the movement pattern of the last string of characters occurs in this case
    for (int i = 0; i < M; ++i)
        veNext[pat[i]] = M - i;

    for (int i = 0; i < N - M; i += veNext[text[i + M]])
    {
        int j = 0; // restart match
        while (j < M)
        {
            if (text[i + j] != pat[j])
                break;
            ++j;  // continues to match the next character
        }
        if (j == M)
        {
            //cout << " ";
            //cout << "found at: " << i << endl;
        }
    }
}


#endif // SUNDAY_H_INCLUDED
