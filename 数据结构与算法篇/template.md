## 常见算法模板

### 二叉树中序遍历

左->中->右
```
void middleOrderTransval(TreeNode *root)
{
    if (root == nullptr) {
        return;
    }
    TreeNode *fake_head = new TreeNode();
    auto node = root;
    TreeNode *it = fake_head;
    stack<TreeNode *> stk;
    while (node != nullptr || !stk.empty()) {
        while (node != nullptr) {
            stk.push(node);
            node = node->left;
        }
        if (!stk.empty()) {
            node = stk.top();
            stk.pop();
            it->right = new TreeNode(node->val, nullptr, nullptr);
            it->right = node;
            node->left = nullptr;
            it = it->right;
            node = node->right;
        }
    }
}
```
