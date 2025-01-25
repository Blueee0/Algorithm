# 代码随想录

## 数组

数组下标都是从0开始的；
数组内存空间的地址是连续的

### 1. 二分查找 

如果说定义 target 是在一个在左闭右开的区间里，也就是[left, right) 。则有如下两点：

- while (left < right)，这里使用 *<* ,因为left == right在区间[left, right)是没有意义的
- if (nums[middle] > target) right 更新为 *middle*，因为当前nums[middle]不等于target，去左区间继续寻找，而寻找区间是左闭右开区间，所以right更新为middle，即：下一个查询区间不会去比较nums[middle]

### 2. 移除元素

- 快指针：寻找新数组的元素 ，新数组就是不含有目标元素的数组
- 慢指针：指向更新 新数组下标的位置

![27.移除元素-双指针法](D:/coding/my_cans/Algorithm/Note.assets/27.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0-%E5%8F%8C%E6%8C%87%E9%92%88%E6%B3%95.gif)

### 3. 有序数组的平方

![img](D:/coding/my_cans/Algorithm/Note.assets/977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.gif)

### 4. 长度最小的子数组（滑动窗口）

窗口就是 满足其和 ≥ s 的长度最小的 连续 子数组。

窗口的起始位置如何移动：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。

窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。

解题的关键在于 窗口的起始位置如何移动，如图所示：

<img src="D:/coding/my_cans/Algorithm/Note.assets/20210312160441942.png" alt="leetcode_209" style="zoom: 80%;" />

### 5. 螺旋矩阵

​	这里一圈下来，我们要画每四条边，这四条边怎么画，每画一条边都要坚持一致的左闭右开，或者左开右闭的原则，这样这一圈才能按照统一的规则画下来。那么我按照左闭右开的原则，来画一圈，大家看一下：

<img src="D:/coding/my_cans/Algorithm/Note.assets/20220922102236.png" alt="img" style="zoom:50%;" />

### 6. 区间和

前缀和的思想是重复利用计算过的子数组之和，从而降低区间查询需要累加计算的次数。

例如，我们要统计 vec[i] 这个数组上的区间和。那么，我们先做累加，即 p[i] 表示 下标 0 到 i 的 vec[i] 累加 之和。

如果，我们想统计，在vec数组上 下标 2 到下标 5 之间的累加和，那是不是就用 p[5] - p[1] 就可以了。

<img src="D:/coding/my_cans/Algorithm/Note.assets/20240627110604.png" alt="img" style="zoom:50%;" />



![img](D:/coding/my_cans/Algorithm/Note.assets/%E6%95%B0%E7%BB%84%E6%80%BB%E7%BB%93.png)

## 链表

数组是在内存中是连续分布的，但是链表在内存中可不是连续分布的

```c++
// 单链表
struct ListNode {
    int val;  // 节点上存储的元素
    ListNode *next;  // 指向下一个节点的指针
    ListNode(int x) : val(x), next(NULL) {}  // 节点的构造函数
};
```

### 1. 移除链表元素 

- 移除头结点：将头结点向后移动一位就可以 head = head -> next 
- 移除其他节点：让节点next指针直接指向下下一个节点 next = next -> next

### 2. 设计链表

- 获取链表第index个节点的数值
- 在链表的最前面插入一个节点
- 在链表的最后面插入一个节点
- 在链表第index个节点前面插入一个节点
- 删除链表的第index个节点

### 3. 反转链表

- 双指针法

  首先定义一个cur指针，指向头结点，再定义一个pre指针，初始化为null。

  然后就要开始反转了，首先要把 cur->next 节点用tmp指针保存一下，也就是保存一下这个节点。

  为什么要保存一下这个节点呢，因为接下来要改变 cur->next 的指向了，将cur->next 指向pre ，此时已经反转了第一个节点了。

  接下来，就是循环走如下代码逻辑了，继续**移动pre和cur指针**（**先pre，后cur**）。

  最后，cur 指针已经指向了null，循环结束，链表也反转完毕了。 此时我们return pre指针就可以了，pre指针就指向了新的头结点。

- 递归法

  本质上就是双指针法

### 4. 两两交换链表中的节点

注意返回头结点时，应该返回dummyhead->next

![24.两两交换链表中的节点1](D:/coding/my_cans/Algorithm/Note.assets/24.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B91.png)

### 5. 删除链表倒数第N个节点

如果要删除倒数第n个节点，让fast移动n步，然后让fast和slow同时移动，直到fast指向链表末尾。删掉slow所指向的节点就可以了。

### 6. 链表相交

我们求出两个链表的长度，并求出两个链表长度的差值，然后让curA移动到，和curB 末尾对齐的位置，此时我们就可以比较curA和curB是否相同，如果不相同，同时向后移动curA和curB，如果遇到curA == curB，则找到交点。否则循环退出返回空指针。

### 7. 环形链表

- 判断是否有环

  可以使用快慢指针法，分别定义 fast 和 slow 指针，从头结点出发，fast指针每次移动两个节点，slow指针每次移动一个节点，如果 fast 和 slow指针在途中相遇 ，说明这个链表有环。

  ![141.环形链表](D:/coding/my_cans/Algorithm/Note.assets/141.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8.gif)

- 如何找到环的入口

  ![img](D:/coding/my_cans/Algorithm/Note.assets/20220925103433.png)那么相遇时： slow指针走过的节点数为: `x + y`， fast指针走过的节点数：`x + y + n (y + z)`，n为fast指针在环内走了n圈才遇到slow指针， （y+z)为 一圈内节点的个数A。

  因为fast指针是一步走两个节点，slow指针一步走一个节点， 所以 fast指针走过的节点数 = slow指针走过的节点数 * 2：

  ```
  (x + y) * 2 = x + y + n (y + z)
  ```

​	因为要找环形的入口，那么要求的是x，因为x表示 头结点到 环形入口节点的的距离：`x = n (y + z) - y = (n - 1) (y + z) + z` 

​	这就意味着，**从头结点出发一个指针，从相遇节点 也出发一个指针，这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是 环形入口的节点**。

​	![142.环形链表II（求入口）](D:/coding/my_cans/Algorithm/Note.assets/142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II%EF%BC%88%E6%B1%82%E5%85%A5%E5%8F%A3%EF%BC%89.gif)

![img](D:/coding/my_cans/Algorithm/Note.assets/%E9%93%BE%E8%A1%A8%E6%80%BB%E7%BB%93.png)

## 哈希表

哈希碰撞的处理方式：拉链法、线性探测法（tableSize > dataSize）

哈希表的数据结构：数组、set、map【红黑树是一种平衡二叉搜索树】

**需要快速判断一个元素是否出现集合里的时候，就要考虑哈希法**

数组：数值较小，比如字母26个。

set：数值比较分散

map：

<img src="D:/coding/my_cans/Algorithm/Note.assets/image-20250125182055849.png" alt="image-20250125182055849" style="zoom: 67%;" />

<img src="D:/coding/my_cans/Algorithm/Note.assets/image-20250125182207335.png" alt="image-20250125182207335" style="zoom:67%;" />

### 1. 有效的字母异位词

定义一个数组hash[26]来记录字符串a里，26个字母出现的频率，然后再遍历字符串b的时候，只需要将对应的字母做-1就可以。当最后hash[26]数组的元素全为0时，则表明这是字母异位词，return true

### 2. 两个数组的交集

<img src="D:/coding/my_cans/Algorithm/Note.assets/20220707173513.png" alt="set哈希法" style="zoom:50%;" />
