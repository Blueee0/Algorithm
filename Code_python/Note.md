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
1. 删除链表的倒数第N个节点
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

2. 环形链表II
   - 题目：
    ```
    给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
    ```
   - 思路：
    1. 如何判断是否有环：分别定义 fast 和 slow 指针，从头结点出发，fast指针每次移动两个节点，slow指针每次移动一个节点，如果 fast 和 slow指针在途中相遇 ，说明这个链表有环。
    2. 如果有环，如何找到这个环的入口：这就意味着，从头结点出发一个指针，从相遇节点 也出发一个指针，这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是 环形入口的节点。
    - 代码：
     ```python
     def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            
            if slow == fast: # 说明此时有环
                slow = head
                while slow != fast:
                    slow = slow.next
                    fast = fast.next
                return slow
        return None
     ```

## 3.哈希表
1. 有效的字母异位词
   - 题目：
    ```
    给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
    ```
   - 思路：
    数组统计字母表

   - 代码：
     ```python
     def isAnagram(self, s: str, t: str) -> bool:
        record = [0] * 26
        for i in s:
            record[ord(i) - ord("a")] += 1
        for i in t:
            record[ord(i) - ord("a")] -= 1
        for i in range(26):
            #record数组如果有的元素不为零0，说明字符串s和t 一定是谁多了字符或者谁少了字符。
            if record[i] != 0:
                return False
        return True
     ```

2. 两个数组的交集
   - 题目：
    ```
    给定两个数组，编写一个函数来计算它们的交集。
    ```
   - 代码：
     ```python
     def intersection(self, nums1: List[int], nums2: List[int]) -> List[int]:
        return list(set(nums1) & set(nums2))
     ```

3. 快乐数
   - 题目：
    ```
    编写一个算法来判断一个数 n 是不是快乐数。

    「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。如果 可以变为  1，那么这个数就是快乐数。

    如果 n 是快乐数就返回 True ；不是，则返回 False 。
    ```
   - 思路：
     题目中说了会 无限循环，那么也就是说求和的过程中，sum会重复出现。
 
     所以这道题目使用哈希法，来判断这个sum是否重复出现，如果重复了就是return false， 否则一直找到sum为1为止。
   
   - 代码：
     ```python
     def isHappy(self, n: int) -> bool:
        record = set()  # 记录中间出现过的sum

        while True:
            n = self.getSum(n)
            if n == 1:
                return True

            # 如果中间结果重复出现，说明陷入死循环了，该数不是快乐数
            if n in record:
                return False
            else:
                record.add(n)

     def getSum(self, n: int) -> int:
        Sum = 0
        while n:
            # n对10求余，然后Sum += 余数平方
            n, r = divmod(n, 10)
            Sum += r ** 2 
        return Sum
     ```

4. 两数之和
   - 题目：
    ```
    给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    ```
   - 代码：
     ```python
     def twoSum(self, nums: List[int], target: int) -> List[int]:
        records = dict()

        # 遍历当前元素，并在map中寻找是否有匹配的key
        for index, value in enumerate(nums):  
            if target - value in records:   
                return [records[target - value], index]
            # 如果没找到匹配对，就把访问过的元素和下标加入到map中
            records[value] = index    
        return []
     ```

5. 四数相加II (哈希表)
   - 题目：
    ```
    给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。
    ```
   - 思路：
      1. 首先定义 一个unordered_map，key放a和b两数之和，value 放a和b两数之和出现的次数。
      2. 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中。
      3. 定义int变量count，用来统计 a+b+c+d = 0 出现的次数。
      4. 再遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就用count把map中key对应的value也就是出现次数统计出来。
      5. 最后返回统计值 count 就可以了
   - 代码：
     ```python
     def twoSum(self, nums: List[int], target: int) -> List[int]:
        records = dict()

        # 遍历当前元素，并在map中寻找是否有匹配的key
        for index, value in enumerate(nums):  
            if target - value in records:   
                return [records[target - value], index]
            # 如果没找到匹配对，就把访问过的元素和下标加入到map中
            records[value] = index    
        return []
     ```

