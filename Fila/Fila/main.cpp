#include <iostream>

using namespace std;

// Estrutura para armazenar matrícula e nota
struct Aluno
{
    int matricula;
    float nota;
    Aluno* prox;
};

// Estrutura para implementar a Fila
struct Fila
{
    Aluno* frente;
    Aluno* tras;

    // Inicializa a fila
    Fila()
    {
        frente = nullptr;
        tras = nullptr;
    }

    // Insere aluno na fila
    void enfileirar(int matricula, float nota)
    {
        Aluno* novo = new Aluno;
        novo->matricula = matricula;
        novo->nota = nota;
        novo->prox = nullptr;

        if (tras == nullptr)   // Fila vazia
        {
            frente = tras = novo;
        }
        else
        {
            tras->prox = novo;
            tras = novo;
        }
    }

    // Remove aluno da fila
    Aluno desenfileirar()
    {
        if (frente == nullptr)
        {
            cerr << "Erro: Fila vazia!" << endl;
            exit(1);
        }
        Aluno temp = *frente;
        Aluno* remover = frente;
        frente = frente->prox;
        if (frente == nullptr)
        {
            tras = nullptr; // A fila está vazia
        }
        delete remover;
        return temp;
    }

    // Verifica se a fila está vazia
    bool vazia()
    {
        return frente == nullptr;
    }
};

// Estrutura para implementar a Pilha
struct Pilha
{
    Aluno* topo;

    // Inicializa a pilha
    Pilha()
    {
        topo = nullptr;
    }

    // Empilha um aluno na pilha
    void empilhar(Aluno aluno)
    {
        Aluno* novo = new Aluno;
        novo->matricula = aluno.matricula;
        novo->nota = aluno.nota;
        novo->prox = topo;
        topo = novo;
    }

    // Desempilha o aluno do topo
    Aluno desempilhar()
    {
        if (topo == nullptr)
        {
            cerr << "Erro: Pilha vazia!" << endl;
            exit(1);
        }
        Aluno temp = *topo;
        Aluno* remover = topo;
        topo = topo->prox;
        delete remover;
        return temp;
    }

    // Verifica se a pilha está vazia
    bool vazia()
    {
        return topo == nullptr;
    }
};

// Função para empilhar ordenadamente por nota (e matrícula em caso de empate)
void empilharOrdenado(Pilha& pilha, Aluno aluno)
{
    Pilha tempPilha;

    // Coloca os elementos na pilha temporária até achar a posição correta
    while (!pilha.vazia() && (pilha.topo->nota > aluno.nota ||
                              (pilha.topo->nota == aluno.nota && pilha.topo->matricula < aluno.matricula)))
    {
        tempPilha.empilhar(pilha.desempilhar());
    }

    // Insere o novo aluno na posição correta
    pilha.empilhar(aluno);

    // Retorna os elementos da pilha temporária de volta à pilha original
    while (!tempPilha.vazia())
    {
        pilha.empilhar(tempPilha.desempilhar());
    }
}

int main()
{
    // Cabeçalho do programa
    cout << "Nome do aluno: Osvanir Jose Viana\n" << endl;
    cout << "Objetivo: Armazenar matriculas e notas de alunos e exibi-los em ordem decrescente.\n" << endl;
    cout << "Entrada: Matricula e nota de cada aluno (quantidade indefinida).\n" << endl;
    cout << "Resultado: Alunos exibidos em ordem decrescente de nota.\n" << endl;

    Fila fila;
    Pilha pilha;
    int matricula;
    float nota;
    char continuar;

    // Entrada de dados na fila
    do
    {
        cout << "Digite a matricula do aluno: ";
        cin >> matricula;
        cout << "Digite a nota do aluno: ";
        cin >> nota;

        fila.enfileirar(matricula, nota);

        cout << "Deseja adicionar mais alunos? (s/n): ";
        cin >> continuar;
    }
    while (continuar == 's' || continuar == 'S');

    // Transferência da fila para a pilha com ordenação
    while (!fila.vazia())
    {
        Aluno alunoAtual = fila.desenfileirar();
        empilharOrdenado(pilha, alunoAtual);
    }

    // Desempilhando e exibindo os resultados
    cout << "\nAlunos em ordem decrescente de nota:" << endl;
    while (!pilha.vazia())
    {
        Aluno aluno = pilha.desempilhar();
        cout << "Matricula: " << aluno.matricula << " - Nota: " << aluno.nota << endl;
    }
    system("pause");

    return 0;
}
