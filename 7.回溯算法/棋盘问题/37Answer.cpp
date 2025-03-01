class Solution {
    public:
        bool backtracking(vector<vector<char>>& board) {
            for (int i = 0; i < board.size(); i++) {        // 遍历行
                for (int j = 0; j < board[0].size(); j++) { // 遍历列
                    if (board[i][j] == '.') {
                        for (char k = '1'; k <= '9'; k++) {
                            if (isValid(i, j, k, board)) {
                                board[i][j] = k;
                                if (backtracking(board)) {
                                    return true;
                                }
                                board[i][j] = '.';
                            }
                        }
                        return false;
                    }
                }
            }
            // 遍历完棋盘都没有return false，则true
            return true;
        }
        
        bool isValid(int row, int col, char val, vector<vector<char>>& board) {
            for (int i = 0; i < 9; i++) { // 判断行里是否重复
                if (board[row][i] == val) {
                    return false;
                }
            }
            for (int j = 0; j < 9; j++) { // 判断列里是否重复
                if (board[j][col] == val) {
                    return false;
                }
            }
            int startRow = (row / 3) * 3;
            int startCol = (col / 3) * 3;
            for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
                for (int j = startCol; j < startCol + 3; j++) {
                    if (board[i][j] == val) {
                        return false;
                    }
                }
            }
            return true;
        }
    
        void solveSudoku(vector<vector<char>>& board) { 
            backtracking(board); 
        }
    };