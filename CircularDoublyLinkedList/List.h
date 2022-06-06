#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdexcept>
#include "Node.h"

class List {
private:
    Node *head; // Ponteiro para o nó sentinela
    int m_size; // Números de elementos na lista

public:

    // Construtor
    List() {
        Node *newnode = new Node (nullptr, nullptr); // nó sentinela
        head = newnode;
        m_size = 0;
    }

    // Esvazia a lista
    void clear() {
        Node *current_last = head->previous; // ponteiro que percorrerá a lista de seu último elemento até o primeiro elemento
        while(m_size != 0){
            Node *temp = current_last;
            current_last = current_last->previous;
            delete temp;
            m_size--;
        }
    }

    // Construtor de cópia
    List(const List& lista) {
        Node *newnode_sentinel = new Node (nullptr, nullptr); // nó sentinela da lista criada
        head = newnode_sentinel;
        m_size = 0;
        Node *current_right = lista.head;// ponteiro que percorrerá os nós da lista passada por parâmetro
        Node *current_left = head; // ponteiro que percorrerá os nós da lista a ser criada
        
        // Caso em que a lista passada por parâmetro contém apenas um elemento
        if(lista.m_size == 1){
            Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
            head->next = newnode;
            head->previous = newnode;
            newnode->next = head;
            newnode->previous = head;
            m_size++;

        // Demais casos
        }else{
            for(int i = 0; i < lista.m_size; i++){
                Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
                current_left->next = newnode;
                current_left->previous = newnode;
                newnode->next = current_left;
                newnode->previous = current_left;
                m_size++;
                current_right = current_right->next;
                current_left = current_left->next;
            }
        }
    }

    // Retorna se a lista está vazia
    bool empty() const {
        return m_size == 0;
    }

    // Retorna o número de nós da lista
    size_t size() const {
        return m_size;
    }

    // Retorna uma referência para o primeiro elemento da lista
    // Retorna uma exceção se a lista estiver vazia
    Item& front() {
        if(m_size == 0){
            throw std::runtime_error("fail: lista vazia");

        }else{
            return head->next->data;
        }
    }

    // Retorna uma referência para o último elemento da lista
    // Retorna uma exceção se a lista estiver vazia
    Item& back() {
        if(m_size == 0){
            throw std::runtime_error("fail: lista vazia");

        }else{
            return head->previous->data;
        }
    }

    // Adiciona um Item ao final da lista
    void push_back(const Item& data) {
        Node *current = head; // ponteiro que percorrerá a lista até chegar no último nó da lista
        Node *newnode = new Node (data, nullptr, nullptr);
        if(m_size == 0){
            current->next = newnode;
            current->previous = newnode;
            newnode->next = current;
            newnode->previous = current;
            m_size++;

        }else{
            for(int i = 0; i < m_size - 1; i++){
                current = current->next;
            }
            current->next->next = newnode;
            head->previous = newnode;
            newnode->previous = current->next;
            newnode->next = head;
            m_size++;
        }
    }

    // Remove o elemento no início da lista
    // Retorna uma exceção se a lista estiver vazia
    void pop_front() {
        if(m_size == 0){
            throw std::runtime_error("fail: lista vazia");
        }else{
            Node *remove = head->next;
            head->next = remove->next;
            Node *prox = remove->next;
            prox->previous = head;
            delete remove;
            m_size--;
        }
    }

    // Remove o elemento no final da lista
    // Retorna uma exceção se a lista estiver vazia
    void pop_back() {
        if(m_size == 0){
            throw std::runtime_error("fail: lista vazia");

        }else{
            Node *remove = head->previous;
            head->previous = remove->previous;
            remove->previous->next = head;
            delete remove;
            m_size--;
        }
    }

    // Remove o elemento na posição index e retorna o seu valor
    // Sendo uma lista com n elementos, esta função só deve remover
    // O elemento se e somente se 0 <= index <= n - 1
    // Caso contrário, uma exceção será lançada
    // Função com complexidade O(n) no pior caso
    Item removeAt(int index) {
        if(m_size == 0){
            throw std::runtime_error("fail: lista vazia");

        }else if(index < 0 || index >= m_size){
            throw std::runtime_error("fail: índice informado não existe na lista");

        }else{
            // Caso a lista tenha apenas um elemento
            if(m_size == 1){
                Node *temp = head->next; // aponta para o nó a ser removido
                Item aux = head->next->data; // guarda o valor Item do nó a ser removido para ser retornado na função
                head->next = head;
                head->previous = head;
                delete temp;
                m_size--;
                return aux;

            // Demais casos
            }else{
                // Caso o elemento a ser removido esteja no final da lista
                if(index == m_size - 1){
                    Node *temp = head->previous; // aponta para o nó a ser removido
                    Item aux = head->previous->data; // guarda o valor Item do nó a ser removido para ser retornado na função
                    head->previous->previous->next = head;
                    head->previous = head->previous->previous;
                    delete temp;
                    m_size--;
                    return aux;

                }else{
                    Node *current = head; // ponteiro que percorrerá a lista
                    for(int i = 0; i < index; i++){
                        current = current->next;
                    }
                    Node *temp = current->next; // aponta para o nó a ser removido
                    Item aux = current->next->data; // guarda o valor Item do nó a ser removido para ser retornado na função
                    current->next->next->previous = current;
                    current->next = current->next->next;
                    delete temp;
                    m_size--;
                    return aux;
                }
            }
        }
    }

