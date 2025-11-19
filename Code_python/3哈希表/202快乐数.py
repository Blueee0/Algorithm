class Solution:
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

