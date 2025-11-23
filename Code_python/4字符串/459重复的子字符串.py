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

    def repeatedSubstringPattern(self, s: str) -> bool:
        if len(s) == 0:
            return False
        next = [0] * len(s)
        self.getNext(next, s)
        if next[-1] != -1 and len(s) % (len(s) - (next[-1] + 1)) == 0:
            return True
        return False