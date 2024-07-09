//! Copyright [2024] <Henrique Mateus Teodoro>
#include <algorithm>
#include "array_list.h"

namespace structures {

template<typename T>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
            height_ = 0;
        }

        T data;
        int height_;
        Node* left;
        Node* right;

        int fb() {
            int left_height = (left != nullptr) ? left->height_ : -1;
            int right_height = (right != nullptr) ? right->height_ : -1;
            return left_height - right_height;
        }

        Node* insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left = left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right = right->insert(data_);
                }
            }
            updateHeight();
            return balance();
        }

        Node* balance() {
            int balance_factor = fb();
            if (balance_factor > 1) {  // desbalanceamento à esquerda
                if (left->fb() >= 0) {  // caso LL
                    return ll(this);
                } else {  // caso LR
                    left = rr(left);
                    return ll(this);
                }
            } else if (balance_factor < -1) {  // desbalanceamento à direita
                if (right->fb() <= 0) {  // caso RR
                    return rr(this);
                } else {  // caso RL
                    right = ll(right);
                    return rr(this);
                }
            }
            return this;
        }

        Node* remove(Node* node, const T& data_) {
            if (node == nullptr) {
                return node;
            }
            if (data_ < node->data) {
                node->left = remove(node->left, data_);
            } else if (data_ > node->data) {
                node->right = remove(node->right, data_);
            } else {
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                Node* temp = node->right->minimum();
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
            node->updateHeight();
            return node->balance();
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                return (left != nullptr) ? left->contains(data_) : false;
            } else {
                return (right != nullptr) ? right->contains(data_) : false;
            }
        }

        void updateHeight() {
            int left_height = (left != nullptr) ? left->height_ : -1;
            int right_height = (right != nullptr) ? right->height_ : -1;
            height_ = 1 + std::max(left_height, right_height);
        }

        Node* ll(Node *px) {  // Rotação à esquerda
            Node *py = px->left;
            px->left = py->right;
            py->right = px;
            px->updateHeight();
            py->updateHeight();
            return py;
        }

        Node* rr(Node *px) {  // Rotação à direita
            Node *py = px->right;
            px->right = py->left;
            py->left = px;
            px->updateHeight();
            py->updateHeight();
            return py;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        Node* minimum() {
            return (left == nullptr) ? this : left->minimum();
        }

        int height() const {
            return height_;
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::AVLTree<T>::AVLTree() : root(nullptr), size_(0) {}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (contains(data)) {
        throw std::out_of_range("Elemento já está presente.");
    }
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root = root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    Node* p = root;
    p = p->remove(p, data);
    if (p != nullptr) {
        size_--;
    }
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return (root != nullptr) ? root->height() : -1;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    return (root != nullptr) ? root->contains(data) : false;
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->pre_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->in_order(L);
    }
    return L;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->post_order(L);
    }
    return L;
}