    // Remove da lista todas as ocorrências do elemento data passado como parâmetro
    // Função com complexidade O(n) no pior caso
    void removeAll(const Item& data) {
        Node *aux = head->next; // ponteiro para percorrer a lista
        Node *remove; // ponteiro para deletar o nó que tenha data igual ao valor passado como parâmetro
        Node *prox; // ponteiro para o nó seguinte ao nó que será deletado
        Node *ant; // ponteiro para o nó anterior ao nó que será deletado
        int cont = 0;
        while(aux != head){
            if(aux->data == data){
                remove = aux;
                aux = aux->next;
                prox = remove->next;
                ant = remove->previous;
                ant->next = prox;
                prox->previous = ant;
                delete remove;
                m_size--;
            }else{
                aux = aux->next;
            }
            cont++;
        }
    }

    // Troca o conteúdo da lista com o conteúdo da lista lst
    void swap(List& lst) {
        List *list_temporary = new List();
        *list_temporary = *this;
        *this = lst;
        lst = *list_temporary;
        delete list_temporary;
    }

    // Concatena a lista atual com a lista lst passada por parâmetro
    // Após essa operação ser executada, lst será uma lista vazia
    // Esta função deve ter complexidade O(n) no pior caso
    void concat(List& lst) {
        Node *aux = head; // ponteiro para percorrer a lista
        m_size += lst.m_size;
        while(aux->next != head){
            aux = aux->next;
        }
        Node *prim = lst.head->next; // aponta para o primeiro elemento da lista lst
        aux->next = prim;
        Node *ult = lst.head->previous; // aponta para o último elemento da lista lst
        ult->next = head;
        head->previous = ult;
        prim->previous = aux;
        lst.head = new Node(1);
        lst.m_size = 0;
    }

    // Retorna um ponteiro para uma cópia desta lista
    // A cópia desta lista deve ser uma outra lista, criada dinamicamente dentro da função
    // Esta função deve ter complexidade O(n) no pior caso
    List *copy() {
        List *copy_list = new List(*this);
        return copy_list;
    }

    // Esta função recebe um array de Item e o seu tamanho n como entrada e copia os
    // Elementos do array para a lista. Todos os elementos anteriores da lista são mantidos e
    // Os elementos do array devem ser adicionados após os elementos originais
    // Esta função deve ter complexidade O(n) no pior caso
    void append(Item vec[], int n) {
        Node *aux; // ponteiro para percorrer a lista
        if(m_size != 0){
            aux = head->next;
            while(aux->next != head){
                aux = aux->next;
            }
            aux->next = new Node(vec[0], aux, head);
            aux = aux->next;
        }else{
            head->next = new Node(vec[0], head, head);
            aux = head->next;
            head->previous = aux;
        }
        m_size++;
        Node *novo = aux; // ponteiro que percorre os nós que serão criados a partir do vetor
        for(int i=1; i<n; i++){
            novo->next = new Node(vec[i], novo, nullptr);
            novo = novo->next;
            if(i == n-1){
                novo->next = head;
                head->previous = novo;
            }
            m_size++;
        }
    }

    // Determina se a lista lst passada por parâmetro é igual à lista em questão
    // Esta função deve ter complexidade O(n) no pior caso
    bool equals(const List& lst) const {
        if(m_size == lst.m_size){
            Node *current_left = head; // ponteiro que percorrerá a lista
            Node *current_right = lst.head; // ponteiro que percorrerá a lista passada como parâmetro
            int aux = 0;
            for(int i = 0; i < m_size; i++){
                if(current_left->next->data == current_right->next->data){
                    aux++;
                }
                current_left = current_left->next;
                current_right = current_right->next;
            }
            if(aux == m_size){
                return true;

            }else{
                return false;
            }

        }else{
            return false;
        }
    }

