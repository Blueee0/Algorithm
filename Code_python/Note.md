# Algorithm - Python

## Python基础知识
> 当前python版本：3.12.9

### 基础语法
1. 编码

    默认情况下，Python3 源码文件以 UTF-8 编码，所有字符串都是 unicode 字符串。

2. 标识符

    - 第一个字符必须以字母（a-z, A-Z）或下划线 _ 。
    - 标识符的其他的部分由字母、数字和下划线组成。
    - 标识符对大小写敏感，count 和 Count 是不同的标识符。
    - 标识符对长度无硬性限制，但建议保持简洁（一般不超过 20 个字符）。
    - 禁止使用保留关键字，如 if、for、class 等不能作为标识符。
    * **Python 3 允许使用 Unicode 字符作为标识符，可以用中文作为变量名，非 ASCII 标识符也是允许的了。**


3. 保留字/关键字

    保留字即关键字，我们不能把它们用作任何标识符名称。Python 的标准库提供了一个 keyword 模块，可以输出当前版本的所有关键字：

    ```text
    >>> import keyword
    >>> keyword.kwlist
    ['False', 'None', 'True', 'and', 'as', 'assert', 'async', 'await', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
    ```

4. 数据类型
    - Number：int、float、bool、complex（复数）
    - **在混合计算时，Python会把整型转换成为浮点数。**
        ```
        数值运算示例
        >>> 5 + 4  # 加法
        9
        >>> 4.3 - 2 # 减法
        2.3
        >>> 3 * 7  # 乘法
        21
        >>> 2 / 4  # 除法，得到一个浮点数
        0.5
        >>> 2 // 4 # 除法，得到一个整数
        0
        >>> 17 % 3 # 取余 
        2
        >>> 2 ** 5 # 乘方
        32
        ```

    - String：用单引号 ' 或双引号 " 括起来，同时使用反斜杠 \ 转义特殊字符。字符串前面添加一个 r，表示原始字符串。
    - **与 C 字符串不同的是，Python 字符串不能被改变。向一个索引位置赋值，比如 word[0] = 'm' 会导致错误。**
        ```
        str = 'Runoob'  # 定义一个字符串变量

        print(str)           # 打印整个字符串
        print(str[0:-1])     # 打印字符串第一个到倒数第二个字符（不包含倒数第一个字符）
        print(str[0])        # 打印字符串的第一个字符
        print(str[2:5])      # 打印字符串第三到第五个字符（不包含索引为 5 的字符）
        print(str[2:])       # 打印字符串从第三个字符开始到末尾
        print(str * 2)       # 打印字符串两次
        print(str + "TEST")  # 打印字符串和"TEST"拼接在一起
        print('Ru\noob')     # 输出Ru 换行 oob
        print(r'Ru\noob')    # 输出Ru\noob
        ```
    
    - List：列表中元素的类型可以不相同，它支持数字，字符串甚至可以包含列表（所谓嵌套）。
        - **列表中的元素是可以改变的**
            ```
            >>> a = [1, 2, 3, 4, 5, 6]
            >>> a[0] = 9
            >>> a[2:5] = [13, 14, 15]
            >>> a
            [9, 2, 13, 14, 15, 6]
            ```
        - 翻转字符串
            ```python
            def reverseWords(input): 
            
            # 通过空格将字符串分隔符，把各个单词分隔为列表
            inputWords = input.split(" ") 
        
            # 翻转字符串
            # 假设列表 list = [1,2,3,4],  
            # list[0]=1, list[1]=2 ，而 -1 表示最后一个元素 list[-1]=4 ( 与 list[3]=4 一样) 
            # inputWords[-1::-1] 有三个参数
            # 第一个参数 -1 表示最后一个元素
            # 第二个参数为空，表示移动到列表末尾
            # 第三个参数为步长，-1 表示逆向
            inputWords = inputWords[-1::-1] 
        
            # 重新组合字符串
            output = ' '.join(inputWords) 
            
            return output 
        
        if __name__ == "__main__": 
            input = 'I like runoob'
            rw = reverseWords(input) 
            print(rw)
            ```
    - Tuple：元组（tuple）与列表类似，不同之处在于元组的元素不能修改。元组写在小括号 () 里，元素之间用逗号隔开。
    - **如果你想创建只有一个元素的元组，需要注意在元素后面添加一个逗号。**

    - Set：Python 中的集合（Set）是一种无序、可变的数据类型，用于存储唯一的元素。
    集合中的元素不会重复，并且可以进行交集、并集、差集等常见的集合操作。
    在 Python 中，集合使用大括号 {} 表示，元素之间用逗号 , 分隔。
        ```python
        sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Zhihu', 'Baidu'}

        print(sites)   # 输出集合，重复的元素被自动去掉

        # 成员测试
        if 'Runoob' in sites :
            print('Runoob 在集合中')
        else :
            print('Runoob 不在集合中')

        # set可以进行集合运算
        a = set('abracadabra')
        b = set('alacazam')

        print(a)
        print(a - b)     # a 和 b 的差集
        print(a | b)     # a 和 b 的并集
        print(a & b)     # a 和 b 的交集
        print(a ^ b)     # a 和 b 中不同时存在的元素
        ```

    - Dictionary:字典是一种映射类型，字典用 { } 标识，它是一个无序的 键(key) : 值(value) 的集合。
        - 键(key)必须使用不可变类型。
        - 在同一个字典中，键(key)必须是唯一的。
        ```python
        dict = {}
        dict['one'] = "1 - 菜鸟教程"
        dict[2]     = "2 - 菜鸟工具"

        tinydict = {'name': 'runoob','code':1, 'site': 'www.runoob.com'}

        print (dict['one'])       # 输出键为 'one' 的值
        print (dict[2])           # 输出键为 2 的值
        print (tinydict)          # 输出完整的字典
        print (tinydict.keys())   # 输出所有键
        print (tinydict.values()) # 输出所有值
        ```
    
