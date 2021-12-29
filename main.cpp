#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <ctime>
#include <vector>

//#include "Rabin_Karp.h"
//#include "KMP.h"
//#include "Sunday.h"
//#include "FSM.h"
//#include "Brute_Force.h"

using namespace std;

//Brute Force
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

//FSM
#define total_chars 256
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

//KMP
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

//Rabin Karp
#define d 256

using namespace std;

void RabinKarp(string text, string pat, int x) {

  int M = pat.size();
  int N = text.size();
  int i, j;
  // hash values of pattern and text respectively
  int hash_p = 0, hash_t = 0;
  int h = 1;

  for (i = 0; i < M - 1; i++)
    h = (h * d) % x;  // d - const value length of characters

    //cout << "h: " << h << endl;
  // Calculate hash value for pattern and text
  for (i = 0; i < M; i++) {
    hash_p = (d * hash_p + pat[i]) % x;
    hash_t = (d * hash_t + text[i]) % x;
  }

  // Find the match
  for (i = 0; i <= N - M; i++) {
    if (hash_p == hash_t) {
      for (j = 0; j < M; j++) {
        if (text[i + j] != pat[j])
          break;
      }

      if (j == M){
          //  cout << " ";
        //cout << "found at: " << i + 1 << endl;
    }
    }
// here is the main part
//calculating new hash value of text string
// removing leading digit
//  adding trailing digit
    if (i < N - M) {
      hash_t = (d * (hash_t - text[i] * h) + text[i + M]) % x;

      if (hash_t < 0)
        hash_t = (hash_t + x);
    }
  }
}

//Sunday
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

string RandomString(int len)
{
   string str = "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   string newstr;
   int pos;
   while(newstr.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    newstr += str.substr(pos,1);
   }
   return newstr;
}

int main()
{
    srand(time(nullptr));
    int N = 10000;
    using chrono::nanoseconds;

    auto begin = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    //Write the header of CSV files
    ofstream dataFile("data.dat");
    dataFile << "Size,  Brute-Force,  Sunday,  Rabin-Karp,  FSM,   KMP ";
    dataFile<< "\n";

    // for random data
    nanoseconds total_brute_force(0), average_brute_force(0);
    nanoseconds total_sunday(0), average_sunday(0);
    nanoseconds total_rabin_karp(0), average_rabin_karp(0);
    nanoseconds total_FSM(0), average_FSM(0);
    nanoseconds total_KMP(0), average_KMP(0);
    int q = 101;

    cout << "Size\t\t Brute-Force\t\t Sunday\t\t Rabin-Karp\t\t FSM\t\t KMP" << endl;
    cout << "------------------------------------------------------------------------------------------------------------\n";
    for (int j=N; j<100000000; j+=700000)
    {
        string text = RandomString(j);
        string pat = "drtgh";

        for(int t = 0; t < 100; t++)
        {

            begin = std::chrono::steady_clock::now();

            search(text, pat);

            end = chrono::steady_clock::now();
            nanoseconds time_brute_force(end - begin);
            total_brute_force += time_brute_force;

            begin = std::chrono::steady_clock::now();

            sunday(text, pat);

            end = chrono::steady_clock::now();
            nanoseconds time_sunday(end - begin);
            total_sunday += time_sunday;

            begin = std::chrono::steady_clock::now();

            RabinKarp(text, pat, q);
            end = chrono::steady_clock::now();
            nanoseconds time_rabin_Karp(end - begin);
            total_rabin_karp += time_rabin_Karp;

            begin = std::chrono::steady_clock::now();

            FSM(text, pat);

            end = chrono::steady_clock::now();
            nanoseconds time_FSM(end - begin);
            total_FSM += time_FSM;

            begin = std::chrono::steady_clock::now();

            KMP(text, pat);

            end = chrono::steady_clock::now();
            nanoseconds time_KMP(end - begin);
            total_KMP += time_KMP;
        }

        // time for random data
        average_brute_force = total_brute_force/100;
        average_sunday= total_sunday/100;
        average_rabin_karp= total_rabin_karp/100;
        average_FSM= total_FSM/100;
        average_KMP= total_KMP/100;

        cout << j << " \t\t " << average_brute_force.count() << " \t\t " << average_sunday.count()<<  " \t\t "
             << average_rabin_karp.count() << " \t\t " << average_FSM.count() << " \t\t " << average_KMP.count() << endl;

             //Write the data to CSV file
             dataFile << j << "," << average_brute_force.count() << "," << average_sunday.count()<<  ","
             << average_rabin_karp.count() << "," << average_FSM.count() << "," << average_KMP.count();
             dataFile<< "\n";

    }
    dataFile.close();

    return 0;
}