6. 三数之和（双指针）
   - 题目：
    ```
    给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
    ```
   - 思路：
     1. 首先将数组排序，然后有一层for循环，i从下标0的地方开始，同时定一个下标left 定义在i+1的位置上，定义下标right 在数组结尾的位置上。
     2. 依然还是在数组中找到 abc 使得a + b +c =0，我们这里相当于 a = nums[i]，b = nums[left]，c = nums[right]。
     3. 接下来如何移动left 和right呢， 如果nums[i] + nums[left] + nums[right] > 0 就说明 此时三数之和大了，因为数组是排序后了，所以right下标就应该向左移动，这样才能让三数之和小一些。
      4. 如果 nums[i] + nums[left] + nums[right] < 0 说明 此时 三数之和小了，left 就向右移动，才能让三数之和大一些，直到left与right相遇为止。

   - 代码：
     ```python
     def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = []
        nums.sort()
        
        for i in range(len(nums)):
            # 如果第一个元素已经大于0，不需要进一步检查
            if nums[i] > 0:
                return result
            
            # 跳过相同的元素以避免重复
            if i > 0 and nums[i] == nums[i - 1]:
                continue
                
            left = i + 1
            right = len(nums) - 1
            
            while right > left:
                sum_ = nums[i] + nums[left] + nums[right]
                
                if sum_ < 0:
                    left += 1
                elif sum_ > 0:
                    right -= 1
                else:
                    result.append([nums[i], nums[left], nums[right]])
                    
                    # 跳过相同的元素以避免重复
                    while right > left and nums[right] == nums[right - 1]:
                        right -= 1
                    while right > left and nums[left] == nums[left + 1]:
                        left += 1
                        
                    right -= 1
                    left += 1
                    
        return result
     ```

7. 四数之和
   - 题目：
    ```
    给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
    ```
   - 思路：
    四数之和的双指针解法是两层for循环nums[k] + nums[i]为确定值，依然是循环内有left和right下标作为双指针，找出nums[k] + nums[i] + nums[left] + nums[right] == target的情况，三数之和的时间复杂度是O(n^2)，四数之和的时间复杂度是O(n^3) 。

   - 代码：
     ```python
     def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        result = []
        for i in range(n):
            if nums[i] > target and nums[i] > 0 and target > 0:# 剪枝（可省）
                break
            if i > 0 and nums[i] == nums[i-1]:# 去重
                continue
            for j in range(i+1, n):
                if nums[i] + nums[j] > target and target > 0: #剪枝（可省）
                    break
                if j > i+1 and nums[j] == nums[j-1]: # 去重
                    continue
                left, right = j+1, n-1
                while left < right:
                    s = nums[i] + nums[j] + nums[left] + nums[right]
                    if s == target:
                        result.append([nums[i], nums[j], nums[left], nums[right]])
                        while left < right and nums[left] == nums[left+1]:
                            left += 1
                        while left < right and nums[right] == nums[right-1]:
                            right -= 1
                        left += 1
                        right -= 1
                    elif s < target:
                        left += 1
                    else:
                        right -= 1
        return result
     ```

## 4.字符串
1. 反转字符串（双指针法）
   - 题目：
    ```
    将输入的字符串反转过来
    ```
   - 代码：
     ```python
     def reverseString(self, s: List[str]) -> None: 
        left = 0
        right = len(s) - 1
        while left < right:
            tmp = s[left]
            s[left] = s[right]
            s[right] = tmp
            left += 1
            right -= 1
     ```

