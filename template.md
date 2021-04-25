# 算法模板
## 中序遍历
左->中->右
```
void middleOrderTraversal(TreeNode *root) {
  if (root = nullptr) {
    return nullptr;
  }
  stack<TreeNode *> stk;
  TreeNode *node = root;
  while (node != nullptr || !stk.empty()) {
    while (node != nullptr) {
      stk.push(node);
      node = node->left;
    }
    if (!stk.emtpy()) {
      node = stk.top();
      stk.pop();
      cout << node->val << " ";
      node = node->right;
    }
  }
```
