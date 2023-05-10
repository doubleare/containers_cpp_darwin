#ifndef __TREE__Node__H__
#define __TREE__Node__H__

namespace s21 {
enum compare { EQ, GR, LS };
enum vect { LEFT, RIGHT, PAR };

template <typename Key, typename M, typename T, typename Comp>
struct Node {
  Node* parent;
  Node* left;
  Node* right;
  T val;

  void connect_right(Node* o) {
    this->right = o;
    o->parent = this;
  }

  void connect_left(Node* o) {
    this->left = o;
    o->parent = this;
  }

  Node<Key, M, T, Comp>* to_root() {
    this->parent = nullptr;
    return this;
  }

  Node<Key, M, T, Comp>* to_right_left_par(vect f);

  Node<Key, M, T, Comp>* plus_minus(bool f);

  compare res_comp(Key v1, Key v2);

  compare cmp(Node* o) { return this->cmp(o->val); }

  compare cmp(Key val) { return this->res_comp(this->val, val); }

  compare cmp(std::pair<Key, M> val) {
    return this->res_comp(this->val.first, val.first);
  }

  compare cmp(std::pair<Key, M> p, Key val) {
    return this->res_comp(p.first, val);
  }

  compare cmp(Key p, Key val) { return this->res_comp(p, val); }

  void parent_ptr() {
    if (this->cmp(this->parent) == LS)
      this->parent->left = nullptr;
    else
      this->parent->right = nullptr;
  }

  void parent_ptr(Node* n_p) {
    if (this->cmp(n_p) == LS)
      n_p->connect_left(this);
    else
      n_p->connect_right(this);
  }
};

template <typename Key, typename M, typename T, typename Comp>
Node<Key, M, T, Comp>* Node<Key, M, T, Comp>::to_right_left_par(vect f) {
  Node<Key, M, T, Comp>* tmp = this;
  if (f == RIGHT)
    while (tmp->right != nullptr) tmp = tmp->right;
  else if (f == LEFT)
    while (tmp->left != nullptr) tmp = tmp->left;
  else
    while (tmp->parent != nullptr) tmp = tmp->parent;
  return tmp;
}

template <typename Key, typename M, typename T, typename Comp>
Node<Key, M, T, Comp>* Node<Key, M, T, Comp>::plus_minus(bool f) {
  Node<Key, M, T, Comp>*tmp = this->parent, *t = this;
  if (f) {
    while (tmp->parent != nullptr && tmp->cmp(t) == LS) tmp = tmp->parent;
  } else {
    while (tmp->parent != nullptr && t->cmp(tmp) == LS) tmp = tmp->parent;
  }
  return f && t->cmp(tmp) == LS ? tmp : !f && t->cmp(tmp) == GR ? tmp : t;
}

template <typename Key, typename M, typename T, typename Comp>
compare Node<Key, M, T, Comp>::res_comp(Key v1, Key v2) {
  compare ans = EQ;
  if (Comp{}(v1, v2))
    ans = LS;
  else if (Comp{}(v2, v1))
    ans = GR;
  return ans;
}

}  // namespace s21

#endif  // __TREE__Node__H__