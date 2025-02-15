# 代码随想录

## 常见算法

### 1. 快速幂

指数折半：`16=4*4=2²*2²`

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



## 备注

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

数组：数值较小，比如字母26个。【Leetcode242：有效的字母异位词】

set：数值比较分散【Leetcode349：两个数组的交集】

map：需要使用 key value结构来存放，key来存元素，value来存下标。【Leetcode1：两数相加】

<img src="D:/coding/my_cans/Algorithm/Note.assets/image-20250125182055849.png" alt="image-20250125182055849" style="zoom: 67%;" />

<img src="D:/coding/my_cans/Algorithm/Note.assets/image-20250125182207335.png" alt="image-20250125182207335" style="zoom:67%;" />

### 1. 有效的字母异位词

定义一个数组hash[26]来记录字符串a里，26个字母出现的频率，然后再遍历字符串b的时候，只需要将对应的字母做-1就可以。当最后hash[26]数组的元素全为0时，则表明这是字母异位词，return true

### 2. 两个数组的交集

<img src="D:/coding/my_cans/Algorithm/Note.assets/20220707173513.png" alt="set哈希法" style="zoom:50%;" />

### 3. 求和

1. **两数之和**

   - 为什么会想到用哈希表：需要存下遍历过的元素，然后在遍历过的元素中，查找对应的元素`target-nums[i]`
   - 哈希表为什么用map：需要存放两个元素，key来存元素（查找对象），value来存下标。
   - 本题map是用来存什么的：用来存放遍历过的元素
   - map中的key和value用来存什么的：key存元素，value存下标

   <img src="D:/coding/my_cans/Algorithm/Note.assets/20220711202638.png" alt="过程一" style="zoom:50%;" />

2. **四数相加**

   1. 首先定义 一个unordered_map，**key放a和b两数之和，value 放a和b两数之和出现的次数**。
   2. 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中。
   3. 定义int变量count，用来统计 a+b+c+d = 0 出现的次数。
   4. 再遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就用count把map中key对应的value也就是出现次数统计出来。
   5. 最后返回统计值 count 就可以了

3. **三数之和**

   1. 首先将数组排序，然后有一层for循环，i从下标0的地方开始，同时定一个下标left 定义在i+1的位置上，定义下标right 在数组结尾的位置上。

   2. 接下来如何移动left 和right呢， 如果nums[i] + nums[left] + nums[right] > 0 就说明 此时三数之和大了，因为数组是排序后了，所以right下标就应该向左移动，这样才能让三数之和小一些。

   3. 如果 nums[i] + nums[left] + nums[right] < 0 说明 此时 三数之和小了，left 就向右移动，才能让三数之和大一些，直到left与right相遇为止。

   - 关键在于**去重**：①对i进行去重`nums[i] == nums[i-1]` 

     ​		         ②在收获结果后，对left和right进行去重`nums[right] == nums[right - 1]`；`nums[left] == nums[left+1]`

4. **四数之和**

   四数之和的双指针解法是两层for循环nums[k] + nums[i]为确定值，依然是循环内有left和right下标作为双指针，找出nums[k] + nums[i] + nums[left] + nums[right] == target的情况，三数之和的时间复杂度是O(n^2)，四数之和的时间复杂度是O(n^3) 。

## 字符串

### 1. 反转字符串

双指针指向头尾，然后同时向中间移动。

**翻转字符串里的单词**：先对字符串整体翻转，再对单词进行翻转

**右旋转字符串**：先对字符串整体翻转，再对两个子串里的的字符在翻转

<img src="D:/coding/my_cans/Algorithm/Note.assets/20231106172058.png" alt="img" style="zoom: 33%;" />

### 2. 替换数字

数组填充类的问题，考虑先预先给数组扩容带填充后的大小，然后在从后向前进行操作。

这么做有两个好处：

1. 不用申请新数组。
2. 从后向前填充元素，避免了从前向后填充元素时，每次添加元素都要将添加元素之后的所有元素向后移动的问题。

### 3. KMP算法 O(n+m)

字符串匹配类题目：在文本串中查找是否出现过模式串。暴力解法：O(m*n)

