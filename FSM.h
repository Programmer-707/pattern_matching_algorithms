#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

#include <iostream>
#include <string>

#define total_chars 256

using namespace std;

int Next_state(string pat, int M, int state, int input)
{

    if (state < M && input == pat[state])
        return state+1;

    for (int ns = state; ns > 0; ns--)
    {
        int i;

        if (pat[ns-1] == input)
        {
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[state-ns+1+i])
                    break;
            if (i == ns-1)
                return ns;
        }
    }
    return 0;
}

//builds Finite Automata
void transaction_function(string pat, int M, int tf[][total_chars])
{
    for (int state = 0; state <= M; state++)
        for (int input = 0; input < total_chars; input++)
            tf[state][input] = Next_state(pat, M, state, input);
}

//prints all occurrences of pattern in text
void FSM(string txt, string pat)
{
    int M = pat.size(); // length of pattern
    int N = txt.size(); // length of text
    auto tf = new int[M+1][total_chars]; // transaction function
    transaction_function(pat, M, tf); // call to calculate transaction function
    int i, state=0;
    for (i = 0; i < N; i++)
    {
        state = tf[state][txt[i]];
        if (state == M){
              //  cout << " ";
            //cout << "found at: " << i-M+1 << endl;
    }
    }
}

#endif // FSM_H_INCLUDED
