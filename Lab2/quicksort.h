#ifndef quicksort
#define quicksort

#define INSERTION_LIMIT 25
#define QTDE_FUNCOES 9
typedef void(*quicksort_type)(int*, int, int, int*);

//Função de partição do vetor, comum às implementações
int partition(int* V, int start, int end, int pivot_index);
/*Função de partição modificada, com uma partição para os números iguais e retorna os pontos de começo e fim da partição
dos números iguais*/ 
int* tripartition(int* V, int start, int end, int pivot_index);
//Função de partição percorrendo o vetor por ponteiro
int partition_pointer(int* V, int start, int end, int pivot_index);
//Seleção do k-ésimo elemento através da mediana das medianas
int selection(int *V, int start, int end, int k);
//Seleção do k-ésimo elemento através da mediana das medianas, usando a partição do vetor em 3
int selection_tripartition(int *V, int start, int end, int k, int *partition_start, int *partition_end);
//Insertion sort para vetor de tamanho pequeno
void insertionsort(int *V, int start, int end); 
//Quicksort ingênuo
void quicksort_naive(int *V, int start, int end, int *calls);
//Quicksort com otimização de iteração, com a recursão sempre de um lado
void quicksort_opt1(int *V, int start, int end, int *calls);
//Quicksort com otimização de iteração, com a recursão no menor lado
void quicksort_opt2(int *V, int start, int end, int *calls);
//Quicksort ingênuo usando a segunda função de partição
void quicksort_naive_tripartition(int *V, int start, int end, int *calls);
//Quicksort com otimização de iteração, recursão no menor lado e a segunda função de partição
void quicksort_opt2_tripartition(int *V, int start, int end, int *calls);
//Quicksort ingênuo que usa o seleção como escolha do pivô
void quicksort_naive_selection(int *V, int start, int end, int *calls);
//Quicksort ingênuo que usa o seleção modificado
void quicksort_naive_selection_tripartition(int *V, int start, int end, int *calls);
//Quicksort ingênuo que, a partir de valores menores que INSERTION_LIMIT (número definido por testes), ordena o vetor por algoritmo n^2
void quicksort_naive_insertion(int *V, int start, int end, int *calls);
//Quicksort ingênuo que percorre o vetor por ponteiro
void quicksort_naive_pointer(int *V, int start, int end, int *calls);
//Printa os valores do vetor
void print_values(int* V, int start, int end);
//Recebe um vetor e o popula com valores aleatórios
void popular_vetor(int* V, int tamanho);
//Verifica se o vetor está ordenado
bool ordenado(int *V, int tamanho);
//Recebe um ponteiro para um tipo de quicksort e um vetor, executa a função e informa o tempo e a quantidade de chamadas
void executa_quicksort(quicksort_type q, int *V, int start, int end);


#endif

