class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int startx = 0, starty = 0; // ����ÿѭ��һ��Ȧ����ʼλ��
        int offset = 1;     // ����ÿһ���߱����ĳ���
        int loop = n / 2;   // ÿ��Ȧѭ�����Σ�����nΪ����3����ôloop = 1 ֻ��ѭ��һȦ�������м��ֵ��Ҫ��������
        int mid = n / 2;    // �����м��λ�ã����磺nΪ3�� �м��λ�þ���(1��1)��nΪ5���м�λ��Ϊ(2, 2)
        int count = 1;      // ������������ÿһ���ո�ֵ
        int i,j;
        vector<vector<int>> results(n, vector<int>(n, 0)); // ʹ��vector����һ����ά����
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