class Solution:
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