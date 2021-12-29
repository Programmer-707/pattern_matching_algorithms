#ifndef RABIN_KARP_H_INCLUDED
#define RABIN_KARP_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>
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


#endif // RABIN_KARP_H_INCLUDED