    // Recebe uma lista lst como parâmetro e constrói uma nova lista que será a intercalação
    // Dos elementos da lista original com os elementos da lista passada por Parâmetro
    // Ao final desta operação, lst deve ficar vazia
    // Como um exemplo, imagine duas listas de inteiros L1 = [ 1 2 3 4 ] e L2 = [ 7 8 9 0 5 6 ]
    // Então, o resultado da operação L1.merge(L2) nos dá as listas
    // L1 = [ 1 7 2 8 3 9 4 0 5 6 ] e L2 = []
    void merge(List& lst) {
        Node *current_left = head; // ponteiro que percorrerá a lista
        Node *current_right = lst.head; // ponteiro que percorrerá a lista passada como parâmetro
        int aux_size1 = m_size; // auxiliar que armazena o tamanho da lista

        // Caso a lista passada como parâmetro seja maior ou igual à lista objeto
        if(lst.m_size >= m_size){
            // Percorre toda a lista objeto inserindo de forma intercalada os nós da lista passada como parâmetro
            // Os novos nós são criados dinamicamente
            for(int i = 1; i < aux_size1; i++){
                Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
                newnode->next = current_left->next->next;
                current_left->next->next->previous = newnode;
                current_left->next->next = newnode;
                newnode->previous = current_left->next;
                m_size++;
                current_left = current_left->next->next;
                current_right = current_right->next;
            }

            // Conecta o último nó da lista com o próximo nó da lista passada como parâmetro
            Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
            current_left->next->next = newnode;
            newnode->previous = head->previous;
            head->previous = newnode;
            newnode->next = head;
            m_size++;
            current_right = current_right->next;
            current_left = current_left->next->next;

            // Verifica se ainda existem nós na lista passada como parâmetro
            // Se true, então é inserido os nós restantes na lista objeto
            if(m_size < aux_size1 + lst.m_size){
                for(int i = m_size; i < aux_size1 + lst.m_size; i++){
                    Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
                    current_left->next = newnode;
                    newnode->previous = current_left;
                    head->previous = newnode;
                    newnode->previous = head;
                    current_left = current_left->next;
                    current_right = current_right->next;
                    m_size++;
                }
            }
            lst.clear();

        // Caso a lista passada como parâmetro seja menor que a lista objeto
        }else{
            for(int i = 0; i < lst.m_size; i++){
                Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
                newnode->next = current_left->next->next;
                current_left->next->next->previous = newnode;
                current_left->next->next = newnode;
                newnode->previous = current_left->next;
                m_size++;
                current_left = current_left->next->next;
                current_right = current_right->next;
            }
            lst.clear();
        }
    }

    // Operador de extração (<<)
    // Sobrecarregado de forma global como friend function
    friend std::ostream& operator<<(std::ostream& out, const List& lst) {
        Node *current = lst.head->next; // ponteiro que percorrerá a lista
        out << "[ ";
        for(int i = 0; i < lst.m_size; i++){
            out << current->data << " ";
            current = current->next;
        }
        out << "]";
        return out;
    }

    // Esta função sobrecarrega o operador de indexação []
    // Ela retorna uma referência para o elemento no índice index
    // Se esse índice não for válido
    // Uma exceção será lançada por esta função
    Item& operator[](int index) {
        if(index < 0 || index >= m_size){
            throw std::runtime_error("fail: índice informado não existe na lista");
        }else{
            Node *current = head; // ponteiro que percorrerá a lista
            for(int i = 0; i < index; i++){
                current = current->next;
            }
            return current->next->data;
        }
    }

    //Esta função sobrecarrega o operador de atribuição
    // Esta função adiciona à lista, os mesmos elementos que estão na lista lst
    // Ao fazer isso, ela apaga todos os elementos da lista original para que ela possa
    // Receber os novos elementos. Por exemplo, considere duas listas
    // P = [ 2 3 4 ] e Q = [ 6 7 8 9 ]. Após a operação: P = Q temos que as listas serão
    // P = [ 6 7 8 9 ] e Q = [ 6 7 8 9 ], onde P e Q são duas listas distintas
    List& operator=(const List& lst) {
        this->clear();
        Node *current_right = lst.head; // ponteiro que percorrerá a lista passada como parâmetro
        Node *current_left = this->head; // ponteiro que percorrerá a lista
        if(lst.m_size == 1){
            Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
            this->head->next = newnode;
            this->head->previous = newnode;
            newnode->next = this->head;
            newnode->previous = this->head;
            this->m_size++;

        }else{
            for(int i = 0; i < lst.m_size; i++){
                Node *newnode = new Node(current_right->next->data, nullptr, nullptr);
                current_left->next = newnode;
                current_left->previous = newnode;
                newnode->next = current_left;
                newnode->previous = current_left;
                this->m_size++;
                current_right = current_right->next;
                current_left = current_left->next;
            }
        }

        return *this;
    }

    // Destrutor
    ~List() {
        clear();
    }
};

#endif