KMP的主要思想是**当出现字符串不匹配时，可以知道一部分之前已经匹配的文本内容，可以利用这些信息避免从头再去做匹配了**。

- 前缀是指不包含最后一个字符的所有以第一个字符开头的连续子串；
- 后缀是指不包含第一个字符的所有以最后一个字符结尾的连续子串

- 如何求next数组（前缀表）

  - 初始化、前后缀不相同、前后缀相同、更新next

  ![KMP精讲3](D:/coding/my_cans/Algorithm/Note.assets/KMP%E7%B2%BE%E8%AE%B23.gif)

- 如何利用前缀表实现匹配

  ![KMP精讲2](D:/coding/my_cans/Algorithm/Note.assets/KMP%E7%B2%BE%E8%AE%B22.gif)

字符串匹配类题目：文本串是否由重复的子串组成。

**当 最长相等前后缀不包含的子串的长度 可以被 字符串s的长度整除，那么不包含的子串 就是s的最小重复子串**

## 栈与队列

### 1. 基础理论 

栈stack（先进后出）、队列queue（先进先出）

- 栈是容器吗？

  **栈是以底层容器完成其所有的工作，对外提供统一的接口，底层容器是可插拔的（也就是说我们可以控制使用哪种容器来实现栈的功能）。**而在STL（c++标准库）中，栈和队列都不被归类为容器，而被归类为container adapter（容器适配器）

- STL中，stack是如何实现的？

  栈的底层实现可以是vector，deque，list。

  **常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。**

  ```c++
  std::stack<int, std::vector<int> > third;  // 使用vector为底层容器的栈
  ```

  <img src="D:/coding/my_cans/Algorithm/Note.assets/20210104235459376.png" alt="栈与队列理论3" style="zoom:50%;" />

- stack 提供迭代器来遍历stack空间么？

  同样不允许有遍历行为，不提供迭代器

**用栈实现队列**：额外设置一个“出栈”，将“进栈”中的元素都push到“出栈”中，然后在“出栈”中pop元素

**用队列实现栈**：一个队列在模拟栈弹出元素的时候只要将队列头部的元素（除了最后一个元素外） 重新添加到队列尾部，此时再去弹出元素就是栈的顺序了。

### 2. 有效的括号

1. 第一种情况，字符串里左方向的括号多余了 ，所以不匹配。
2. 第二种情况，括号没有多余，但是 括号的类型没有匹配上。
3. 第三种情况，字符串里右方向的括号多余了，所以不匹配。

考虑将字符串里的括号push进去，遇到左括号，则放入右括号，最后弹出进行匹配。

1. 第一种情况：已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false
2. 第二种情况：遍历字符串匹配的过程中，发现栈里没有要匹配的字符。所以return false
3. 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号return false

### 3. 波兰表达式（后缀表达式）

逆波兰表达式：是一种后缀表达式，所谓后缀就是指运算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。

该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。

逆波兰表达式主要有以下两个优点：

- 去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
- 适合用栈操作运算：遇到数字则入栈；遇到运算符则取出栈顶两个数字进行计算，并将结果压入栈中。

### 4. 滑动窗口最大值

队列模拟过程pop、push、getMaxValue【deque是可以两边扩展的，而且deque里元素并不是严格的连续分布的】

1. pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
2. push(value)：如果push的元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止

<img src="D:/coding/my_cans/Algorithm/Note.assets/239.%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3%E6%9C%80%E5%A4%A7%E5%80%BC-2.gif" alt="239.滑动窗口最大值-2" style="zoom: 67%;" />

### 5. 前K个高频元素

1. 要统计元素出现频率：**map**数据结构（key记录元素，value记录频率）
2. 对频率排序：利用**小顶堆**对value进行排序
3. 找出前K个高频元素

- **堆**

  堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。

  大顶堆：根节点是最大元素；小顶堆：根节点是最小元素

- **优先级队列**（披着队列外衣的堆）

  优先级队列，对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式，看起来就是一个队列。而且优先级队列内部元素是自动依照元素的权值排列。

  那么它是如何有序排列的呢：缺省情况下priority_queue利用max-heap（大顶堆）完成对元素的排序，这个大顶堆是以vector为表现形式的complete binary tree（完全二叉树）。

## 二叉树

### 1. 基础理论

