class MyStack {
public:
    queue<int> que;

    MyStack() {

    }

    void push(int x) { 
        que.push(x); 
    }

    int pop() {
        int size = que.size();
        size--;
        while (size--) {
            que.push(que.front());
            que.pop();
        }
        int result = que.front(); // ��ʱ������Ԫ��˳�����ջ��˳����
        que.pop();
        return result;
    }

    int top() {
        int size = que.size();
        size--;
        while (size--) {
            que.push(que.front());
            que.pop();
        }
        int result = que.front();   // ��ʱ������Ԫ��˳�����ջ��˳����
        que.push(que.front());      // ����ȡ���Ԫ��Ҳ������ӵ�����β������֤���ݽṹû�б仯
        que.pop();
        return result;
    }

    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */