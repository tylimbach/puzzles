
/*
     3
 2  2
1  1  1 3
 3     2


1 1
1 

left = n, right =2 * n - 1
[1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1``
0
1 or 2
]
  
 2 ** (n) - 2 ** (n - 1)
*/

#include <vector>
namespace leetcode {

int numTreesRecursive(std::vector<int>& memo, int n)
{
	if (n == 0 || memo[n] != 0) return memo[n];

	int both = 0;
	for (int l = n - 1; l >= 0; l--) {
		int r = n - 1 - l;
		both += numTreesRecursive(memo, l) * numTreesRecursive(memo, r);
	}

	memo[n] = both;

	return memo[n];
}

inline int numTrees(int n) {
	std::vector<int> memo(static_cast<size_t>(n + 2), 0);
	memo[0] = 1;
	memo[1] = 1;
	memo[2] = 2;
	return numTreesRecursive(memo, n);
}


}
