'''

for each square
put a queen there
then for each next square, we have a branch
add a queen or don't

this is backtracking

key realization - n queens and nxn board means each row has exactly 1 queen

base cases:
- no squares left
- n queens are placed -> add board

output should be a string
'''


class Solution:
    def solveNQueens(self, n: int) -> list[list[str]]:
        board: list[list[bool]] = [[False for _ in range(n)] for _ in range(n)]
        results: list[list[str]] = []
        self.solveNQueensR(n, 0, board, results)
        return results

    def solveNQueensR(
            self,
            n: int,
            row: int,
            board: list[list[bool]],
            results: list[list[str]]
    ) -> None:
        # print(self.boardToStrList(board))

        if row == n:
            results.append(self.boardToStrList(board))
            return

        for c in range(n):
            if self.canPlace(row, c, board):
                board[row][c] = True
                self.solveNQueensR(n, row + 1, board, results)
                board[row][c] = False

    def canPlace(self, row: int, col: int, board: list[list[bool]]) -> bool:
        lcol = rcol = col
        for r in reversed(range(0, row)):
            if board[r][col]:
                return False

            lcol = lcol - 1
            if lcol >= 0 and board[r][lcol]:
                return False

            rcol = rcol + 1
            if rcol < len(board) and board[r][rcol]:
                return False

        return True

    def boardToStrList(self, board: list[list[bool]]) -> list[str]:
        return ["".join("Q" if cell else "." for cell in row) for row in board]

    def test_boardToStrList(self):
        print(self.boardToStrList([[True, False, False], [False, True, False], [False, False, True]]))
        print(self.boardToStrList([[True, False, False]]))


x = Solution()
print(x.solveNQueens(4))

x.test_boardToStrList()


x = 5
x = --x
print(--x)
print(--x)
