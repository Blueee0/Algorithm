# 代码随想录+Hot100

## 数组

数组下标都是从0开始的；数组内存空间的地址是连续的

### 移除元素（双指针）

- 快指针：寻找新数组的元素 ，新数组就是不含有目标元素的数组
- 慢指针：指向更新 新数组下标的位置

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 慢指针：更新下标；快指针：更新元素
        int slowIndex = 0, fastIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            // 如果值不相等（该元素需要保留），更新数组，更新慢指针
            if (nums[fastIndex] != val) {
                nums[slowIndex] = nums[fastIndex];
                slowIndex++;
            }
            // 如果值相等（该元素需要移除），不更新数组，慢指针不动，快指针++
        }
        return slowIndex; // 返回k（当前下标，即不同的值的个数）
    }
};
```



### 有序数组的平方（双指针）

数组平方的最大值就在数组的两端，两个指针指向两端，比较他们谁大，就更新到新数组的值。

```c++
class Solution {
public:
    // 新数组最右边的最大值，要么在nums最左边，要么在nums最右边
    // 双指针，指nums两端，i指最左，j指最右
    vector<int> sortedSquares(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;     // 两端的指针
        vector<int> result(nums.size(), 0); // result(大小，初始值)
        // k是 result 数组的下标，从最大往最小更新
        for (int k = nums.size() - 1; k >= 0; k--) {
            if (nums[i] * nums[i] <= nums[j] * nums[j]) {
                result[k] = nums[j] * nums[j];
                j--;
            } else {
                result[k] = nums[i] * nums[i];
                i++;
            }
        }
        return result;
    }
};
```



### 移动零（双指针）

- **问题**：给定一个数组 `nums`，编写一个函数将所有 `0` 移动到数组的末尾，同时保持非零元素的相对顺序。**请注意** ，必须在不复制数组的情况下原地对数组进行操作。

  ```
  输入: nums = [0,1,0,3,12]
  输出: [1,3,12,0,0]
  ```

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // 慢指针：更新下标；快指针：更新元素
        int slow = 0, fast = 0;
        for (fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != 0) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        while (slow > 0 && slow < nums.size()) {
            nums[slow++] = 0;
        }
    }
};
```



### 长度最小的子数组（滑动窗口）

- 窗口就是 满足其和 ≥ s 的长度最小的**连续**子数组。
- **窗口的起始位置如何移动**：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。
- **窗口的结束位置如何移动**：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // 滑动窗口：维持一个总和 ≥ target的滑动窗口
        int result = INT32_MAX;
        int i = 0;         // 滑动窗口的起始位置
        int sum = 0;       // 滑动窗口的总和
        int subLength = 0; // 满足条件的子数组的长度
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            // 出现满足条件的数组时，开始向右滑动
            while (sum >= target) {
                subLength = j - i + 1;
                if (subLength < result) {
                    result = subLength;
                }
                // 把起始位置的元素移出窗口
                sum -= nums[i];
                i++;
            }
        }
        if (result == INT32_MAX) {
            return 0;
        } else {
            return result;
        }
    }
};
```



### 无重复字符的最长子串（滑动窗口）

- **问题**：给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长 子串** 的长度。`s` 由英文字母、数字、符号和空格组成
- **解决**：滑动窗口+哈希表

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int slow = 0, fast = 0;
        int result = 0;
        unordered_map<char, int> umap;
        for (fast = 0; fast < s.size(); fast++) {
            umap[s[fast]]++;
            while (umap[s[fast]] > 1) {
                umap[s[slow]]--;
                slow++;
            }
            result = max(result, fast - slow + 1);
        }
        return result;
    }
};
```



### √最小覆盖子串（滑动窗口）

- **问题**：一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。
- **解决**：滑动窗口+哈希表

```c++
class Solution {
    bool is_covered(int cnt_s[128], int cnt_t[128]) {
        for (int i = 'A'; i <= 'Z'; i++) {
            if (cnt_s[i] < cnt_t[i]) {
                return false;
            }
        }
        for (int i = 'a'; i <= 'z'; i++) {
            if (cnt_s[i] < cnt_t[i]) {
                return false;
            }
        }
        return true;
    }
public:
    string minWindow(string s, string t) {
        int cnt_s[128]{}; // s 子串字母的出现次数
        int cnt_t[128]{}; // t 中字母的出现次数
        // 统计哈希表
        for (char c : t) {
            cnt_t[c]++;
        }
        // 维护滑动窗口
        int slow = 0, fast = 0;
        int minLength = INT_MAX;
        int begin = -1;
        while (fast < s.size()) {
            cnt_s[s[fast]]++;
            while (is_covered(cnt_s, cnt_t)) {
                if (fast - slow + 1 < minLength) {
                    minLength = fast - slow + 1;
                    begin = slow;
                }
                cnt_s[s[slow]]--;
                slow++;
            }
            fast++;
        }
        if (begin < 0) {
            return "";
        } else {
            return s.substr(begin, minLength);
        }
    }
};
```



### 多数元素—找众数（数学）

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};
```



### √只出现一次的元素—异或运算

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            // 注意i从1开始
            ans ^= nums[i];
        }
        return ans;
    }
};
```



### 螺旋矩阵（模拟）

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        int startx = 0, starty = 0; // 起始位置的横纵坐标
        int loop = n / 2;           // 循环圈数（比如n = 3，循环1次，如图）
        int mid = n / 2;            // 若n = 3，则(1,1)需要单独填充
        int count = 1;              // 填充数字，1 ~ n^2
        int offset = n - 1;         // 控制每条边遍历的长度
        int i, j;
        // 每次循环统一：左闭右开
        while (loop--) {
            i = startx;
            j = starty;
            // 注意：同一行是同一个i，所以先变的是j
            for (j; j < offset; j++) {
                result[i][j] = count++;
            }
            for (i; i < offset; i++) {
                result[i][j] = count++;
            }
            for (j; j > startx; j--) {
                result[i][j] = count++;
            }
            for (i; i > starty; i--) {
                result[i][j] = count++;
            }
            startx++;
            starty++;
            offset--;
        }
        if (n % 2 == 1) {
            result[mid][mid] = n * n;
        }
        return result;
    }
};
```



### 旋转图像（模拟）

- **问题**：给定一个 *n* × *n* 的二维矩阵 `matrix` 表示一个图像。请你将图像顺时针旋转 90 度。你必须在**[ 原地](https://baike.baidu.com/item/原地算法)** 旋转图像。
- **解决**：
  - **转置**：把主对角线下面的元素 `matrix[i][j]`和（关于主对角线）对称位置的元素 `matrix[j][i]`交换。
  - **行翻转**：遍历每一行 row=matrix[i]，把左半边的元素 row[j] 和（关于垂直中轴）对称位置的元素 row[n−1−j] 交换。或者，使用库函数翻转 row。

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // 第一步：转置
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) { // 遍历对角线下方元素
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        // 第二步：行翻转
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
```



### √汉明距离（模拟位运算）

- 模2取余，余数不等的即距离加一

```c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        // 模2取余 余数不等的即距离加一
        int ans = 0;
        while (x != 0 || y != 0) {
            if (x % 2 != y % 2) {
                ans++;
            }
            x /= 2;
            y /= 2;
        }
        return ans;
    }
};
```



### √比特位计数（模拟）十进制->二进制

- 整数 `n` ，对于 `0 <= i <= n` 中的每个 `i` ，计算其二进制表示中 **`1` 的个数** ，返回一个长度为 `n + 1` 的数组 `ans` 作为答案。
- 二进制的转换：对十进制数进行除以二，取其余数，循环求解，直至商为0为止。

```c++
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1);
        for (int i = 0; i <= n; i++) {
            int m = i;
            while (m) {
                if (m % 2 == 1) {
                    ans[i]++;
                }
                m /= 2;
            }
        }
        return ans;
    }
};
```



### √区间和（前缀和）

前缀和的思想是重复利用计算过的子数组之和，从而降低区间查询需要累加计算的次数。

```c++
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, a, b;
    cin >> n;
    vector<int> vec(n);
    vector<int> p(n);
    int presum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &vec[i]);
        presum += vec[i];
        p[i] = presum;
    }

    while (~scanf("%d%d", &a, &b)) {
        int sum;
        if (a == 0) sum = p[b];
        else sum = p[b] - p[a - 1];
        printf("%d\n", sum);
    }
}
```



### 除自身以外数组的乘积（前缀和）

- 问题：给你一个整数数组 `nums`，返回 数组 `answer` ，其中 `answer[i]` 等于 `nums` 中除 `nums[i]` 之外其余各元素的乘积 。
- 解决：
  - 定义 *pre*[*i*] 表示从 *nums*[0] 到 *nums*[*i*−1] 的乘积。`pre[i]=pre[i−1]⋅nums[i−1]`
  - 定义 *suf*[*i*] 表示从 *nums*[*i*+1] 到 *nums*[*n*−1] 的乘积。`suf[i]=suf[i+1]⋅nums[i+1]`
  - 初始值：*pre*[0]=*suf*[*n*−1]=1；结果：*answer*[*i*]=*pre*[*i*]⋅*suf*[*i*]

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> pre(nums.size(), 1); // [0,i-1]
        vector<int> suf(nums.size(), 1); // [i+1,n-1]
        for (int i = 1; i < nums.size(); i++) {
            pre[i] = pre[i - 1] * nums[i - 1];
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] * nums[i + 1];
        }
        vector<int> ans(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            ans[i] = pre[i] * suf[i];
        }
        return ans;
    }
};
```



### *和为k的子数组（前缀和）

- 前缀和+哈希表

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> Sum(nums.size() + 1);
        for (int i = 0; i < nums.size(); i++) {
            Sum[i + 1] = Sum[i] + nums[i];
        }
        int ans = 0;
        unordered_map<int, int> umap;
        for (int s : Sum) {
            if (umap.contains(s - k)) {
                ans += umap[s - k];
            }
            umap[s]++;
        }
        return ans;
    }
};
```



### 下一个排列

- **题意**：`arr = [1,2,3]` ，以下这些都可以视作 `arr` 的排列：`[1,2,3]`、`[1,3,2]`、`[3,1,2]`、`[2,3,1]` 。整数数组的 **下一个排列** 是指其整数的下一个字典序更大的排列。给你一个整数数组 `nums` ，找出 `nums` 的下一个排列。必须**原地**修改，只允许使用额外常数空间。

  ```
  输入：nums = [1,2,3]
  输出：[1,3,2]
  ```

- 解决：

  ```
  问：排列 [1,3,5,4,2] 的下一个排列是什么？
  如果 1,3,5 保持不变，只重新排列 4,2，得到 2,4。排列变小了，这不行。
  如果 1,3 保持不变，只重新排列 5,4,2，由于 5 右边都是小于 5 的数，所以重排后，5 这个位置上的数必然变小，导致排列变小，这也不行。
  如果 1 保持不变，只重新排列 3,5,4,2，这是可以的，因为 3 右边有比 3 大的数，重排后可以让 3 这个位置上的数变大，从而得到更大的排列。
  由于要求的是下一个排列，所以 3 这个位置上的数只要「大一点点」就好了。找到 3 右边最小的大于 3 的数，也就是 4，放到 3 这个位置上。于是，下一个排列是 [1,4,_,_,_]。
  剩余的三个数是 2,3,5。由于只看前两位 [1,4,_,_,_] 就已经比 [1,3,5,4,2] 大了，所以后三位填最小的排列就行，即按照 2,3,5 的顺序填，得到 [1,4,2,3,5]。
  ```

  - **从右向左，找第一个数字 x，满足 x 右边有大于 x 的数**，这样可以把 x 变大。我们找到的数是 3。注意到，3 右边的数是递减的（证明见答疑），所以 3 右侧相邻数字就是 3 右边最大的数。如果 3 右侧相邻数字小于 3，那么 3 右边必然没有大于 3 的数。因此，这一步可以简化为，从右向左，找第一个小于右侧相邻数字的数 x。
  - **找 3 右边最小的大于 3 的数，即 4**。由于 3 右边的数是递减的，所以从右向左找到的第一个大于 3 的数，就是 3 右边最小的大于 3 的数。然后把 4 放到 3 的位置上，把 3 放到右边的三个位置中。这一步可以简化为交换 3 和 4。交换后得到 [1,4,5,3,2]。注意交换后 5,4,2 变成 5,3,2，仍然是递减的（证明见答疑）。
  - **把 4 右边的数从小到大排序。**由于第二步交换后，4 右边的数 5,3,2 是递减的，所以只需要把 5,3,2 反转，就得到了答案 [1,4,2,3,5]。

```c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        // 1. 从右向左，找第一个小于右侧相邻数字的数 x
        int x = -1;
        for (int i = n - 1; i > 0; i--) {
            if (nums[i - 1] < nums[i]) {
                x = i - 1;
                break;
            }
        }
        if (x == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        // 2. 找 x 右边最小的大于 x 的数 y，交换 x 和 y
        // x右侧递减，所以从右向左找
        int y = n - 1;
        for (int i = n - 1; i > x; i--) {
            if (nums[i] > nums[x]) {
                y = i;
                break;
            }
        }
        swap(nums[x], nums[y]);
        // 3. 反转 下标x 右边的数，把右边的数变成最小的排列
        reverse(nums.begin() + x + 1, nums.end());
    }
};
```



## √搜索算法

### 二分查找

- `while (left <= right)` 要使用 <= ，因为left == right是有意义的，所以使用 <=
- `if (nums[middle] > target) right` 要赋值为 middle - 1，因为当前这个nums[middle]一定不是target，那么接下来要查找的左区间结束下标位置就是 middle - 1

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 定义区间[left, right]
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) { // 因为left == right 有意义
            int middle = (left + right) / 2;
            if(nums[middle] > target){
                right = middle -1;  // 必须-1，因为nums[middle] != target
            }else if(nums[middle] < target){
                left = middle +1;
            }else{  // nums[middle] = target
                return middle;
            }
        }
        return -1;
    }
};
```



### 在排序数组中查找元素的第一个和最后一个位置（二分法）

- 问题：按照非递减顺序排列的整数数组 `nums`，目标值 `target`。找出`target`在数组中的开始位置和结束位置。如果数组中不存在目标值 `target`，返回 `[-1, -1]`。时间复杂度为 `O(log n)` 的算法。

```c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        vector<int> result(2, -1);
        while (left <= right) {
            int mid = (left + right) / 2;
            if (target > nums[mid]) {
                left = mid + 1;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else { // nums[mid] == target
                int l_val = mid, r_val = mid;
                while (l_val > 0 && nums[l_val - 1] == target) {
                    l_val--;
                }
                while (r_val < nums.size() - 1 && nums[r_val + 1] == target) {
                    r_val++;
                }
                result[0] = l_val;
                result[1] = r_val;
                return result;
            }
        }
        return result;
    }
};
```



### *寻找两个正序数组的中位数（二分查找）

- **问题**：给定两个大小分别为 `m` 和 `n` 的正序（从小到大）数组 `nums1` 和 `nums2`。请你找出并返回这两个正序数组的 **中位数** 。算法的时间复杂度应该为 `O(log (m+n))` 。

  ```
  输入：nums1 = [1,3], nums2 = [2]
  输出：2.00000
  解释：合并数组 = [1,2,3] ，中位数 2
  ```

- 中位数可将数值集合**划分**为**大小相等**的两部分

  - **初始化 *i*=0，那么 *j* 应该初始化成多少？**
  - 如果 $m + n$ 是偶数，那么每组的大小为 $\frac{m + n}{2}$，$j$ 应当初始化成 $\frac{m + n}{2}$。
  - 如果 $m + n$ 是奇数，我们规定第一组比第二组多一个数，第一组的大小为 $\frac{m + n + 1}{2}$，$j$ 应当初始化成 $\frac{m + n + 1}{2}$。

  两种情况可以合并为：$j$ 初始化成 $\left\lfloor \frac{m + n + 1}{2} \right\rfloor$。

  - *i* 的含义变成了 *a* 有 *i*+1 个数在第一组，*j* 的含义变成了 *b* 有 *j*+1 个数在第一组。则上述关系修改为：

  $$
  j + 1 = \left\lfloor \frac{m + n + 1}{2} \right\rfloor - (i + 1)
  $$

- 算法步骤

  - 设 *a* 的 *b* 的长度分别为 *m* 和 *n*，且 *m*≤*n*（如果不满足则交换两个数组）。
  -  *a* 有 *i*+1 个数在第一组， *b* 有 *j*+1 个数在第一组，利用二分法找到满足条件的i、j
  - 根据图片中的结论，只要发现**第一组的最大值≤第二组的最小值**，即 $a_i \leq b_{j+1}$ 且 $a_{i+1} > b_j$，那么：

    - 如果 $m + n$ 是偶数，中位数为 $\max(a_i, b_j)$ 和 $\min(a_{i+1}, b_{j+1})$ 的平均值。
    - 如果 $m + n$ 是奇数，中位数为 $\max(a_i, b_j)$。

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b);
        }

        int m = a.size(), n = b.size();
        // 循环不变量：a[left] <= b[j+1]
        // 循环不变量：a[right] > b[j+1]
        int left = -1, right = m;
        while (left + 1 < right) { // 开区间 (left, right) 不为空
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i - 2;
            if (a[i] <= b[j + 1]) {
                left = i; // 缩小二分区间为 (i, right)
            } else {
                right = i; // 缩小二分区间为 (left, i)
            }
        }

        // 此时 left 等于 right-1
        // a[left] <= b[j+1] 且 a[right] > b[j'+1] = b[j]，所以答案是 i=left
        int i = left;
        int j = (m + n + 1) / 2 - i - 2;
        int ai = i >= 0 ? a[i] : INT_MIN;
        int bj = j >= 0 ? b[j] : INT_MIN;
        int ai1 = i + 1 < m ? a[i + 1] : INT_MAX;
        int bj1 = j + 1 < n ? b[j + 1] : INT_MAX;
        int max1 = max(ai, bj);
        int min2 = min(ai1, bj1);
        return (m + n) % 2 ? max1 : (max1 + min2) / 2.0;
    }
};
```



### 搜索二维矩阵II（二分查找）

- **题目**：编写一个高效的算法来搜索 `m x n` 矩阵 `matrix` 中的一个目标值 `target` 。该矩阵具有以下特性：
  - 每行的元素从左到右升序排列。
  - 每列的元素从上到下升序排列。

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int i = 0, j = n - 1;     // 从右上角开始
        while (i < m && j >= 0) { // 还有剩余元素
            if (matrix[i][j] == target) {
                return true; // 找到 target
            }
            if (matrix[i][j] < target) {
                i++; // 这一行剩余元素全部小于 target，排除
            } else {
                j--; // 这一列剩余元素全部大于 target，排除
            }
        }
        return false;
    }
};
```



### 寻找重复数（二分查找）

- **题目**：给定一个包含 `n + 1` 个整数的数组 `nums` ，其数字都在 `[1, n]` 范围内（包括 `1` 和 `n`），可知至少存在一个重复的整数。假设 `nums` 只有 **一个重复的整数** ，返回 **这个重复的数** 。

- **解决**：因为在区间 [1,n] 内存在重复的数。所以，先累计大小在 $\left[1, \left\lfloor \frac{n}{2} \right\rfloor \right]$之间的数字个数，如果重复数在这个范围内，则$$ 个数 > \left\lfloor \frac{n}{2} \right\rfloor $$，否则可确定区间$$\left\lfloor \frac{n}{2} \right\rfloor, n]$$内存在重复数。

```c++
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int min = 1;
        int max = nums.size();
        while (min < max) {
            int mid = (min + max) / 2;
            int cnt = 0;
            // 统计个数
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] >= min && nums[i] <= mid) {
                    cnt++;
                }
            }
            // 二分
            if (cnt > mid - min + 1) {
                max = mid;
            } else {
                min = mid + 1;
            }
        }
        return min;
    }
};
```



### 搜索旋转排序数组（二分法）

- **问题**：整数数组 `nums` 按升序排列，数组中的值 **互不相同** 。现对数组进行右旋，比如 `[0,1,2,4,5,6,7]` 在下标 `3` 处经旋转后变为 `[4,5,6,7,0,1,2]` 。给你 **旋转后** 的数组 `nums` 和一个整数 `target` ，如果 `nums` 中存在这个目标值 `target` ，则返回它的下标，否则返回 `-1` 。

- **解决**：

  设 `x = nums[mid]` 是我们现在二分取到的数，讨论 *x* 和 *target* 是否在不同的递增段

  - 如果 x 和 target 在不同的递增段：
    - 如果 target 在第一段（左），x 在第二段（右）；`target > nums[n - 1] && x <= nums[n - 1]`，更新`right`
    - 如果 target 在第二段（右），x 在第一段（左）。`target <= nums[n - 1] && x > nums[n - 1]`，更新`left`
  - 如果 x 和 target 在相同的递增段：
    - 比较 x 和 target 的大小即可。


```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (target > nums[n - 1] && nums[mid] <= nums[n - 1]) {
                // 目标在右半部分，mid在左半部分
                right = mid;
            } else if (target <= nums[n - 1] && nums[mid] > nums[n - 1]) {
                // 目标在左半部分，mid在右半部分
                left = mid + 1;
            } else {
                // 目标和mid在同一部分
                if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
        }
        return nums[left] == target ? left : -1;
    }
};
```



### 数组的第k个最大元素（快速选择算法）

- 问题：给定整数数组 `nums` 和整数 `k`，请返回数组中第 `k` 个最大的元素。设计并实现时间复杂度为 `O(n)` 的算法解决此问题。
- 解决：快排

```c++
class Solution {
public:
    int quickSelect(vector<int>& nums, int k) {
        // 随机选择基准数
        int pivot = nums[rand() % nums.size()];
        // 将大于、小于、等于 pivot 的元素划分至 big, small, equal 中
        vector<int> big, equal, small;
        for (int num : nums) {
            if (num > pivot)
                big.push_back(num);
            else if (num < pivot)
                small.push_back(num);
            else
                equal.push_back(num);
        }
        // 第 k 大元素在 big 中，递归划分
        if (k <= big.size())
            return quickSelect(big, k);
        // 第 k 大元素在 small 中，递归划分
        if (nums.size() - small.size() < k)
            return quickSelect(small, k - nums.size() + small.size());
        // 第 k 大元素在 equal 中，直接返回 pivot
        return pivot;
    }
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, k);
    }
};
```



### 颜色分类（插入排序）

- **问题**：给定一个包含红色、白色和蓝色、共 `n` 个元素的数组 `nums` ，**[原地](https://baike.baidu.com/item/原地算法)** 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。我们使用整数 `0`、 `1` 和 `2` 分别表示红色、白色和蓝色。
- 插入排序：
  - 维护 *a* 中 0 的个数，即为改成 0 的位置，记作 $p_0$。
  - 维护 *a* 中 0 和 1 的个数，即为改成 1 的位置，记作$p_1$。
  - 末尾新增的位置记作 *i*，把 *a*[*i*] 改成 2。
  - **注意**：先插入2，然后分类讨论覆盖p1和p0

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) {
                nums[p1] = 1;
                p1++;   // p1 = 0个数+1个数
            }
            if (x == 0) {
                nums[p0] = 0;
                p0++;   // p0 = 0个数
            }
        }
    }
};
```



## √链表

数组是在内存中是连续分布的，但是链表在内存中可不是连续分布的

```c++
class MyLinkedList {
public:
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int val) : val(val), next(nullptr) {}
    };
	
    // 初始化链表
    MyLinkedList() {
        _dummyHead = new LinkedNode(0);
        _size = 0;
    }

    // 获取链表中下标为 index 的节点的值
    int get(int index) {
        if (index > (_size - 1) || index < 0)
            return -1;
        LinkedNode* cur = _dummyHead->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }

    // 将一个值为 val 的节点插入到链表中第一个元素之前
    void addAtHead(int val) {
        LinkedNode* newNode = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;
    }

    // 将一个值为 val 的节点追加到链表中作为链表的最后一个元素
    void addAtTail(int val) {
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead; // 注意从头结点开始添加
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }

    // 将一个值为 val 的节点插入到链表中下标为 index 的节点之前
    void addAtIndex(int index, int val) {
        if (index > _size) {
            return;
        }
        if (index < 0) {
            index = 0;
        }
        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        }
        LinkedNode* cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp = nullptr;
        _size--;
    }

private:
    int _size;
    LinkedNode* _dummyHead;
};

```



### √LRU缓存（双向链表）

- `LRUCache(int capacity)` 以 **正整数** 作为容量 `capacity` 初始化 LRU 缓存
- `int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。
- `void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 **逐出** 最久未使用的关键字。

```c++
class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LRUCache {
private:
    int capacity;
    Node* dummy; // 哨兵节点
    unordered_map<int, Node*> key_to_node;

    // 删除一个节点（抽出一本书）
    void remove(Node* x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    // 在链表头添加一个节点（把一本书放到最上面）
    void push_front(Node* x) {
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    // 获取 key 对应的节点，同时把该节点移到链表头部
    Node* get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) { // 没有这本书
            return nullptr;
        }
        Node* node = it->second; // 有这本书
        remove(node);            // 把这本书抽出来
        push_front(node);        // 放到最上面
        return node;
    }

public:
    LRUCache(int capacity) : capacity(capacity), dummy(new Node()) {
        dummy->prev = dummy;
        dummy->next = dummy;
    }
    int get(int key) {
        Node* node = get_node(key); // get_node 会把对应节点移到链表头部
        return node ? node->value : -1;
    }
    void put(int key, int value) {
        Node* node = get_node(key); // get_node 会把对应节点移到链表头部
        if (node) {                 // 有这本书
            node->value = value;    // 更新 value
            return;
        }
        key_to_node[key] = node = new Node(key, value); // 新书
        push_front(node);                               // 放到最上面
        if (key_to_node.size() > capacity) {            // 书太多了
            Node* back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node); // 去掉最后一本书
            delete back_node;  // 释放内存
        }
    }
};
```



### 移除链表元素 

设置一个虚拟头结点，再进行移除节点操作

```c++
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* cur = dummyHead;
        while (cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
};
```



### 两数相加

- 有一个不是空节点，或者还有进位，就继续迭代

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;
        int carry = 0; // 进位
        
        // 有一个不是空节点，或者还有进位，就继续迭代
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            if (l1 != nullptr) {
                carry += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                carry += l2->val;
                l2 = l2->next;
            }
            cur->next = new ListNode(carry % 10); // 每个节点保存一个数位
            cur = cur->next;
            carry /= 10; // 新的进位
        }
        return dummyHead->next;
    }
};
```



### 合并两个有序链表

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;
        
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                cur->next = new ListNode(list1->val);
                list1 = list1->next;
            } else {
                cur->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if (list1 != nullptr) {
            cur->next = list1;
        } else {
            cur->next = list2;
        }
        return dummyHead->next;
    }
};
```



### 合并k个升序链表

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                cur->next = new ListNode(list1->val);
                list1 = list1->next;
            } else {
                cur->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if (list1 != nullptr) {
            cur->next = list1;
        } else {
            cur->next = list2;
        }
        return dummyHead->next;
    }

    ListNode* merge(vector<ListNode*>& lists, int left, int right) {
        if (left == right)
            return lists[left];
        if (left > right)
            return nullptr;
        int mid = (left + right) / 2;
        return mergeTwoLists(merge(lists, left, mid), merge(lists, mid + 1, right));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};
```



### 排序链表

```c++
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* pre = head;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            pre = slow; // 记录 slow 的前一个节点
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr; // 断开 slow 的前一个节点和 slow 的连接
        return slow;
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                cur->next = new ListNode(list1->val);
                list1 = list1->next;
            } else {
                cur->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if (list1 != nullptr) {
            cur->next = list1;
        } else {
            cur->next = list2;
        }
        return dummyHead->next;
    }

    ListNode* sortList(ListNode* head) {
        // 如果链表为空或者只有一个节点，无需排序
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 找到中间节点 midNode，并断开 midNode 与其前一个节点的连接
        ListNode* midNode = middleNode(head);
        // 分治
        head = sortList(head);
        midNode = sortList(midNode);
        // 合并
        return mergeTwoLists(head, midNode);
    }
};
```



### 反转链表

- 双指针，逐个反转

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        ListNode* tmp = cur;
        while (cur != nullptr) {
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};
```



### 回文链表

