#include <iostream>
#include <deque>
#include <unordered_map>
#include <algorithm>
// reference: 
// https://en.wikipedia.org/wiki/Tree_traversal#Depth-first_search_2
// https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack

struct TreeNode {
    int val_;
    TreeNode *left_;
    TreeNode *right_;
    TreeNode() : val_(0), left_(nullptr), right_(nullptr) {}
    TreeNode(int x) : val_(x), left_(nullptr), right_(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val_(x), left_(left), right_(right) {}
};

void process(TreeNode *node) {
    printf(" %d", node->val_);
}

// Preorder
void preorder(TreeNode *root) {
    if (!root) {
        return;
    }
    
    process(root);
    preorder(root->left_);
    preorder(root->right_);
}

void preorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    
    while (!stack.empty() || curr) {
        if (curr) {
            process(curr);
            stack.push_back(curr->right_);
            curr = curr->left_;
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
    
    inorder(root->left_);
    process(root);
    inorder(root->right_);
}

void inorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    
    while (!stack.empty() || curr) {
        if (curr) {
            stack.push_back(curr);
            curr = curr->left_;
        } else {
            curr = stack.back();
            stack.pop_back();
            process(curr);
            curr = curr->right_;
        }
    }
}

// Postorder
void postorder(TreeNode *root) {
    if (!root) {
        return;
    }
    
    postorder(root->left_);
    postorder(root->right_);
    process(root);
}

void postorder_iterative(TreeNode *root) {
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    TreeNode *last = nullptr;
    while (!stack.empty() || curr) {
        if (curr) {
            stack.push_back(curr);
            curr = curr->left_;
        } else {
            TreeNode *peek = stack.back(); // Only peek the top, not pop
            if (peek->right_ && peek->right_ != last) {
                curr = peek->right_; // Here to update curr
            } else {
                stack.pop_back(); // Pop and process
                process(peek);
                last = peek;
            }
        }
    }
}


bool is_balanced(TreeNode *root, int &height) {
    if (!root) {
        height = 0;
        return true;
    }
    
    int left_h;
    int right_h;
    bool left_blcd;
    bool right_blcd;
    left_blcd = is_balanced(root->left_, left_h);
    right_blcd = is_balanced(root->right_, right_h);
    height = std::max(left_h, right_h) + 1;
    printf("node: %d height: %d\n", root->val_, height);
    
    return abs(left_h - right_h) <= 1 && left_blcd && right_blcd;
}

bool is_balanced_iterative(TreeNode *root, int &height) {
    std::unordered_map<TreeNode *, int> heights;
    std::deque<TreeNode *> stack;
    TreeNode *curr = root;
    TreeNode *last = nullptr;
    bool is_balanced = true;
    
    while (!stack.empty() || curr) {
        if (curr) {
            heights[curr] = 0;
            stack.push_back(curr);
            curr = curr->left_;
        } else {
            TreeNode *peek = stack.back();
            if (peek->right_ && peek->right_ != last) {
                curr = peek->right_;
            } else {
                stack.pop_back();
//              curr = peek;
//              process(curr);
//              last = curr;
                process(peek);
                last = peek;
                
                int left_h = heights[peek->left_];
                int right_h = heights[peek->right_];
                heights[peek] = std::max(left_h, right_h) + 1;
                is_balanced = (abs(left_h - right_h) <= 1);
                printf("node: %d height: %d\n", peek->val_, heights[peek]);
            }
        }
    }
    
    height = heights[root];
    return is_balanced;
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
        tree[i].val_ = i + 1;
    }
    tree[0].left_ = tree + 1;
    tree[0].right_ = tree + 5;
    tree[1].left_ = tree + 2;
    tree[1].right_ = tree + 3;
    tree[3].left_ = tree + 4;
    tree[5].left_ = tree + 6;
    tree[5].right_ = tree + 8;
    tree[6].left_ = tree + 7;
    
//  preorder(tree); printf("\n");
//  preorder_iterative(tree); printf("\n");
//  inorder(tree); printf("\n");
//  inorder_iterative(tree); printf("\n");
//  postorder(tree); printf("\n");
//  postorder_iterative(tree); printf("\n");
    
    int height;
    std::cout << is_balanced(tree, height) << std::endl;
    printf("height: %d\n", height);
    
//  std::cout << is_balanced_iterative(tree, height) << std::endl;
    bool is_blcd = is_balanced_iterative(tree, height);
    printf("is_blcd: %d height: %d\n", static_cast<int>(is_blcd), height);
    
    delete [] tree;
    return 0;
}
