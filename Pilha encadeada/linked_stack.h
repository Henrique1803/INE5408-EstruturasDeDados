//! Copyright [year] <Copyright Owner>
namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {  // Elemento (implementação pronta)
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
	top_ = nullptr;
	size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
	clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
	while (!empty()) {
		pop();
	}
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    if (top_ == nullptr) {
        novo -> next(nullptr);
    } else {
        novo -> next(top_);
    }
    top_ = novo;
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    }
    T aux;
    Node *p = top_;
    aux = p -> data();
    top_ = p -> next();
    delete p;
    size_--;
    return aux;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    }
    Node *p = top_;
    return p->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
