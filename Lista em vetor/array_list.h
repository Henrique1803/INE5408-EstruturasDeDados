// Copyright [year] <Copyright Owner>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

//-------------------------------------

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size());
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (!full() && index >= 0 && index <= size()) {
        int indexInt = static_cast<int>(index);
        for (int i = size()-1; i >= indexInt; i--) {
            contents[i + 1] = contents[i];
        }
        size_++;
        contents[indexInt] = data;
    } else {
        throw std :: out_of_range("lista cheia ou index inválido!");
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    int i;
    for (i = 0; i < static_cast<int>(size()) && contents[i] < data; i++) {}
    insert(data, i);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (!empty() && index >= 0 && index < size()) {
        int indexInt = static_cast<int>(index);
        T aux = contents[index];
        for (int i = indexInt+1; i < static_cast<int>(size()); i++) {
            contents[i -1] = contents[i];
        }
        size_--;
        return aux;
    } else {
        throw std :: out_of_range("lista vazia ou index inválido!");
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size()-1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    size_t posicao = find(data);
    pop(posicao);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    if (size() == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size() == max_size());
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    std::size_t index = find(data);
    return (index < size());
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    // retorna o indice da primeira ocorrencia de 'data' na lista, se houver
    // retorna 'size()', se 'data' nao for parte da lista
    size_t posicao = size();
    for (size_t i = 0; i < size(); i++) {
        if (contents[i] == data) {
            posicao = i;
        }
    }
    return posicao;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    } else if (index >= size()) {
        throw std::out_of_range("invalid index");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    const T aux = at(index);
    return aux;
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
