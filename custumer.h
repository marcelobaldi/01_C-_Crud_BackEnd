//Configuração Inicial
#pragma once					//Impedir 2x Carregar
#include <iostream>				//Lib Linguagem C++   
using namespace std;			//Omitir Classe Std

///////////////////////////////////////////////////////////////

class Custumer {
    
    //Variáveis e Constantes
    public:                     
    int id, idade = 0;
    string nome, email, mensagem = "";
    bool isExist, isValid = false;
    const string EMPRESA = "XYZ";

///////////////////////////////////////////////////////////////

    //Construtores e Destrutor
    public:
    Custumer() {
    }

    Custumer(string nome, string email, int idade) {
        this->nome = nome;
        this->email = email;
        this->idade = idade;
    }

    Custumer(int id, string nome, string email, int idade) {
        this->id = id;
        this->nome = nome;
        this->email = email;
        this->idade = idade;
    }

    ~Custumer() {
        //cout << "Objeto Apagado \n";
    }

///////////////////////////////////////////////////////////////

    //Métodos Diversos
    string exibirUsuario() {
        return this->email + " - " + this->EMPRESA;
    }

};



