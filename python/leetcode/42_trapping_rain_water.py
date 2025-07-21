'''
We are first searching for water level ranges
Then we compute the height of each cell
'''


class Solution:
    def trap(self, height: list[int]) -> int:
        lres: list[int] = list()
        rres: list[int] = list()
        lmax = 0 
        rmax = 0

        for h in height:
            lmax = max(h, lmax)
            lres.append(lmax - h)

        for h in reversed(height):
            rmax = max(h, rmax)
            rres.append(rmax - h)

        return sum(min(x, y) for x, y in zip(lres, reversed(rres)))
        
s = Solution().trap([5, 0, 1, 2, 5, 1, 2])
print(s)

