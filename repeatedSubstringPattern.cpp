#define ture true;
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
	bool repeatedSubstringPattern(string s) {
		int n = s.size();
		for (int i = 1; i <= n / 2; i++) {
			if (n % i == 0) {
				bool flag = true;
				for (int j = i; j < n; j++) {
					if (s[j] != s[j - i]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					return true;
				}
			}
		}
		return false;
	}
};
