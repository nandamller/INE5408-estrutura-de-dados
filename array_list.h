// Copyright [2022] <Fernanda Larissa Müller>
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
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    contents[size_] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    size_++;
    for (int i = size_ - 1; i > 0; i--) {
        contents[i] = contents[i-1];
    }
    contents[0] = data;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (index > size_) {
        throw std::out_of_range("fora do alcance");
    }
    if (index == 0) {
        return push_front(data);
    } else if (index == size_) {
        return push_back(data);
    } else {
        size_++;
        for (int i = size_-1; (std::size_t)i > index; i--) {
            contents[i] = contents[i-1];
        }
    }
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    int i = 0;
    while ((std::size_t)i < size_ && contents[i] < data) {
        i++;
    }
    insert(data, i);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (index > size_-1) {
        throw std::out_of_range("fora de alcance");
    }
    size_--;
    int aux = contents[index];
    for (int i = index; (std::size_t)i < size_; i++) {
        contents[i] = contents[i+1];
    }
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    size_--;
    return contents[size_];
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    int aux = contents[0];
    size_--;
    for (int i = 0; (std::size_t)i < size_; i++) {
        contents[i] = contents[i+1];
    }
    return aux;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; (std::size_t)i < size_; i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; (std::size_t)i < size_; i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size_;
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
    if (size_-1 < index) {
        throw std::out_of_range("posicao nao existente");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (size_-1 < index) {
        return std::out_of_range("posicao nao existente");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (size_-1 < index) {
        throw std::out_of_range("posicao nao existente");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (size_-1 < index) {
        return std::out_of_range("posicao nao existente");
    }
    return contents[index];
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    for (int i = 0; (std::size_t)i < size_; i++) {
        if (contents[i] == data) {
            pop(i);
    }
}
}

