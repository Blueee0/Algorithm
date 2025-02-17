/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
    public:
        Node* connect(Node* root) {
            queue<Node*> que;
            // Node* result = root;
    
            if (root != NULL) {
                que.push(root);
            }
    
            while (!que.empty()) {
                int size = que.size();
                // vector<int*> vec;
                Node* node;
                Node* nodePre;
    
                for (int i = 0; i < size; i++) {
                    if (i == 0) {
                        nodePre = que.front(); // 取出一层的头结点
                        que.pop();
                        node = nodePre;
                    } else {
                        node = que.front();
                        que.pop();
                        nodePre->next = node; // 本层前一个节点next指向本节点
                        nodePre = nodePre->next;
                    }
                    if (node->left)
                        que.push(node->left);
                    if (node->right)
                        que.push(node->right);
                }
                nodePre->next = NULL; // 本层最后一个节点指向NULL
            }
            return root;
        }
    };