5. 迭代器与生成器
    - 迭代器：迭代器对象从集合的第一个元素开始访问，直到所有的元素被访问完结束。迭代器只能往前不会后退。
    迭代器有两个基本的方法：iter() 和 next()。
        ```python
        list=[1,2,3,4]
        it = iter(list)    # 创建迭代器对象
        for x in it:
            print (x, end=" ")
        ```

## 1.数组

### 二分查找
> 时间复杂度`O(log n)`，空间复杂度`O(1)`

  定义 target 是在一个在左闭右闭的区间里，也就是[left, right]。

  - `while (left <= right)` 要使用 <= ，因为left == right是有意义的，所以使用 <=

  - `if (nums[middle] > target) right = middle - 1`，因为当前这个nums[middle]一定不是target，那么接下来要查找的左区间结束下标位置就是 middle - 1
    ```python
    def search(self, nums: List[int], target: int) -> int:
        # 定义target在左闭右闭的区间里，[left, right]
        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = int((left + right) / 2)
            if nums[middle] > target:
                right = middle - 1
            elif nums[middle] < target:
                left = middle + 1  # target在右区间，所以[middle + 1, right]
            else:
                return middle  # 数组中找到目标值，直接返回下标
        return -1  # 未找到目标值
    ```

### 双指针法
1. 移除元素
   - 题目：
    ```
    给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
    不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
    ```
   - 思路：
    `slow`指向更新后的数组的下标，`fast`指向当前元素，`return slow`即更新后数组的个数。
   - 代码：
    ```python
     def removeElement(self, nums: List[int], val: int) -> int:
        slow = 0   # 慢指针指向下标
        fast = 0   # 快指针指向当前元素
        size = len(nums)
        while fast < size :
            if nums[fast] != val:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1
        return slow
    ```

2. 有序数组的平方
   - 题目：
    ```
    给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序
    ```
   - 思路：
    最大值要么在最左边，要么在最右边。`left = 0`,`right = len(nums) - 1`
   - 代码：
    ```python
    def sortedSquares(self, nums: List[int]) -> List[int]:
        left = 0
        right = len(nums) - 1
        i = len(nums) - 1
        res = [float('inf')] * len(nums) # 需要提前定义列表，存放结果
        while left <= right:
            if(nums[left] ** 2 < nums[right] **2):
                res[i] = nums[right] **2
                right -= 1
            else:
                res[i] = nums[left] **2
                left += 1
            i -= 1
        return res
    ```

### 滑动窗口
1. 长度最小的子数组
   - 题目：
    ```
    给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
    ```
   - 思路：
    只用一个for循环，那么这个循环的索引，一定是表示 滑动窗口的终止位置。
        - 窗口内是什么：满足其和 ≥ s 的长度最小的 连续 子数组。
        - 窗口的起始位置如何移动：如果当前窗口的值大于等于s了，窗口就要向前移动了（也就是该缩小了）。
        - 窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。
   - 代码：
    ```python
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        right = 0
        min_len = float('inf')
        cur_sum = 0 #当前的累加值
        while right < len(nums):
            cur_sum += nums[right]
            while(cur_sum >= target):
                min_len = min(min_len, right - left + 1)
                cur_sum -= nums[left]
                left += 1
            right += 1
        if min_len == float('inf') :
            return 0
        else:
            return min_len
    ```

