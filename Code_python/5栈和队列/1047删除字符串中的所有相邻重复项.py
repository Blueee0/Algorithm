class Solution:
    def removeDuplicates(self, s: str) -> str:
        stack = []
        for item in s:
            if stack and stack[-1] == item:
                stack.pop()
            else:
                stack.append(item)
        return "".join(stack)  # 字符串拼接