#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Node.h"
#include "List.h"

using namespace std;

int main() {

	vector <List*> listas;
	
	while(true) {
		string comando;
		getline(cin, comando);
		std::stringstream ss{ comando };
		vector<string> tokens;
		string buffer;

        cout << "$" << ss.str() << endl;

		while(ss >> buffer) 
			tokens.push_back(buffer);

		// create -> Cria uma lista
		if(tokens[0] == "create") {
			List *lst = new List;
			listas.push_back(lst);
		}

		// exit -> function clear
		else if(tokens[0] == "exit") {
			for(unsigned i = 0; i < listas.size(); i++)
				delete listas[i];
			listas.clear();
			break;
		}

		// show -> mostra os valores das listas criadas
		else if(tokens[0] == "show") {
            for(unsigned i = 0; i < listas.size(); ++i) {
                cout << "lista " << i << ": " << *listas[i] << endl;
            }	
		}

		// clear l -> esvazia a lista l
		else if(tokens[0] == "clear") {
			int l = std::stoi(tokens[1]);
			listas[l]->clear();
		}

		// constructor_copy l -> cria uma lista com os mesmos elementos da lista l
		// Porém, são listas distintas
		else if(tokens[0] == "constructor" && tokens[1] == "copy") {
			int l = std::stoi(tokens[2]);
			List *lst = new List(*listas[l]);
			listas.push_back(lst);
		}

		// empty l -> informa se a lista l está vazia
		else if(tokens[0] == "empty") {
			int l = std::stoi(tokens[1]);
			cout.setf(ios::boolalpha);
			cout << listas[l]->empty() << endl;
		}

		// size l -> retorna o número de elementos na lista l
		else if(tokens[0] == "size") {
			int l = std::stoi(tokens[1]);
			cout << "Size: " << listas[l]->size() << endl;
		}

		// front l -> imprime o primeiro elemento da lista l
		else if(tokens[0] == "front") {
			int l = std::stoi(tokens[1]);
			cout << "First element: " << listas[l]->front() << endl;
		}

		// back l -> retorna o último elemento da lista
		else if(tokens[0] == "back") {
			int l = std::stoi(tokens[1]);
			cout << "Last element: " << listas[l]->back() << endl;
		}

		// push back n l -> insere o elemento n no final da lista l
		else if(tokens[0] == "push" && tokens[1] == "back") {
			int n = std::stoi(tokens[2]);
			int l = std::stoi(tokens[3]);
			listas[l]->push_back(n);
		}

		// pop front l -> remove o primeiro elemento da lista l
		else if(tokens[0] == "pop" && tokens[1] == "front") {
			int l = std::stoi(tokens[2]);
			listas[l]->pop_front();
		}
		
		// pop back l -> remove o último elemento da lista l
		else if(tokens[0] == "pop" && tokens[1] == "back") {
			int l = std::stoi(tokens[2]);
			listas[l]->pop_back();
		}

		// removeAt n l -> remove o elemento de índice n da lista l
		// E retorna o valor do elemento removido
		else if(tokens[0] == "removeAt") {
			int n = std::stoi(tokens[1]);
			int l = std::stoi(tokens[2]);
			cout << listas[l]->removeAt(n) << endl;
		}

		// removeAll n l -> remove todos os elementos n da lista l
		else if(tokens[0] == "removeAll") {
			int n = std::stoi(tokens[1]);
			int l = std::stoi(tokens[2]);
			listas[l]->removeAll(n);
		}

		// swap l t -> troca o conteúdo da lista l com a lista t
		else if(tokens[0] == "swap") {
			int l = std::stoi(tokens[1]);
			int t = std::stoi(tokens[2]);
			listas[l]->swap(*listas[t]);
		}

		// copy l -> retorna uma cópia da lista l
		else if(tokens[0] == "copy") {
			int l = std::stoi(tokens[1]);
			List *lst = new List;
			lst = listas[l]->copy();
			listas.push_back(lst);
		}

		// append l a1 ... an -> insere os elementos do vetor de a1 até an na lista l
		else if(tokens[0] == "append") {
			int l = std::stoi(tokens[1]);
			int n = tokens.size() - 2;
			int *v = new int[n];
			for(int i = 0; i < n; i++)
				v[i] = std::stoi(tokens[i + 2]);
			listas[l]->append(v, n);
		}

		// equals l t -> determina se a lista l é igual a lista t
		else if(tokens[0] == "equals") {
			int l = std::stoi(tokens[1]);
			int t = std::stoi(tokens[2]);
			cout << "Lista " << l << " equal " << t << " : " << listas[l]->equals(*listas[t]) << endl;
		}

		// merge l t -> intercala a lsita l na lista t
		else if(tokens[0] == "merge") {
			int l = std::stoi(tokens[1]);
			int t = std::stoi(tokens[2]);
			listas[l]->merge(*listas[t]);
		}

		// show[] n l -> imprime o elemento de índice n da lista l
		else if(tokens[0] == "show[]") {
			int n = std::stoi(tokens[1]);
			int l = std::stoi(tokens[2]);
			cout << listas[l]->operator[](n) << endl;
		}

		// equal l t -> lista l recebe lista t
		else if(tokens[0] == "equal") {
			int l = std::stoi(tokens[1]);
			int t = std::stoi(tokens[2]);
			*listas[l] = *listas[t];
		}

		else {
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}
