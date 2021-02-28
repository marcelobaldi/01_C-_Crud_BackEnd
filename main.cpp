//Importar - Libs
#include <iostream>				   //Linguagem C++   
#include <cstdlib>                 //Linguagem C++ 
#include <stdlib.h>                //Linguagem C++ 
#include <stdio.h>                 //Linguagem C++ 
#include <string>                  //String 
#include <cstring>			       //String
#include <cctype>                  //String
#include <algorithm>               //String 
#include <functional>              //Funções
#include <vector>                  //Array Vector
#include <windows.h>               //Acentuação
#include <locale.h>                //Acentuação

//Importar - Arquivos
#include "config.h"                //Configuração
#include "helper.h"				   //Helper
#include "custumer.h"			   //Classe Cliente
#include "databaseModel.h"		   //Classe BD

//NameSpaces - Classes
using namespace std;			   //Omitir Classe Interna Std

//Classes Instanciadas
DatabaseModel* databaseModel = new DatabaseModel();

///////////////////////////////////////////////////////////////

//Métodos - Secundários
void create() {
   
    Custumer custumer = arquivoHelper::catchForm();
   
    if (custumer.isValid == false) {
        cout << "\n" << custumer.mensagem << "\n\n";
        return;
    } else {
        databaseModel->create(custumer);
    }

}


void findByEmail() {
    cout << "Email: \n";
    getline(cin, email);

    if (email == "") {
        cout << "\n" << "Há Campos em Branco! \n\n";
        return;
    }

    Custumer custumer = databaseModel->findByEmail(email);
    if (custumer.isExist == false) {
        cout << "\n" << custumer.mensagem << "\n\n";
        return;
    } else {
        cout << "ID: " << custumer.id << " - ";
        cout << "Nome: " << custumer.nome << " - ";
        cout << "Email: " << custumer.email << " - ";
        cout << "Idade: " << custumer.idade << "\n";
    }
}


void findById() {
    cout << "Id: \n";
    string idS = "";
    getline(cin, idS);

    if (idS == "") {
        cout << "\n" << "Há Campos em Branco! \n\n";
        return;
    }

    Custumer custumer = databaseModel->findById(idS);
    if (custumer.isExist == false) {
        cout << "\n" << custumer.mensagem << "\n\n";
        return;
    }
    else {
        cout << "ID: " << custumer.id << " - ";
        cout << "Nome: " << custumer.nome << " - ";
        cout << "Email: " << custumer.email << " - ";
        cout << "Idade: " << custumer.idade << "\n";
    }
}


void findByName() {
    cout << "Nome: \n";
    getline(cin, nome);

    if (nome == "") {
        cout << "\n" << "Há Campos em Branco! \n\n";
        return;
    }

    databaseModel->findByName(nome);
}

void findByAll() {
    databaseModel->findByAll();
}


void update() {

    //Pegar ID
    cout << "Id: \n";
    string idS = "";
    getline(cin, idS);

    //Tratamento ID - Campo Branco
    if (idS == "") {
        cout << "\n" << "Há Campos em Branco! \n\n";
        return;
    }

    //Se Existir o ID, Então Pegar o Email
    string emailCadastrado = "";
    Custumer custumerID = databaseModel->findById(idS);
    if (custumerID.isExist == false) {
        cout << "\n" << custumerID.mensagem << "\n\n";
        return;
    } else {
        emailCadastrado = custumerID.email;
    }

    //Tratamento Campos Branco
    Custumer custumerDados = arquivoHelper::catchForm();
    if (custumerDados.isValid == false) {
        cout << "\n" << custumerDados.mensagem << "\n\n";
        return;
    }

    //Tratamento Email Existente
    if (custumerDados.email != emailCadastrado) {
        Custumer custumerEmail = databaseModel->findByEmail(custumerDados.email);
        if (custumerEmail.isExist) {
            cout << "\n" << "Este Email Já Existe!" << "\n\n";
            return;
        }
    }

    //Atualizar
    int id = stoi(idS);
    Custumer custumerUp = Custumer(id, custumerDados.nome, custumerDados.email, custumerDados.idade);
    databaseModel->update(custumerUp);
   
}


void remove() {
    //Pegar Dados
    cout << "Id: \n";
    string idS = "";
    getline(cin, idS);

    //Tratamento Campos Branco
    if (idS == "") {
        cout << "\n" << "Há Campos em Branco! \n\n";
        return;
    }

    //Chamar Método Cadastrar
    databaseModel->remove(idS);
}


///////////////////////////////////////////////////////////////

//Método - Principal
int main(){    
    
    //Arquivos Suporte
    arquivoConfig::configuracao();
    cout << arquivoHelper::saudacao();

    //Menu - View
    string opcao;
    cout << "1 - Cadastrar \n";
    cout << "2 - Buscar Todos \n";
    cout << "3 - Buscar Por Id \n";
    cout << "4 - Buscar Por Email \n";
    cout << "5 - Buscar Por Nome \n";
    cout << "6 - Atualizar \n";
    cout << "7 - Deletar \n\n";
    getline(cin, opcao);

    //Menu - Ação
    if (opcao == "1") { create();      }
    if (opcao == "2") { findByAll();   }
    if (opcao == "3") { findById();    }
    if (opcao == "4") { findByEmail(); }
    if (opcao == "5") { findByName();  }
    if (opcao == "6") { update();      }
    if (opcao == "7") { remove();      }
}



