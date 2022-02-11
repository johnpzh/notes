#include <iostream>
#include <deque>
// reference: 
// https://en.wikipedia.org/wiki/Tree_traversal#Depth-first_search_2
// https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void process(TreeNode *node) {
    printf(" %d", node->val);
}

// Preorder
void preorder(TreeNode *root) {
    if (!root) {
        return;
    }
    
    process(root);
    preorder(root->left);
    preorder(root->right);
}

void preorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    
    while (!stack.empty() || curr) {
        if (curr) {
            process(curr);
            stack.push_back(curr->right);
            curr = curr->left;
        } else {
            curr = stack.back();
            stack.pop_back();
        }
    }
}

// Inorder
void inorder(TreeNode *root) {
    if (!root) {
        return;
    }
    
    inorder(root->left);
    process(root);
    inorder(root->right);
}

void inorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    
    while (!stack.empty() || curr) {
        if (curr) {
            stack.push_back(curr);
            curr = curr->left;
        } else {
            curr = stack.back();
            stack.pop_back();
            process(curr);
            curr = curr->right;
        }
    }
}

// Postorder
void postorder(TreeNode *root) {
    if (!root) {
        return;
    }
    
    postorder(root->left);
    postorder(root->right);
    process(root);
}

void postorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    TreeNode *last = nullptr;
    while (!stack.empty() || curr) {
        if (curr) {
            stack.push_back(curr);
            curr = curr->left;
        } else {
            TreeNode *peek = stack.back(); // Only peek the top, not pop
            if (peek->right && peek->right != last) {
                curr = peek->right; // Here to update curr
            } else {
                stack.pop_back(); // Pop and process
                process(peek);
                last = peek;
            }
        }
    }
}


////
//     1
//    / \
//   2   6
//  / \ / \
// 3  4 7  9
//   / /
//  5 8
////
// Preorder:  1 2 3 4 5 6 7 8 9
// Inorder:   3 2 5 4 1 8 7 6 9
// Postorder: 3 5 4 2 8 7 9 6 1

int main(int argc, char *argv[]) {
    TreeNode *tree = new TreeNode[9];
    for (int i = 0; i < 9; ++i) {
        tree[i].val = i + 1;
    }
    tree[0].left = tree + 1;
    tree[0].right = tree + 5;
    tree[1].left = tree + 2;
    tree[1].right = tree + 3;
    tree[3].left = tree + 4;
    tree[5].left = tree + 6;
    tree[5].right = tree + 8;
    tree[6].left = tree + 7;
    
    preorder(tree); printf("\n");
    preorder_iterative(tree); printf("\n");
    inorder(tree); printf("\n");
    inorder_iterative(tree); printf("\n");
    postorder(tree); printf("\n");
    postorder_iterative(tree); printf("\n");
    
    delete [] tree;
    return 0;
}
