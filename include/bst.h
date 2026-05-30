// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T     value;
    int   count;
    Node* left;
    Node* right;

    explicit Node(const T& val)
        : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insertNode(Node* node, const T& val) {
    if (!node) return new Node(val);
    if (val == node->value) {
      node->count++;
    } else if (val < node->value) {
      node->left  = insertNode(node->left,  val);
    } else {
      node->right = insertNode(node->right, val);
    }
    return node;
  }

  int depthNode(Node* node) const {
    if (!node) return 0;
    int l = depthNode(node->left);
    int r = depthNode(node->right);
    return 1 + (l > r ? l : r);
  }

  Node* searchNode(Node* node, const T& val) const {
    if (!node)              return nullptr;
    if (val == node->value) return node;
    if (val <  node->value) return searchNode(node->left,  val);
    return searchNode(node->right, val);
  }

  void collectNodes(Node* node, std::vector<Node*>& vec) const {
    if (!node) return;
    collectNodes(node->left,  vec);
    vec.push_back(node);
    collectNodes(node->right, vec);
  }

  void destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() { destroyTree(root); }

  BST(const BST&)            = delete;
  BST& operator=(const BST&) = delete;

  void insert(const T& val) {
    root = insertNode(root, val);
  }

  int depth() const {
    if (!root) return 0;
    return depthNode(root) - 1;
  }

  int search(const T& val) const {
    Node* n = searchNode(root, val);
    return n ? n->count : 0;
  }

  std::vector<std::pair<T, int>> sortedByFrequency() const {
    std::vector<Node*> nodes;
    collectNodes(root, nodes);

    std::vector<std::pair<T, int>> result;
    result.reserve(nodes.size());
    for (Node* n : nodes)
      result.emplace_back(n->value, n->count);

    std::sort(result.begin(), result.end(),
              [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
              });

    return result;
  }
};

#endif  // INCLUDE_BST_H_
