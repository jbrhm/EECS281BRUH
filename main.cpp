
// C++ program for implementation of KMP pattern searching
// algorithm
 
#include <bits/stdc++.h>
#include <iostream>
 
void computeLPSArray(char* pat, int M, int* lps);
 
// Prints occurrences of pat[] in txt[]
void KMPSearch(char* pat, char* txt, int* indices)
{
	int indiceIndex = 0;
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            printf("Found pattern at index %d \n", i - j);
			
			indices[indiceIndex] = i-j;
			++indiceIndex;
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}
 
// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
 

void filterString(char* txt, int subStrLen, int* indices){
	int strLength = strlen(txt);
	int leftIndex = 0;
	int rightIndex = 0;
	int indiceIndex = 0;
	while(rightIndex < strLength){
		if(rightIndex == indices[indiceIndex]){
			std::cout << "Skipping: " << rightIndex <<std::endl;
			rightIndex += subStrLen;
			++indiceIndex;
		}else{
			txt[leftIndex] = txt[rightIndex];
			++leftIndex;
			++rightIndex;
		}
	}
	txt[leftIndex] = '\0';
}
// Driver code
int main()
{
    char txt[] = "ABABDABACDABABCABABABABCABAB";

	std::cout << txt << std::endl;

	int indices[strlen(txt)];
	std::fill_n(indices, strlen(txt), -1);
    char pat[] = "ABABCABAB";

	std::cout << pat << " length: " << strlen(pat) << std::endl;

    KMPSearch(pat, txt, indices);
	filterString(txt, strlen(pat), indices);
	
	std::cout << txt << std::endl;

	

    return 0;
}

