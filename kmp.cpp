#include <iostream>
#include <vector>
using namespace std;

vector<int> getLps(string pattern) {
	int m = pattern.length();
	vector<int> lps(m, 0);
	
	int i = 1, j = 0;
	while (i < m) {
		if (pattern[i] == pattern[j]) {
			lps[i] = 1 + j;
			++i; ++j;
		} else {
			if (j == 0) {
				lps[i] = 0;
				++i;
			} else {
				j = lps[j - 1];
			}
		}
	}
	
	return lps;
}

void kmp(string text, string pattern) {
	vector<int> lps = getLps(pattern);
	
	int i = 0, j = 0;
	while (i < text.length()) {
		if (text[i] == pattern[j]) {
			++i; ++j;
		} else {
			if (j == 0) {
				++i;
			} else {
				j = lps[j - 1];
			}
		}
		
		if (j == pattern.length()) {
			cout << i - j << " ";
			j = lps[j - 1];
		}
	}
}


int main() {
	string text = "this is very misti";
	string pattern = "is"; // 2, 5, 14
	kmp(text, pattern);
	
	return 0;
}
