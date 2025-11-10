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
        int result = que.front(); // 此时弹出的元素顺序就是栈的顺序了
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
        int result = que.front();   // 此时弹出的元素顺序就是栈的顺序了
        que.push(que.front());      // 将获取完的元素也重新添加到队列尾部，保证数据结构没有变化
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