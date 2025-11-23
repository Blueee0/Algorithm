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