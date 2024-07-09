// Copyright [2023] <COLOQUE SEU NOME AQUI...>

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/



void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    k--;
    if (!(f -> empty())) {
        for (int i = 0; i < k; i++) {
            f -> enqueue(f -> dequeue());
        }
        f -> dequeue();
    } else {
        throw std :: out_of_range("fila vazia!");
    }
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    k--;
    if (!(f -> empty())) {
        size_t aux = f -> size();
        for (size_t i = 0 ; i < aux; i++) {
            int posicao = static_cast<int>(i);
            if (posicao != k) {
                f -> dequeue();
            } else {
                f -> enqueue(f -> dequeue());
            }
        }
    } else {
        throw std :: out_of_range("fila vazia!");
    }
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