2. 反转字符串II（模拟）
   - 题目：
    ```
    给定一个字符串 s 和一个整数 k，从字符串开头算起, 每计数至 2k 个字符，就反转这 2k 个字符中的前 k 个字符。
    如果剩余字符少于 k 个，则将剩余字符全部反转。
    如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
    ```
   - 思路：
    其实在遍历字符串的过程中，只要让 i += (2 * k)，i 每次移动 2 * k 就可以了，然后判断是否需要有反转的区间。

   - 代码：
     ```python
     def reverseStr(self, s: str, k: int) -> str:
        """
        1. 使用range(start, end, step)来确定需要调换的初始位置
        2. 对于字符串s = 'abc'，如果使用s[0:999] ===> 'abc'。字符串末尾如果超过最大长度，则会返回至字符串最后一个值，这个特性可以避免一些边界条件的处理。
        3. 用切片整体替换，而不是一个个替换.
        """
        def reverse_substring(text):
            left, right = 0, len(text) - 1
            while left < right:
                text[left], text[right] = text[right], text[left]
                left += 1
                right -= 1
            return text
        
        res = list(s)

        for cur in range(0, len(s), 2 * k):
            res[cur: cur + k] = reverse_substring(res[cur: cur + k])
        
        return ''.join(res)
     ```

3. 反转字符串中的单词
   - 题目：
     ```
     给定一个字符串，逐个翻转字符串中的每个单词。
     ```
   - 思路：
     将字符串转换成列表类型 -> 反转单词 -> 将列表转换为字符串

   - 代码：
     ```python
     def reverseWords(self, s: str) -> str:
        # 将字符串拆分为单词，即转换成列表类型
        words = s.split()

        # 反转单词
        left, right = 0, len(words) - 1
        while left < right:
            words[left], words[right] = words[right], words[left]
            left += 1
            right -= 1

        # 将列表转换成字符串
        return " ".join(words)
     ```

### KMP算法
- KMP的经典思想就是：当出现字符串不匹配时，可以记录一部分之前已经匹配的文本内容，利用这些信息避免从头再去做匹配。
1. 找出字符串中第一个匹配项的下标（即`strStr()`）
   - 题目：
     ```
     给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。
     ```
   - 思路：
     1. 初始化：

        a. 定义两个指针i和j，j指向前缀末尾位置，i指向后缀末尾位置。`j = -1`, 

        b. 初始化next数组 `next[0] = j`
        - `next[i]` 表示 i（包括i）之前最长相等的前后缀长度（其实就是j）

     2. 从`i = 1`开始遍历字符串s

        a. 处理前后缀不相同的情况：向前回退`j = next[j]`
        
        b. 处理前后缀相同的情况：i和j++，同时更新next数组`j++;` `next[i] = j`

   - 代码：
     ```python
     class Solution:
     # 构建next数组
     def getNext(self, next, s):
        # 1.初始化
        j = -1
        next[0] = j
        # 2. 循环遍历
        for i in range(1, len(s)):
            # a. 未找到匹配前后缀
            while j >= 0 and s[i] != s[j+1]:
                j = next[j]
            # b. 找到匹配前后缀
            if s[i] == s[j+1]:
                j += 1
            next[i] = j
    
     def strStr(self, haystack: str, needle: str) -> int:
        # 特殊处理：当needle为空没，返回0
        if not needle:
            return 0
        next = [0] * len(needle)
        self.getNext(next, needle)
        j = -1
        # 在haystack字符串里面找needle的匹配项
        for i in range(len(haystack)):
            while j >= 0 and haystack[i] != needle[j+1]:
                j = next[j]
            if haystack[i] == needle[j+1]:
                j += 1
            if j == len(needle) - 1:
                return i - len(needle) + 1
        return -1
     ```

