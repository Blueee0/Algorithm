class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
        int offset = 1;     // 控制每一条边遍历的长度
        int loop = n / 2;   // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
        int mid = n / 2;    // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
        int count = 1;      // 用来给矩阵中每一个空格赋值
        int i,j;
        vector<vector<int>> results(n, vector<int>(n, 0)); // 使用vector定义一个二维数组
        while(loop --){
            i = startx;
            j = starty;
            for (j = starty; j < n - offset ; j++){
                results[i][j] = count ++ ;
            }
            for (i = startx; i < n - offset ; i++){
                results[i][j] = count ++ ;
            }
            for (;j > starty ; j--){
                results[i][j] = count ++ ;
            }
            for (;i > startx ; i--){
                results[i][j] = count ++ ;
            }
            startx ++ ;
            starty ++ ;
            offset ++ ;
        }
        if(n%2==1){
            results[mid][mid]=count;
        }
        return results;
    }
};