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
            // ͬ�в����лʺ�
            // ���ü�顣��Ϊÿ�λ��ݣ�ѡ��ͬһ�еĲ�ͬԪ��
    
            // ͬ�в����лʺ�
            for (int i = 0; i < row; i++) {
                if (chessboard[i][col] == 'Q')
                    return false;
            }
    
            // б�Խǲ����лʺ�
            // ��� 45�Ƚ��Ƿ��лʺ����ϣ�
            for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
                if (chessboard[i][j] == 'Q') {
                    return false;
                }
            }
            // ��� 135�Ƚ��Ƿ��лʺ����ϣ�
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