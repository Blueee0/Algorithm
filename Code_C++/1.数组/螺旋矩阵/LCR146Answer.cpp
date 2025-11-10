class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        if (array.size() == 0 || array[0].size() == 0) {
            return {};
        }
        int rows = array.size(),columns = array[0].size();
        vector<int> result;
        int left = 0, right = columns -1, top = 0 , bottom = rows -1;
        int cnt = 0;
        while(left <= right && top <= bottom){
            for(int column = left; column <= right ; column++){
                result.push_back(array[top][column]);
            }
            for(int row = top + 1; row <=bottom ; row++){
                result.push_back(array[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    result.push_back(array[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    result.push_back(array[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return result;
    }
};