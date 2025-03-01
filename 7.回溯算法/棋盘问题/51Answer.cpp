class Solution {
    public:
        vector<vector<string>> result;
    
        void backtracking(int n, int row, vector<string>& chessboard) {
            if (row == n) {
                result.push_back(chessboard);
                return;
            }
            for (int i = 0; i < n; i++) {
                if (isValid(row, i, n, chessboard)) {
                    chessboard[row][i] = 'Q';
                    backtracking(n, row + 1, chessboard);
                    chessboard[row][i] = '.';
                }
            }
        }
    
        bool isValid(int row, int col, int n, vector<string>& chessboard) {
            // 同行不能有皇后
            // 不用检查。因为每次回溯，选择同一行的不同元素
    
            // 同列不能有皇后
            for (int i = 0; i < row; i++) {
                if (chessboard[i][col] == 'Q')
                    return false;
            }
    
            // 斜对角不能有皇后
            // 检查 45度角是否有皇后（右上）
            for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
                if (chessboard[i][j] == 'Q') {
                    return false;
                }
            }
            // 检查 135度角是否有皇后（左上）
            for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
                if (chessboard[i][j] == 'Q') {
                    return false;
                }
            }
    
            return true;
        }
    
        vector<vector<string>> solveNQueens(int n) {
            result.clear();
            std::vector<std::string> chessboard(n, std::string(n, '.'));
            backtracking(n, 0, chessboard);
            return result;
        }
    };