## 2.链表
```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
class MyLinkedList:
    def __init__(self):
        self.dummy_head = ListNode()
        self.size = 0

    # 获取链表中下标为 index 的节点的值。
    def get(self, index: int) -> int:
        if index < 0 or index >= self.size:
            return -1
        current = self.dummy_head.next
        for i in range(index):
            current = current.next            
        return current.val

    # 将一个值为 val 的节点插入到链表中第一个元素之前
    def addAtHead(self, val: int) -> None:
        self.dummy_head.next = ListNode(val, self.dummy_head.next)
        self.size += 1

    # 将一个值为 val 的节点追加到链表中作为链表的最后一个元素
    def addAtTail(self, val: int) -> None:
        current = self.dummy_head
        while current.next:
            current = current.next
        current.next = ListNode(val)
        self.size += 1

    # 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。
    def addAtIndex(self, index: int, val: int) -> None:
        if index < 0 or index > self.size:
            return  
        current = self.dummy_head
        for i in range(index):
            current = current.next
        current.next = ListNode(val, current.next)
        self.size += 1

    # 删除链表中下标为 index 的节点
    def deleteAtIndex(self, index: int) -> None:
        if index < 0 or index >= self.size:
            return
        current = self.dummy_head
        for i in range(index):
            current = current.next
        current.next = current.next.next
        self.size -= 1
```
### 基础操作
1. 删除链表元素
   - 题目：
    ```
    题意：删除链表中等于给定值 val 的所有节点。
    ```
   - 代码：
    ```python
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, val=0, next=None):
    #         self.val = val
    #         self.next = next
    def removeElements(self, head: Optional[ListNode], val: int) -> Optional[ListNode]:
        # 创建虚拟头结点
        dummy_head = ListNode(next = head)
        current = dummy_head

        while current.next is not None:
            if current.next.val == val:
                current.next = current.next.next
            else:
                current = current.next
        return dummy_head.next
    ```
2. 反转链表
   - 题目：
    ```
    给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
    ```
   - 思路：
     双指针法，cur指向当前节点，pre指向之前一个节点，先用tmp保存cur.next，然后cur.next = pre，pre = cur，cur = temp
   - 代码：
    ```python
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        pre = None
        while cur:
            tmp = cur.next
            cur.next = pre
            pre = cur
            cur = tmp
        return pre
    ```
3. 链表相交
   - 题目：
    ```
    给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
    ```
   - 思路：
    1. 先计算两个链表的长度差，然后让长的链表先走差值步，然后两个链表一起走，直到相遇
    2. 双指针法，两个指针分别从两个链表的头结点出发，走到末尾后，再从另一个链表的头结点出发，直到相遇
   - 代码：
    ```python
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        lenA, lenB = 0, 0

        cur = headA
        while cur:         # 求链表A的长度
            cur = cur.next 
            lenA += 1

        cur = headB
        while cur:         # 求链表B的长度
            cur = cur.next 
            lenB += 1

        curA, curB = headA, headB

        if lenA > lenB:     # 让curB为最长链表的头，lenB为其长度
            curA, curB = curB, curA
            lenA, lenB = lenB, lenA 

        for _ in range(lenB - lenA):  # 让curA和curB在同一起点上（末尾位置对齐）
            curB = curB.next 

        while curA:         #  遍历curA 和 curB，遇到相同则直接返回
            if curA == curB:
                return curA
            else:
                curA = curA.next 
                curB = curB.next
                
        return None 
    ```


### 双指针法
3. 删除链表的倒数第N个节点
   - 题目：
    ```
    给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
    ```
   - 思路：
    快慢指针，快指针先走n步，然后快慢指针一起走，当快指针走到头时，慢指针指向的就是倒数第n个节点
   - 代码：
    ```python
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy_Head = ListNode(next = head)
        slow = fast = dummy_Head

        for i in range(n+1):
            fast = fast.next

        while fast:
            slow = slow.next
            fast = fast.next
        
        slow.next = slow.next.next
        
        return dummy_Head.next
    ```

## 模拟
1. 螺旋矩阵II
   - 题目：
    ```
    给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
    ```
   - 代码：
    ```python
    def generateMatrix(self, n: int) -> List[List[int]]:
        if n <= 0:
            return []
        
        # 初始化 n x n 矩阵
        matrix = [[0]*n for _ in range(n)]

        # 初始化边界和起始值
        top, bottom, left, right = 0, n-1, 0, n-1
        num = 1

        while top <= bottom and left <= right:
            # 从左到右填充上边界
            for i in range(left, right + 1):
                matrix[top][i] = num
                num += 1
            top += 1

            # 从上到下填充右边界
            for i in range(top, bottom + 1):
                matrix[i][right] = num
                num += 1
            right -= 1

            # 从右到左填充下边界

            for i in range(right, left - 1, -1):
                matrix[bottom][i] = num
                num += 1
            bottom -= 1

            # 从下到上填充左边界

            for i in range(bottom, top - 1, -1):
                matrix[i][left] = num
                num += 1
            left += 1

        return matrix
    ```

2. 两两交换链表中的节点
   - 题目：
    ```
    给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
    ```
   - 思路：
    tmp暂存cur.next，tmp1暂存cur.next.next.next
   - 代码：
    ```python
        def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy_head = ListNode(next = head)
        current = dummy_head

        while current.next and current.next.next:
            tmp = current.next
            tmp1 = current.next.next.next

            current.next = current.next.next
            current.next.next = tmp
            current = current.next.next # 更新current的值
            tmp.next = tmp1
            
        return dummy_head.next
    ```