1. 复制链表值到数组列表中。
2. 使用双指针法判断是否为回文。

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> res;
        while (head != nullptr) {
            res.emplace_back(head->val);
            head = head->next;
        }
        int start = 0;
        int end = res.size() - 1;
        while (start < end) {
            if (res[start] != res[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
};
```



### 两两交换链表中的节点

```c++
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* _dummyHead = new ListNode(0);
        _dummyHead->next = head;
        ListNode* cur = _dummyHead;
        while (cur->next != nullptr && cur->next->next != nullptr) {
            // A--B*--C--D*
            ListNode* tmp1 = cur->next;
            ListNode* tmp2 = cur->next->next->next;
            // 第一步：A接C
            cur->next = cur->next->next;
            // 第二步：C接B
            cur = cur->next;
            cur->next = tmp1;
            // 第三步：B接D
            cur = cur->next;
            cur->next = tmp2;
        }
        return _dummyHead->next;
    }
};
```



### 删除链表倒数第N个节点（双指针）

如果要删除倒数第n个节点，让fast移动n步，然后让fast和slow同时移动，直到fast指向链表末尾。删掉slow所指向的节点就可以了。

**fast提前走一步，则slow会移动到需要删除的节点的前一个节点。**

```c++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* fast = dummyHead;
        ListNode* slow = dummyHead;
        while (n-- && fast != nullptr) {
            fast = fast->next;
        }
        // 注意：fast再提前走一步，因为需要让slow指向删除节点的上一个节点
        fast = fast->next; 
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;
        return dummyHead->next;
    }
};
```



### 链表相交

- 先求出两个链表的长度，并求出两个链表长度的差值（让A为最长的那条链）
- 让curA移动到，和curB 末尾对齐的位置，向后比较curA和curB，如果遇到curA == curB，则找到交点
- 注意：计算完长度后，需要重新初始化curA和curB

```c++
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;
        int lenA = 0, lenB = 0;
        while (curA != nullptr) {
            lenA++;
            curA = curA->next;
        }
        while (curB != nullptr) {
            lenB++;
            curB = curB->next;
        }
        // !计算完长度后，重新初始化curA和curB
        curA = headA;
        curB = headB;
        if (lenB > lenA) {
            swap(lenA, lenB);
            swap(curA, curB);
        }
        int gap = lenA - lenB;
        while (gap--) {
            curA = curA->next;
        }
        while (curA != nullptr) {
            if (curA == curB) {
                return curA;
            } else {
                curA = curA->next;
                curB = curB->next;
            }
        }
        return nullptr;
    }
};
```



### 环形链表

- 判断是否有环

  可以使用快慢指针法，分别定义 fast 和 slow 指针，从头结点出发，fast指针每次移动两个节点，slow指针每次移动一个节点，如果 fast 和 slow指针在途中相遇 ，说明这个链表有环。

- 如何找到环的入口


​	**从头结点出发一个指针，从相遇节点 也出发一个指针，这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是 环形入口的节点**。

```c++
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        // fast 走得快，要用fast作为while循环的边界
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) {
                ListNode* index1 = head;
                ListNode* index2 = slow;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2;
            }
        }
        return nullptr;
    }
};
```





## √哈希表

**需要快速判断一个元素是否出现集合里的时候，就要考虑哈希法**

数组：数值较小，比如字母26个。

```c++
int hash[26] = {0};
```

set：数值比较分散

```c++
unordered_set<int> nums1_set(nums1.begin(), nums1.end());
for (int i = 0; i < nums2.size(); i++) {
    if (nums1_set.find(nums2[i]) != nums1_set.end()) {
        result.insert(nums2[i]);
    }
}
```

map：需要使用 key - value结构来存放，key存**元素（查找对象）**，value存**元素的下标**。

```c++
unordered_map<int, int> map;
for (int i = 0; i < nums.size(); i++) {
// 如果在map中找到了和target配对的另一个数，即target-nums[i]，则返回
if (map.find(target - nums[i]) != map.end()) {
    return {map[target - nums[i]], i};;
}
map[nums[i]] = i;
}
```



### 有效的字母异位词（int数组）

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        int hash[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            hash[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (hash[i] != 0) {
                return false;
            }
        }
        return true;
    }
};
```



### 找到字符串中的所有字母异位词（`vector<int>`数组，滑动窗口）

- 使用`vector<int>`可以直接比较两个哈希表是否相同

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();
        if (sLen < pLen) {
            return {};
        }
        vector<int> result;
        vector<int> sCount(26, 0);
        vector<int> pCount(26, 0);
        for (int i = 0; i < p.size(); i++) {
            sCount[s[i] - 'a']++;
            pCount[p[i] - 'a']++;
        }
        if (sCount == pCount) {
            result.push_back(0);
        }
        for (int i = 0; i < sLen - pLen; i++) {
            sCount[s[i] - 'a']--;
            sCount[s[i + pLen] - 'a']++;
            if (sCount == pCount) {
                result.push_back(i + 1);
            }
        }
        return result;
    }
};
```



### 字母异位词分组（map）

- 当且仅当两个字符串排序后一样，这两个字符串才能分到同一组
- 用`unordered_map`来分组，把排序后的字符串当作 key，原字符串组成的列表（即答案）当作 value。

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string s : strs) {
            string sorted_s = s;
            sort(sorted_s.begin(), sorted_s.end());
            map[sorted_s].push_back(s);
        }
        vector<vector<string>> ans;
        ans.reserve(map.size()); // 预分配空间
        for (auto [key, value] : map) {
            ans.push_back(value);
        }
        return ans;
    }
};
```



### 两个数组的交集

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> nums1_set(nums1.begin(), nums1.end());
        unordered_set<int> result;
        for (int i = 0; i < nums2.size(); i++) {
            if (nums1_set.find(nums2[i]) != nums1_set.end()) {
                result.insert(nums2[i]);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
```



### 找到数组中所有消失的数字

- 一个含 `n` 个整数的数组 `nums` ，其中 `nums[i]` 在区间 `[1, n]` 内。找出所有在 `[1, n]` 范围内但没有出现在 `nums` 中的数字。

```c++
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<int> hash(n + 1, 1);
        vector<int> result;
        
        for (int num : nums) {
            hash[num] = 0; // 标记出现过的数字
        }

        for (int i = 1; i <= nums.size(); i++) {
            if (hash[i] == 1) {
                result.push_back(i);
            }
        }
        return result;
    }
};
```



### 最长连续序列

- **问题**：给定一个未排序的整数数组 `nums` ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。请你设计并实现时间复杂度为 `O(n)` 的算法解决此问题。

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (int x : st) { // 遍历哈希集合
            // 以 x−1 为起点计算出的序列长度，一定比以 x 为起点计算出的序列长度要长！
            if (st.contains(x - 1)) {
                continue;
            }
            // x 是序列的起点
            int y = x + 1;
            while (st.contains(y)) { // 不断查找下一个数是否在哈希集合中
                y++;
            }
            // 循环结束后，y-1 是最后一个在哈希集合中的数
            ans = max(ans, y - x);
        }
        return ans;
    }
};
```



### 快乐数

**「快乐数」** 定义为：

- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
- 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
- 如果这个过程 **结果为** 1，那么这个数就是快乐数。

题目中说了会 **无限循环**，那么也就是说**求和的过程中，sum会重复出现**

所以，使用`unordered_set<int> set`来记录出现过的sum，如果这个sum曾经出现过，说明已经陷入了无限循环了，立刻return false

```c++
class Solution {
public:
    // 求各个位上的单数平方之和
    int getSum(int n) {
        int sum = 0;
        while (n != 0) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> set;
        while (1) {
            int sum = getSum(n);
            if (sum == 1)
                return true;
            if (set.find(sum) != set.end()) {
                return false;
            } else {
                set.insert(sum);
            }
            n = sum;
        }
    }
};
```



### 两数之和

- 为什么会想到用哈希表：需要存下遍历过的元素，然后在遍历过的元素中，查找对应的元素`target-nums[i]`
- 哈希表为什么用map：需要存放两个元素，key来存元素（查找对象），value来存下标。
- 本题map是用来存什么的：用来存放遍历过的元素
- map中的key和value用来存什么的：key存元素，value存下标

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            // 如果在map中找到了和target配对的另一个数，即target-nums[i]，则返回
            if (map.find(target - nums[i]) != map.end()) {
                return {map[target - nums[i]], i};;
            }
            map[nums[i]] = i;
        }
        return {};
    }
};
```



### **四数相加**

- 四个整数数组 `nums1`、`nums2`、`nums3` 和 `nums4` ，数组长度都是 `n` ，计算有多少个元组 `(i, j, k, l)` 满足：`nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`

```c++
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        // key:a+b的数值，value:a+b数值出现的次数
        // 先统计nums1和nums2所有和的情况
        unordered_map<int, int> map;
        for (int a : A) {
            for (int b : B) {
                map[a + b]++;
            }
        }
        int cnt = 0; // 统计a+b+c+d = 0 出现的次数
        for (int c : C) {
            for (int d : D) {
                if (map.find(0 - (c + d)) != map.end()) {
                    cnt += map[0 - (c + d)];
                }
            }
        }
        return cnt;
    }
};
```



### 三数之和（双指针法）

- 在一个数组中找到3个数形成的三元组，它们的和为0，不能重复使用（三数下标互不相同），且三元组不能重复。
- 首先，`sort(nums.begin(), nums.end())`，然后left 定义在i+1的位置上，定义下标right在数组结尾的位置，移动left和right，直到left与right相遇。
  - `a = nums[i]`，`b = nums[left]`，`c = nums[right]`
  - 如果`nums[i] + nums[left] + nums[right] > 0` ，则right下标就应该向左移动。
  - 如果`nums[i] + nums[left] + nums[right] < 0` ，则left 就向右移动。
- 去重情况：
  - 如果a是正数，a<b<c，不可能形成和为0的三元组
  - 如果本轮a和上轮a相同，那么找到的b，c也是相同的，所以去重a
  - 去重逻辑应该放在找到一个三元组之后，对b 和 c去重

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            // 如果a是正数，a<b<c，不可能形成和为0的三元组
            if (nums[i] > 0)
                break;

            // 如果本轮a和上轮a相同，那么找到的b，c也是相同的，所以去重a
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            // a = nums[i], b = nums[left], c = nums[right]
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1])
                        right--;
                    while (right > left && nums[left] == nums[left + 1])
                        left++;
                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};
```



### 四数之和（双指针法）

- 固定两次的过程中都需要去重，一共去重4次，此外，在收获结果后再去重

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > target && nums[i] >= 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] > target && nums[i] + nums[j] >= 0) {
                    break;
                }
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target) {
                        right--;
                    } else if ((long)nums[i] + nums[j] + nums[left] + nums[right] < target) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[right] == nums[right - 1])
                            right--;
                        while (left < right && nums[left] == nums[left + 1])
                            left++;
                        right--;
                        left++;
                    }
                }
            }
        }
        return result;
    }
};
```



## √字符串

### 反转字符串（双指针）

```c++
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0, j = s.size() - 1; i <= j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
};
```



### 反转字符串II（前k个）

1. 每隔 2k 个字符的前 k 个字符进行反转
2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
3. 剩余字符少于 k 个，则将剩余字符全部反转

```c++
class Solution {
public:
    void reverse(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += (2 * k)) {
            if (i + k <= s.size()) {
                reverse(s, i, i + k - 1);
                continue;
            }
            reverse(s, i, s.size() - 1);
        }
        return s;
    }
};
```



### 翻转字符串里的单词（双指针）

- 移除多余空格（输入字符串 `s`中可能会存在前导空格、尾随空格或者单词间的多个空格）——快慢指针
- 将整个字符串反转
- 将每个单词反转

```c++
class Solution {
public:
    // 翻转字符串
    void reserve(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    // 去除所有空格并在相邻单词之间添加空格——快慢指针
    void removeExtraSpaces(string& s) {
        int slow = 0; // 记录去除多余空格后的字符串长度
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                if (slow != 0) {
                    // 如果slow!=0，即不是第一个单词，单词之间需要加空格
                    s[slow++] = ' ';
                }
                while (i < s.size() && s[i] != ' ') {
                    // 补全单词
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow);
    }

    string reverseWords(string s) {
        removeExtraSpaces(s);
        reserve(s, 0, s.size() - 1);
        int start = 0;
        // 注意i从0到s.size()，才能处理到最后一个单词
        for (int i = 0; i <= s.size(); i++) {
            if (i == s.size() || s[i] == ' ') {
                reserve(s, start, i - 1);
                start = i + 1;
            }
        }
        return s;
    }
};
```



### 右旋转字符串

- 先对字符串整体翻转
- 再对两个子串里的的字符在翻转

```c++
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    int len = s.size();
    reverse(s.begin(),s.end());
    reverse(s.begin(), s.begin() + n); 
    reverse(s.begin() + n, s.end());
    cout << s;
    return 0;
}
```



### √*KMP算法—字符串匹配算法

- **字符串匹配类题目**：文本串中是否出现过模式串。
- **KMP算法**：告诉我们当前位置匹配失败，跳到之前已经匹配过的地方
- **构造前缀表**：
  - 初始化：定义两个指针i和j，`j`指向**前缀末尾**位置，`i`指向**后缀末尾**位置
  - 循环遍历`i`：如果前后缀不相同，后退`j`，`j=next[j]`；如果前后缀相同，前进`j`，`j++`，同时`next[i]=j`

```c++
void getNext(int* next, const string& s){
    int j = -1;
    next[0] = j;
    for(int i = 1; i < s.size(); i++) { // 注意i从1开始
        while (j >= 0 && s[j + 1] != s[i]) { // 前后缀不相同了
            j = next[j]; // 向前回退
        }
        if (s[j + 1] == s[i]) { // 找到相同的前后缀
            j++;
        }
        next[i] = j; // 将j（前缀的长度）赋给next[i]
    }
}
```

- **使用next数组来做匹配**
  - 初始化：定义两个下标，`j` 指向模式串t起始位置，`i`指向文本串s起始位置。
  - 匹配：比较 `s[i]` 与 `t[j + 1]` 

```c++
int j = -1; // 因为next数组里记录的起始位置为-1
for (int i = 0; i < s.size(); i++) { // 注意i就从0开始
    while(j >= 0 && s[i] != t[j + 1]) { // 不匹配
        j = next[j]; // j 寻找之前匹配的位置
    }
    if (t[j + 1] == s[i]) { // 匹配，j和i同时向后移动
        j++; // i的增加在for循环里
    }
    if (j == (t.size() - 1) ) { // 文本串s里出现了模式串t
        return (i - t.size() + 1);	// 返回文本串中出现模式串的第一个位置
    }
}
```



### 找出字符串中第一个匹配项的下标（KMP）

- 字符串s，模式串t，KMP算法

```c++
class Solution {
public:
    void getNext(int* next, const string& s) {
        // j表示前缀末尾，i表示后缀末尾
        int j = -1;
        next[0] = j;
        for (int i = 1; i < s.size(); i++) {
            // 前后缀不相同
            while (j >= 0 && s[j + 1] != s[i]) {
                j = next[j];
            }
            if (s[j + 1] == s[i]) {
                j++;
            }
            next[i] = j;
        }
    }

    int strStr(string s, string t) {
        // 边界情况处理
        if (t.size() == 0) {
            return 0;
        }
        // KMP匹配
        vector<int> next(t.size());
        getNext(&next[0], t);
        int j = -1; // j表示next数组下标，i表示字符串下标
        for (int i = 0; i < s.size(); i++) {
            // 不匹配
            while (j >= 0 && t[j + 1] != s[i]) {
                j = next[j];
            }
            if (t[j + 1] == s[i]) {
                j++;
            }
            if (j == (t.size() - 1)) { // 文本串s里出现了模式串t
                return (i - t.size() + 1);
            }
        }
        return -1;
    }
};
```



### 重复的子字符串（KMP）

- 重复子串：如果 s 是 t = s + s 的子串，且起始位置既不在开头也不在末尾，那么 s 一定是由某个更短的子串重复多次得到的。

  ```c++
  class Solution {
  public:
      bool repeatedSubstringPattern(string s) {
          if ((s + s).find(s, 1) != s.size()){
              return true;
          }
          return false;
      }
  };
  ```

- KMP算法：只需要判断 `s.size()` 是否为 `s.size()−next[s.size()−1]−1` 的倍数即可

  ```c++
  class Solution {
  public:
      void getNext(int* next, const string& s) {
          // j表示前缀末尾，i表示后缀末尾
          int j = -1;
          next[0] = j;
          for (int i = 1; i < s.size(); i++) {
              // 前后缀不相同
              while (j >= 0 && s[j + 1] != s[i]) {
                  j = next[j];
              }
              if (s[j + 1] == s[i]) {
                  j++;
              }
              next[i] = j;
          }
      }
  
      bool repeatedSubstringPattern(string s) {
          // 边界情况处理
          if (s.size() == 0) {
              return 0;
          }
          // KMP匹配
          vector<int> next(s.size());
          getNext(&next[0], s);
          
          // 匹配重复的子字符串
          int len = s.size();
          if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0) {
              return true;
          }
          return false;
      }
  };
  ```



### 前缀树 Trie Tree（26叉树）

- `Trie()` 初始化前缀树对象。
- `void insert(String word)` 向前缀树中插入字符串 `word` 。
- `boolean search(String word)` 如果字符串 `word` 在前缀树中，返回 `true`（即，在检索之前已经插入）；否则，返回 `false` 。
- `boolean startsWith(String prefix)` 如果之前已经插入的字符串 `word` 的前缀之一为 `prefix` ，返回 `true` ；否则，返回 `false` 。

```c++
class Trie {
public:
    struct Node {
        Node* son[26]{};  // 长26的儿子节点
        bool end = false; // end表示是否为终止节点
    };

    Node* root = new Node();

    int find(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) { // 道不同，不相为谋
                return 0;
            }
            cur = cur->son[c];
        }
        // 走过同样的路（2=完全匹配，1=前缀匹配）
        return cur->end ? 2 : 1;
    }

    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (Node* son : node->son) {
            destroy(son);
        }
        delete node;
    }

    ~Trie() { 
        destroy(root); 
    }

    void insert(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) { // 无路可走？
                cur->son[c] = new Node(); // new 出来！
            }
            cur = cur->son[c];
        }
        cur->end = true;
    }

    bool search(string word) { 
        return find(word) == 2; 
    }

    bool startsWith(string prefix) { 
        return find(prefix) != 0; 
    }
};
```



## √栈与队列

### 用栈实现队列*(理解)

- **输入栈**：进入队列时，直接进入栈
- **输出栈**：出队列时，输入栈元素全部pop到输出栈，在“出栈”中pop元素

```c++
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;

    MyQueue() {}

    void push(int x) { stIn.push(x); }

    int pop() {
        // 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty()) {
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    int peek() {
        // 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty()) {
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        return result;
    }

    bool empty() { 
        return stIn.empty() && stOut.empty(); 
    }
};
```



### 用队列实现栈*(理解)

- **用两个队列que1和que2实现栈的功能，que2其实完全就是一个备份的作用**
- `pop()`：把que1最后面的元素以外的元素都备份到que2，然后弹出最后面的元素，再把其他元素从que2导回que1。

```c++
class MyStack {
public:
    queue<int> que1;
    queue<int> que2;

    MyStack() {}

    void push(int x) { que1.push(x); }

    int pop() {
        int size = que1.size();
        size--;
        while (size--) {
            que2.push(que1.front());
            que1.pop();
        }
        int result = que1.front();
        que1.pop();
        que1 = que2;
        while (!que2.empty()) {
            que2.pop();
        }
        return result;
    }

    int top() {
        int size = que1.size();
        size--;
        while (size--) {
            que2.push(que1.front());
            que1.pop();
        }
        int result = que1.front();
        // 获取值后将最后一个元素也加入que2中，保持原本的结构不变
        que2.push(que1.front());
        que1.pop();
        que1 = que2;
        while (!que2.empty()) {
            que2.pop();
        }
        return result;
    }

    bool empty() { return que1.empty(); }
};
```



### √最小栈

- 设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。
  - 栈中除了保存添加的元素，还保存前缀最小值。

```c++
class MinStack {
    stack<pair<int, int>> st;

public:
    // MinStack() 初始化堆栈对象。
    MinStack() {
        // 添加栈底哨兵 INT_MAX
        st.emplace(0, INT_MAX);
    }

    // void push(int val) 将元素val推入堆栈。
    void push(int val) { 
        st.emplace(val, min(getMin(), val)); 
    }

    // void pop() 删除堆栈顶部的元素。
    void pop() {
        st.pop();
    }

    // int top() 获取堆栈顶部的元素。
    int top() {
        return st.top().first;
    }

    // int getMin() 获取堆栈中的最小元素。
    int getMin() {
        return st.top().second;
    }
};
```



### 有效的括号

- 考虑将字符串里的括号push进去，遇到左括号，则放入右括号，最后弹出进行匹配。

1. 第一种情况，字符串里左方向的括号多余了 ，所以不匹配。
2. 第二种情况，括号没有多余，但是 括号的类型没有匹配上。
3. 第三种情况，字符串里右方向的括号多余了，所以不匹配。

```c++
class Solution {
public:
    bool isValid(string s) {
        // 如果s的长度为奇数，一定不符合要求
        if (s.size() % 2 == 1) {
            return false;
        }
        stack<int> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(')');
            } else if (s[i] == '[') {
                st.push(']');
            } else if (s[i] == '{') {
                st.push('}');
            } else if (st.empty() || s[i] != st.top()) {
                return false;
            } else {
                st.pop();
            }
        }
        return st.empty();
    }
};
```



### 最长有效括号

- **问题**：给你一个只包含 `'('` 和 `')'` 的字符串，找出最长有效（**格式正确且连续**）括号子串的长度。

  ```
  输入：s = "(()"
  输出：2
  解释：最长有效括号子串是 "()"
  ```

- **解决**：栈底为 **最后一个没有被匹配的右括号的下标**，从而截断计数

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        stack<int> st;
        st.push(-1); // 栈底为最后一个没有被匹配的右括号的下标
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                st.pop();
                if(st.empty()){ // 从此处开始，多余')'，更新栈底
                    st.push(i); // 截断计数
                }else{
                    ans = max(ans, i - st.top());
                }
            }
        }
        return ans;
    }
};
```



### 字符串解码

- 问题：编码规则为: `k[encoded_string]`，表示其中方括号内部的 `encoded_string` 正好重复 `k` 次。注意 `k` 保证为正整数。

  ```
  输入：s = "3[a]2[bc]"
  输出："aaabcbc"
  ```

- 解决：

  - 设置数字栈`stack <int> nums;`和字母栈`stack <string> strs;`
  - 碰到`[`，数字和当前字符串入栈，碰到`]`，出栈。

  ```c++
  class Solution {
  public:
      string decodeString(string s) {
          // 设置数字栈`stack <int> nums;`和字母栈`stack <string> strs;`
          // 碰到`[`，数字和当前字符串入栈；碰到`]`，出栈。
          stack<int> nums;
          stack<string> strs;
          string res = "";
          int num = 0;
          for(int i = 0; i < s.size();i++){
              if(s[i] >= '0' && s[i] <='9'){
                  num = num*10 + s[i] -'0';
              }else if(s[i] >= 'a' && s[i]<='z'){
                  res += s[i];
              }else if(s[i]=='['){
                  nums.push(num);
                  num = 0;
                  strs.push(res);
                  res = "";
              }else{
                  int times = nums.top();
                  nums.pop();
                  for(int j = 0; j < times; j++){
                      // 在strs.top()中添加res，因为他们是同一级运算
                      strs.top() += res;
                  }
                  res = strs.top();
                  strs.pop();
              }
          }
          return res;
      }
  };
  ```



### 删除字符串中的所有相邻重复项

- 因为从栈里弹出的元素是倒序的，所以再对字符串进行反转一下，就得到了最终的结果。

```c++
class Solution {
public:
    string removeDuplicates(string s) {
        if (s.size() == 0) {
            return {};
        }
        stack<char> st;
        for (int i = 0; i < s.size(); i++) {
            if (st.empty() || st.top() != s[i]) {
                st.push(s[i]);
            } else {
                st.pop();
            }
        }
        string ans;
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```



### 波兰表达式（后缀表达式）

- 遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

```c++
class Solution {
public:
    // 遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                long long num1 = st.top();
                st.pop();
                long long num2 = st.top();
                st.pop();
                if (tokens[i] == "+")    st.push(num2 + num1);
                if (tokens[i] == "-")    st.push(num2 - num1);
                if (tokens[i] == "*")    st.push(num2 * num1);
                if (tokens[i] == "/")    st.push(num2 / num1);
            } else {
                st.push(stoll(tokens[i]));
            }
        }
        long long result = st.top();
        st.pop();
        return result;
    }
};
```



### √*滑动窗口最大值（难点）

- 维护单调队列：front 从大到小 back
  - pop()：如果移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
  - push()：如果元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止
  - front()：保证队列的出口元素是最大值。

```c++
class Solution {
private:
    class MyQueue {
    public: // 注意public
        deque<int> que; // 使用deque来实现单调队列

        // pop()：如果移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }

        // push()：如果元素value > 入口元素，那么就弹出入口元素，直到push的
        // value ≤ 入口元素 为止
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);
        }

        // front()：保证队列的出口元素是最大值
        int front() { return que.front(); }
    };

public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        // 先将前k的元素放进队列
        for (int i = 0; i < k; i++) {
            que.push(nums[i]);
        }
        // result 记录前k的元素的最大值
        result.push_back(que.front());
        for (int i = k; i < nums.size(); i++) {
            // 按照滑动窗口的规定开始滑动
            que.pop(nums[i - k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }
        return result;
    }
};
```



### *前K个高频元素（小顶堆）

1. 要统计元素出现频率：**map**数据结构（key记录元素，value记录频率）
2. 对频率排序：利用**优先级队列**构造**小顶堆**对value进行排序
3. 找出前K个高频元素

- **堆**

  堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。

  大顶堆：根节点是最大元素；小顶堆：根节点是最小元素

- **优先级队列**（披着队列外衣的堆）

  优先级队列，对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式，看起来就是一个队列。而且优先级队列内部元素是自动依照元素的权值排列。

  那么它是如何有序排列的呢：一般情况下priority_queue利用max-heap（大顶堆）完成对元素的排序，这个大顶堆是以vector为表现形式的complete binary tree（完全二叉树）。

```c++
class Solution {
public:
    // 小顶堆
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 统计元素出现频率：map<nums[i],对应出现的次数>
        unordered_map<int, int> map; //
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }

        // 对频率排序
        // 定义一个小顶堆，大小为k
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫面所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) {
                pri_que.pop();
            }
        }

        // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;
    }
};
```



## √二叉树

### 基础理论

#### 1. **二叉树的种类**

- 满二叉树：只有度为0的结点和度为2的结点，并且度为0的结点在同一层上。深度为k，有 ${ 2^k - 1 }$个节点

  <img src="./Note.assets/20200806185805576.png" alt="img" style="zoom: 25%;" />

- 完全二叉树：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 ${1 到 2^{h-1} }$ 个节点。

  <img src="./Note.assets/20200920221638903.png" alt="img" style="zoom:50%;" />

- 二叉搜索树（有序树）：O(logn)

  - 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；

  - 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；

  - 它的左、右子树也分别为二叉排序树

    <img src="./Note.assets/20200806190304693.png" alt="img" style="zoom: 67%;" />

- 平衡二叉搜索树（AVL）：它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。

  <img src="./Note.assets/20200806190511967.png" alt="img" style="zoom: 50%;" />

**C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树**，所以map、set的增删操作时间时间复杂度是**logn**，

注意，**unordered_map、unordered_set，unordered_map、unordered_set底层实现是哈希表**。

#### **2. 二叉树的存储方式**

- 链式存储

  <img src="./Note.assets/2020092019554618.png" alt="img" style="zoom:50%;" />

- 顺序存储（数组）

  下标`i`的左孩子`2i+1`，右孩子`2i+2`

  <img src="./Note.assets/20200920200429452.png" alt="img" style="zoom:50%;" />

#### **3. 遍历方式**

```c++
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```

- 深度优先遍历：栈

  - 前序遍历（递归法，迭代法）
  - 中序遍历（递归法，迭代法）
  - 后序遍历（递归法，迭代法）

  ```c++
  // 递归法：参数和返回值；终止条件；单层递归逻辑
  class Solution {
  public:
      void traversal(TreeNode* cur, vector<int>& res) {
          if (cur == NULL)
              return;
          res.push_back(cur->val);	// 中
          traversal(cur->left, res);	// 左
          traversal(cur->right, res);	// 右
      }
  
      vector<int> preorderTraversal(TreeNode* root) {
          vector<int> ans;
          traversal(root, ans);
          return ans;
      }
  };
  ```

- 广度优先遍历：队列

  - 层次遍历（递归法、迭代法）


```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL)
            que.push(root);
        vector<vector<int>> ans;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            ans.push_back(vec);
        }
        return ans;
    }
};
```

- 模版题：104.二叉树的最大深度

#### 4. 二叉树展开为链表

- 展开后的单链表应该同样使用 `TreeNode` ，其中 `right` 子指针指向链表中下一个结点，而左子指针始终为 `null` 。
- 展开后的单链表应该与二叉树**先序遍历**顺序相同。

