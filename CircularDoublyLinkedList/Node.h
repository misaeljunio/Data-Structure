#ifndef NODE_H
#define NODE_H

typedef int Item;

struct Node {
    Item data;      // Armazena o dado
    Node *previous; // Ponteiro para o Node anterior
    Node *next;     // Ponteiro para o Node posterior

    // Construtor node para os demais nós da lista exceto o sentinela
    Node (const Item& d, Node *p = nullptr, Node *n = nullptr){
        data = d;
        previous = p;
        next = n;
    }

    // Constutor node para o nó sentinela
    Node (Node *p = nullptr, Node *n = nullptr){
        previous = p;
        next = n;
    }
};

#endif