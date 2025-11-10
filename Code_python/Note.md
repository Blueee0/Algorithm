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
    class Solution(object):
    def search(self, nums, target):
        # 定义target在左闭右闭的区间里，[left, right]
        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = (left + right) / 2
            if nums[middle] > target:
                right = middle - 1
            elif nums[middle] < target:
                left = middle + 1  # target在右区间，所以[middle + 1, right]
            else:
                return middle  # 数组中找到目标值，直接返回下标
        return -1  # 未找到目标值
    ```