```c++
class Solution {
public:
    void preorderTraversal(TreeNode* root, vector<TreeNode*>& ans) {
        if (root != nullptr) {
            ans.push_back(root);
            preorderTraversal(root->left, ans);
            preorderTraversal(root->right, ans);
        }
    }

    void flatten(TreeNode* root) {
        vector<TreeNode*> ans;
        preorderTraversal(root, ans);
        for (int i = 1; i < ans.size(); i++) {
            TreeNode* pre = ans[i - 1];
            TreeNode* cur = ans[i];
            pre->left = nullptr;
            pre->right = cur;
        }
    }
};
```

#### 5. 二叉树的序列化和反序列化

- 序列化：层序遍历
- 反序列化：递推

```c++
class Codec {
public:
    // 把二叉树编码为string
    string serialize(TreeNode* root) {
        if (root == NULL)
            return "[]";
        string ans = "[";
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if (node != NULL) {
                ans += to_string(node->val) + ",";
                que.push(node->left);
                que.push(node->right);
            } else {
                ans += "null,";
            }
        }
        ans.pop_back();
        ans += "]";
        return ans;
    }

    // 将data反序列化为二叉树.
    TreeNode* deserialize(string data) {
        if (data == "[]")
            return NULL;
        // 初始化vals
        string strs = data.substr(1, data.size() - 2);  // 去掉[]
        stringstream ss(strs);
        string item;
        vector<string> vals;
        while (getline(ss, item, ','))
            vals.push_back(item);
        // 初始化根节点root、队列que
        TreeNode* root = new TreeNode(stoi(vals[0]));
        queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        // 按层构建
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (vals[i] != "null") {
                node->left = new TreeNode(stoi(vals[i]));
                q.push(node->left);
            }
            i++;
            if (vals[i] != "null") {
                node->right = new TreeNode(stoi(vals[i]));
                q.push(node->right);
            }
            i++;
        }
        return root;
    }
};
```



### 二叉树的属性

#### **1. 对称二叉树**

- 首先排除空节点和值不相等的情况（如果left和right均为NULL，return true）
- 然后递归比较： 左子树的左孩子和右子树的右孩子（**外侧**）；左子树的右孩子和右子树的左孩子（**内侧**）

```c++
class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) {
        // 首先排除空节点、值不相等
        if (left == NULL && right != NULL)
            return false;
        else if (left != NULL && right == NULL)
            return false;
        else if (left == NULL && right == NULL)
            return true;
        else if (left->val != right->val)
            return false;

        // 然后递归比较
        bool outside = compare(left->left, right->right);
        bool inside = compare(left->right, right->left);
        return outside && inside;
    }

    bool isSymmetric(TreeNode* root) {
        if (root == NULL)
            return true;
        return compare(root->left, root->right);
    }
};
```



#### **2. 最小深度**（前序遍历）

- **深度**（前序遍历）：任意一个节点到**根节点**的距离；

```c++
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root==NULL)
            return 0;
        int leftDepth = minDepth(root->left);
        int rightDepth = minDepth(root->right);
        if (root->left == NULL && root->right != NULL) { 
            return 1 + rightDepth;
        }   
        if (root->left != NULL && root->right == NULL) { 
            return 1 + leftDepth;
        }
        int result = 1 + min(leftDepth, rightDepth);
        return result;
    }
};
```



#### **3. 平衡二叉树**（后序遍历）

- 一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1
- **高度**（后序遍历）：任意一个节点到**叶子结点**的距离。

```c++
class Solution {
public:
    // -1 表示已经不是平衡二叉树了，否则返回值是以该节点为根节点树的高度
    int getHeight(TreeNode* node) {
        if (node == NULL)
            return 0;
        int leftHeight = getHeight(node->left);
        if (leftHeight == -1)
            return -1;
        int rightHeight = getHeight(node->right);
        if (rightHeight == -1)
            return -1;
        int result;
        if (abs(leftHeight - rightHeight) > 1) {
            result = -1;
        } else {
            result = 1 + max(leftHeight, rightHeight);
        }
        return result;
    }

    bool isBalanced(TreeNode* root) {
        int ans = getHeight(root);
        if (ans == -1)
            return false;
        else
            return true;
    }
};
```



#### **4. 完全二叉树的节点个数**

```c++
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == NULL)
            return 0;
        int leftNum = countNodes(root->left);
        int rightNum = countNodes(root->right);
        int num = leftNum + rightNum + 1;
        return num;
    }
};
```



#### **5.二叉树的所有路径**

- 注意回溯

```c++
class Solution {
public:
    void traversal(TreeNode* node, vector<int>& path, vector<string>& result) {
        path.push_back(node->val);  // 中写在这里，因为最后一个节点也要加入到path中
        if (node->left == NULL && node->right == NULL) {
            string sPath;
            for (int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }
        if (node->left) { // 左
            traversal(node->left, path, result);
            path.pop_back(); // 回溯
        }
        if (node->right) { // 右
            traversal(node->right, path, result);
            path.pop_back(); // 回溯
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<int> path;
        vector<string> result;
        if (root == NULL)
            return result;
        traversal(root, path, result);
        return result;
    }
};
```



#### **6. 左子叶之和**

- 通过父节点来判断，**①其左孩子不为空，②且左孩子的左右孩子为空 --> 左叶子**
- 从下往上返回（**左子树的左叶子之和+右子树的左子叶之和**） --> **后序遍历**（左右中）

```c++
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == NULL)
            return 0;
        if (root->left == NULL && root->right == NULL)
            return 0;
        int leftVal = sumOfLeftLeaves(root->left);
        int rightVal = sumOfLeftLeaves(root->right);
        int Val = leftVal + rightVal;
        if (root->left != NULL && root->left->left == NULL &&
            root->left->right == NULL)
            Val += root->left->val;
        return Val;
    }
};
```



#### **7. 找树左下角的值**

- 层序遍历：result = vec[0]

```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL)
            que.push(root);
        int ans = 0;
        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == 0) // 记录最后一行第一个元素
                    ans = node->val;
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
        }
        return ans;
    }
};
```



#### 8. 二叉树的直径

- 一条路径的长度，为该路径经过的节点数减一 => 求直径（即求路径长度的最大值）等效于求**路径经过节点数的最大值减一**。
- 该节点的左儿子向下遍历经过最多的节点数 L （即以左儿子为根的子树的深度） 和其右儿子向下遍历经过最多的节点数 R （即以右儿子为根的子树的深度），那么以该节点为起点的路径经过节点数的最大值即为 **L+R+1** .


```c++
class Solution {
public:
    int ans;
    int getdepth(TreeNode* root) {
        if (root == NULL)
            return 0;
        int leftDepth = getdepth(root->left);
        int rightDepth = getdepth(root->right);
        ans = max(ans, leftDepth + rightDepth + 1);
        return max(leftDepth, rightDepth) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        getdepth(root);
        return ans - 1;
    }
};
```



#### ***9. 路径总和**

递归函数什么时候需要返回值？什么时候不需要返回值？这里总结如下三点：

- 如果需要搜索整棵二叉树，且不用处理递归返回值，递归函数就不要返回值。

- 如果需要搜索整棵二叉树，且需要处理递归返回值，递归函数就需要返回值。 

- 如果要搜索其中一条符合条件的路径，那么递归一定需要返回值，因为遇到符合条件的路径了就要及时返回。

1. **路径总和I**

- 给你二叉树的根节点 `root` 和一个表示目标和的整数 `targetSum` 。判断该树中是否存在 **根节点到叶子节点** 的路径，这条路径上所有节点值相加等于目标和 `targetSum` 。如果存在，返回 `true` ；否则，返回 `false` 。

  ```c++
  class Solution {
  private:
      bool traversal(TreeNode* cur, int count) {
          // 遇到叶子节点，并且计数为0，即找到了目标和
          if (!cur->left && !cur->right && count == 0)
              return true;
          // 遇到叶子节点直接返回
          if (!cur->left && !cur->right)
              return false;
  
          if (cur->left) { // 左
              count -= cur->left->val;
              if (traversal(cur->left, count))
                  return true;
              count += cur->left->val;
          }
          if (cur->right) { // 右
              count -= cur->right->val;
              if (traversal(cur->right, count))
                  return true;
              count += cur->right->val;
          }
          return false;
      }
  
  public:
      bool hasPathSum(TreeNode* root, int sum) {
          if (root == NULL)
              return false;
          return traversal(root, sum - root->val);
      }
  };
  ```

2. **路径总和II**

- 给你二叉树的根节点 `root` 和一个整数目标和 `targetSum` ，找出所有 **从根节点到叶子节点** 路径总和等于给定目标和的路径。

  ```c++
  class Solution {
  public:
      vector<vector<int>> result;
      vector<int> path;
  
      void traversal(TreeNode* node, int cnt) {
          if (node->left == NULL && node->right == NULL && cnt == 0) {
              result.push_back(path);
              return;
          }
          if (node->left == NULL && node->right == NULL)
              return;
          if (node->left) {
              path.push_back(node->left->val);
              cnt -= node->left->val;
              traversal(node->left, cnt);
              cnt += node->left->val;
              path.pop_back();
          }
          if (node->right) {
              path.push_back(node->right->val);
              cnt -= node->right->val;
              traversal(node->right, cnt);
              cnt += node->right->val;
              path.pop_back();
          }
      }
  
      vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
          result.clear();
          path.clear();
          if (root == NULL)
              return result;
          path.push_back(root->val);
          traversal(root, targetSum - root->val);
          return result;
      }
  };
  ```

3. **路径总和III**

- 给定一个二叉树的根节点 `root` ，和一个整数 `targetSum` ，求该二叉树里节点值之和等于 `targetSum` 的 **路径** 的数目。
- **路径** 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
- 解决：由于路径是从上往下，所以traversal是中序遍历（中左右）

  ```c++
  class Solution {
  public:
      unordered_map<long long, int> prefix; // 前缀和
      // 以节点 node 为起点向下且满足路径总和为 targetSum 的路径数目
      int traversal(TreeNode* node, long long curSum, int targetSum) {
          if (node == NULL) {
              return 0;
          }
          int num = 0;
          curSum += node->val;
          if (prefix.count(curSum - targetSum)) {
              num = prefix[curSum - targetSum];
          }
  
          prefix[curSum]++;
          num += traversal(node->left, curSum, targetSum);
          num += traversal(node->right, curSum, targetSum);
          prefix[curSum]--;
  
          return num;
      }
  
      int pathSum(TreeNode* root, int targetSum) {
          prefix[0] = 1;
          return traversal(root, 0, targetSum);
      }
  };
  ```




### 二叉树的修改与构造

#### **1. 翻转二叉树**

- 翻转每个节点的左右孩子即可

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL)
            return root;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```



#### 2**. 合并二叉树**

```c++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL)
            return root2;
        if (root2 == NULL)
            return root1;
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};
```



#### ***3. 构造二叉树**

- 从中序和后序遍历构造二叉树 / 从中序和前序遍历构造二叉树 **【必须有中序】**

1. 第一步：排除空节点。如果数组大小为零的话，说明是空节点了。
2. 第二步：获得前/后序节点。取后序数组最后一个元素作为节点元素。
3. 第三步：叶子结点（终止条件）
4. 第四步：定位中序遍历的切割点。找到后序数组最后一个元素在中序数组的位置，作为切割点
5. 第五步：切割中序数组[)，切成中序左数组和中序右数组 （顺序别搞反了，一定是**先切中序数组**）
6. 第六步：切割前序序数组[)，**先扔掉切割点**，然后切成后序左数组和后序右数组（使用**左中序数组大小作为切割点**）
7. 第七步：递归处理左区间和右区间，记得返回`root`

```c++
class Solution {
public:
    // 如果直接使用vector调用，内存过大
    TreeNode* traversal(vector<int>& preorder, int PreBegin, int PreEnd,
                        vector<int>& inorder, int InBegin, int InEnd) {
        // 1.排除空节点
        if (PreBegin == PreEnd)
            return NULL;

        // 2.获得前序节点
        int rootValue = preorder[PreBegin];
        TreeNode* root = new TreeNode(rootValue);

        // 3.叶子结点（终止条件）
        if (PreEnd - PreBegin == 1)
            return root;

        // 4.定位中序遍历的切割点
        int MidIndex = 0;
        for (int i = InBegin; i < InEnd; i++) {
            if (inorder[i] == rootValue) {
                MidIndex = i;
                break;
            }
        }

        // 5.切割中序遍历
        // vector<int> leftInorder(inorder.begin(), inorder.begin() + MidIndex);
        // vector<int> rightInorder(inorder.begin() + MidIndex + 1, inorder.end());
        int leftInorderBegin = InBegin;
        int leftInorderEnd = MidIndex;
        int rightInorderBegin = MidIndex + 1;
        int rightInorderEnd = InEnd;

        // 6.切割前序遍历
        // vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + leftInorder.size());
        // vector<int> rightPreorder(preorder.begin() + 2 + leftInorder.size(), preorder.end());
        int leftPreorderBegin = PreBegin + 1;
        int leftPreorderEnd = PreBegin + 1 + MidIndex - InBegin;
        int rightPreorderBegin = leftPreorderEnd;
        int rightPreorderEnd = PreEnd;

        // 7. 递归处理左右数组
        root->left = traversal(preorder, leftPreorderBegin, leftPreorderEnd, inorder,
                  leftInorderBegin, leftInorderEnd); // 左
        root->right = traversal(preorder, rightPreorderBegin, rightPreorderEnd, inorder,
                  rightInorderBegin, rightInorderEnd); // 右
        return root;
        
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0 || inorder.size() == 0)
            return NULL;
        return traversal(preorder, 0, preorder.size(), inorder, 0,
                         inorder.size());
    }
};
```



#### **4. 最大二叉树**

给定一个不重复的整数数组 `nums` 。 **最大二叉树** 可以用下面的算法从 `nums` 递归地构建:

1. 创建一个根节点，其值为 `nums` 中的最大值。
2. 递归地在最大值 **左边** 的 **子数组前缀上** 构建左子树。
3. 递归地在最大值 **右边** 的 **子数组后缀上** 构建右子树。

```c++
class Solution {
public:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        // 1. 排除空节点
        if (left >= right) {
            return nullptr;
        }
        // 2. 定位MaxIndex
        int MaxIndex = left;
        for (int i = left; i < right; i++) {
            if (nums[i] > nums[MaxIndex]) {
                MaxIndex = i;
            }
        }
        // 3. 切割
        // int leftBegin = left;
        // int leftEnd = MaxIndex;
        // int rightBegin = MaxIndex+1;
        // int rightEnd = right;

        // 4. 递归
        TreeNode* root = new TreeNode(nums[MaxIndex]);
        root->left = traversal(nums, left, MaxIndex);
        root->right = traversal(nums, MaxIndex + 1, right);
        return root;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) {
            return nullptr;
        }
        return traversal(nums, 0, nums.size());
    }
};
```



### 二叉搜索树 BST 的属性 

二叉搜索树（有序树）：--> **转化为有序数组**

- 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
- 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
- 它的左、右子树也分别为二叉搜索树

#### **1. 二叉搜索树中的搜索**

```c++
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL || root->val == val) {
            return root;
        }
        TreeNode* result = NULL;
        if (root->val > val)
            result = searchBST(root->left, val);
        else
            result = searchBST(root->right, val);
        return result;
    }
};
```



#### **2. 验证二叉搜索树**

```c++
class Solution {
public:
    vector<int> vec;
    void Midtraversal(TreeNode* cur) {
        if (cur == NULL)
            return;
        Midtraversal(cur->left);
        vec.push_back(cur->val);
        Midtraversal(cur->right);
    }

    bool isValidBST(TreeNode* root) {
        Midtraversal(root);
        for (int i = 0; i < vec.size() - 1; i++) {
            if (vec[i] >= vec[i + 1]) {
                return false;
            }
        }
        return true;
    }
};
```



#### **3. 二叉搜索树的最小绝对差**

```c++
class Solution {
public:
    vector<int> vec;
    void traversal(TreeNode* cur) {
        if (cur == NULL)
            return;
        traversal(cur->left);
        vec.push_back(cur->val);
        traversal(cur->right);
    }

    int getMinimumDifference(TreeNode* root) {
        vec.clear();
        traversal(root);
        int ans = INT_MAX;
        for (int i = 0; i < vec.size() - 1; i++) {
            if (ans > vec[i + 1] - vec[i]) {
                ans = vec[i + 1] - vec[i];
            }
        }
        return ans;
    }
};
```



#### **4. 二叉搜索树中的众数**

- 在遍历过程中，因为是有序数组，所以可以直接比较cur和pre的val是否相同，然后直接把结果放进result，如果不是最高频率，再更新result即可。

```c++
class Solution {
public:
    int cnt = 0;
    int MAXcnt = 0;
    TreeNode* pre = NULL;
    vector<int> result;
    void traversal(TreeNode* cur) {
        if (cur == NULL)
            return;
        traversal(cur->left);

        if (pre == NULL) {
            cnt = 1;
        } else if (pre->val == cur->val) {
            cnt++;
        } else {
            cnt = 1;
        }
        pre = cur;

        if (cnt == MAXcnt) {
            result.push_back(cur->val);
        }
        if (cnt > MAXcnt) {
            MAXcnt = cnt;
            result.clear();
            result.push_back(cur->val);
        }

        traversal(cur->right);
        return;
    }

    vector<int> findMode(TreeNode* root) {
        cnt = 0;
        MAXcnt = 0;
        pre = NULL;
        result.clear();
        traversal(root);
        return result;
    }
};
```



#### **5. 把二叉搜索树转换为累加树**

```c++
class Solution {
public:
    int pre = 0;
    TreeNode* convertBST(TreeNode* root) {
        if (root == NULL)
            return root;
        root->right = convertBST(root->right);
        root->val += pre;
        pre = root->val;
        root->left = convertBST(root->left);
        return root;
    }
};
```



### 二叉搜索树的修改与构造

#### **1. 二叉搜索树中的插入操作**

- 注意：在有返回值的递归函数中，要接住返回值！

```c++
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode* node = new TreeNode(val);
            return node;
        }
        if (root->val > val)
            root->left = insertIntoBST(root->left, val);
        if (root->val < val)
            root->right = insertIntoBST(root->right, val);
        return root;
    }
};
```



#### ***2. 删除二叉搜索树中的节点**

1. 左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
2. 删除节点的左孩子为空，右孩子不为空，则删除节点，右孩子补位，返回右孩子（反之亦然）
3. 左右孩子节点都不为空，假设使用右孩子继位，返回root->right；将`root->left`放到right节点的子树的最左侧

**注意**：本题不需要遍历全部二叉树，遇到需要删除的节点时就终止，然后开始判断删除逻辑

```c++
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) {
            return NULL;
        }
        if (root->val == key) {
            // 1. 左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
            if (root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            }
            // 2. 左孩子为空，右孩子不为空，则删除节点，右孩子补位，返回右孩子
            else if (root->left == NULL) {
                auto retNode = root->right;
                delete root;
                return retNode;
            } else if (root->right == NULL) {
                auto retNode = root->left;
                delete root;
                return retNode;
            }
            // 3. 左右孩子节点都不为空，假设使用右孩子继位，返回root->right
            // 将`root->left`放到right节点的子树的最左侧
            else {
                TreeNode* cur = root->right;
                while (cur->left != NULL) {
                    cur = cur->left;
                }
                cur->left = root->left;
                auto retNode = root->right;
                delete root;
                return retNode;
            }
        }
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
};
```



#### **3. 修剪二叉搜索树**

```c++
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr)
            return nullptr;
        if (root->val < low) {
            TreeNode* right = trimBST(root->right, low, high);
            return right;
        }
        if (root->val > high) {
            TreeNode* left = trimBST(root->left, low, high);
            return left;
        }
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};
```



#### **4. 将有序数组转换为二叉搜索树**

- 数组中间的元素作为中间节点，然后构造左子树、右子树

```c++
class Solution {
public:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) {
            return NULL;
        }
        int mid = left + ((right - left) / 2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1);
        return root;
    }
};
```



### 二叉树公共祖先问题

#### ***1. 二叉树的最近公共祖先**

- 求最小公共祖先，需要从底向上遍历，那么二叉树，只能通过**后序遍历（即：回溯）**实现从底向上的遍历方式。

- 在回溯的过程中，必然要遍历整棵二叉树，即使已经找到结果了，依然要把其他节点遍历完，因为要**使用递归函数的返回值（也就是代码中的left和right）做逻辑判断**。

- 如果返回值left为空，right不为空要返回right，因为这样可以用返回right传给上一层结果。

```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || root == NULL) {
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left != NULL && right != NULL)
            return root;
        if (left == NULL && right != NULL)
            return right;
        else if (left != NULL && right == NULL)
            return left;
        else {
            return NULL;
        }
    }
};
```



#### **2. 二叉搜索树的最近公共祖先**

- 利用BST的性质：比较根节点和p、q的大小，加快搜索，如果节点的值在p和q之间，则节点就是公共祖先

```c++
class Solution {
public:
    TreeNode* traversal(TreeNode* cur, TreeNode* p, TreeNode* q) {
        if (cur == NULL) {
            return cur;
        }
        if (cur->val > p->val && cur->val > q->val) { // 左
            TreeNode* left = traversal(cur->left, p, q);
            if (left != NULL) {
                return left;
            }
        }

        if (cur->val < p->val && cur->val < q->val) { // 右
            TreeNode* right = traversal(cur->right, p, q);
            if (right != NULL) {
                return right;
            }
        }
        return cur;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return traversal(root, p, q);
    }
};
```



## √回溯算法

- 组合问题：N个数里面按一定规则找出k个数的集合
- 切割问题：一个字符串按一定规则有几种切割方式
- 子集问题：一个N个数的集合里有多少符合条件的子集
- 排列问题：N个数按一定规则全排列，有几种排列方式
- 棋盘问题：N皇后，解数独等等

回溯的本质是**穷举，纯暴力搜索**

```c++
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
```

### 组合问题

#### **组合**

- 函数：void backtracking(n, k , startIndex)

- 终止条件：path.size()==k

- 回溯逻辑：取数、递归、回溯

- 剪枝：在集合n中**至多**要从该起始位置` i <= n - (k - path.size()) + 1` 开始遍历（再往后，for循环也取不够）

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }
};
```



#### **组合总和III**

- 函数：void backtracking(n, targetSum , startIndex,sum)

- 终止条件：path.size() == k && sum == targetSum

- 回溯逻辑：取数、递归、回溯

- 剪枝：` i <= n - (k - path.size()) + 1 && if (sum > targetSum)  return;`


```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backtracking(int k, int n, int startIndex) {
        if (sum > n) { // 剪枝操作
            return;
        }
        if (path.size() == k) {
            if (sum == n) {
                result.push_back(path);
            }
            return;
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {
            sum += i;
            path.push_back(i);
            backtracking(k, n, i + 1);
            path.pop_back();
            sum -= i;
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(k, n, 1);
        return result;
    }
};
```



#### **电话号码的字母组合**

- 映射

  ```c++
  const string letterMap[10] = {
      "",     // 0
      "",     // 1
      "abc",  // 2
      "def",  // 3
      "ghi",  // 4
      "jkl",  // 5
      "mno",  // 6
      "pqrs", // 7
      "tuv",  // 8
      "wxyz", // 9
  };
  ```

- 函数：`void backtracking(string& digits, int index)` // index 表示本层在处理输入字符串的第几个数字

- 终止条件：`if (index == digits.size())` //处理完字符串中的最后一个数字后，结束

- 回溯逻辑：取数、递归、回溯


```c++
class Solution {
public:
    const string letterMap[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz", // 9
    };
    vector<string> result;
    string path;
    void backtracking(const string& digits, int index) {
        if (index == digits.size()) {
            result.push_back(path);
            return;
        }
        int num = digits[index] - '0'; // 当前摁下的数字
        string str = letterMap[num];   // 数字映射的字符串
        for (int i = 0; i < str.size(); i++) {
            path.push_back(str[i]);
            backtracking(digits, index + 1);
            path.pop_back();
        }
        return;
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return {};
        }
        backtracking(digits, 0);
        return result;
    }
};
```



#### 括号生成

- 题意：数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。
- 用`l`，`r`分别记录可以插入 `'('` 和 `')'` 的数量。
  - 剪枝：如果出现异常括号，不需要继续遍历，即`left < 0 || left > right`
  - 遍历：直接进入递归

```c++
class Solution {
public:
    vector<string> result;
    void dfs(const string& str, int left, int right) {
        if (left < 0 || left > right) // 剪枝
            return;
        if (left == 0 && right == 0) {
            result.push_back(str);
            return;
        }
        dfs(str + '(', left - 1, right);
        dfs(str + ')', left, right - 1);
    }

    vector<string> generateParenthesis(int n) {
        dfs("", n, n);
        return result;
    }
};
```



#### *删除无效的括号

- 题意：给你一个由若干括号和字母组成的字符串 `s` ，**删除最小数量的无效括号**，使得输入的字符串有效，输出所有可能结果。
- 思路：
  1. 括号匹配的规则求出该字符串 s 中最少需要去掉的左括号的数目`LeftRemove` 和右括号的数目`RightRemove`
  2. 利用回溯算法来尝试搜索所有可能的去除括号的方案
     - 终止条件：当`LeftRemove` 和`RightRemove` 同时为 0 时，则检测当前的字符串是否合法匹配
     - 递归逻辑：分别尝试删除左括号和右括号
       - 去重：如果遇到连续相同的括号，则跳过
       - 剪枝：每去掉一个括号，则更新`LeftRemove` 或者 `RightRemove`，当剩余字符串的长度小于`LeftRemove + RightRemove` 时，则停止本次搜索

```c++
class Solution {
public:
    vector<string> result;
    void backtracking(int LeftRemove, int RightRemove, string s, int startIndex) {
        // 终止条件：LeftRemove和RightRemove均为0，判断是否有效
        if (LeftRemove == 0 && RightRemove == 0) {
            if (isValid(s)) {
                result.push_back(s);
            }
            return;
        }
        // 递归逻辑：分别尝试删除左括号和右括号
        for (int i = startIndex; i < s.size(); i++) {
            // 去重：如果剩余括号 = 上一个括号，则无需删除
            if (i > startIndex && s[i] == s[i - 1]) {
                continue;
            }
            // 剪枝：剩余括号 < LeftRemove + RightRemove
            if (s.size() - i < LeftRemove + RightRemove) {
                return;
            }
            // 尝试删除左括号
            if (LeftRemove > 0 && s[i] == '(') {
                backtracking(LeftRemove - 1, RightRemove, s.substr(0, i) + s.substr(i + 1), i);
            }
            // 尝试删除右括号
            if (RightRemove > 0 && s[i] == ')') {
                backtracking(LeftRemove, RightRemove - 1, s.substr(0, i) + s.substr(i + 1), i);
            }
        }
    }
    bool isValid(const string& s) {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                cnt++;
            } else if (s[i] == ')') {
                cnt--;
                if (cnt < 0) {
                    return false;
                }
            }
        }
        return cnt == 0;
    }
    vector<string> removeInvalidParentheses(string s) {
        // 1. 用括号匹配规则，求出最少需要删除的括号数
        int LeftRemove = 0, RightRemove = 0;
        for (char ch : s) {
            if (ch == '(') {
                LeftRemove++;
            } else if (ch == ')') {
                if (LeftRemove == 0) {
                    RightRemove++;
                } else {
                    LeftRemove--;
                }
            }
        }

        // 2. 利用回溯遍历所有修改情况，搜索有效修改
        backtracking(LeftRemove, RightRemove, s, 0);
        return result;
    }
};
```



#### **组合总和**

- 题意：**无重复元素** 的整数数组`candidates` ，其中 **同一个** 数字可以 **无限制重复被选取**

- 函数：`void backtracking(const vector<int>& candidates, int targetSum, int sum, int startIndex)`
- 终止条件：`sum > targetSum 返回; sum == targetSum 收获`
- 回溯逻辑：取数、递归、回溯
- 优化：先排序candidate，然后`sum + candidates[i] <= target`放到for循环的判断条件里

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backtracking(const vector<int>& candidates, int targetSum, int startIndex) {
        if (sum > targetSum) {
            return;
        }
        if (sum == targetSum) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= targetSum; i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, targetSum, i);
            sum -= candidates[i];
            path.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0);
        return result;
    }
};
```



#### **组合总和II**

- 难点：**集合（数组candidates）元素只能使用一次，有重复元素，但不能有重复的组合**
- 解析：**我们要去重的是同一树层上的“使用过”，同一树枝上的都是一个组合里的元素，不用去重**

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void backtracking(const vector<int>& candidates, int targetSum, int startIndex) {
        if (sum > targetSum) {
            return;
        }
        if (sum == targetSum) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size(); i++) {
            // 去重逻辑：i>startIndex 表明在同一树层第二个元素开始，然后如果树层重复，就不需要进入递归
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, targetSum, i + 1);
            sum -= candidates[i];
            path.pop_back();
        }
        return;
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // 先排列再去重
        backtracking(candidates, target, 0);
        return result;
    }
};
```



