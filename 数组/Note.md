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