2. 重复的子字符串
   - 题目：
     ```
     给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超过10000。
     ```
   - 思路：
     
     如果一个字符串s是由重复子串组成，那么 最长相等前后缀不包含的子串一定是字符串s的最小重复子串。
     
     如果s 是由最小重复子串p组成，即 s = n * p

   - 代码：
     ```python
     # 构建next数组
     def getNext(self, next, s):
        # 1.初始化
        j = -1
        next[0] = j
        # 2. 循环遍历
        for i in range(1, len(s)):
            # a. 未找到匹配前后缀
            while j >= 0 and s[i] != s[j+1]:
                j = next[j]
            # b. 找到匹配前后缀
            if s[i] == s[j+1]:
                j += 1
            next[i] = j

     def repeatedSubstringPattern(self, s: str) -> bool:
        if len(s) == 0:
            return False
        next = [0] * len(s)
        self.getNext(next, s)
        if next[-1] != -1 and len(s) % (len(s) - (next[-1] + 1)) == 0:
            return True
        return False
     ```

## 5.栈和队列
- 用队列实现栈
  ```python
  class MyStack:

    def __init__(self):
        self.que = deque()

    def push(self, x: int) -> None:
        self.que.append(x)

    def pop(self) -> int:
        if self.empty():
            return None
        for i in range(len(self.que)-1):
            self.que.append(self.que.popleft())
        return self.que.popleft()

    def top(self) -> int:
        # 写法一：
        # if self.empty():
        #     return None
        # return self.que[-1]

        # 写法二：
        if self.empty():
            return None
        for i in range(len(self.que)-1):
            self.que.append(self.que.popleft())
        temp = self.que.popleft()
        self.que.append(temp)
        return temp

    def empty(self) -> bool:
        return not self.que
  ```

- 用栈实现队列
  ```python
  class MyQueue:

    def __init__(self):
        """
        in主要负责push，out主要负责pop
        """
        self.stack_in = []
        self.stack_out = []


    def push(self, x: int) -> None:
        """
        有新元素进来，就往in里面push
        """
        self.stack_in.append(x)


    def pop(self) -> int:
        """
        Removes the element from in front of queue and returns that element.
        """
        if self.empty():
            return None
        
        if self.stack_out:
            return self.stack_out.pop()
        else:
            for i in range(len(self.stack_in)):
                self.stack_out.append(self.stack_in.pop())
            return self.stack_out.pop()


    def peek(self) -> int:
        """
        Get the front element.
        """
        ans = self.pop()
        self.stack_out.append(ans)
        return ans


    def empty(self) -> bool:
        """
        只要in或者out有元素，说明队列不为空
        """
        return not (self.stack_in or self.stack_out)
  ```

1. 有效的括号
   - 题目：
     ```
     给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
     ```
   - 思路：
     1. 第一种情况，字符串里左方向的括号多余了 ，所以不匹配。
        - 已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false
     2. 第二种情况，括号没有多余，但是 括号的类型没有匹配上。
        - 遍历字符串匹配的过程中，发现栈里没有要匹配的字符。所以return false
     3. 第三种情况，字符串里右方向的括号多余了，所以不匹配。  
        - 遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号return false

   - 代码：
     ```python
     def isValid(self, s: str) -> bool:
        stack = []
        
        for item in s:
            if item == '(':
                stack.append(')')
            elif item == '[':
                stack.append(']')
            elif item == '{':
                stack.append('}')
            elif not stack or stack[-1] != item:
                return False
            else:
                stack.pop()
        
        if not stack:
            return True
        else:
            return False
     ```


2. 删除字符串中的所有相邻重复项
   - 题目：
     ```
     给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
     在 S 上反复执行重复项删除操作，直到无法继续删除。
     返回最终的字符串。答案保证唯一。
     ```
   - 思路：
     用栈存放遍历过的元素，当遍历当前的这个元素的时候，检查栈顶是否是相同元素，若是则删除，若否则继续遍历。

   - 代码：
     ```python
     def removeDuplicates(self, s: str) -> str:
        stack = []
        for item in s:
            if stack and stack[-1] == item:
                stack.pop()
            else:
                stack.append(item)
        return "".join(stack)  # 字符串拼接
     ```