### 分割问题

#### **分割回文串**

- 题意：请你将 `s` 分割成一些 子串，使每个子串都是 **回文串** 

- 函数：`void backtracking(const string& s, int startIndex)`
- 终止条件：`if (startIndex == s.size())`**// 遍历到字符串的最后一个字母**
- 回溯逻辑：如果是回文子串，则放入path，然后进入递归，否则continue进入下一个循环
- 判断回文子串的逻辑：从起始和终点，同时向内遍历，如果不相等则return false

```c++
class Solution {
public:
    vector<vector<string>> result;
    vector<string> path;
    bool isHUIWEN(const string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
    void backtracking(const string& s, int startIndex) {
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isHUIWEN(s, startIndex, i)) {
                // s.substr(起始位置，长度)
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            } else {
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
        return;
    }
    vector<vector<string>> partition(string s) {
        backtracking(s, 0);
        return result;
    }
};
```



#### **复原IP地址**

- 函数：`void backtracking(string& s, int startIndex, int times)`
- 终止条件：`if (pointNum == 3)`  // `pointNum`:添加逗点的数量，有三个逗点，不再继续分割
- 回溯逻辑：取数、递归、回溯
- 判断当前字段是否合法：
  - 段位以0为开头的数字不合法
  - 段位里有非正整数字符不合法
  - 段位如果大于255了不合法

```c++
class Solution {
public:
    vector<string> result;
    void backtracking(string& s, int startIndex, int pointNum) {
        if (pointNum == 3) { // 逗点数量为3时，分隔结束
            // 判断第四段子字符串是否合法，如果合法就放进result中
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
            }
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            // 判断 [startIndex,i] 这个区间的子串是否合法
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                backtracking(s, i + 2, pointNum + 1);
                s.erase(s.begin() + i + 1);
            } else {
                break;
            }
        }
        return;
    }
    // 判断字符串s在左闭右闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        // 0开头的数字不合法
        if (s[start] == '0' && start != end) {
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }
    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0, 0);
        return result;
    }
};
```



### 子集问题

#### **子集**

- 难点：什么时候收获结果？——**遍历这个树的时候，把所有节点都记录下来，就是要求的子集集合**——每层递归都收获
- 终止条件：`startIndex >= 数组的长度`

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, int startIndex) {
        // 收集子集，要放在终止条件的上面，否则会漏掉自己
        result.push_back(path);
        if (startIndex >= nums.size()) {
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
```



#### **子集II**

- 题意：数组中包含重复元素

- 难点：去重！和**组合总和II**的思路一致，注意先排序，后去重。这里不重复


```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, int startIndex) {
        result.push_back(path);
        if (startIndex >= nums.size()) {
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > startIndex && nums[i] == nums[i - 1]) {
                continue;
            }
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return result;
    }
};
```



#### ***非递减子序列**

- 题意：本题求自增子序列，是**不能对原数组进行排序的**，子序列是从给定序列中抽取，**不改变元素相对顺序**

- 去重：同一树层去重

```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, int startIndex) {
        if (path.size() > 1) {
            result.push_back(path);
            // 注意这里不要加return，因为要取树上的所有节点
        }
        unordered_set<int> uset; // 使用set对本层元素进行去重
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back()) ||
                uset.find(nums[i]) != uset.end()) {
                // 1.当path不为空时，若读取元素小于path结尾（不构成非递减），则不需要进入递归
                // 2.若发现当前取的数在本树层已经被用过，不进入递归
                continue;
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
```



### 排列问题

#### **全排列**

- 需要用**used数组**`vector<bool> used(nums.size(), false)`来标记什么元素使用过了；由于是排列，所以不需要`startIndex`了

- 函数：`void backtracking(vector<int>& nums, vector<bool>& used)`

- 终止条件：`if (path.size() == nums.size())`

- 回溯逻辑：取数、递归、回溯


```c++
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(const vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i])
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
```



#### **全排列II**

- **难点：去重**（先排序，然后用used数组在树层上去重。注意：**对used数组到底是true还是false的判断**）

  ```c++
  class Solution {
  public:
      vector<vector<int>> result;
      vector<int> path;
      void backtracking(const vector<int>& nums, vector<bool> used) {
          if (path.size() == nums.size()) {
              result.push_back(path);
              return;
          }
          for (int i = 0; i < nums.size(); i++) {
              // 注意树层去重条件：used[i - 1] == false，说明同一树层nums[i - 1]使用过
              if (used[i] == true || (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)) {
                  continue;
              }
              used[i] = true;
              path.push_back(nums[i]);
              backtracking(nums, used);
              path.pop_back();
              used[i] = false;
          }
      }
      vector<vector<int>> permuteUnique(vector<int>& nums) {
          sort(nums.begin(), nums.end());
          vector<bool> used(nums.size(), false);
          backtracking(nums, used);
          return result;
      }
  };
  ```



#### *重新安排行程

- **题意**：给你一份航线列表 `tickets` ，其中 `tickets[i] = [fromi, toi]` 表示飞机出发和降落的机场地点。所有的机票 必须都用一次 且 只能用一次。

- **如何记录映射关系**？——出发机场映射多个到达机场：`unordered_map<出发机场, map<到达机场, 航班次数>> targets`

  - 在遍历过程中，**可以使用"航班次数"这个字段的数字做相应的增减，来标记到达机场是否使用过了。**

    如果“航班次数”大于零，说明目的地还可以飞，如果“航班次数”等于零说明目的地不能飞了，而不用对集合做删除元素或者增加元素的操作。

- **Hierholzer 算法**（暴力搜索已超时）

  - 从起点（`"JFK"`）开始，沿着未访问过的边（航班）进行深度优先搜索（DFS）。
  - 每次访问一个机场后，将其从当前路径中移除（即减少航班次数）。
  - 当无法继续前进时（即当前机场没有未访问的航班），将当前机场加入结果路径的前面。
  - 重复上述过程，直到所有航班都被访问。

```c++
class Solution {
public:
    // unordered_map<出发机场, map<到达机场, 航班次数>> umap
    unordered_map<string, map<string, int>> umap;
    vector<string> result;

    void dfs(string airport) {
        while (!umap[airport].empty()) {
            auto& destinations = umap[airport];
            auto it = destinations.begin(); // 获取字典序最小的到达机场
            string next = it->first;
            int& count = it->second;
            if (count > 0) {
                count--; // 减少航班次数
                if (count == 0) {
                    destinations.erase(it); // 如果航班次数为 0，移除该条边
                }
                dfs(next); // 递归访问下一个机场
            }
        }
        result.insert(result.begin(), airport); // 回溯时将机场加入结果路径的前面
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (int i = 0; i < tickets.size(); i++) { // 初始化地图
            umap[tickets[i][0]][tickets[i][1]]++;
        }
        dfs("JFK"); // 从 "JFK" 开始深度优先搜索
        return result;
    }
};
```



### 棋盘问题

#### **N皇后**

- 函数：用row记录当前遍历到第几行，并且传入chessboard，跟着每一次递归和isValid变化。

  -  `void backtracking(int n, int row, vector<string>& chessboard)`

- 终止条件：遍历到棋盘的最后一行，即`if (row == n)`

  ```c++
  class Solution {
  public:
      vector<vector<string>> result;
      bool isValid(int row, int col, vector<string>& chessBoard, int n) {
          // 1. 不能在同一列：col列的位置上没有Q
          for (int i = 0; i < row; i++) {
              if (chessBoard[i][col] == 'Q')
                  return false;
          }
          // 2. 不能在斜对角（左上角）
          for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
              if (chessBoard[i][j] == 'Q') {
                  return false;
              }
          }
          // 3. 不能在斜对角（右上角）
          for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
              if (chessBoard[i][j] == 'Q') {
                  return false;
              }
          }
          return true;
      }
      void backtracking(int n, int loop, vector<string>& chessBoard) {
          if (loop == n) {
              result.push_back(chessBoard);
              return;
          }
          for (int col = 0; col < n; col++) {
              if (isValid(loop, col, chessBoard, n)) {
                  chessBoard[loop][col] = 'Q';
                  backtracking(n, loop + 1, chessBoard);
                  chessBoard[loop][col] = '.';
              }
          }
      }
      vector<vector<string>> solveNQueens(int n) {
          vector<string> chessBoard(n, string(n, '.'));
          backtracking(n, 0, chessBoard);
          return result;
      }
  };
  ```



#### **解数独**

- 难点：在判断是否有效的时候，**需要行和列的二维数据**。

- 函数：用bool类型，只要找到单个结果就立刻返回，即`bool backtracking(vector<vector<char>>& board)`

  ```c++
  class Solution {
  public:
      bool isValid(int row, int col, int val, vector<vector<char>>& board) {
          // 1. 数字 1-9 在每一行只能出现一次
          for (int i = 0; i < 9; i++) {
              if (board[i][col] == val) {
                  return false;
              }
          }
          // 2. 数字 1-9 在每一列只能出现一次。
          for (int j = 0; j < 9; j++) {
              if (board[row][j] == val) {
                  return false;
              }
          }
          // 3. 判断9方格里是否重复
          int startRow = (row / 3) * 3;
          int startCol = (col / 3) * 3;
          for (int i = startRow; i < startRow + 3; i++) {
              for (int j = startCol; j < startCol + 3; j++) {
                  if (board[i][j] == val) {
                      return false;
                  }
              }
          }
          return true;
      }
      bool backtracking(vector<vector<char>>& board) {
          for (int i = 0; i < board.size(); i++) {        // 遍历行
              for (int j = 0; j < board[0].size(); j++) { // 遍历列
                  if (board[i][j] != '.')
                      continue;
                  for (char k = '1'; k <= '9'; k++) {
                      if (isValid(i, j, k, board)) {
                          board[i][j] = k; // 放置k
                          if (backtracking(board))
                              return true;
                          board[i][j] = '.';
                      }
                  }
                  return false; // 9个数都试完了，都不行，那么就返回false
              }
          }
          return true; // 遍历完没有返回false，说明找到了合适棋盘位置了
      }
      void solveSudoku(vector<vector<char>>& board) {
          backtracking(board);
          return;
      }
  };
  
  ```



## √贪心算法

### 分发饼干

- **局部最优**：大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个     -->      **全局最优**：喂饱尽可能多的小孩。
- 注意，先sort成有序数组！

```c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int cnt = 0;
        int sIndex = s.size() - 1; // 记录饼干数组的下标
        for (int i = g.size() - 1; i >= 0; i--) {
            if (sIndex >= 0 && g[i] <= s[sIndex]) {
                cnt++;
                sIndex--;
            }
        }
        return cnt;
    }
};
```



### K次取反后最大化的数组和

- **局部最优**：让绝对值大的负数变为正数；最小的正数取反     -->      **全局最优**：整个数组和达到最大
- `sort`：按**绝对值**从小到大来

```c++
class Solution {
public:
    bool static compare(int a, int b) {
        if (abs(a) < abs(b))
            return true;
        else
            return false;
    }
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), compare);
        int sum = 0;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] < 0 && k > 0) {
                nums[i] *= -1;
                k--;
            }
            sum += nums[i];
        }
        if (k % 2 == 1) {
            nums[0] *= -1;
            sum += nums[0] * 2;
        }
        return sum;
    }
};
```



### 柠檬水找零

- **局部最优**：遇到账单20，优先消耗美元10，完成本次找零。

```c++
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five++;
            }
            if (bill == 10) {
                if (five <= 0)
                    return false;
                five--;
                ten++;
            }
            if (bill == 20) {
                if (ten >= 1 && five >= 1) {
                    ten--;
                    five--;
                    continue;
                }
                if (five >= 3) {
                    five -= 3;
                    continue;
                }
                return false;
            }
        }
        return true;
    }
};
```



### 摆动序列

- 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 **摆动序列 。**第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。

- **局部最优**：删除单调坡度上的节点     -->      **全局最优**：达到最长摆动序列

- 平坡：一个是 上下中间有平坡`preDiff=0,curDiff>0`，一个是单调有平坡，`只有在更新了cnt时，更新preDiff = curDiff`

  <img src="https://file1.kamacoder.com/i/algo/20201124174327597.png" alt="376.摆动序列" style="zoom:50%;" />

```c++
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int cnt = 1;
        int preDiff = 0;
        int curDiff = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                cnt++;
                preDiff = curDiff;
            }
        }
        return cnt;
    }
};
```



### 单调递增的数字

- 输入：332；输出299**（单调自增，且不大于输入的最大数字）**
- **从后向前**遍历输入的数字
  - 如果前一位＞当前位，说明不满足单调自增，则把前一位-1，当前位变为9**（注意，应该用flag来标记）**
  - 如果输入就是单调自增，则输出就是原来的数

```c++
class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string str = to_string(n);
        int flag = str.size();
        // 标记数字flag
        for (int i = str.size() - 1; i > 0; i--) {
            if (str[i] < str[i - 1]) {
                flag = i;
                str[i - 1]--;
            }
        }
        // 将flag之后的数字改为9
        for (int i = flag; i < str.size(); i++) {
            str[i] = '9';
        }
        return stoi(str);
    }
};
```



### 最大子数组和

- **局部最优**：当“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数继续加， “连续和”只会越来越小。

- **全局最优**：选取最大“连续和”

- **注意**：由于是区间和，所以应该用一个`MaxSum`来记录区间最大值

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int MaxSum = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum > MaxSum) {
                MaxSum = sum;
            }
            if (sum <= 0) {
                sum = 0;
            }
        }
        return MaxSum;
    }
};
```



### 乘积最大子数组（DP）

- **问题**：整数数组 `nums` ，找出数组中**乘积最大的非空连续 子数组**（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
- **解决**：由于要考虑**负数**，所以需要**同时维护最大乘积和最小乘积**
  - `f_max[i]`：`[0, i]`子数组的最大乘积；`f_min[i]`：`[0, i]`子数组的最小乘积
    - `x` 单独组成一个子数组，`f_max[i] = x`
    - `x` 和前面的子数组拼起来
  - 综上，递推公式为：
    - `f_max[i] = max(x * f_max[i - 1], x * f_min[i - 1], x)`
    - `f_min[i] = min(x * f_max[i - 1], x * f_min[i - 1], x)`
  - 注意：结果不一定是`f_max[n - 1]`，而是`f_max`中的最大值

```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> f_min(n);
        vector<int> f_max(n);
        f_max[0] = f_min[0] = nums[0];
        // 递推公式
        for (int i = 1; i < n; i++) {
            f_min[i] = min(nums[i], min(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]));
            f_max[i] = max(nums[i], max(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]));
        }
        // 统计结果
        int result = nums[0];
        for (int i = 0; i < n; i++) {
            if (f_max[i] > result)
                result = f_max[i];
        }
        return result;
    }
};
```



### 加油站

- **局部最优**：每个加油站的剩余量`rest[i]为gas[i] - cost[i]`，当前累加`rest[i]`之和`curSum`一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。

- **全局最优**：找到可以跑一圈的起始位置

```c++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int startIndex = 0;
        for (int i = 0; i < gas.size(); i++) {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if (curSum < 0) {
                startIndex = i + 1;
                curSum = 0;
            }
        }
        if (totalSum < 0)
            return -1;
        return startIndex;
    }
};
```



### 买卖股票的最佳时机II

- **利润**：`price[i]-price[i-1]`

- **局部最优**：收集所有**利润**为正数的时候    -->      **全局最优**：股票收益最大

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sum = 0;
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            profit = prices[i] - prices[i - 1];
            if (profit > 0) {
                sum += profit;
            }
        }
        return sum;
    }
};
```



### 买卖股票的最佳时机-含手续费

- **局部最优**：最低值买，最高值（如果算上手续费还盈利）就卖

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int sum = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            if (minPrice > prices[i]) {
                minPrice = prices[i];
            } else if (minPrice <= prices[i] && prices[i] <= minPrice + fee) {
                continue;
            }
            if (prices[i] > minPrice + fee) {
                sum += prices[i] - (minPrice + fee);
                minPrice = prices[i] - fee; // 避免重复扣手续费
            }
        }
        return sum;
    }
};
```



### *分发糖果

- **条件1**：右孩子比左孩子得分高（**从前向后**遍历）
- **条件2**：左孩子比右孩子得分高（**从后向前**遍历），取`max(candyVec[i], candyVec[i + 1] + 1)`

```c++
class Solution {
public:
    int candy(vector<int>& ratings) {
        // 所有小孩初始化1个糖果
        vector<int> candy(ratings.size(), 1);
        candy[0] = 1;
        // 从前向后：右 ＞ 左
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) {
                candy[i] = candy[i - 1] + 1;
            }
        }
        // 从后向前：左 ＞ 右
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candy[i] = max(candy[i + 1] + 1, candy[i]);
            }
        }
        // 统计结果
        int result = 0;
        for (int i = 0; i < candy.size(); i++) {
            result += candy[i];
        }
        return result;
    }
};
```



### *根据身高重建队列

题意：h【身高】，k【前面有k个人的身高≥h】

- **条件1**：身高从大到小排（**前面的人一定比后面高**）；身高相同时，k小的站前面（**k=0表示前面没有人比我高**）
- **条件2**：从身高的高到低，按照k来插入，插入队列首部的第`k`个位置【Eg. `[5,0]`插入队列的第`0`个位置】

```c++
class Solution {
public:
    static bool compare(vector<int>& a, vector<int>& b) {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), compare);
        vector<vector<int>> que;
        for (int i = 0; i < people.size(); i++) {
            int k = people[i][1];
            que.insert(que.begin() + k, people[i]);
        }
        return que;
    }
};
```



### 最短无序连续子数组

- 从左到右看，数应该越来越大，如果某个数，比前面最大值大，那他没问题，如果小于前面的最大值，那么这个数就有问题
- 从左到右不断更新最大值，遇到有问题的数，就记录下来作为right，并且right可以更新
- right更新到最后面不动了，说明right右边的数都比，right左边的max的数大，但是right自己比max小，right右边是排好序的，right左边需要重新排序，right是需要重新排序的区间的右边界。
- left同理，left就是从右往左看，数要越来越小才行，如果某个数，比右边最小值还要小，那他没问题，如果它比右边的最小值要大，说明他有问题。

```c++
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int left = -1, right = -1;
        // 找右边界：从左往右，找到比左边最大值还小的最右下标
        int maxVal = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < maxVal) {
                right = i;
            }
            maxVal = max(maxVal, nums[i]);
        }
        // 从右往左，找到比右边最小值还大的最左下标
        int minVal = INT_MAX;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] > minVal) {
                left = i;
            }
            minVal = min(minVal, nums[i]);
        }
        // 如果数组已有序，返回0
        if (left == -1 && right == -1) {
            return 0;
        }
        return right - left + 1;
    }
};
```



### 盛最多水的容器

- 双指针：表示容器两端
- 贪心：每次移动对应数字较小的那个指针

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int MaxWater = 0;
        int curWater = 0;
        while (left < right) {
            curWater = (right - left) * min(height[left], height[right]);
            if (curWater > MaxWater) {
                MaxWater = curWater;
            }
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return MaxWater;
    }
};
```



### *任务调度器

- 最多任务数量 `N`，用于构建 `N`个桶；最多任务数量的个数`count`，用于标记最后一个桶的任务数。——6A6B，则最后一行count=2

- **任务种类少**：`time1 = (N - 1) * (n + 1) + count`

  <img src="https://pic.leetcode-cn.com/8993d48fb4109d5d207f135bf73e10fd22c898c25113e5fa09bc91829790f9a0-image.png" alt="image.png" style="zoom:80%;" />

- **任务种类多**：`time2 = 任务的数量`

  <img src="https://pic.leetcode-cn.com/893c01db5923889a865d7a4fe71de22b9519fc5a673473196ab58f26c1073ed2-image.png" alt="image.png" style="zoom:80%;" />

  ```c++
  class Solution {
  public:
      int leastInterval(vector<char>& tasks, int n) {
          int len = tasks.size();
          vector<int> vec(26);
          int N = 0;
          int count = 0;
          // 统计每个任务的数量
          for (char task : tasks) {
              vec[task - 'A']++;
          }
          // 找出任务数量最多的任务，以及最多任务数量出现的次数
          for (int i = 0; i < 26; i++) {
              if (vec[i] > N) {
                  N = vec[i];
                  count = 1;
              } else if (vec[i] == N) {
                  count++;
              }
          }
          // 计算所需的最小时间间隔
          return max(len, (N - 1) * (n + 1) + count);
      }
  };
  ```




### 跳跃游戏

- **局部最优**：每次取最大跳跃步数（取最大覆盖范围）    -->      **全局最优**：最后得到整体最大覆盖范围，看是否能到终点

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int MaxPosition = 0;
        for (int cur = 0; cur <= MaxPosition; cur++) {
            MaxPosition = max(MaxPosition, cur + nums[cur]);
            if (cur >= nums.size() - 1) {
                return true;
            }
        }
        return false;
    }
};
```



### 跳跃游戏II

- **局部最优**：每一步尽可能增加覆盖范围    -->      **全局最优**：最后到终点

- 统计两个覆盖范围，当前这一步的最大覆盖和下一步最大覆盖，如果**到达最大覆盖范围**，但没到终点，更新最大覆盖，然后步数+1。

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        // 分别记录当前覆盖范围和最大覆盖范围
        int MaxPosition = 0, curPosition = 0;
        int steps = 0;
        for (int cur = 0; cur <= curPosition; cur++) {
            curPosition = max(curPosition, cur + nums[cur]);
            if (cur == MaxPosition && curPosition > MaxPosition) {
                MaxPosition = curPosition;
                steps++;
            }
            if (MaxPosition >= nums.size() - 1) {
                break;
            }
        }
        return steps;
    }
};
```



### 用最少数量的箭引爆气球

- **局部最优**：当气球出现重叠，一起射    -->      **全局最优**：把所有气球射爆所用弓箭最少

- **实现局部最优**：求不重叠的区间数。
  - 先排序，从小到大排序
  - 如果，气球不重叠（**气球的左边界 > 上一个的右边界**），加一只箭
  - 如果，气球重叠，**要更新边界信息**！`min(points[i - 1][1], points[i][1])`
  

```c++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) { 
        return a[1] < b[1]; 
    }
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        int rightIndex = points[0][1];
        int arrow = 1;
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] <= rightIndex) {
                continue;
            } else {
                arrow++;
                rightIndex = points[i][1];
            }
        }
        return arrow;
    }
};
```



### 无重叠区间

- 给定一个区间的集合 `intervals` ，其中 `intervals[i] = [starti, endi]` 。返回 *需要移除区间的最小数量，使剩余区间互不重叠* 。**注意**：只在一点上接触的区间是 **不重叠的**。例如 `[1, 2]` 和 `[2, 3]` 是不重叠的。

- **局部最优**：求出最多的非重叠区间数量    -->      **全局最优**：所有区间 - 非重叠区间 = 需要删除的区间

```c++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        int cnt = 1;
        int rightIndex = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (rightIndex <= intervals[i][0]) {
                cnt++;
                rightIndex = intervals[i][1];
            }
        }
        return intervals.size() - cnt;
    }
};
```



### 合并区间

- 如果，区间不重叠（区间的左边界 **>** 上一个的右边界），直接放入区间`result.push_back(intervals[i]);`

- 如果，区间重叠，更新右边界即可，`result.back()[1] = max(result.back()[1], intervals[i][1]);`

```c++
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) { 
        return a[0] < b[0]; 
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (result.back()[1] >= intervals[i][0]) {
                // 发现重叠区间，更新右边界 
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                // 区间不重叠，直接放入即可
                result.push_back(intervals[i]); 
            }
        }
        return result;
    }
};
```



### 划分字母区间

- 统计每一个字符最后出现的位置
- 从头遍历字符，并更新字符的最远下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点
- **注意：**返回分割的区间长度，所有要记录`left（开始下标）`和`right（最远下标）`

```c++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int hash[27] = {0};
        for (int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++) {
            right = max(right, hash[s[i] - 'a']);
            if (i == right) {
                result.push_back(right - left + 1);
                left = right + 1;
            }
        }
        return result;
    }
};
```



### **监控二叉树**

- **局部最优**：让叶子节点的父节点安摄像头，所用摄像头最少    -->      **全局最优**：全部摄像头数量所用最少

- **实现局部最优**：先给叶子节点父节点放个摄像头**，**然后隔两个节点放一个摄像头，直至到头结点。

  - **二叉树的遍历方式？**——从下往上（**左右中**）

  - **如何隔两个节点放一个摄像头？**——设置状态
    - 0：该节点无覆盖、1：本节点有摄像头、2：本节点有覆盖	【注：**空节点**应该是**有覆盖**的状态】
    
  - **模拟过程？**
  
    - 左右节点都有覆盖——父节点无覆盖 0
  
    - 左右节点至少有一个无覆盖的情况——父节点有摄像头 1 

    - 左右节点至少有一个有摄像头——父节点有覆盖 2
    
    - 头结点没有覆盖 ——头结点为1

  ```c++
  class Solution {
  public:
      int result;
      int traversal(TreeNode* cur) {
          // 0：该节点无覆盖、1：本节点有摄像头、2：本节点有覆盖
          // 空节点：该结点有覆盖
          if (cur == NULL)
              return 2;
          int left = traversal(cur->left);
          int right = traversal(cur->right);
  
          // 左右节点都有覆盖——父节点无覆盖 0
          if (left == 2 && right == 2) {
              return 0;
          }
          // 左右节点至少有一个无覆盖的情况——父节点有摄像头 1
          if (left == 0 || right == 0) {
              result++;
              return 1;
          }
          // 左右节点至少有一个有摄像头——父节点有覆盖 2
          if (left == 1 || right == 1) {
              return 2;
          }
          return -1;
      }
      int minCameraCover(TreeNode* root) {
          result = 0;
          // 头结点没有覆盖 ——头结点为1
          if (traversal(root) == 0) {
              result++;
          }
          return result;
      }
  };
  ```



### 树形DP

#### 二叉树中的最大路径

- **问题**：二叉树中的 **路径** 被定义为一条节点序列。同一个节点在一条路径序列中 **至多出现一次** 。该路径 **至少包含一个** 节点，且不一定经过根节点。**路径和** 是路径中各节点值的总和。给你一个二叉树的根节点 `root` ，返回其 **最大路径和** 。
- **解决**：
  - 函数：`int dfs(TreeNode* node,int& result)`
  - 终止条件：遇到空节点，返回0
  - **单层处理逻辑**：`result = max(result, l_val + r_val + node->val);`
  - **返回值**：`max(max(l_val, r_val) + node->val, 0); `**注意只能走左或右，同时要和 0 取最大值**，避免负数
  - 遍历顺序：左右中

```c++
class Solution {
public:
    int dfs(TreeNode* node, int& result) {
        if (node == nullptr) {
            return 0; // 没有节点，返回0
        }
        int l_val = dfs(node->left, result);             // 左子树最大链和
        int r_val = dfs(node->right, result);            // 右子树最大链和
        result = max(result, l_val + r_val + node->val); // 两条链拼成路径
        return max(max(l_val, r_val) + node->val, 0);    // 当前子树最大链和
    }
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        dfs(root, result);
        return result;
    }
};
```



## 动态规划

- 确定dp数组（dp table）以及下标的含义
- 确定递推公式
- dp数组如何初始化
- 确定遍历顺序

### 斐波那契数列

- `dp[i]`：第`i`个斐波那契数的值为`dp[i]`
- 确定递推公式：`dp[i] = dp[i - 1] + dp[i - 2]`

- dp数组如何初始化：`dp[0]=0`、`dp[1]=1`

- 确定遍历顺序：从前向后

```c++
class Solution {
public:
    int fib(int n) {
        if (n <= 1)
            return n;
        vector<int> dp(n + 1);
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```



### 爬楼梯

- `dp[i]`：到达`i`阶有`dp[i]`中方法

- 确定递推公式：`dp[i] = dp[i - 1] + dp[i - 2]`
  - 每次只能迈1阶或2阶，那么`dp[i]`只能用`dp[i-1]+dp[i-2]`得到

- dp数组如何初始化：`dp[1]=1`、`dp[2]=2`
  - `1 <= n <= 45`，所以不需要考虑`dp[0]`

- 确定遍历顺序：从前向后

```c++
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) {
            return n;
        }
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```



### 使用最小花费爬楼梯

- `dp[i]`：到达`i`阶所需的最小花费为`dp[i]`

- 确定递推公式：`dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2])`

- dp数组如何初始化：`dp[0]=0`、`dp[1]=0`

- 确定遍历顺序：从前向后

```c++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        if (n == 2) {
            return min(cost[0], cost[1]);
        }
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= n; i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};
```



### 最小路径和

- **问题**：给定一个包含非负整数的 `m x n` 网格 `grid` ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。每次只能向下或者向右移动一步。

  - **`dp[i][j]`**：到达`grid[i][j]`所使用的最小路径和

  - 递推公式：`dp[i][j]= min(dp[i-1][j], dp[i][j-1])`

  - dp数组如何初始化：初始化`dp[i][0]`和`dp[0][j] `

```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 205));
        // 初始化dp数组
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        // 递推公式
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
```



### 不同路径

- `dp[i][j]`：从`[0][0]`到达`[i][j]`的位置，有`dp[i][j]`中方法
- 确定递推公式：`dp[i][j] = dp[i - 1][j] + dp[i][j - 1]`

- dp数组如何初始化：`dp[i][0]=1`、`dp[0][j]=1`

- 确定遍历顺序：从左往右，从上往下

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```



