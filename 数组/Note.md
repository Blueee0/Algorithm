# 代码随想录

## 数组

数组下标都是从0开始的；
数组内存空间的地址是连续的

1. 二分查找 Leetcode704

   如果说定义 target 是在一个在左闭右开的区间里，也就是[left, right) 。则有如下两点：

   - while (left < right)，这里使用 *<* ,因为left == right在区间[left, right)是没有意义的
   - if (nums[middle] > target) right 更新为 *middle*，因为当前nums[middle]不等于target，去左区间继续寻找，而寻找区间是左闭右开区间，所以right更新为middle，即：下一个查询区间不会去比较nums[middle]

2. 移除元素
   - 快指针：寻找新数组的元素 ，新数组就是不含有目标元素的数组
   - 慢指针：指向更新 新数组下标的位置

![27.移除元素-双指针法](D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/27.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0-%E5%8F%8C%E6%8C%87%E9%92%88%E6%B3%95.gif)

3. 有序数组的平方

   ![img](D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.gif)

4. 长度最小的子数组（滑动窗口）

   窗口就是 满足其和 ≥ s 的长度最小的 连续 子数组。

   窗口的起始位置如何移动：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。

   窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。

   解题的关键在于 窗口的起始位置如何移动，如图所示：

   <img src="D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/20210312160441942.png" alt="leetcode_209" style="zoom: 80%;" />

5. 螺旋矩阵

   这里一圈下来，我们要画每四条边，这四条边怎么画，每画一条边都要坚持一致的左闭右开，或者左开右闭的原则，这样这一圈才能按照统一的规则画下来。

   那么我按照左闭右开的原则，来画一圈，大家看一下：

   <img src="D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/20220922102236.png" alt="img" style="zoom:50%;" />

6. 区间和

   前缀和的思想是重复利用计算过的子数组之和，从而降低区间查询需要累加计算的次数。

   例如，我们要统计 vec[i] 这个数组上的区间和。那么，我们先做累加，即 p[i] 表示 下标 0 到 i 的 vec[i] 累加 之和。

   如果，我们想统计，在vec数组上 下标 2 到下标 5 之间的累加和，那是不是就用 p[5] - p[1] 就可以了。

   <img src="D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/20240627110604.png" alt="img" style="zoom:50%;" />

   

![img](D:/coding/my_cans/Algorithm/%E6%95%B0%E7%BB%84/Note.assets/%E6%95%B0%E7%BB%84%E6%80%BB%E7%BB%93.png)
