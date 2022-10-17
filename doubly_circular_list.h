//! Copyright [2022] <Fernanda Larissa Müller>
#ifndef STRUCTURES_DOUBLE_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLE_CIRCULAR_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return next_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0;
}


template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }

    Node *q = head->prev();

    Node *novo = new Node(data);
    novo->next(head);
    novo->prev(q);

    head->prev(novo);
    q->next(novo);

    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);

    if (empty()) {
        head = novo;
        novo->prev(novo);
        novo->next(novo);
    } else {
        Node *p = head;
        Node *q = p->prev();

        novo->next(p);
        novo->prev(q);

        q->next(novo);
        p->prev(novo);

        head = novo;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                               std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("Index fora de alcance!");
    } else if (index == 0) {
        return push_front(data);
    } else if (index == size_) {
        return push_back(data);
    } else {
        Node *p = head;

        for (int i = 1; (std::size_t)i < index; i++) {
            p = p->next();
        }

        Node *novo = new Node(data);

        novo->next(p->next());
        novo->prev(p);

        p->next()->prev(novo);
        p->next(novo);

        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head->data()) {
        return push_front(data);
    } else if (data > head->prev()->data()) {
        return push_back(data);
    } else {
        Node *p = head;
        Node *q = nullptr;

        while (p->next() != head && data > p->data()) {
            q = p;
            p = p->next();
        }

        Node *novo = new Node(data);

        novo->prev(q);
        novo->next(p);

        p->prev(novo);
        q->next(novo);

        size_++;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else if (index > size_-1 || index < 0) {
        throw std::out_of_range("fora de alcance");
    } else if (size_ == 1 || index == 0) {
        return pop_front();
    } else if (index == size_-1) {
        return pop_back();
    } else {
        Node *p = head;

        for (int i = 1; (std::size_t)i < index; i++) {
            p = p->next();
        }

        Node *aux = p->next();
        p->next(aux->next());
        aux->next()->prev(p);

        T saida = aux->data();

        delete aux;

        size_--;

        return saida;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else if (size_ == 1) {
        return pop_front();
    } else {
        Node *p = head->prev();

        T saida = p->data();
        p->prev()->next(head);
        head->prev(p->prev());

        delete p;

        size_--;

        return saida;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else if (size_ == 1) {
        T saida = head->data();

        head = nullptr;
        size_--;
        return saida;
    } else {
        Node *p = head;

        p->prev()->next(p->next());
        p->next()->prev(p->prev());

        head = p->next();

        T saida = p->data();

        delete p;

        size_--;
        return saida;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            pop(i);
            return;
        }
        p = p->next();
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty() || index > size_-1) {
        throw std::out_of_range("erro");
    }

    Node *p = head;

    for (int i = 0; (std::size_t)i < index; i++) {
        p = p->next();
    }
    return p->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (empty() || index > size_-1) {
        throw std::out_of_range("erro");
    }

    Node *p = head;

    for (int i = 0; (std::size_t)i < index; i++) {
        p = p->next();
    }
    return p->data();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p;
    p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            return (std::size_t)i;
        }
        p = p->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}