### 不同路径II

- `dp[i]`：从`[0][0]`到达`[i][j]`的位置，有`dp[i][j]`中方法

- 确定递推公式：`dp[i][j] = dp[i - 1][j] + dp[i][j - 1]`

  - 注意，如果`(i, j)`有障碍，那么`dp[i][j]=0`

- dp数组如何初始化：`dp[i][0]=1`、`dp[0][j]=1`

  - 如果`(i,0)` 这条边有了障碍之后，障碍之后（包括障碍）都是走不到的位置了，所以障碍之后的`dp[i][0]`应该还是0。

- 确定遍历顺序：从左往右，从上往下

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1)
                    continue;
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```




### **整数拆分**

- 题解：每次尽可能拆分成相等的数

- `dp[i]`：对`i`进行拆分，得到的最大乘积为`dp[i]`

- 确定递推公式：`dp[i] = max{dp[i], (i - j) * j, dp[i - j] * j}`
  
  - 开始拆分`i`，`j`从`1`遍历到`i-1`，有两种渠道得到`dp[i]`
    - 拆分成两个数，就是`j * (i - j)` 直接相乘。
    - 拆分成三个及以上，就是`j * dp[i - j]`，相当于是拆分`(i - j)`
  
- dp数组如何初始化：`dp[2]=1` （`dp[0]`、`dp[1]`都没有意义）

- 确定遍历顺序：从小到大

```c++
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] = max(dp[i], max(dp[i - j] * j, (i - j) * j));
            }
        }
        return dp[n];
    }
};
```



### 不同的二叉搜索树

- `dp[i]`：第`i`个二叉搜索树的个数为`dp[i]`

- 确定递推公式：`dp[i] = ∑ dp[i - 1] * dp[j - i]`

- dp数组如何初始化：`dp[0]=1`、`dp[1]=1`

- 确定遍历顺序：从前向后

```c++
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};
```



### *戳气球

- **问题**：

  - 有 `n` 个气球，编号为`0` 到 `n - 1`，每个气球上都标有一个数字，这些数字存在数组 `nums` 中。现在要求你戳破所有的气球。戳破第 `i` 个气球，你可以获得 `nums[i - 1] * nums[i] * nums[i + 1]` 枚硬币。 这里的 `i - 1` 和 `i + 1` 代表和 `i` 相邻的两个气球的序号。如果 `i - 1`或 `i + 1` 超出了数组的边界，那么就当它是一个数字为 `1` 的气球。求所能获得硬币的最大数量。

  ```
  输入：nums = [3,1,5,8]
  输出：167
  解释：
  nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
  coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
  ```

- `dp[i][j]`：填满开区间 `(i,j)`能得到的最多硬币数，所求结果为`dp[0][n+1]`
- 递推公式：
  - $$dp[i][j] = \begin{cases} 
    \max_{k=i+1}^{j-1} val[i] \times val[k] \times val[j] + dp[i][k] + dp[k][j], & i < j - 1 \\
    0, & i \geq j - 1 
    \end{cases}$$
- 遍历顺序：
  - 从后向前遍历区间的左边界，然后在区间内从前向后遍历要戳的气球

```c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 2, vector<int>(n + 2));
        // 初始化硬币数组，越界的值记为1
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        // 递推
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 2; j <= n + 1; j++) {
                for (int k = i + 1; k < j; k++) {
                    int sum = val[i] * val[k] * val[j] + dp[i][k] + dp[k][j];
                    dp[i][j] = max(dp[i][j], sum);
                }
            }
        }
        return dp[0][n + 1];
    }
};
```



### 背包问题

<img src="./Note.assets/20210117171307407.png" alt="416.分割等和子集1" style="zoom:50%;" />

- **递推公式**

  - 问背包装满最大价值：`dp[j] = max(dp[j], dp[j - weight[i]] + value[i])`; 
  - 问能否能装满背包（或者最多装多少）：`dp[j] = max(dp[j], dp[j - nums[i]] + nums[i])`; 
  - 问装满背包有几种方法：`dp[j] += dp[j - nums[i]]` 
  - 问装满背包所有物品的最小个数：`dp[j] = min(dp[j - coins[i]] + 1, dp[j]);` 

- **遍历顺序**

  - 01背包

    - 二维dp数组：先遍历物品还是先遍历背包都是可以的，且第二层for循环是从小到大遍历。
    - 一维dp数组：只能先遍历物品再遍历背包容量，且第二层for循环是**从大到小**遍历。

  - 完全背包

    - 如果求组合数就是外层for循环遍历物品，内层for遍历背包。

    - 如果求排列数就是外层for遍历背包，内层for循环遍历物品



#### 01背包

1. ==基础解法：二维dp数组==

   - **`dp[i][j]`：**`i` 表示物品、`j`背包容量，`dp[i][j] `表示从下标为`[0-i]`的物品里任意取，放进容量为`j`的背包，**价值总和最大**是`dp[i][j] `。
   - **确定递推公式**：`dp[i][j] = max(dp[i-1][j],dp[i-1][j-weigth[i]]+value[i])`
     - 不放物品`i`：`dp[i-1][j]`**；**放物品`i`：`dp[i-1][j-weigth[i]]+value[i]`
   - **dp数组如何初始化**：`dp[i][0]=0`（背包没有容量）；`dp[0][j]=存放物品0时，不同容量背包所能存放的最大价值`；其他无所谓
   - **确定遍历顺序**：从左到右，从上到下
   
   ```c++
   #include <iostream>
   #include <vector>
   using namespace std;
   int main(){
       int M,N;
       cin >> M >> N;
       vector<int> costs(M,0);
       vector<int> values(M,0);
   
       for(int i = 0; i < M; i++){
           cin >> costs[i];
       }
       for(int i = 0; i < M; i++){
           cin >> values[i];
       }
   
       vector<vector<int>> dp(M, vector<int>(N + 1, 0));
       for(int j = costs[0]; j <= N; j++){
           dp[0][j] = values[0];
       }
   
       for(int i = 1; i < M; i++) { // 遍历科研物品
           for(int j = 0; j <= N; j++) { // 遍历行李箱容量
               if(j < costs[i])
                   dp[i][j] = dp[i - 1][j];
               else
                   dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - costs[i]] + values[i]);
           }
       }
       cout << dp[M - 1][N] << endl;
   
       return 0;
   }
   ```
   
2. ==进阶：一维数组（滚动数组）==

   - **`dp[j]`**：**容量为`j`的背包，价值总和最大是`dp[j] `。**

   - **确定递推公式**：`dp[j] = max(dp[j],dp[j-weigth[i]]+value[i])`

   - **dp数组如何初始化**：`dp[0]=0`，由于最后要求max，所以所有位置都初始化成0

   - **确定遍历顺序**：物品正序遍历；背包**倒叙**遍历！——从 N 空间逐渐减少到当前研究材料所占空间cost[i]

   ```c++
   #include <iostream>
   #include <vector>
   using namespace std;
   
   int main() {
       // 读取 M 和 N
       int M, N;
       cin >> M >> N;
   
       vector<int> costs(M);
       vector<int> values(M);
   
       for (int i = 0; i < M; i++) {
           cin >> costs[i];
       }
       for (int j = 0; j < M; j++) {
           cin >> values[j];
       }
   
       // 创建一个动态规划数组dp，初始值为0
       vector<int> dp(N + 1, 0);
   
       // 外层循环遍历每个类型的研究材料
       for (int i = 0; i < M; ++i) {
           // 内层循环从 N 空间逐渐减少到当前研究材料所占空间
           for (int j = N; j >= costs[i]; --j) {
               // 考虑当前研究材料选择和不选择的情况，选择最大值
               dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
           }
       }
   
       // 输出dp[N]，即在给定 N 行李空间可以携带的研究材料最大价值
       cout << dp[N] << endl;
   
       return 0;
   }
   
   ```



##### **分割等和子集**

- **解题思路**：求集合里能否出现总和为` sum / 2` 的子集  ->  大小为`sum / 2`的背包，每个物品价值 = 重量

- **如果`dp[j] == j` ，说明集合中的子集总和正好可以凑成总和j**

  ```c++
  class Solution {
  public:
      bool canPartition(vector<int>& nums) {
          int sum = 0;
          for (int i = 0; i < nums.size(); i++) {
              sum += nums[i];
          }
          if (sum % 2 == 1)
              return false;
          int target = sum / 2;
          vector<int> dp(10001, 0);
          for (int i = 0; i < nums.size(); i++) {
              for (int j = target; j >= nums[i]; j--) {
                  dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
              }
          }
          if (dp[target] == target)
              return true;
          return false;
      }
  };
  ```



##### **最后一块石头的重量II** 

- **解题思路**：尽量让石头分成重量相同的两堆（尽可能相同，重量为`sum/2`），相撞之后剩下的石头就是最小的。

```c++
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = 0;
        for (int i = 0; i < stones.size(); i++) {
            sum += stones[i];
        }
        int target = sum / 2;
        vector<int> dp(1501, 0);
        for (int i = 0; i < stones.size(); i++) {
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }
};
```



##### **目标和**

- **解题思路**：假设加法的总和为`x`，那么减法对应的总和就是`sum - x`；而目标总和target，则`x - (sum - x) = target`，即得到`x = (target + sum) / 2`。

- **`dp[j]`**：装满容量为`j`的背包，有`dp[j]`种方法。

- **确定递推公式**：`dp[j] += dp[j-nums[i]]`

- **dp数组如何初始化**：`dp[0]=1`，其他位置都初始化成0

- **确定遍历顺序**：物品正序遍历；背包**倒叙**遍历！

```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (abs(target) > sum)
            return 0;
        if ((target + sum) % 2 == 1)
            return 0;
        int bagSize = (sum + target) / 2;
        vector<int> dp(1001, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = bagSize; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};
```



##### **一和零**

- **解题思路**：找出并返回 strs 的最大子集的大小，该子集中 **最多 有 m 个 0 和 n 个 1** 。
  - 这个背包有两个维度，一个是m 一个是n，而不同长度的字符串就是不同大小的待装物品。
  
- **`dp[i][j]`**：装满`i`个0，`j`个1，最多有`dp[i][j]`个物品 =>  求`dp[m][n]`

- **确定递推公式**：`dp[i][j] = max(dp[i-x][j-y]+1,dp[i][j])`

- **dp数组如何初始化**：`dp[0][0]=0`，由于最后要求max，所以所有位置都初始化成0

- **确定遍历顺序**：物品正序遍历；背包**倒叙**遍历

```c++
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(101, vector<int>(101, 0));
        for (string str : strs) {
            // 先正序遍历物品
            int zero_num = 0;
            int one_num = 0;
            for (char c : str) {
                if (c == '0') {
                    zero_num++;
                } else {
                    one_num++;
                }
            }
            // 倒序遍历背包
            for (int i = m; i >= zero_num; i--) {
                for (int j = n; j >= one_num; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zero_num][j - one_num] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
```



#### 完全背包

1. ==基础解法：二维dp数组==

   - **题意**：有N件物品和一个最多能背重量为W的背包。第i件物品的重量是weight[i]，得到的价值是value[i] 。**每件物品都有无限个（也就是可以放入背包多次）**，求解将哪些物品装入背包里物品价值总和最大。

   - **`dp[i][j]`：**`i` 表示物品、`j`背包容量，`dp[i][j] `表示从下标为`[0-i]`的物品里任意取，**每个物品可以取无限次**，放进容量为`j`的背包，价值总和最大是`dp[i][j] `。

   - **确定递推公式**：`dp[i][j] = max(dp[i-1][j],dp[i-1][j-weigth[i]]+value[i])`
     
   - **dp数组如何初始化**：`dp[i][0]=0`（背包没有容量）；`dp[0][j]=存放物品0时，如果能放下weight[0]就一直装`；其他无所谓
   
   - **确定遍历顺序**：物品正序遍历；背包**正序**遍历。**二层遍历可以颠倒**

   ```c++
   #include <iostream>
   #include <vector>
   using namespace std;
   int main(){
       int n, bagSize;
       cin >> n >> bagSize;
       
       vector<int> costs(n, 0);
       vector<int> values(n, 0);
   
       for(int i = 0; i < n; i++){
           cin >> costs[i];
           cin >> values[i];
       }
   
       // 初始化dp数组
       vector<vector<int>> dp(n, vector<int>(bagSize + 1, 0));
       for(int j = costs[0]; j <= bagSize; j++){
           dp[0][j] = dp[0][j - costs[0]] + values[0];
       }
       // 遍历dp
       for(int i = 1; i < n; i++){
           for(int j = 0; j <= bagSize; j++){
               if (j < costs[i]) 
                   dp[i][j] = dp[i - 1][j];
               else 
                   dp[i][j] = max(dp[i - 1][j], dp[i][j - costs[i]] + values[i]);
           }
       }
   
       cout << dp[n - 1][bagSize] << endl;
   
       return 0;
   }
   ```
   
2. ==进阶：一维数组（滚动数组）==

   - **`dp[j]`**：容量为`j`的背包，价值总和最大是`dp[j] `。

   - **确定递推公式**：`dp[j] = max(dp[j], dp[j - weight[i]] + value[i])`

   - **dp数组如何初始化**：`dp[0]=0`

   - **确定遍历顺序**：物品正序遍历；背包**正序**遍历。**二层遍历可以颠倒**

   ```c++
   #include <iostream>
   #include <vector>
   using namespace std;
   int main(){
       int n, bagSize;
       cin >> n >> bagSize;
   
       vector<int> costs(n, 0);
       vector<int> values(n, 0);
   
       for(int i = 0; i < n; i++){
           cin >> costs[i];
           cin >> values[i];
       }
   
       for(int i = 0; i < n; i++){
           for(int j = costs[i]; j <= bagSize; j++){
               dp[j] = max(dp[j], dp[j - costs[i]] + values[i]);
           }
       }
   
       cout << dp[bagSize] << endl;
   
       return 0;
   }
   ```
   

- **遍历顺序**
  - 如果求组合数，外层for循环遍历物品，内层for遍历背包。
  - 如果求排列数，外层for遍历背包，内层for循环遍历物品。



##### **零钱兑换II（求组合）**

- **`dp[j]`**：装满容量为`j`的背包，有`dp[j] `种方法，求`dp[amount]`

- **确定递推公式**：`dp[j] += dp[j - coins[j])`

- **dp数组如何初始化**：`dp[0]=1`

- **确定遍历顺序**：先遍历物品，再遍历背包

```c++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j] < INT_MAX - dp[j - coins[i]]) { // 防止相加数据超int
                    dp[j] += dp[j - coins[i]];
                }
            }
        }
        return dp[amount];
    }
};
```



##### **组合总和IV（求排列）**

- **题意**：顺序不同的序列被视作不同的组合

```c++
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<uint64_t> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 0; j <= target; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j - nums[i] >= 0) {
                    dp[j] += dp[j - nums[i]];
                }
            }
        }
        return dp[target];
    }
};
```



##### **爬楼梯（求排列）**

- **题意：**一共n阶，每次只能爬m个台阶（物品重量 = 每次的步数；背包容量 = 楼顶的台阶数）

- **确定遍历顺序**：先爬一阶，再爬两阶；先爬两阶，再爬一阶，是两种方法 -> 求排列

```c++
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int bagSize, MaxStep;
    cin >> bagSize >> MaxStep;

    vector<int> dp(bagSize + 1, 0);
    dp[0] = 1;
    for(int j = 1; j <= bagSize; j++){  // 遍历背包
        for(int i = 1; i<= MaxStep; i++){     //遍历物品
            if(j - i >= 0){
                dp[j] += dp[j - i];
            }
        }
    }
    cout << dp[bagSize] << endl;
    return 0;
}
```



##### **零钱兑换**

- **`dp[j]`**：装满容量为`j`的背包，所需的最少物品为`dp[j] `，求`dp[amount]`
- **确定递推公式**：`dp[j] = min(dp[j - coins[i]] + 1, dp[j])`
- **dp数组如何初始化**：`dp[0]=0`，因为这里要求min，所以其余初始成INT_MAX
- **注意：**如果`dp[j - coins[i]]`是初始值则跳过，否则会越界

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 背包大小：amount；物品：coins
        // dp：装满容量为j的背包，最少需要dp[j]个物品
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j - coins[i]] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
                }
            }
        }
        if (dp[amount] == INT_MAX) // 凑不出amount
            return -1;
        return dp[amount];
    }
};
```



##### **完全平方数拼凑正整数**（求最小值）

- **题意：**物品 = 平方数；背包容量 = 目标数值。

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++) {
            for (int j = i * i; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - i * i] + 1);
            }
        }
        return dp[n];
    }
};
```



##### **单词拆分**

- **题意**：拆分单词，是否出现在字典里 -> **（反过来）字典里的物品，是否可以组成单词**

- **`dp[j]`**：字符串长度为`j`的单词，能被字典中的单词组成，则`dp[j]=true`，求`dp[s.size()]`。

- **确定递推公式**：`wordSet.find(word) != wordSet.end() && dp[j]`

  - 如果确定`dp[j]` 是true，且 `[j, i]` 这个区间的子串出现在字典里，那么`dp[i]`一定是true。

- **dp数组如何初始化**：`dp[0]=true`，其他为false

- **确定遍历顺序**：先遍历背包，再遍历物品（求排列）

  - `s = "applepenapple"`, `wordDict = ["apple", "pen"]` 
- 只有物品的组合是 `"apple" + "pen" + "apple"`才能组成 背包`"applepenapple"`，强调物品之间顺序。

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int j = 1; j <= s.size(); j++) { // 遍历背包：最终单词s
            for (int i = 0; i < j; i++) {     // 遍历物品：字典
                string word = s.substr(i, j - i); // substr(起始位置，截取的个数)
                if (wordSet.find(word) != wordSet.end() && dp[i] == true) {
                    dp[j] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
```



#### 多重背包

- 有`N`种物品和一个容量为`V` 的背包。第`i`种物品最多有`Mi`件可用，每件耗费的空间是`Ci` ，价值是`Wi` 。
- 求解将哪些物品装入背包可使这些物品的耗费的空间 总和不超过背包容量，且价值总和最大。

```c++
#include<iostream>
#include<vector>
using namespace std;
int main() {
    int bagWeight,n;
    cin >> bagWeight >> n;
    vector<int> weight(n, 0);
    vector<int> value(n, 0);
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) cin >> weight[i];
    for (int i = 0; i < n; i++) cin >> value[i];
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> dp(bagWeight + 1, 0);

    for(int i = 0; i < n; i++) { // 遍历物品
        for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
            // 以上为01背包，然后加一个遍历个数
            for (int k = 1; k <= nums[i] && (j - k * weight[i]) >= 0; k++) { // 遍历个数
                dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
            }
        }
    }

    cout << dp[bagWeight] << endl;
}
```



### 打家劫舍

#### **打家劫舍（数组）**

- **`dp[i]`**：对于`0-i`的房间数，能偷到的最大金额`dp[i] `，求`dp[nums.size()-1]`
- **确定递推公式**：`dp[i] = max(dp[i-1],dp[i-2]+nums[i])`
- **dp数组如何初始化**：`dp[0]=nums[0]`，`dp[1]=max(nums[0],nums[1])`
- **确定遍历顺序**：从小到大遍历

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }
};
```



#### **打家劫舍II（环）**

- **题意**：把首尾相连，连成环了。

- Eg. 分析环的首尾元素（情况二和情况三，**包含了情况一**）

  - 情况一：考虑不包含首尾元素
  - 情况二：考虑包含首元素，不包含尾元素
  - 情况三：考虑包含尾元素，不包含首元素

  ```c++
  class Solution {
  public:
      int robRange(vector<int>& nums, int start, int end) {
          if (end == start)
              return nums[start];
          vector<int> dp(nums.size());
          dp[start] = nums[start];
          dp[start + 1] = max(nums[start], nums[start + 1]);
          for (int i = start + 2; i <= end; i++) {
              dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
          }
          return dp[end];
      }
      int rob(vector<int>& nums) {
          if (nums.size() == 1)
              return nums[0];
          int result1 = robRange(nums, 0, nums.size() - 2);
          int result2 = robRange(nums, 1, nums.size() - 1);
          return max(result1, result2);
      }
  };
  ```
  
  

#### **打家劫舍III（二叉树）**

- **题意**：二叉树相连的两个节点不能偷

- **`dp[i]`**：每一层都用一个长度为`2`的`dp`数组来维护（**`dp[0]`偷当前节点，获得的最大金钱；`dp[1]`不偷获得的最大金钱**）

- **递归函数**：`vector<int> traversal(TreeNode* cur)`

- **终止条件**：`if (cur == NULL) return vector<int>{0, 0};`

- **单层逻辑**：遍历顺序，左右中

```c++
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> result = traversal(root);
        return max(result[0], result[1]);
    }
    // 每个节点都有长度为2的数组，vec[0]：偷，vec[1]：不偷
    vector<int> traversal(TreeNode* cur) {
        if (cur == NULL) {
            return {0, 0};
        }
        vector<int> left = traversal(cur->left);
        vector<int> right = traversal(cur->right);
        int val1 = cur->val + left[1] + right[1]; // 偷当前节点
        int val2 = max(left[0], left[1]) + max(right[0], right[1]); // 不偷当前节点
        return {val1, val2};
    }
};
```




### 买卖股票的最佳时机

#### **股票：只能买卖一次**

- **`dp[i][j]`**：对于第`i`天，`dp[i][0]`持有这只股票，获得的最大金钱；`dp[i][1]`不持有这只股票，获得的最大金钱

- **确定递推公式**：
  - `dp[i][0] = max(dp[i-1][0],-prices[i])` （保持持有，买入）
  
  - `dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i])`（保持没有，卖出）
  
- **dp数组如何初始化**：`dp[0][0]=-prices[0]`，`dp[0][1]=0`

- **确定遍历顺序**：从小到大

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++) {
            // dp[i][0] 持有；dp[i][1] 卖出
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }
};
```



#### **股票：可以买卖多次**

- **区别**：多次买卖，那么买入时，应该是当前手上的现金 - 买入的价格
- **确定递推公式**：
  - `dp[i][0] = max(dp[i-1][0],dp[i-1][1]-prices[i])` （已经持有+买入）

  - `dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i])`（已经没有+卖出）

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++) {
            // 0：买入；    1：卖出
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }
};
```



#### **股票：最多买卖两次**

- **`dp[i][j]`含义和递推公式**
  - `dp[i][0]`：没有操作  `dp[i][0] = dp[i-1][0]`
  - `dp[i][1]`：第一次持有股票  `dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i])`
  - `dp[i][2]`：第一次不持有股票  `dp[i][2] = max(dp[i-1][2],dp[i-1][1]+prices[i])`
  - `dp[i][3]`：第二次持有股票  `dp[i][3] = max(dp[i-1][3],dp[i-1][2]-prices[i])`
  - `dp[i][4]`：第二次不持有股票  `dp[i][4] = max(dp[i-1][4],dp[i-1][3]+prices[i])`
  
- **dp数组如何初始化**：`dp[0][0]=0`，`dp[0][1]=-prices[0]`，`dp[0][2]=0`，`dp[0][3]=-prices[0]`，`dp[0][4]=0`

- **确定遍历顺序**：从小到大


```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
        // dp[i][0]：没有操作
        // dp[i][1]：第一次持有股票    dp[i][2]：第一次不持有股票
        // dp[i][3]：第二次持有股票    dp[i][4]：第二次不持有股票
        dp[0][1] = dp[0][3] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
        }
        return dp[prices.size() - 1][4];
    }
};
```



#### **股票：最多买卖k次**

- `dp[i][j]`含义和递推公式：
  - ` dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1])`
  - `dp[i][2] = max(dp[i - 1][1] + prices[i], dp[i - 1][2])`


```c++
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
        // dp[i][0]：没有操作   (j从0-2k+1)
        // dp[i][j + 1]：第k次持有股票    dp[i][j + 2]：第k次不持有股票
        for (int j = 1; j < 2 * k; j += 2) {
            dp[0][j] = -prices[0];
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < 2 * k - 1; j += 2) {
                dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] - prices[i]);
                dp[i][j + 2] =
                    max(dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i]);
            }
        }
        return dp[prices.size() - 1][2 * k];
    }
};
```



#### **股票：买卖多次，卖出有一天冷冻期**

- **`dp[i][j]`含义和递推公式**
  - 买入股票：`dp[i][0] = max(dp[i - 1][0], dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i])`
  - 保持卖出：`dp[i][1] = max(dp[i - 1][1], dp[i - 1][3])`（无股票在手）
  - 今天卖出：`dp[i][2] = dp[i - 1][0] + prices[i]`
  - 冷冻期：`dp[i][3] = dp[i - 1][2]`

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(4, 0));
        dp[0][0] -= prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
            dp[i][2] = dp[i - 1][0] + prices[i];
            dp[i][3] = dp[i - 1][2];
        }
        return max(dp[prices.size() - 1][3], max(dp[prices.size() - 1][1], dp[prices.size() - 1][2]));
    }
};
```



#### 股票：买卖多次，每次有手续费

- **区别：**卖股票的时候，减去手续费
- **确定递推公式**：
  - `dp[i][0] = max(dp[i-1][0],dp[i-1][1]-prices[i])` （已经持有，买入）

  - **`dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]-fee)`**（已经没有，卖出）

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < prices.size(); i++) {
            // 0：买入；    1：卖出
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
        }
        return dp[prices.size() - 1][1];
    }
};
```



### 子序列问题

#### 子序列（连续）

##### **最长连续递增子序列**

- **`dp[i]`**：**从任意位置开始，但一定以是`nums[i]`为结尾的**，最长连续递增子序列的长度为`dp[j]`

- **确定递推公式**：`if (nums[i] > nums[i-1]) dp[i] = dp[i-1]+1`
  
- **dp数组如何初始化**：序列中至少有一个元素，所有初始值都为1

- **确定遍历顺序**：从小到大

- **注意**：最后求的结果是`dp`数组里面的**最大值**！**(不一定以`dp[nums.size()-1]`结尾)**

```c++
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
            if (dp[i] > result) {
                result = dp[i];
            }
        }
        return result;
    }
};
```



##### **最长连续重复子数组**

- **`dp[i][j]`**：以**下标`i - 1`**为结尾的`nums1`，和以**下标`j - 1`**为结尾的`nums2`，最长连续重复子数组长度为`dp[i][j]`

- **确定递推公式**：`if(nums1[i - 1] ==nums2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1`

- **dp数组如何初始化**：`dp[i][0]`和`dp[0][j]`都初始化成0，全部初始化为0

- **确定遍历顺序**：从小到大

- **注意**：设置成下标`i-1`，**可以避免对`dp[i][0]行`和`dp[0][j]列`的初始化**

```c++
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                if (dp[i][j] > result) {
                    result = dp[i][j];
                }
            }
        }
        return result;
    }
};
```



##### **最大子数组和**

- **`dp[i]`**：以`nums[i]`为结尾的，最大连续子序列的和为`dp[j]`，求**dp数组中的最大值**

- **确定递推公式**：`dp[i] = max(dp[i - 1] + nums[i], nums[i])`
  
- **dp数组如何初始化**：`dp[0]=nums[0]`，其余都为0

- **确定遍历顺序**：从小到大

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 1)
            return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int result = dp[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            if (dp[i] > result) {
                result = dp[i];
            }
        }
        return result;
    }
};
```



#### 子序列（不连续）

##### **最长递增子序列**

- **`dp[i]`**：**从任意位置开始，但一定以是`nums[i]`为结尾的**，最长递增子序列的长度为`dp[j]`

- **确定递推公式**：`if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1)`

- **dp数组如何初始化**：序列中至少有一个元素，所有初始值都为1

- **确定遍历顺序**：从小到大