3. 逆波兰表达式求值
   - 题目：
     ```
     根据 逆波兰表示法，求表达式的值。
     ```

   - 代码：
     ```python
     from operator import add, sub, mul

     def div(x, y):
        # 使用整数除法的向零取整方式
        return int(x / y) if x * y > 0 else -(abs(x) // abs(y))

     class Solution(object):
        op_map = {'+': add, '-': sub, '*': mul, '/': div}
        
        def evalRPN(self, tokens: List[str]) -> int:
            stack = []
            for token in tokens:
                if token not in {'+', '-', '*', '/'}:
                    stack.append(int(token))
                else:
                    op2 = stack.pop()
                    op1 = stack.pop()
                    stack.append(self.op_map[token](op1, op2))  # 第一个出来的在运算符后面
            return stack.pop()
     ```

4. 滑动窗口最大值
   - 题目：
     ```
     给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
    
     返回滑动窗口中的最大值。
     ```
   - 思路：
    这是思路

   - 代码：
     ```python
        from collections import deque
        def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
            max_list = [] # 结果集合
            kept_nums = deque() # 单调队列

            for i in range(len(nums)):
                update_kept_nums(kept_nums, nums[i]) # 右侧新元素加入

                if i >= k and nums[i - k] == kept_nums[0]: # 左侧旧元素如果等于单调队列头元素，需要移除头元素
                    kept_nums.popleft()

                if i >= k - 1:
                    max_list.append(kept_nums[0])

            return max_list

        def update_kept_nums(kept_nums, num): # num 是新加入的元素
            # 所有小于新元素的队列尾部元素，在新元素出现后，都是没有价值的，都需要被移除
            while kept_nums and num > kept_nums[-1]:
                kept_nums.pop()

            kept_nums.append(num)
     ```

5. 前k个高频元素
   - 题目：
     ```
     给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
     ```
     
   - 代码：
     ```python
     import heapq
        def topKFrequent(self, nums: List[int], k: int) -> List[int]:
            #要统计元素出现频率
            map_ = {} #nums[i]:对应出现的次数
            for i in range(len(nums)):
                map_[nums[i]] = map_.get(nums[i], 0) + 1
            
            #对频率排序
            #定义一个小顶堆，大小为k
            pri_que = [] #小顶堆
            
            #用固定大小为k的小顶堆，扫描所有频率的数值
            for key, freq in map_.items():
                heapq.heappush(pri_que, (freq, key))
                if len(pri_que) > k: #如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
                    heapq.heappop(pri_que)
            
            #找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
            result = [0] * k
            for i in range(k-1, -1, -1):
                result[i] = heapq.heappop(pri_que)[1]
            return result
     ```

## 6.二叉树
### 遍历方法
1. 递归遍历
```python
# 前序遍历-递归-LC144_二叉树的前序遍历
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        res = []
        
        def dfs(node):
            if node is None:
                return
            
            res.append(node.val)
            dfs(node.left)
            dfs(node.right)
        dfs(root)
        return res

# 中序遍历-递归-LC94_二叉树的中序遍历
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        res = []
        
        def dfs(node):
            if node is None:
                return
            
            dfs(node.left)
            res.append(node.val)
            dfs(node.right)
        dfs(root)
        return res

# 后序遍历-递归-LC145_二叉树的后序遍历
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        res = []
        
        def dfs(node):
            if node is None:
                return
            
            dfs(node.left)
            dfs(node.right)
            res.append(node.val)

        dfs(root)
        return res
```

2. 层序遍历
```python
class Solution:
    """二叉树层序遍历II迭代解法"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def levelOrderBottom(self, root: TreeNode) -> List[List[int]]:
        if not root:
            return []
        queue = collections.deque([root])
        result = []
        while queue:
            level = []
            for _ in range(len(queue)):
                cur = queue.popleft()
                level.append(cur.val)
                if cur.left:
                    queue.append(cur.left)
                if cur.right:
                    queue.append(cur.right)
            result.append(level)
        return result[::-1]
```

1. 模版
   - 题目：
     ```
     这是题目
     ```
   - 思路：
    这是思路

   - 代码：
     ```python
     def result
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