- **注意**：最后求的结果是`dp`数组里面的**最大值**！**(不一定以`dp[nums.size()-1]`结尾)**，所以应该定义`result`，存储`dp[i]`的最大值

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            if (dp[i] > result) {
                result = dp[i];
            }
        }
        return result;
    }
};
```



##### **最长公共子序列**

- **`dp[i][j]`**：长度为`[0, i - 1]`的字符串text1与长度为`[0, j - 1]`的字符串text2的最长公共子序列为`dp[i][j]`

  - 不是以**下标`i - 1`**为结尾的`text1`，和以**下标`j - 1`**为结尾的`text2`

- **确定递推公式**：
  - 如果`text1[i - 1]` 与 `text2[j - 1]`相同，那么找到了一个公共元素，所以`dp[i][j] = dp[i - 1][j - 1] + 1`
  
  - 如果`text1[i - 1]` 与 `text2[j - 1]`不相同，那就取最大的。即：`dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`
  
- **dp数组如何初始化**：`dp[i][0]`和`dp[0][j]`都初始化成0

- **确定遍历顺序**：从上到下，从左到右

- **注意**：设置成下标`i-1`，可以避免对`dp[i][0]`和`dp[0][j]`的初始化


```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
                if (dp[i][j] > result) {
                    result = dp[i][j];
                }
            }
        }
        return result;
    }
};
```



##### **不相交的线**

- **题意：**本题说是求绘制的最大连线数，其实就是求两个字符串的**最长公共子序列的长度**！

```c++
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
        int result = 0;
        for (int i = 1; i <= nums1.size(); i++) {
            for (int j = 1; j <= nums2.size(); j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
                if (dp[i][j] > result) {
                    result = dp[i][j];
                }
            }
        }
        return result;
    }
};
```



#### 编辑距离

##### **判断子序列**

- **`dp[i][j]`**：以**下标`i - 1`**为结尾的字符串`s`，和以**下标`j - 1`**为结尾的字符串`t`的最长公共子序列长度为`dp[i][j]`

- **确定递推公式**：

  ```c++
  if (s[i - 1] == t[j - 1]) {
      dp[i][j] = dp[i - 1][j - 1] + 1;
  } else {
      dp[i][j] = dp[i][j - 1];
  }
  ```

- **dp数组如何初始化**：`dp[i][0]`和`dp[0][j]`都初始化成0

- **确定遍历顺序**：从上到下，从左到右

- **注意**：如果`dp[i][j]=s.size()`，那么字符串s为字符串t的子序列

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        if (dp[s.size()][t.size()] == s.size()) {
            return true;
        }
        return false;
    }
};
```



##### **不同的子序列**

- **`dp[i][j]`**：以`i-1`为结尾的`s`子序列中出现以`j-1`为结尾的`t`的个数为`dp[i][j]`

- **确定递推公式**：

  ```c++
  if (s[i - 1] == t[j - 1]) {
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
  } else {
      dp[i][j] = dp[i - 1][j];
  }
  ```

- **dp数组如何初始化**：`dp[i][0]=1`,`dp[0][j]=0`,`dp[0][0]=1`

- **确定遍历顺序**：从上到下，从左到右


```c++
class Solution {
public:
    int numDistinct(string s, string t) {
        // dp[i][j]:以i-1为结尾的s子序列中出现以j-1为结尾的t的个数
        vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1, 0));
        // 初始化！
        for (int i = 0; i < s.size(); i++)
            dp[i][0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};
```



##### **两个字符串的删除操作**

- **`dp[i][j]`**：以`i-1`为结尾的字符串`word1`，和以`j-1`为结尾的字符串`word2`，想要达到相等，所需要删除元素的最少次数为`dp[i][j]`。

- **确定递推公式**：

  ```c++
  if (word1[i - 1] == word2[j - 1]) {
      dp[i][j] = dp[i - 1][j - 1];
  } else {
      dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
  }
  ```

- **dp数组如何初始化**：`dp[i][0]=i`,`dp[0][j]=j`,`dp[0][0]=0`

- **确定遍历顺序**：从上到下，从左到右


```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        // 求相同的最大长度，ans = len1+len2-dp[len1][len2]
        int len1 = word1.size(), len2 = word2.size();
        // dp[i][j]: 以i-1为结尾的word1和以j-1为结尾的word2的最长公共子序列长度
        int result = 0;
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                }
                if (dp[i][j] > result) {
                    result = dp[i][j];
                }
            }
        }
        return len1 + len2 - result * 2;
    }
};
```



##### **编辑距离**

- **`dp[i][j]`**：以`i-1`为结尾的字符串`word1`，和以`j-1`为结尾的字符串`word2`，想要达到相等，最少操作次数为`dp[i][j]`。

- **确定递推公式**：

  ```c++
  if (word1[i - 1] == word2[j - 1]) {
      dp[i][j] = dp[i - 1][j - 1];
  } else {
      dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1,dp[i - 1][j - 1] + 1));
  }
  ```

  - 增：word2添加一个元素，相当于word1删除一个元素 -> 增加=删除
  - 删：`min(dp[i - 1][j] + 1, dp[i][j - 1] + 1)`
  - **替：`dp[i - 1][j - 1] + 1`**

- **dp数组如何初始化**：`dp[i][0]=i`,`dp[0][j]=j`,`dp[0][0]=0`

- **确定遍历顺序**：从上到下，从左到右

```c++
class Solution {
public:
    int minDistance(string word1, string word2) {
        // dp[i][j]: 将 word1 转换成 word2 所使用的最少操作数
        int len1 = word1.size(), len2 = word2.size();
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        // 初始化
        for (int i = 1; i <= len1; i++)
            dp[i][0] = i;
        for (int j = 1; j <= len2; j++)
            dp[0][j] = j;
        // 递推公式
        // 插入 = 删除：min(dp[i - 1][j] + 1, dp[i][j - 1] + 1)
        // 替换：dp[i-1][j-1] + 1
        for (int i = 1; i <= word1.size(); i++) {
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] =
                        min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[len1][len2];
    }
};
```



##### 正则表达式匹配

- **问题**：用字符规律`p`匹配字符串 `s` ，其中`p`有`.`和`*`，`'.'` 匹配任意单个字符；`'*'` 匹配零个或多个前面的那一个元素
- **注意**：由于 `dp[0][0]` 代表的是空字符的状态， 因此 `dp[i][j]` 对应的添加字符是 `s[i - 1]` 和 `p[j - 1]` 。
- `dp[i][j]`：以`i - 1`结尾的`s`与以`j - 1`结尾的`p[..j]`是否能够匹配，所求为`dp[s.size()-1][p.size()-1]`
- **递推公式**：
  - 当 `p[j - 1] = '*'` 时， `dp[i][j]` 在当以下任一情况为 true 时等于 true ：
    - `dp[i][j - 2]`： 即将字符组合 p[j - 2] * 看作出现 0 次时，能否匹配。
    - `dp[i - 1][j] 且 s[i - 1] = p[j - 2]`: 即让字符 p[j - 2] 多出现 1 次时，能否匹配。
    - `dp[i - 1][j] 且 p[j - 2] = '.'`: 即让字符 '.' 多出现 1 次时，能否匹配。
  - 当 `p[j - 1] != '*'` 时， `dp[i][j]`在当以下任一情况为 true 时等于 true ：
    - `dp[i - 1][j - 1] 且 s[i - 1] = p[j - 1]`： 即让字符 p[j - 1] 多出现一次时，能否匹配。
    - `dp[i - 1][j - 1] 且 p[j - 1] = '.'`： 即将字符 . 看作字符 s[i - 1] 时，能否匹配。
- **初始化**：
  - `dp[0][0] = true`： 代表两个空字符串能够匹配。
  - `dp[0][j] = dp[0][j - 2] 且 p[j - 1] = '*'`： **首行 s 为空字符串，因此当 p 的偶数位为 * 时才能够匹配**（即让 p 的奇数位出现 0 次，保持 p 是空字符串）。因此，循环遍历字符串 p ，步长为 2（即只看偶数位）。

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.size(), pLen = p.size();
        vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1, false));
        // 初始化
        dp[0][0] = true;
        for (int j = 2; j < pLen + 1; j += 2) {
            dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
        }
        // 递推公式
        for (int i = 1; i < sLen + 1; i++) {
            for (int j = 1; j < pLen + 1; j++) {
                // 没有*
                if (p[j - 1] != '*') {
                    if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
                        dp[i][j] = dp[i - 1][j - 1];
                }
                // 使用*匹配0个、1个、多个
                else {
                    if (dp[i][j - 2]) // 匹配0次
                        dp[i][j] = true;
                    else if (dp[i - 1][j] && s[i - 1] == p[j - 2]) // 匹配1次
                        dp[i][j] = true;
                    else if (dp[i - 1][j] && p[j - 2] == '.') // 匹配.
                        dp[i][j] = true;
                }
            }
        }
        return dp[sLen][pLen];
    }
};
```



#### 回文

##### **回文子串**

- **`bool dp[i][j]`**：表示区间范围`[i,j]` （注意是左闭右闭）的子串是否是回文子串，如果是`dp[i][j]`为`true`，否则为`false`。

- **确定递推公式**：
  - 当`s[i]`与`s[j]`不相等，那`dp[i][j]`一定是`false`。
  
  - 当`s[i]`与`s[j]`相等时，
    - 情况一：下标`i`与`j`相同，例如`a`，当然是回文子串
    - 情况二：下标`i`与`j`相差为1，例如`aa`，也是回文子串
    - 情况三：下标`i - j > 1`的时候，例如`cabac`，那么，`if(dp[i + 1][j - 1]) dp[i][j] = true`
  
- **dp数组如何初始化**：全部都是false

- **确定遍历顺序**：**从下往上**，从左到右

```c++
class Solution {
public:
    int countSubstrings(string s) {
        // dp[i][j]:区间范围[i,j]的子串是否是回文子串
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    // 如果i和j下标相差1，即aa或a，则回文
                    if (j - i <= 1) {
                        result++;
                        dp[i][j] = true;
                    } else if (dp[i + 1][j - 1]) {
                        // 否则，判断dp[i+1][j-1]是否回文
                        result++;
                        dp[i][j] = true;
                    }
                }
                // 若s[i] != s[j]，不是回文
            }
        }
        return result;
    }
};
```



##### **最长回文子序列**

- **`dp[i][j]`**：字符串s在`[i, j]`范围内最长的回文子序列的长度为`dp[i][j]`。

- **确定递推公式**：

  ```c++
  if (s[i] == s[j]) {
      dp[i][j] = dp[i + 1][j - 1] + 2;
  } else {
      dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
  }
  ```

- **dp数组如何初始化**：当`i`与`j`相同，那么`dp[i][j]=1`，其他默认为0

- **确定遍历顺序**：从下往上，从左到右

```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        // dp:区间[i,j]的最长回文子序列长度
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        // i = j 时，dp[i][j] = 1
        for (int i = 0; i < s.size(); i++)
            dp[i][i] = 1;
        // 递推公式
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};
```



##### **最长回文子串**

- **`dp[i][j]`**：字符串`s[i:j]`是否为回文子串

- **确定递推公式**：只有` s[i+1:j−1] `是回文串，并且 *s* 的第 *i* 和 *j* 个字母相同时，`s[i:j]`才会是回文串。

- **dp数组如何初始化**：当`i`与`j`相同，那么`dp[i][j]=1`，其他默认为0

- **确定遍历顺序**：枚举子串长度，从左边界开始

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        // dp:区间[i,j]是否为回文子串
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        // i = j 时，dp[i][j] = 1
        for (int i = 0; i < s.size(); i++)
            dp[i][i] = 1;
        // 递推公式
        int maxLen = 1;
        int begin = 0;
        // 先枚举子串长度，左边界i，长度L，右边界j = i + L -1
        for (int L = 2; L <= s.size(); L++) {
            for (int i = 0; i < s.size(); i++) {
                int j = L + i - 1;
                if (j >= s.size()) {   // 右边界越界
                    break;
                }
                if (s[i] != s[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                // 只要 dp[i][L] == true 成立，就表示子串 s[i..L]是回文
                // 此时记录回文长度和起始位置
                if (dp[i][j] && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};
```



## √单调栈

通常是**一维数组**，要寻找**任一个元素的右边或者左边第一个比自己大或者小的元素**。时间复杂度为**O(n)**。

单调栈的作用是：**用一个栈来记录当前遍历过的元素**

### 每日温度

- **题意**：给定一个整数数组 `temperatures` ，表示每天的温度，返回一个数组 `answer` ，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。
  - **解析**：找到右边第一个比当前元素**大的**，下标相减。

- 栈内为**当前元素的下标**，从**栈头到栈底**保持**递增单调栈**
  - 当前遍历的元素**小于**栈顶元素的情况`temperatures[i] < temperatures[st.top()]`：压入栈内
  - 当前遍历的元素**等于**栈顶元素的情况`temperatures[i] == temperatures[st.top()]`：压入栈内
  - 当前遍历的元素**大于**栈顶元素的情况`temperatures[i] > temperatures[st.top()]`：记录result，弹出栈内元素，直到小于


```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        vector<int> result(temperatures.size(), 0);
        st.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            if (temperatures[i] < temperatures[st.top()]) {
                st.push(i);
            } else if (temperatures[i] == temperatures[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
```



### 下一个更大元素I

- **题意**：`nums1` 是 `nums2`的子集，找`nums1`中的元素在`nums2`右侧**第一个比当前元素大的元素**。
- **解决**：对`nums2`使用单调栈，同时在遍历`nums2`的过程中，判断`nums2[i]`是否在`nums1`中出现过，因为最后是要根据`nums1`元素的下标来更新`result`数组 => **使用map做映射**`unordered_map<int, int> umap; // key:元素，value：下标`
- 注意：当前遍历的元素T[i]大于栈顶元素T[st.top()]时，注意，**只有nums1中存在这个比较大的元素时，才可以更新nums1的下标**

```c++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st; // 建立递增单调栈（栈头到栈底，从小到大）
        vector<int> result(nums1.size(), -1);
        if (nums1.size() == 0)
            return result;

        unordered_map<int, int> umap; // key:元素，value：下标
        for (int i = 0; i < nums1.size(); i++) {
            umap[nums1[i]] = i;
        }
        st.push(0);
        for (int i = 1; i < nums2.size(); i++) {
            if (nums2[i] < nums2[st.top()]) {
                st.push(i);
            } else if (nums2[i] == nums2[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() && nums2[i] > nums2[st.top()]) {
                    if (umap.count(nums2[st.top()]) > 0) {
                        // 查看nums1里是否存在这个元素
                        int index = umap[nums2[st.top()]];
                        result[index] = nums2[i];
                    }
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
```



### 下一个更大元素II

- **题意**：给定一个**循环数组**，输出每个元素的下一个更大元素
- **解决**：模拟遍历两遍`nums`，注意一下都是用`i % nums.size()`来操作

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        st.push(0);
        vector<int> result(nums.size(), -1);
        for (int i = 0; i < nums.size() * 2; i++) {
            if (nums[i % nums.size()] < nums[st.top()]) {
                st.push(i % nums.size());
            } else if (nums[i % nums.size()] == nums[st.top()]) {
                st.push(i % nums.size());
            } else {
                while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                    result[st.top()] = nums[i % nums.size()];
                    st.pop();
                }
                st.push(i % nums.size());
            }
        }
        return result;
    }
};
```



### 接雨水

- **题意**：给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

  <img src="C:\Users\25225\AppData\Roaming\Typora\typora-user-images\image-20250731153302337.png" alt="image-20250731153302337" style="zoom:50%;" />

- **解决**：

  1. 首先单调栈是**按照行方向**来计算雨水；从**栈头到栈底**的顺序应该是**单调递增**的顺序，**栈里保存下标**。

  3. 遇到**相同高度的柱子**：更新栈内下标，就是将栈里元素（旧下标）弹出，将新元素（新下标）加入栈中。

  5. 当前遍历的元素（柱子）高度大于栈顶元素的高度，此时就出现凹槽

     **凹槽底部**：**弹出的栈顶元素**，下标记为`mid`，对应的高度为`height[mid]`（图中的高度1）

     **凹槽左边**：**此时的栈顶元素**，下标为`st.top()`，对应的高度为`height[st.top()]`（图中的高度2）

     **凹槽右边**：**当前遍历的元素**，下标为`i`，对应的高度为`height[i]`（就是图中的高度3）。

     雨水高度是 `min(凹槽左边高度, 凹槽右边高度) - 凹槽底部高度`，代码为：`int h = min(height[st.top()], height[i]) - height[mid];`

     雨水的宽度是 `凹槽右边的下标 - 凹槽左边的下标 - 1（因为只求中间宽度）`，代码为：`int w = i - st.top() - 1 ;`

  ```c++
  class Solution {
  public:
      int trap(vector<int>& height) {
          stack<int> st;
          st.push(0);
          int sum = 0;
          for (int i = 0; i < height.size(); i++) {
              if (height[i] < height[st.top()]) {
                  st.push(i);
              } else if (height[i] == height[st.top()]) {
                  st.pop();
                  st.push(i);
              } else {
                  while (!st.empty() && height[i] > height[st.top()]) {
                      int midHeight = height[st.top()];
                      st.pop();
                      if (!st.empty()) {
                          int h = min(height[i], height[st.top()]) - midHeight;
                          int w = i - st.top() - 1;
                          sum += w * h;
                      }
                  }
                  st.push(i);
              }
          }
          return sum;
      }
  };
  ```



### 柱状图中最大的矩形

- **题意**：给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积。

  <img src="./Note.assets/histogram.jpg" alt="img" style="zoom: 50%;" />

- **解决**【求每个柱子左右两边第一个**小于**该柱子的柱子】

  - 当前遍历的元素`heights[i]`**小于**栈顶元素`heights[st.top()]`，收获结果

    **矩形基准**：**弹出的栈顶元素**，下标记为`mid`，对应的高度为`height[mid]`（图中的高度60）

    **凹槽左边**：**此时的栈顶元素**，下标为`st.top()`，对应的高度为`height[st.top()]`（图中的高度40）

    **凹槽右边**：**当前遍历的元素**，下标为`i`，对应的高度为`height[i]`（就是图中的高度50）。

    **矩形高度**是 `矩形基准的高度`，代码为：`int h = height[mid];`

    **矩形宽度**是 `右边的下标 - 左边的下标 - 1`，代码为：`int w = i - st.top() - 1 ;`

- **注意**：需要在 height数组**前后各加一个元素0**

  - 为什么**数组尾部要加0**：如果数组本身就是升序的，例如[2,4,6,8]，那么入栈之后 都是单调递减，一直都没有走 情况三 计算结果的那一步，所以最后输出的就是0了。 

  - 为什么**数组头部要加0**：如果数组本身是降序的，例如 [8,6,4,2]，在 8 入栈后，6 开始与8 进行比较，此时我们得到 mid（8），right（6），但是得不到 left

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        st.push(0);
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        int result = 0;
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int w = i - st.top() - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};
```



### 最大矩形

- **题意**：给定一个仅包含 `0` 和 `1` 、大小为 `rows x cols` 的二维二进制矩阵，找出只包含 `1` 的最大矩形，并返回其面积

- **解决**：对于本题，设 *matrix* 有 *m* 行，我们可以枚举矩形的底边，求 *m* 次最大矩形

  <img src=".\Note.assets\1750330058-gMdckr-lc85.png" alt="lc85.png" style="zoom: 67%;" />

  - 以第一行为底的柱子高度为 [1,0,1,0,0]，最大矩形面积为 1。
  - 以第二行为底的柱子高度为 [2,0,2,1,1]，最大矩形面积为 3。
  - 以第三行为底的柱子高度为 [3,1,3,2,2]，最大矩形面积为 6。
  - 以第四行为底的柱子高度为 [4,0,0,3,0]，最大矩形面积为 4。
  - 答案为 max(1,3,6,4)=6。

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        st.push(0);
        int result = 0;
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.pop();
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int w = i - st.top() - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int MaxMatrix = 0;
        vector<int> heights(matrix[0].size() + 1, 0);
        heights.insert(heights.begin(), 0);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == '0') {
                    heights[j + 1] = 0;
                } else if (matrix[i][j] == '1') {
                    heights[j + 1]++;
                }
            }
            MaxMatrix = max(MaxMatrix, largestRectangleArea(heights));
        }
        return MaxMatrix;
    }
};
```



### 最大正方形

- **题意**：在一个由 `'0'` 和 `'1'` 组成的二维矩阵内，找到只包含 `'1'` 的最大正方形，并返回其面积

- **解决**：单调栈

```c++
class Solution {
public:
    // 使用单调栈寻找最大的正方形边长
    int largestLength(vector<int>& heights) {
        stack<int> st;
        st.push(0);
        int MaxLength = 0;
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) {
                st.push(i);
            } else if (heights[i] == heights[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int w = i - st.top() - 1;
                        int h = heights[mid];
                        MaxLength = max(MaxLength, min(w, h));
                    }
                }
                st.push(i);
            }
        }
        return MaxLength;
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        int MaxLength = 0;
        vector<int> heights(matrix[0].size() + 1, 0);
        heights.insert(heights.begin(), 0);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == '1') {
                    heights[j + 1]++;
                } else {
                    heights[j + 1] = 0;
                }
            }
            MaxLength = max(MaxLength, largestLength(heights));
        }
        return MaxLength * MaxLength;
    }
};
```



## 图论

### 基础理论

- **图的种类**： 有向图、无向图；加权图

- **度、出度、入度**：有几条边连接该节点，该节点就有几度

- **连通性**：

  - **连通图、非连通图**：在无向图中，任何两个节点都是可以到达的，我们称之为连通图
  - **连通分量**：在无向图中的**==极大==连通子图**，称之为该图的一个**连通分量**。
  - **强连通图**：在有向图中，任何两个节点是可以相互到达的，我们称之为强连通图。
  - **强连通分量**：在有向图中极大强连通子图，称之为该图的强连通分量。

- **图的构造**

  - **邻接矩阵**：使用**二维数组**来表示图结构。 邻接矩阵是从节点的角度来表示图，有多少节点就申请多大的二维数组。

    - 优点：

      - 表达方式简单，易于理解
      - 检查任意两个顶点间是否存在边的操作非常快
      - 适合**稠密图**，在边数接近顶点数平方的图中，邻接矩阵是一种空间效率较高的表示方法。

    - 缺点：

      - 遇到稀疏图，会导致申请过大的二维数组造成空间浪费 且遍历 边 的时候需要遍历整个n * n矩阵，造成时间浪费

  - **邻接表**：使用 **数组 + 链表**的方式来表示。邻接表是从边的数量来表示图，有多少边才会申请对应大小的链表。

    - 优点：

      - 对于**稀疏图**的存储，只需要存储边，空间利用率高
      - 遍历节点连接情况相对容易
  
    - 缺点：

      - 检查任意两个节点间是否存在边，效率相对低，需要 O(V)时间，V表示某节点连接其他节点的数量。
      - 实现相对复杂，不易理解
  
- **图的遍历**

  - **深度优先搜索DFS**

    ```c++
    vector<vector<int>> result; // 保存符合条件的所有路径
    vector<int> path; // 起点到终点的路径
    void dfs(图，目前搜索的节点) {
        if (终止条件) {
            存放结果;
            return;
        }
    
        for (选择：本节点所连接的其他节点) {
            处理节点;
            dfs(图，选择的节点); // 递归
            回溯，撤销处理结果
        }
    }
    ```

  - **广度优先搜索BFS**

    适合于解决两个点之间的最短路径问题

    ```c++
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向
    
    // grid 是地图，也就是一个二维数组
    // visited标记访问过的节点，不要重复访问
    // x,y 表示开始搜索节点的下标
    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        queue<pair<int, int>> que; 	 // 定义队列
        que.push({x, y}); 			// 起始节点加入队列
        visited[x][y] = true; 		// 只要加入队列，立刻标记为访问过的节点
        
        while(!que.empty()) { 		// 开始遍历队列里的元素
             // 从队列取元素
            pair<int ,int> cur = que.front(); 
            que.pop();
            
            // 当前节点坐标
            int curx = cur.first;
            int cury = cur.second; 
            for (int i = 0; i < 4; i++) { // 向当前节点的四个方向左右上下去遍历
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) 
                    continue;  // 坐标越界了，直接跳过
                if (!visited[nextx][nexty]) {     // 如果节点没被访问过
                    que.push({nextx, nexty});     // 队列添加该节点为下一轮要遍历的节点
                    visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
                }
            }
        }
    }
    ```
    



### 深搜与广搜

#### 所有可能的路径

- **题意**：给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。请编写一个函数，找出并返回所有从节点 1 到节点 n 的路径。

```c++
#include <iostream>
#include <vector>
using namespace std;
 
vector<vector<int>> result;
vector<int> path;
 
void dfs(const vector<vector<int>>& graph, int x, int n){
    // 当前遍历的节点x 到达节点n 
    if (x == n) { // 找到符合条件的一条路径
        result.push_back(path);
        return;
    }
 
    for (int i = 1; i <= n; i++) {  // 遍历节点x链接的所有节点
        if (graph[x][i] == 1) {     // 找到 x链接的节点
            path.push_back(i);      // 遍历到的节点加入到路径中来
            dfs(graph, i, n);       // 进入下一层递归
            path.pop_back();        // 回溯，撤销本节点
        }
    }
}
 
 
int main() {
    int n, m, i, j;
    cin >> n >> m; // 输入n个节点，m条边
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
 
    while (m--) {
        cin >> i >> j;
        graph[i][j] = 1;
    }
 
    path.push_back(1);
    dfs(graph, 1, n);
 
    // 输出结果
    if (result.size() == 0) 
        cout << -1 << endl;
    for(int i = 0; i < result.size(); i++){
        for(int j = 0; j < result[i].size(); j++){
            cout << result[i][j];
            if (j < result[i].size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}

```



#### **岛屿数量**

- **题意**：给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算岛屿的数量。岛屿由水平方向或垂直方向上相邻的陆地连接而成，并且四周都是水域。如图，有三座岛屿

  <img src="./Note.assets/20240411153209_67737.png" alt="img" style="zoom: 50%;" />

- **DFS思路**

  - 遇到一个没有遍历过的节点陆地，计数器就加一，然后**使用dfs把该节点陆地所能遍历到的陆地都标记上**。在遇到标记过的陆地节点和海洋节点的时候直接跳过。

    ```c++
    #include <iostream>
    #include <vector>
    using namespace std;
    
    int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0}; 
    void dfs(const vector<vector<int>> &graph,vector<vector<bool>> &visited,int x,int y){
        for(int i = 0; i < 4; i++){
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if(nextx < 0 || nextx >= graph.size() || nexty < 0 || nexty >= graph[0].size())
                continue;
            if(!visited[nextx][nexty] && graph[nextx][nexty] == 1){
                visited[nextx][nexty] = true;
                dfs(graph, visited, nextx, nexty);
            }
        }
    }
    int main(){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> graph(n, vector<int>(m, 0));
        vector<vector<bool>> visited(n, (vector<bool>(m, false)));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> graph[i][j];
            }
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (graph[i][j] == 1 && visited[i][j] == false) {
                    result++;
                    dfs(graph, visited, i, j);
                }
            }
        }
        cout << result << endl;
        return 0;
    }
    ```
  
- **BFS思路**：

  - 遇到一个没有遍历过的节点陆地，计数器就加一，然后**使用bfs把该节点陆地所能遍历到的陆地都标记上**。在遇到标记过的陆地节点和海洋节点的时候直接跳过。

    ```c++
    #include <iostream>
    #include <vector>
    #include <queue>
    using namespace std;
    
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向
    void bfs(vector<vector<int>>& graph, vector<vector<bool>>& visited, int x, int y){
        queue<pair<int, int>> que;  // 定义队列
        que.push({x, y});           // 起始节点加入队列
        visited[x][y] = true;       // 只要加入队列，立刻标记为访问过的节点
        while(!que.empty()){
            pair<int, int> cur = que.front();
            que.pop();
            // 当前节点坐标
            int curx = cur.first;
            int cury = cur.second; 
            for (int i = 0; i < 4; i++) {
                int nextx = curx + dir[i][0];
                int nexty = cury + dir[i][1];
                if (nextx < 0 || nextx >= graph.size() || nexty < 0 || nexty >= graph[0].size()) 
                    continue;
                if (!visited[nextx][nexty] && graph[nextx][nexty] == 1) {
                    que.push({nextx, nexty});     // 队列添加该节点为下一轮要遍历的节点
                    visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
                }
            }
        }
    }
    int main(){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> graph(n, vector<int>(m, 0));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> graph[i][j];
            }
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (graph[i][j] == 1 && visited[i][j] == false) {
                    result++;
                    bfs(graph, visited, i, j);
                }
            }
        }
        cout << result << endl;
        return 0;
    }
    ```
  
  

#### 岛屿的最大面积

- **题意**：给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算每个岛屿的最大面积
- **思路**：cnt作为全局变量，使用`dfs/bfs`把该节点所能遍历到的陆地都标记上，同时计算最大cnt。在遇到标记过的陆地节点和海洋节点的时候直接跳过。

  - **DFS：**

    ```c++
    class Solution {
    public:
        int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
        int cnt = 0;
        void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
            for (int i = 0; i < 4; i++) {
                int nextx = x + dir[i][0];
                int nexty = y + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                    continue;
                }
                if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                    visited[nextx][nexty] = true;
                    cnt++;
                    dfs(grid, visited, nextx, nexty);
                }
            }
        }
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            int MaxArea = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (!visited[i][j] && grid[i][j] == 1) {
                        cnt = 1;
                        visited[i][j] = true;
                        dfs(grid, visited, i, j);
                        MaxArea = max(MaxArea, cnt);
                    }
                }
            }
            return MaxArea;
        }
    };
    ```

  - **BFS：**

    ```c++
    class Solution {
    public:
        int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
        int cnt = 0;
        void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
            queue<pair<int, int>> que;
            que.push({x, y});
            visited[x][y] = true;
            while (!que.empty()) {
                pair<int, int> cur = que.front();
                que.pop();
                int curx = cur.first;
                int cury = cur.second;
                for (int i = 0; i < 4; i++) {
                    int nextx = x + dir[i][0];
                    int nexty = y + dir[i][1];
                    if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                        continue;
                    }
                    if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                        visited[nextx][nexty] = true;
                        cnt++;
                        bfs(grid, visited, nextx, nexty);
                    }
                }
            }
        }
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            int MaxArea = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (!visited[i][j] && grid[i][j] == 1) {
                        cnt = 1;
                        visited[i][j] = true;
                        bfs(grid, visited, i, j);
                        MaxArea = max(MaxArea, cnt);
                    }
                }
            }
            return MaxArea;
        }
    };
    ```



#### **孤岛的总面积**

- **题意**：给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算每个孤岛的总面积，**孤岛是那些位于矩阵内部、所有单元格都不接触边缘的岛屿。**

- **思路**：只要从周边找到陆地，然后通过`dfs`或者`bfs` 将周边靠陆地且相邻的陆地都变成海洋，然后再去重新遍历地图，统计此时还剩下的陆地就可以了。

  - **DFS**

    ```c++
    #include <iostream>
    #include <vector>
    using namespace std;
    
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
        grid[x][y] = 0;
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                continue;
            }
            if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                visited[nextx][nexty] = true;
                dfs(grid, visited, nextx, nexty);
            }
        }
    }
    
    int main(){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        vector<vector<bool>> visited(n, vector<bool>(m, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> grid[i][j];
            }
        }
        // 从边缘遍历，将边缘所在的孤岛都变为海洋
        // 遍历左右两列
        for(int i = 0; i < n; i++){
            if(grid[i][0] == 1){
                visited[i][0] = true;
                dfs(grid, visited, i, 0);
            }
            if(grid[i][m - 1] == 1){
                visited[i][m - 1] = true;
                dfs(grid, visited, i, m - 1);
            }
        }
        // 遍历上下两行
        for(int j = 0; j < m; j++){
            if(grid[0][j] == 1){
                visited[0][j] = true;
                dfs(grid, visited, 0, j);
            }
            if(grid[n - 1][j] == 1){
                visited[n - 1][j] = true;
                dfs(grid, visited, n - 1, j);
            }
        }
        // 重新遍历地图，查找剩余岛屿面积
        int cnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1){
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
        return 0;
    }
    ```
  
  - **BFS**
  
    ```c++
    #include <iostream>
    #include <vector>
    #include <queue>
    using namespace std;
    
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
    void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
        queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true;
        grid[x][y] = 0;
        while (!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            int curx = cur.first;
            int cury = cur.second;
            for (int i = 0; i < 4; i++) {
                int nextx = x + dir[i][0];
                int nexty = y + dir[i][1];
                if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                    continue;
                }
                if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                    visited[nextx][nexty] = true;
                    bfs(grid, visited, nextx, nexty);
                }
            }
        }
    }
    
    int main(){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        vector<vector<bool>> visited(n, vector<bool>(m, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> grid[i][j];
            }
        }
        // 从边缘遍历，将边缘所在的孤岛都变为海洋
        // 遍历左右两列
        for(int i = 0; i < n; i++){
            if(grid[i][0] == 1){
                visited[i][0] = true;
                bfs(grid, visited, i, 0);
            }
            if(grid[i][m - 1] == 1){
                visited[i][m - 1] = true;
                bfs(grid, visited, i, m - 1);
            }
        }
        // 遍历上下两行
        for(int j = 0; j < m; j++){
            if(grid[0][j] == 1){
                visited[0][j] = true;
                bfs(grid, visited, 0, j);
            }
            if(grid[n - 1][j] == 1){
                visited[n - 1][j] = true;
                bfs(grid, visited, n - 1, j);
            }
        }
        // 重新遍历地图，查找剩余岛屿面积
        int cnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1){
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
        return 0;
    }
    ```
  



#### 沉没孤岛

- **题意**：给定一个由 1（陆地）和 0（水）组成的矩阵，**孤岛是那些位于矩阵内部、所有单元格都不接触边缘的岛屿。**现在你需要将所有孤岛“沉没”，即将孤岛中的所有陆地单元格（1）转变为水域单元格（0）。

- **思路**：

  - 步骤一：深搜或者广搜将地图周边的 1 （陆地）全部改成 2 （特殊标记）

  - 步骤二：将水域中间 1 （陆地）全部改成 水域（0）

  - 步骤三：将之前标记的 2 改为 1 （陆地）

- **DFS**

  ```c++
  #include <iostream>
  #include <vector>
  using namespace std;
  
  int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
  void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
      grid[x][y] = 2;
      for (int i = 0; i < 4; i++) {
          int nextx = x + dir[i][0];
          int nexty = y + dir[i][1];
          if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
              continue;
          }
          if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
              visited[nextx][nexty] = true;
              dfs(grid, visited, nextx, nexty);
          }
      }
  }
  
  int main(){
      int n, m;
      cin >> n >> m;
      vector<vector<int>> grid(n, vector<int>(m, 0));
      vector<vector<bool>> visited(n, vector<bool>(m, 0));
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              cin >> grid[i][j];
          }
      }
      // 1.将地图周边的 1 （陆地）全部改成 2 （特殊标记）
      // 遍历左右两列
      for(int i = 0; i < n; i++){
          if(grid[i][0] == 1){
              visited[i][0] = true;
              dfs(grid, visited, i, 0);
          }
          if(grid[i][m - 1] == 1){
              visited[i][m - 1] = true;
              dfs(grid, visited, i, m - 1);
          }
      }
      // 遍历上下两行
      for(int j = 0; j < m; j++){
          if(grid[0][j] == 1){
              visited[0][j] = true;
              dfs(grid, visited, 0, j);
          }
          if(grid[n - 1][j] == 1){
              visited[n - 1][j] = true;
              dfs(grid, visited, n - 1, j);
          }
      }
      // 2.将水域中间 1 （陆地）全部改成 水域（0）
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              if(grid[i][j] == 1){
                  grid[i][j] = 0;
              }
          }
      }
      // 3.将之前标记的 2 改为 1 （陆地）
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              if(grid[i][j] == 2){
                  grid[i][j] = 1;
              }
          }
      }
      // 输出结果
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              cout << grid[i][j] << " ";
          }
          cout << endl;
      }
      return 0;
  }
  ```
  
- **BFS**

  ```C++
  #include <iostream>
  #include <vector>
  #include <queue>
  using namespace std;
  
  int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
  void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
      queue<pair<int, int>> que;
      que.push({x, y});
      visited[x][y] = true;
      grid[x][y] = 2;
      while (!que.empty()) {
          pair<int, int> cur = que.front();
          que.pop();
          int curx = cur.first;
          int cury = cur.second;
          for (int i = 0; i < 4; i++) {
              int nextx = x + dir[i][0];
              int nexty = y + dir[i][1];
              if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                  continue;
              }
              if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                  visited[nextx][nexty] = true;
                  bfs(grid, visited, nextx, nexty);
              }
          }
      }
  }
  
  int main(){
      int n, m;
      cin >> n >> m;
      vector<vector<int>> grid(n, vector<int>(m, 0));
      vector<vector<bool>> visited(n, vector<bool>(m, 0));
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              cin >> grid[i][j];
          }
      }
      // 1.将地图周边的 1 （陆地）全部改成 2 （特殊标记）
      // 遍历左右两列
      for(int i = 0; i < n; i++){
          if(grid[i][0] == 1){
              visited[i][0] = true;
              bfs(grid, visited, i, 0);
          }
          if(grid[i][m - 1] == 1){
              visited[i][m - 1] = true;
              bfs(grid, visited, i, m - 1);
          }
      }
      // 遍历上下两行
      for(int j = 0; j < m; j++){
          if(grid[0][j] == 1){
              visited[0][j] = true;
              bfs(grid, visited, 0, j);
          }
          if(grid[n - 1][j] == 1){
              visited[n - 1][j] = true;
              bfs(grid, visited, n - 1, j);
          }
      }
      // 2.将水域中间 1 （陆地）全部改成 水域（0）
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              if(grid[i][j] == 1){
                  grid[i][j] = 0;
              }
          }
      }
      // 3.将之前标记的 2 改为 1 （陆地）
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              if(grid[i][j] == 2){
                  grid[i][j] = 1;
              }
          }
      }
      // 输出结果
      for(int i = 0; i < n; i++){
          for(int j = 0; j < m; j++){
              cout << grid[i][j] << " ";
          }
          cout << endl;
      }
      return 0;
  }
  ```



#### 水流问题

- **题意**：给定一个 `m x n` 的整数矩阵 `heights` ， `heights[r][c]` 表示坐标 `(r, c)` 上单元格 **高于海平面的高度** 。如果相邻单元格的高度 **小于或等于** 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。矩阵的左边界和上边界被认为是第一组边界，而矩阵的右边界和下边界被视为第二组边界。返回网格坐标 `result` 的 **2D 列表** ，其中 `result[i] = [ri, ci]` 表示雨水从单元格 `(ri, ci)` 流动 **既可流向太平洋也可流向大西洋** 。

  <img src="./Note.assets/1743039781712.jpg" alt="1743039781712" style="zoom:50%;" />

- **思路**：从第一组边界上的节点 逆流而上，将遍历过的节点都标记上；同样从第二组边界的边上节点逆流而上。然后**两方都标记过的节点就是既可以流向第一组边界也可以流向第二组边界的节点**。

  ```c++
  class Solution {
  public:
      int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
      void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
          visited[x][y] = true;
          for (int i = 0; i < 4; i++) {
              int nextx = x + dir[i][0];
              int nexty = y + dir[i][1];
              if (nextx < 0 || nextx >= grid.size() || nexty < 0 ||
                  nexty >= grid[0].size()) {
                  continue;
              }
              if (!visited[nextx][nexty] && grid[nextx][nexty] >= grid[x][y]) {
                  visited[nextx][nexty] = true;
                  dfs(grid, visited, nextx, nexty);
              }
          }
      }
  
      vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
          int m = heights.size();
          int n = heights[0].size();
          vector<vector<bool>> firstBoarder(m, vector<bool>(n, 0));
          vector<vector<bool>> secondBoarder(m, vector<bool>(n, 0));
          // 从上下两行出发
          for (int j = 0; j < n; j++) {
              dfs(heights, firstBoarder, 0, j);
              dfs(heights, secondBoarder, m - 1, j);
          }
          // 从左右两列出发
          for (int i = 0; i < m; i++) {
              dfs(heights, firstBoarder, i, 0);
              dfs(heights, secondBoarder, i, n - 1);
          }
          // 两方都标记过的节点就是既可以流向第一组边界也可以流向第二组边界的节点。
          vector<vector<int>> result;
          for (int i = 0; i < m; i++) {
              for (int j = 0; j < n; j++) {
                  if (firstBoarder[i][j] && secondBoarder[i][j]) {
                      result.push_back({i, j});
                  }
              }
          }
          return result;
      }
  };
  ```



#### ***建造最大岛屿** 

- **题意**：给定一个由 1（陆地）和 0（水）组成的矩阵，你最多可以将矩阵中的一格水变为一块陆地，在执行了此操作之后，矩阵中最大的岛屿面积是多少。

- **思路**：
  
  - **第一步**：一次遍历地图，得出各个岛屿的面积，并做编号记录。
    - **记录方式**：使用map记录，key为岛屿编号，value为岛屿面积
    
    - **终止条件**：访问过的节点 或者 遇到海水
    
    - **注意**：如果整张地图都是陆地，直接返回总面积
    
  - **第二步**：再遍历地图，遍历0的方格（因为要将0变成1），并统计该1（由0变成的1）周边岛屿面积，将其相邻面积相加在一起，得到最大岛屿面积。
  - **注意**：在计算相邻岛屿面积时，需要检查相邻格子是否属于同一个岛屿
  
  ```c++
  class Solution {
  public:
      int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
      int cnt = 0;
      void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int mark) {
          // 终止条件：访问过的节点 或者 遇到海水
          if (visited[x][y] || grid[x][y] == 0)
              return;
          visited[x][y] = true;
          grid[x][y] = mark;
          cnt++;
          for (int i = 0; i < 4; i++) {
              int nextx = x + dir[i][0];
              int nexty = y + dir[i][1];
              if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid.size()) {
                  continue;
              }
              dfs(grid, visited, nextx, nexty, mark);
          }
          return;
      }
      int largestIsland(vector<vector<int>>& grid) {
          int n = grid.size();
          vector<vector<bool>> visited(n, vector<bool>(n, false));
          // 1.一次遍历地图，得出各个岛屿的面积，并做编号记录。
          // 剪枝：引入isAllGrid
          int mark = 2;
          bool isAllGrid = true;
          unordered_map<int, int> umap; // key：mark; 值：面积
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < n; j++) {
                  if (grid[i][j] != 1) {
                      isAllGrid = false;
                  }
                  if (!visited[i][j] && grid[i][j] == 1) {
                      cnt = 0;
                      dfs(grid, visited, i, j, mark);
                      umap[mark] = cnt;
                      mark++;
                  }
              }
          }
          if (isAllGrid == true) {
              return n * n;
          }
          // 2.遍历0的方格，并统计（由0变成的1）周边岛屿面积之和，得到最大岛屿面积。
          unordered_set<int> visitedGrid; // 标记访问过的岛屿
          int result = 0;                 // 记录最后的结果
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < n; j++) {
                  if (grid[i][j] == 0) {
                      cnt = 1;
                      visitedGrid.clear();
                      for (int k = 0; k < 4; k++) {
                          int nearx = i + dir[k][0];
                          int neary = j + dir[k][1];
                          // 越界
                          if (nearx < 0 || nearx >= n || neary < 0 || neary >= n) {
                              continue;
                          }
                          // 添加过的岛屿不要重复添加
                          if (visitedGrid.count(grid[nearx][neary])) {
                              continue;
                          }
                          cnt += umap[grid[nearx][neary]];
                          visitedGrid.insert(grid[nearx][neary]);
                      }
                  }
                  result = max(result, cnt);
              }
          }
          return result;
      }
  };
  ```



#### **岛屿的周长**

- **题意**：在矩阵中恰好**拥有一个岛屿**，假设组成岛屿的陆地边长都为 1，请计算岛屿的周长。岛屿内部没有水域。

- **思路**：遍历每一个节点，遇到岛屿则计算其上下左右的空格情况，遇到水域或者边界，则边长+1

  ```c++
  class Solution {
  public:
      int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
      int result = 0;
      void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x,
               int y) {
          visited[x][y] = true;
          for (int i = 0; i < 4; i++) {
              int nextx = x + dir[i][0];
              int nexty = y + dir[i][1];
              if (nextx < 0 || nextx >= grid.size() || nexty < 0 ||
                  nexty >= grid[0].size()) {
                  result++;
                  continue;
              }
              if (grid[nextx][nexty] == 0) {
                  result++;
                  continue;
              }
              if (!visited[nextx][nexty] && grid[nextx][nexty] == 1) {
                  visited[nextx][nexty] = true;
                  dfs(grid, visited, nextx, nexty);
              }
          }
      }
      int islandPerimeter(vector<vector<int>>& grid) {
          int row = grid.size();
          int col = grid[0].size();
          vector<vector<bool>> visited(row, vector<bool>(col, false));
          for (int i = 0; i < row; i++) {
              for (int j = 0; j < col; j++) {
                  if (grid[i][j] == 1) {
                      dfs(grid, visited, i, j);
                      return result;
                  }
              }
          }
          return 0;
      }
  };
  ```
  
- 不使用DFS：

  ```c++
  class Solution {
  public:
      int islandPerimeter(vector<vector<int>>& grid) {
          int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
          int result = 0;
          int row = grid.size();
          int col = grid[0].size();
          for (int i = 0; i < row; i++) {
              for (int j = 0; j < col; j++) {
                  if (grid[i][j] == 1) {
                      for (int k = 0; k < 4; k++) { // 上下左右四个方向
                          int x = i + direction[k][0];
                          int y = j + direction[k][1]; // 计算周边坐标x,y
                          if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0) {
                              result++;
                          }
                      }
                  }
              }
          }
          return result;
      }
  };
  ```



#### 单词搜索

```c++
class Solution {
public:
    int rows, cols;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int k) {
        if (i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k])
            return false;
        if (k == word.size() - 1)
            return true;
        board[i][j] = '\0';
        bool result = dfs(board, word, i + 1, j, k + 1) ||
                      dfs(board, word, i - 1, j, k + 1) ||
                      dfs(board, word, i, j + 1, k + 1) ||
                      dfs(board, word, i, j - 1, k + 1);
        board[i][j] = word[k];
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
};
```



#### *单词接龙

- **题意**：给你两个字符串 beginStr 和 endStr 和一个字典 strList，找到从 beginStr 到 endStr 的最短转换序列中的字符串数目。如果不存在这样的转换序列，返回 0。

  ```
  输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
  输出：5
  解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
  ```

- **思路**：

  1. 建模：如果两个字符串之间可以通过改变一个字符相互转换，则在这两个节点之间存在一条边。
  2. 使用BFS求最短路径

  ```c++
  class Solution {
  public:
      bool canConvert(const string& str1, const string& str2) {
          if (str1.size() != str2.size()) {
              return false;
          }
          int diffCount = 0;
          for (int i = 0; i < str1.size(); i++) {
              if (str1[i] != str2[i]) {
                  diffCount++;
              }
              if (diffCount > 1) {
                  return false;
              }
          }
          return true;
      }
      // 广度优先搜索
      int bfs(const string& beginWord, const string& endWord, const unordered_map<string, vector<string>>& graph) {
          queue<pair<string, int>> que;
          unordered_set<string> visited;
  
          que.push({beginWord, 1}); // 初始步数为1
          visited.insert(beginWord);
  
          while (!que.empty()) {
              string curWord = que.front().first;
              int step = que.front().second;
              que.pop();
              if (curWord == endWord) 
                  return step; // 找到目标字符串，返回步数
              // 遍历当前字符串的所有邻居
              if (graph.find(curWord) != graph.end()) {
                  for (const string& nextWord : graph.at(curWord)) {
                      if (!visited.count(nextWord)) {
                          visited.insert(nextWord);
                          que.push({nextWord, step + 1});
                      }
                  }
              }
          }
          return 0; // 找不到路径
      }
  
      int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
          // 1.建模：如果两个字符串之间可以相互转换，则在这两个节点之间存在一条边。
          // 注意：beginWord需要额外判断，而endWord不需要
          // 注意：构建双向图
          unordered_map<string, vector<string>> graph;
          for (int i = 0; i < wordList.size(); i++) {
              if (canConvert(beginWord, wordList[i])) {
                  graph[beginWord].push_back(wordList[i]);
              }
              for (int j = i + 1; j < wordList.size(); j++) {
                  if (canConvert(wordList[i], wordList[j])) {
                      graph[wordList[i]].push_back(wordList[j]);
                      graph[wordList[j]].push_back(wordList[i]);
                  }
              }
          }
          // 2. 使用BFS求最短路径
          int result = bfs(beginWord, endWord, graph);
          return result;
      }
  };
  ```
  



#### **有向图的完全可达性**

- **题意**：给定一个有向图，包含 N 个节点，节点编号分别为 1，2，...，N。现从 1 号节点开始，如果可以从 1 号节点的边可以到达任何节点，则输出 1，否则输出 -1。

- **思路**：

  - 第一步建模，使用**数组+链表**来表示图结构（邻接表）
  - 第二步使用**DFS**求可达性

    ```c++
    #include <iostream>
    #include <vector>
    #include <list>
    using namespace std;
    
    void dfs(const vector<list<int>>& graph, vector<bool>& visited, int key){
        if(visited[key])
            return;
        visited[key] = true;
        list<int> keys = graph[key];
        for(int i : keys){
            dfs(graph, visited, i);
        }
    
    }
    
    int main(){
        int n, k;
        cin >> n >> k;
    
        // 使用邻接表读取graph
        vector<list<int>> graph(n + 1); // 邻接表
        for(int i = 0; i < k; i++){
            int s, t;
            cin >> s >> t;
            graph[s].push_back(t);
        }
    
        vector<bool> visited(n + 1, false); // 记录是否被访问过
        dfs(graph, visited, 1);
        for(int i = 1; i < n + 1; i++){
            if(visited[i] == false){
                cout << -1 << endl;
                return 0;
            }
        }
    
        cout << 1 << endl;
        return 0;
    } 
    ```
  - 邻接矩阵版
  
    ```c++
    #include <iostream>
    #include <vector>
    using namespace std;
    
    void dfs(const vector<vector<int>>& graph, vector<bool>& visited, int cur){
        if(visited[cur]){
            return;
        }
        visited[cur] = true;
        for(int i = 0; i < graph[cur].size(); i++){
            if(graph[cur][i] == 1){
                dfs(graph, visited, i);
            }
        }
    }
    
    int main(){
        int n, k, s, t;
        cin >> n >> k;
        // 使用邻接矩阵建模
        vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
        for(int i = 0; i < k; i++){
            cin >> s >> t;
            graph[s][t] = 1;
        }
        // 记录是否被访问过
        vector<bool> visited(n, false);
        visited[0] = true;
        dfs(graph, visited, 1);
        for(int i = 0; i < n; i++){
            if(visited[i] == false){
                cout << -1 << endl;
                return 0;
            }
        }
        cout << 1 << endl;
        return 0;
    }
    ```
  



#### 除法求值

- 题意：给你一个变量对数组 `equations` 和一个实数值数组 `values` 作为已知条件，另有一些以数组 `queries` 表示的问题，其中 `queries[j] = [Cj, Dj]` 表示第 `j` 个问题，请你根据已知条件找出 `Cj / Dj = ?` 的结果作为答案。返回 **所有问题的答案** 。如果存在某个无法确定的答案，则用 `-1.0` 替代这个答案。

  ```
  输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
  输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
  解释：
  条件：a / b = 2.0, b / c = 3.0
  问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
  结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
  注意：x 是未定义的 => -1.0
  ```

- 解决：

  - 建模，然后遍历queries数组，对每个元素进行dfs，检查每个queries[0] 和queries[1]是否相连接。
    - 相连接：遍历路径上的权值相乘得结果
    - 不相连接，结果是-1.

  ```c++
  class Solution {
  public:
      vector<double> res;
      bool flag;
      void dfs(unordered_map<string, vector<pair<string, double>>>& g, unordered_map<string, int>& visit, string val, const string& target, const double& path) {
          // 如果节点已经相连接，那没必要再dfs搜索了，直接返回
          if (flag == false)
              return;
  
          if (val == target) {
              flag = false;
              res.push_back(path);
              return;
          }
          for (int j = 0; j < g[val].size(); ++j) {
              // 检查与val相连接的点，是否已经访问过了。没访问过继续dfs
              if (visit[g[val][j].first] == 0) {
                  visit[g[val][j].first] = 1;
                  dfs(g, visit, g[val][j].first, target, path * g[val][j].second);
                  visit[g[val][j].first] = 0;
              }
          }
      }
  
      vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
          // string - string(double)  a连接b(b带上权值)
          unordered_map<string, vector<pair<string, double>>> g;
          unordered_map<string, int> visit;
  
          // 构建无向图，a-b的value是3的话 ，b-a是3的倒数
          for (int i = 0; i < equations.size(); ++i) {
              g[equations[i][0]].push_back(make_pair(equations[i][1], values[i]));
              g[equations[i][1]].push_back(make_pair(equations[i][0], 1.0 / values[i]));
          }
  
          // 遍历queries，对每一组进行dfs计算结果。
          // 如果相连接，就把 路径上的权值相乘就是结果
          for (int i = 0; i < queries.size(); ++i) {
              // 如果queries[0]是不存在的，直接出结果：-1
              if (g.find(queries[i][0]) == g.end()) {
                  res.push_back(-1.0);
                  continue;
              }
              // 设置一个全局变量，如果进行dfs后，queries[0]到不了queries[1]，flag = true;
              flag = true;
              visit[queries[i][0]] = 1;
              dfs(g, visit, queries[i][0], queries[i][1], 1);
              visit[queries[i][0]] = 0;
              
              if (flag)
                  res.push_back(-1.0);
          }
  
          return res;
      }
  };
  ```



### √并查集

#### **代码模版**

- **功能**：

  - 寻找根节点，函数：`find(int u)`，也就是判断这个节点的祖先节点是哪个
  - 将两个节点接入到同一个集合，函数：`join(int u, int v)`，将两个节点连在同一个根节点上， **要分别对 u 和 v 寻根之后再进行关联。**
  - 判断两个节点是否在同一个集合，函数：`isSame(int u, int v)`，就是判断两个节点是不是同一个根节点

- **代码实现**：

  ```c++
  #include <iostream>
  #include <vector>
  using namespace std;
  int N = 1005; // n根据题目中节点数量而定，一般比节点数量大一点就好
  vector<int> father = vector<int> (N, 0);
  
  // 并查集初始化
  void init() {
      for (int i = 0; i < N; ++i) {
          father[i] = i;
      }
  }
  
  // 并查集里寻根的过程
  int find(int u) {
      if (u == father[u]) return u;
      else return father[u] = find(father[u]); // 路径压缩
      //else return find(father[u]);	// 无路径压缩：如果根不是自己，就根据数组下标一层一层向下找
  }
  
  // 判断 u 和 v是否找到同一个根
  bool isSame(int u, int v) {
      u = find(u);
      v = find(v);
      return u == v;
  }
  
  // 将v->u 这条边加入并查集
  void join(int u, int v) {
      u = find(u); // 寻找u的根
      v = find(v); // 寻找v的根
      if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
      father[v] = u;
  }
  ```
  
  

#### **寻找存在的路径**

- **题意**：给定一个包含 n 个节点的无向图中，节点编号从 1 到 n （含 1 和 n ）。判断是否有一条从节点 source 出发到节点 destination 的路径存在。

  ```c++
  bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
      init();
      for (int i = 0; i < edges.size(); i++) {
          join(edges[i][0], edges[i][1]);
      }
      return isSame(source, destination);
  }
  ```

  

#### **冗余连接**

- **题意**：有一个图，它是一棵树，他是拥有 n 个节点（节点编号1到n）和 n - 1 条边的连通无环无向图。现在在这棵树上的基础上，添加一条边（依然是n个节点，但有n条边），使这个图变成了有环图。请你找出冗余边，删除后，使该图可以重新变成一棵树。

- **思路**：从前向后遍历每一条边（因为优先让前面的边连上）

  - 边的两个节点如果不在同一个集合，就加入集合（即：同一个根节点）。
  - 如果边的两个节点已经出现在同一个集合里，说明着边的两个节点已经连在一起了，再加入这条边一定就出现环了。
  
  ```c++
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
      init();
      for (int i = 0; i < edges.size(); i++) {
          if (isSame(edges[i][0], edges[i][1])) {
              return {edges[i][0], edges[i][1]};
          } else {
              join(edges[i][0], edges[i][1]);
          }
      }
      return {};
  }
  ```
  



#### *冗余连接II

- **题意**：删除有向图的一条边，变成有向树

  - 不能直接参考无向图的做法，因为需要确保删除后是有向树（无环且每个节点只有一个父节点）

- **思路**：有向树的性质（只有**根节点入度为0**，其他**节点入度都为1**）

  - 出现入度为2的点，随便删除一条指向该节点的边（1-3或2-3）

    <img src="./Note.assets/20240527115807.png" alt="img" style="zoom: 67%;" />

  - 出现入度为2的点，只能删特定的一条边（1-3）

    <img src="./Note.assets/20240527151456.png" alt="img" style="zoom:67%;" />

  - 全部都没有入度为2的点，但是图中出现有向环

    <img src="./Note.assets/20240527120531.png" alt="img" style="zoom:67%;" />

- **代码**

  - **第一步**：把每条边记录下来，并统计节点入度

  - **第二步**：对于入度为2的情况，删除指向入度为2的节点的两条边其中的一条，如果删了一条，判断这个图是一个树，那么这条边就是答案。

    **`isTreeAfterRemoveEdge()` 判断删一个边之后是不是有向树**： 

    - 将所有边的两端节点分别加入并查集，遇到要删除的边则跳过；
    - 如果遇到即将加入并查集的边的两端节点，本来就在并查集了，说明构成了环；
    - 如果顺利将所有边的两端节点（除了要删除的边）加入了并查集，则说明删除该条边还是一个有向树。

  - **第三步**：如果明确没有入度为2的情况，那么一定有向环，找到构成环的边就是要删除的边。

    **`getRemoveEdge()`找到有向环中需要删除的那条边**

     将所有边的两端节点分别加入并查集，如果遇到即将加入并查集的边的两端节点本来就在并查集了，说明构成了环。

  ```c++
  // 删一条边之后判断是不是树
  bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge) {
      init(); // 初始化并查集
      for (int i = 0; i < edges.size(); i++) {
          if (i == deleteEdge)
              continue;
          if (isSame(edges[i][0], edges[i][1])) {
              // 构成有向环了，一定不是树
              return false;
          }
          join(edges[i][0], edges[i][1]);
      }
      return true;
  }
  // 在有向图里找到删除的那条边，使其变成树
  vector<int> getRemoveEdge(const vector<vector<int>>& edges) {
      init();                       // 初始化并查集
      for (int i = 0; i < edges.size(); i++) { // 遍历所有的边
          if (isSame(edges[i][0], edges[i][1])) {
              // 构成有向环了，就是要删除的边
              return {edges[i][0], edges[i][1]};
          } else {
              join(edges[i][0], edges[i][1]);
          }
      }
      return {};
  }
  vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
      vector<int> result;
      // 1. 统计节点入度
      int n = edges.size();
      vector<int> inDegree(n + 1, 0); // 记录节点入度
      for (int i = 0; i < n; i++) {
          inDegree[edges[i][1]]++;
      }
      // 2. 对于入度为2的情况，删除指向入度为2的节点的两条边其中的一条，
      // 如果删完后仍为树，那么这条边就是答案。
      vector<int> vec; // 记录入度为2的边（如果有的话就两条边）
      // 找入度为2的节点所对应的边，注意要倒序，因为优先删除最后出现的一条边
      for (int i = n - 1; i >= 0; i--) {
          if (inDegree[edges[i][1]] == 2) {
              vec.push_back(i);
          }
      }
      if (vec.size() > 0) {
          // 放在vec里的边已经按照倒叙放的，所以这里就优先删vec[0]这条边
          if (isTreeAfterRemoveEdge(edges, vec[0])) {
              return {edges[vec[0]][0], edges[vec[0]][1]};
          } else {
              return {edges[vec[1]][0], edges[vec[1]][1]};
          }
      }
      // 3. 没有入度为2的情况，寻找有向环
      return getRemoveEdge(edges);
  }
  ```



### 拓扑排序

#### 软件构建（模版）

- **理论**：给出一个 有向图，把这个**有向图转成线性**的排序 就叫拓扑排序；也是图论中**判断有向无环图**的常用方法

- **思路**：

  - 找到入度为0 的节点，加入结果集
  - 将该节点从图中移除

- **判断有向无环图**？

  - 节点1、2、3、4 形成了环，找不到入度为0 的节点了，所以此时结果集里只有一个元素。

    说明，如果 **结果集元素个数 不等于 图中节点个数**，我们就可以认定图中一定有 有向环！

    <img src="./Note.assets/20240510115115.png" alt="img" style="zoom:67%;" />

  ```c++
  #include <iostream>
  #include <vector>
  #include <queue>
  using namespace std;
  
  int main(){
      int m, n, s, t;
      cin >> n >> m;
      // 记录文件依赖关系，统计入度
      vector<vector<int>> graph(n, vector<int>(n, 0));
      vector<int> inDegree(n, 0);
      for(int i = 0; i < m; i++){
          cin >> s >> t;
          inDegree[t]++;
          graph[s][t] = 1;
      }
      // 将入度为0的节点放入队列当中
      queue<int> que;
      for (int i = 0; i < n; i++) {
          if (inDegree[i] == 0) 
              que.push(i);
      }
      // 当队列为空时，结束算法
      vector<int> result;
      while(!que.empty()){
          // 1.找到入度为0的节点，加入结果集
          int cur = que.front();
          que.pop();
          result.push_back(cur);
          // 2.将该节点从图中移除，即改变入度
          for (int i = 0; i < n; i++) {
              // cur指向的节点，入度减一
              if (graph[cur][i] == 1) {
                  inDegree[i]--;
                  // 如果指向的节点减一后入度为0，说明是要选取的下一个节点，放入队列
                  if (inDegree[i] == 0) {
                      que.push(i);
                  }
              }
          }
      }
      // 输出结果：若result长度和节点数量一致，说明成功
      if (result.size() == n) {
          for (int i = 0; i < n - 1; i++) 
              cout << result[i] << " ";
          cout << result[n - 1];
      } else 
          cout << -1 << endl;
      
      return 0;
  }
  ```



#### 课程表

- 在选修某些课程之前需要一些先修课程。 先修课程按数组 `prerequisites` 给出，其中 `prerequisites[i] = [ai, bi]` ，表示如果要学习课程 `ai` 则 **必须** 先学习课程 `bi` 。请你判断是否可能完成所有课程的学习？如果可以，返回 `true` ；否则，返回 `false` 。
  - 例如，先修课程对 `[0, 1]` 表示：想要学习课程 `0` ，你需要先完成课程 `1` 。

```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 记录文件依赖关系，统计入度
        vector<vector<int>> graph(numCourses, vector<int>(numCourses, 0));
        vector<int> inDegree(numCourses, 0);
        int s, t;
        for (int i = 0; i < prerequisites.size(); i++) {
            s = prerequisites[i][0];
            t = prerequisites[i][1];
            inDegree[t]++;
            graph[s][t] = 1;
        }
        // 将入度为0的节点放入队列当中
        queue<int> que;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                que.push(i);
            }
        }
        // 当队列为空时，结束算法
        vector<int> result;
        while (!que.empty()) {
            // 1.找到入度为0的节点，加入结果集
            int cur = que.front();
            que.pop();
            result.push_back(cur);
            // 2.将该节点从图中移除，即改变入度
            for (int i = 0; i < numCourses; i++) {
                // cur指向的节点，入度减一
                if (graph[cur][i] == 1) {
                    inDegree[i]--;
                    // 如果指向的节点减一后入度为0，说明是要选取的下一个节点，放入队列
                    if (inDegree[i] == 0) {
                        que.push(i);
                    }
                }
            }
        }
        // 输出结果：若result长度和节点数量一致，说明成功
        if (result.size() == numCourses) {
            return true;
        } else
            return false;
    }
};
```




### 最小生成树

**题意**：给定无向图，其中包括了所有的岛屿，以及它们之间的距离。如何可以以最短的总公路距离将所有岛屿联通起来。-> 最小生成树

图中有n个节点，那么一定可以用n-1条边将所有节点连接到一起，最小生成树算法就是如何选择这n-1条边。

<img src="./Note.assets/20231206164306.png" alt="img" style="zoom: 50%;" />

#### **Prim算法**（维护节点）

- Prim算法：时间复杂度为 O(n^2)，其中 n 为节点数量，它的运行效率和图中边树无关，**适用稠密图**。

  - 第一步，选距离生成树最近节点：遍历节点，查找`未访问过`&&`minDist[j] < minVal`的节点，更新`minVal`
  - 第二步，最近节点加入生成树：`isInTree[cur] = true;`
  - 第三步，更新非生成树节点到生成树的距离：对于`未访问过`&&`imap[cur][j] < minDist[j]`的节点，更新`minDist[j]`
  - **注意：**初始化`imap`和`minDist`时，选择比Val大的值即可，不能初始化成`INT_MAX`，否则第一步比较失效

  ```c++
  #include <iostream>
  #include <vector>
  #include <climits>
  using namespace std;
  int main(){
      // 初始化无向图
      int v, e, v1, v2, val;
      cin >> v >> e;
      vector<vector<int>> graph(v + 1, vector<int>(v + 1, 10001));
      for(int i = 0; i < e; i++){
          cin >> v1 >> v2 >> val;
          graph[v1][v2] = val;
          graph[v2][v1] = val;
      }
  
      // 维护节点集合
      vector<int> minDist(v + 1, 10001);
      vector<bool> isInTree(v + 1, false);
      for(int i = 1; i <= v; i++){
          // 1.查找最近节点
          int cur = -1;
          int minVal = INT_MAX;
          for(int j = 1; j <= v; j++){
              if(!isInTree[j] && minDist[j] < minVal){
                  minVal = minDist[j];
                  cur = j;
              }
          }
          // 2.将最近节点加入最小生成树
          isInTree[cur] = true; 
          // 3.更新minDist数组
          for(int j = 1; j <= v; j++){
              if(!isInTree[j] && graph[cur][j] < minDist[j]){
                  minDist[j] = graph[cur][j];
              }
          }
      }
      // 统计结果：最小路径总距离
      int result = 0;
      for (int i = 2; i <= v; i++) {
          result += minDist[i];
      }
      cout << result << endl;
      return 0;
  }
  ```

  

#### **Kruskal算法**（维护边）

- Kruskal算法：时间复杂度 为 nlogn，其中n为边的数量，**适用稀疏图**。

  - 边的权值排序，因为要优先选最小的边加入到生成树里
  - 遍历排序后的边
    - 如果边首尾的两个节点在同一个集合，说明如果连上这条边图中会出现环
    - 如果边首尾的两个节点不在同一个集合，加入到最小生成树，并把两个节点加入同一个集合

  ```c++
  #include <iostream>
  #include <vector>
  #include <algorithm>
  using namespace std;
  // l,r为边两边的节点，val为边的数值
  struct Edge {
      int l, r, val;
  };
  // 按边的权值对边进行从小到大排序
  bool cmp(const Edge& a, const Edge& b){
      return a.val < b.val;
  }
  int N = 10005; // n根据题目中节点数量而定，一般比节点数量大一点就好
  vector<int> father = vector<int> (N, 0);
  // 并查集初始化
  void init() {
      for (int i = 0; i < N; ++i) {
          father[i] = i;
      }
  }
  // 并查集里寻根的过程
  int find(int u) {
      if (u == father[u]) 
          return u;
      else 
          return father[u] = find(father[u]);
  }
  // 判断 u 和 v是否找到同一个根
  bool isSame(int u, int v) {
      u = find(u);
      v = find(v);
      return u == v;
  }
  // 将v->u 这条边加入并查集
  void join(int u, int v) {
      u = find(u); // 寻找u的根
      v = find(v); // 寻找v的根
      if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
      father[v] = u;
  }
  int main(){
      // 初始化无向图
      int v, e, v1, v2, val;
      cin >> v >> e;
      vector<Edge> edges;
      for(int i = 0; i < e; i++){
          cin >> v1 >> v2 >> val;
          edges.push_back({v1, v2, val});
      }
      // 从小到大对边进行排序
      sort(edges.begin(), edges.end(), cmp);
      // 遍历边：如果边首尾的两个节点不在同一个集合，加入到最小生成树；反之会出现环
      init();
      int result = 0;
      for (Edge edge : edges) {
          int x = find(edge.l);
          int y = find(edge.r);
          if (x != y) {
              result += edge.val;
              join(x, y);
          }
      }
      cout << result << endl;
      return 0;
  }
  ```




### 最短路算法

#### dijkstra

不能解决**负权值**问题

- **思路**

  - 第一步，选源点到哪个节点近且该节点未被访问过
  - 第二步，该最近节点被标记访问过
  - 第三步，更新**非访问节点到源点**的距离（即更新minDist数组）

- **朴素版**（该解法的时间复杂度为 O(n^2)，n为节点数量）

  ```c++
  #include <iostream>
  #include <vector>
  #include <climits>
  using namespace std;
  
  int main(){
  
      int n, m, s, e, val;
      cin >> n >> m;
      vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
      while(m--){
          cin >> s >> e >> val;
          grid[s][e] = val;
      }
      int start = 1, end = n;
      
      // 记录非访问节点到源点的距离
      vector<int> minDist(n + 1, INT_MAX);
      minDist[start] = 0;
  
      // 记录访问过的节点
      vector<bool> visited(n + 1, false);
      
      // 遍历所有节点
      for(int i = 1; i <= n; i++){
          // 第一步，选源点到哪个节点近且该节点未被访问过
          int minVal = INT_MAX;
          int cur = 1;
          for (int j = 1; j <= n; j++){
              if(!visited[j] && minDist[j] < minVal){
                  minVal = minDist[j];
                  cur = j;
              }
          }
  
          // 第二步，该最近节点被标记访问过
          visited[cur] = true;
  
          // 第三步，更新非访问节点到源点的距离（即更新minDist数组）
          for(int j = 1; j <= n; j++){
              if(!visited[j] && grid[cur][j] != INT_MAX && minDist[cur] + grid[cur][j] < minDist[j]){
                  minDist[j] = minDist[cur] + grid[cur][j];
              }
          }
      }
      if (minDist[end] == INT_MAX)    // 不能到达终点
          cout << -1 << endl; 
      else 
          cout << minDist[end] << endl; // 到达终点最短路径
  
  
      return 0;
  }
  ```
  
- **堆优化版**（时间复杂度：O(ElogE) E 为边的数量；      空间复杂度：O(N + E) N 为节点的数量）

  ```c++
  #include <iostream>
  #include <vector>
  #include <list>
  #include <queue>
  #include <climits>
  using namespace std;
   
  // 小顶堆
  class mycomparison {
  public:
      bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
          return lhs.second > rhs.second;
      }
  };
  
  // 定义一个结构体来表示带权重的边
  struct Edge {
      int to;  // 邻接顶点
      int val; // 边的权重
      Edge(int t, int w): to(t), val(w) {}  // 构造函数
  };
  
  int main() {
      int n, m, p1, p2, val;
      cin >> n >> m;
  
      vector<list<Edge>> grid(n + 1);
  
      for(int i = 0; i < m; i++){
          cin >> p1 >> p2 >> val; 
          // p1 指向 p2，权值为 val
          grid[p1].push_back(Edge(p2, val));
  
      }
  
      int start = 1;  // 起点
      int end = n;    // 终点
  
      // 存储从源点到每个节点的最短距离
      std::vector<int> minDist(n + 1, INT_MAX);
  
      // 记录顶点是否被访问过
      std::vector<bool> visited(n + 1, false); 
      
      // 优先队列中存放 pair<节点，源点到该节点的权值>
      priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pq;
  
  
      // 初始化队列，源点到源点的距离为0，所以初始为0
      pq.push(pair<int, int>(start, 0)); 
      
      minDist[start] = 0;  // 起始点到自身的距离为0
  
      while (!pq.empty()) {
          // 1. 第一步，选源点到哪个节点近且该节点未被访问过 （通过优先级队列来实现）
          // <节点， 源点到该节点的距离>
          pair<int, int> cur = pq.top(); pq.pop();
          if (visited[cur.first]) 
              continue;
  
          // 2. 第二步，该最近节点被标记访问过
          visited[cur.first] = true;
  
          // 3. 第三步，更新非访问节点到源点的距离（即更新minDist数组）
          for (Edge edge : grid[cur.first]) { // 遍历cur指向的节点
              // cur指向的节点edge.to，这条边的权值为 edge.val
              if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) { // 更新minDist
                  minDist[edge.to] = minDist[cur.first] + edge.val;
                  pq.push(pair<int, int>(edge.to, minDist[edge.to]));
              }
          }
  
      }
  
      if (minDist[end] == INT_MAX) 
          cout << -1 << endl; // 不能到达终点
      else 
          cout << minDist[end] << endl; // 到达终点最短路径
  }
  ```




#### Bellman_ford（SPFA、负权回路、单源有限最短路）

解决**负权值**问题

- **核心思想**：对所有边进行**松弛**`n-1`次操作（n为节点数量），从而求得目标最短路。

  - **松弛**：`minDist[B] = min(minDist[A] + value, minDist[B])`

  - **为什么是`n-1`次**：对所有边松弛**一次**，相当于计算 起点到达 与起点**一条边**相连的节点 的最短距离

- **Bellman_ford算法**

  ```c++
  #include <iostream>
  #include <vector>
  #include <list>
  #include <climits>
  using namespace std;
  
  int main(){
      int n, m, s, t, val;
      cin >> n >> m;
      vector<vector<int>> umap; 
      for(int i = 0; i < m; i++){
          cin >> s >> t >> val;
          umap.push_back({s, t, val});
      }
  
      int start = 1, end = n;
      vector<int> minDist(n + 1, INT_MAX);
      minDist[start] = 0;
      for(int i = 0; i < n - 1; i++){
          for(vector<int> &side : umap){
              int from = side[0];
              int to = side[1];
              int value = side[2];
              // minDist[from] != INT_MAX 防止从未计算过的节点出发
              if(minDist[from] != INT_MAX && minDist[to] > minDist[from] + value){
                  minDist[to] = minDist[from] + value;
              }
          }
      }
  
      if (minDist[end] == INT_MAX) 
          cout << "unconnected" << endl; // 不能到达终点
      else 
          cout << minDist[end] << endl; // 到达终点最短路径长度
  }
  ```

- **Bellman_ford 队列优化算法（SPFA）**

  不需要对所有边进行松弛，只需要对 **上一次松弛的时候更新过的节点作为出发节点所连接的边** 进行松弛就够了。

  - SPFA 的时间复杂度为 `O(K * N)`，K 为不定值，节点需要计入几次队列取决于**图的稠密度** -> 图越稀疏，SPFA的效率就越高。
  - SPFA 在最坏的情况下是 `O(N * E)`，但 一般情况下 时间复杂度为 `O(K * N)`。

  ```c++
  #include <iostream>
  #include <vector>
  #include <queue>
  #include <list>
  #include <climits>
  using namespace std;
  
  struct Edge { // 邻接表
      int to;   // 链接的节点
      int val;  // 边的权重
  
      Edge(int t, int w): to(t), val(w) {}  // 构造函数
  };
  
  int main(){
      int n, m, s, t, val;
      cin >> n >> m;
      vector<list<Edge>> umap(n + 1);
      vector<bool> isInQueue(n + 1);
  
      for(int i = 0; i < m; i++){
          cin >> s >> t >> val;
          umap[s].push_back(Edge(t, val));
      }
  
      int start = 1, end = n;
      vector<int> minDist(n + 1, INT_MAX);
      minDist[start] = 0;
  
      queue<int> que;
      que.push(start);
  
      while(!que.empty()){
          int node = que.front(); que.pop();
          isInQueue[node] = false;
          for(Edge edge : umap[node]){
              int from = node;
              int to = edge.to;
              int value = edge.val;
              if (minDist[to] > minDist[from] + value) {
                  minDist[to] = minDist[from] + value; 
                  // 已经在队列里的元素不用重复添加
                  if (isInQueue[to] == false) { 
                      que.push(to);
                      isInQueue[to] = true;
                  }
              }
          }
      }
  
  
      if (minDist[end] == INT_MAX) 
          cout << "unconnected" << endl; // 不能到达终点
      else 
          cout << minDist[end] << endl; // 到达终点最短路径长度
  }
  ```

- **Bellman_ford之判断负权回路**

  - **负权回路**：一系列道路的总权值为负，这样的回路使得通过反复经过回路中的道路，可以无限地减少总成本/增加总收益。

    如果松弛 `n` 次，结果有变化了，说明存在负权回路，因为 有负权回路 就是可以无限最短路径（一直绕圈，就可以一直得到无限小的最短距离）。

  - 时间复杂度：`O(N * E)` , N为节点数量，E为图中边的数量；空间复杂度： `O(N)` ，即 minDist 数组所开辟的空间

  ```c++
  #include <iostream>
  #include <vector>
  #include <list>
  #include <climits>
  using namespace std;
  
  int main(){
      int n, m, s, t, val;
      cin >> n >> m;
      vector<vector<int>> umap; 
      for(int i = 0; i < m; i++){
          cin >> s >> t >> val;
          umap.push_back({s, t, val});
      }
  
      int start = 1, end = n;
      vector<int> minDist(n + 1, INT_MAX);
      minDist[start] = 0;
      bool flag = false;
      for(int i = 1; i <= n; i++){
          for(vector<int> &side : umap){
              int from = side[0];
              int to = side[1];
              int value = side[2];
              if (i < n) {
                  if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + value) minDist[to] = minDist[from] + value;
              } else { // 多加一次松弛判断负权回路
                  if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + value) flag = true;
              }
          }
      }
  
      if (flag) {
          cout << "circle" << endl;
      } else if (minDist[end] == INT_MAX) {
          cout << "unconnected" << endl;
      } else {
          cout << minDist[end] << endl;
      }
  
      return 0;
  }
  ```

- **Bellman_ford之单源有限最短路**

  - **单源有限最短路**：起点**最多经过`k`个点（`k + 1`条边）**到达终点的最短距离；本题中可能存在**负权回路**！
    - 本题有负权回路=如果多做松弛，结果会改变。-->    每次计算` minDist `时候，要基于 **对所有边上一次松弛的` minDist `数值**
    - 本题要求最多经过k个节点，对松弛次数是有限制的。          -->          最多松弛`k + 1`次

  - 时间复杂度：`O(K * E)` ，K为至多经过K个节点，E为图中边的数量；空间复杂度： `O(N)` ，即 minDist 数组所开辟的空间

  ```c++
  #include <iostream>
  #include <vector>
  #include <list>
  #include <climits>
  using namespace std;
  
  int main(){
      int n, m, s, t, val, src, dst, k;
      cin >> n >> m;
      vector<vector<int>> umap; 
      for(int i = 0; i < m; i++){
          cin >> s >> t >> val;
          umap.push_back({s, t, val});
      }
      cin >> src >> dst >> k;
  
      vector<int> minDist(n + 1, INT_MAX);
      vector<int> minDist_copy(n + 1, INT_MAX);
      minDist[src] = 0;
      for(int i = 0; i < k + 1; i++){
          minDist_copy = minDist;
          for(vector<int> &side : umap){
              int from = side[0];
              int to = side[1];
              int value = side[2];
              // minDist[from] != INT_MAX 防止从未计算过的节点出发
              if(minDist_copy[from] != INT_MAX && minDist[to] > minDist_copy[from] + value){
                  minDist[to] = minDist_copy[from] + value;
              }
          }
      }
  
      if (minDist[dst] == INT_MAX) 
          cout << "unreachable" << endl; // 不能到达终点
      else 
          cout << minDist[dst] << endl; // 到达终点最短路径长度
  }
  ```

#### Floyd

- **题意**：求多个起点到多个终点的多条最短路径

- **思路**：Floyd 算法对边的权值正负没有要求，都可以处理。（核心思想：**动态规划**）

- **步骤**：

  - **确定dp数组含义**

    - `grid[i][j][k] = m`，表示 节点`i` 到 节点`j` 以`[1...k]` 集合中的**节点`k`为中间节点**的最短距离为`m`。

  - **确定递推公式**

    - 节点`i`到 节点`j`的最短路径经过节点 `k`——> `grid[i][j][k] = grid[i][k][k - 1] + grid[k][j][k - 1]`
    - 节点`i`到 节点`j`的最短路径不经过节点`k`——> `grid[i][j][k] = grid[i][j][k - 1]`
    - `grid[i][j][k] = min(grid[i][k][k - 1] + grid[k][j][k - 1], grid[i][j][k - 1])`

  - **初始化**

    - 本题 节点0 是无意义的，节点是从1 到 n，所以初始化`grid[i][j][0]=val`，其他值初始化为最大值
    - 例如：题目中输入边（节点2 -> 节点6，权值为3），那么`grid[2][6][0] = 3`

  - **遍历顺序**

    - 我们需要三个for循环，分别遍历i，j 和k。**最外层遍历`k`，然后`i`，`j`**

      <img src="./Note.assets/20240424120109.png" alt="img" style="zoom:33%;" />

  - **代码**：

    ```c++
    #include <iostream>
    #include <vector>
    #include <list>
    using namespace std;
    
    int main(){
        int n, m, u, v, val;
        cin >> n >> m;
    
        vector<vector<vector<int>>> grid(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 10005)));  // 因为边的最大距离是10^4
        for(int i = 0; i < m; i++){
            cin >> u >> v >> val;
            grid[u][v][0] = val;
            grid[v][u][0] = val;
        }
    
        // floyd
        for(int k = 1; k <= n; k++){
            for(int j = 1; j <= n; j++){
                for(int i = 1; i <= n; i++){
                    grid[i][j][k] = min(grid[i][k][k - 1] + grid[k][j][k - 1], grid[i][j][k - 1]);
                }
            }
        }
    
        int q, start, end;
        cin >> q;
        while (q--) {
            cin >> start >> end;
            if (grid[start][end][n] == 10005) 
                cout << -1 << endl;
            else 
                cout << grid[start][end][n] << endl;
        }
    
        return 0;
    }
    ```




#### A*算法

- **题意**：骑士只能走日字格，如何找到最短路径

- **思路**：相对于 普通BFS，A * 算法只从 队列里取出 距离终点最近的节点。

- **代码**：

  ```c++
  #include<iostream>
  #include<queue>
  #include<string.h>
  using namespace std;
  
  // 日字格有八种走法
  int dir[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};    
  int b1, b2; // 目标位置
  int moves[1001][1001];  // 表示从起点到位置 (next.x, next.y) 的最小移动步数。
  
  // F = G + H
  // G = 从起点到该节点路径消耗
  // H = 该节点到终点的预估消耗
  struct Knight{
      int x,y;
      int g,h,f;
      bool operator < (const Knight & k) const{  // 重载运算符， 从小到大排序
          return k.f < f;
      }
  };
  
  int Heuristic(const Knight& k) { // 欧拉距离：不开根号，提高精度
      return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2);
  }
  
  priority_queue<Knight> que;
  void Astar(const Knight& k)
  {
      Knight cur, next;
  	que.push(k);
  	while(!que.empty()){
  
  		cur=que.top(); que.pop();
  		if(cur.x == b1 && cur.y == b2)
  		    break;  // 走到终点，退出
  
  		for(int i = 0; i < 8; i++){
  
  			next.x = cur.x + dir[i][0];
  			next.y = cur.y + dir[i][1];
  			if(next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)
  			    continue;   // 越界了，跳过
  			if(!moves[next.x][next.y]){ // 检查目标位置是否已经被访问过。为0，则未访问
  				moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                  // 开始计算F
  				next.g = cur.g + 5; // 马走日，欧拉距离：1 * 1 + 2 * 2 = 5
                  next.h = Heuristic(next);
                  next.f = next.g + next.h;
                  que.push(next);
  			}
  
  		}
  	}
  }
  
  int main()
  {
      int n, a1, a2;
      cin >> n;
      while (n--) {
          cin >> a1 >> a2 >> b1 >> b2;
          memset(moves,0,sizeof(moves));
          Knight start;
          start.x = a1;
          start.y = a2;
          start.g = 0;
          start.h = Heuristic(start);
          start.f = start.g + start.h;
  		Astar(start);
          while(!que.empty()) 
              que.pop(); // 队列清空
  		cout << moves[b1][b2] << endl;
  	}
  	return 0;
  }
  ```

![img](./Note.assets/20240508121355.png)

- 如果遇到**单源且边为正数**，直接Dijkstra（堆优化版）
- 如果遇到**单源边可为负数**，直接 Bellman-Ford（SPFA）
- 如果有**负权回路**，优先 Bellman-Ford
- 如果是**有限节点最短路**，也优先 Bellman-Ford，理由是写代码比较方便。
- 如果是遇到**多源点求最短路**，直接 Floyd。



## 数学

1. 快速幂：`16=4*4=2²*2²`

   ```c++
   double myPow(double x, int n) {
       double result = 1;
       long long N = n; // 注意-n会超出int限制
   
       if (N < 0) { // 如果指数小于0，则反转底数x，并且把n变为正数
           x = 1 / x;
           N = -N;
       }
   
       while (N > 0) // 指数大于0进行指数折半，底数变其平方的操作
       {
           if (N & 1)       // 指数为奇数，power & 1这相当于power % 2 == 1
               result *= x; // 分离出当前项并累乘后保存
           N >>= 1;         // 指数折半,power >>= 1这相当于power /= 2;
           x *= x;          // 底数变其平方
       }
   
       return result; // 返回最终结果
   }
   ```

   

## 模拟

1. 大小写转换：A + 32 = a

2. 机器人走环形路判定：机器人想要摆脱循环，在一串指令之后的状态，必须是**不位于原点且方向朝北**。

   ```c++
   class Solution {
   public:
       bool isRobotBounded(string instructions) {
           vector<vector<int>> direc{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
           int direcIndex = 0;
           int x = 0, y = 0;
   
           for (int i = 0; i < instructions.size(); i++) {
               switch (instructions[i]) {
               case 'G':
                   x += direc[direcIndex][0];
                   y += direc[direcIndex][1];
                   break;
               case 'L':
                   direcIndex += 3;
                   direcIndex %= 4;
                   break;
               case 'R':
                   direcIndex++;
                   direcIndex %= 4;
                   break;
               }
           }
   
           return direcIndex != 0 || (x == 0 && y == 0);
       }
   };
   ```

