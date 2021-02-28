//Configura��o Inicial
#pragma once					//Impedir Duplo Carregamento
#include <iostream>				//Lib Linguagem C++   
#include <cstdlib>              //Lib Linguagem C++ 
#include <stdlib.h>             //Lib Linguagem C++ 
#include <stdio.h>              //Lib Linguagem C++ 
#include <string>               //Lib String 
#include <windows.h>            //Lib Acentua��o
#include <locale.h>				//Lib Acentua��o
using namespace std;            //Omitir Classe Std 

//Importar - Arquivos
#include "config.h"             //Configura��o
#include "custumer.h"			//Classe Cliente
#include "databaseModel.h"		//Classe BD

//Vari�veis Globais             //Neste Arquivo
int id, idade = 0;
string nome, email = "";

//Vari�veis e Fun��es
namespace arquivoHelper {
	
	string saudacao() {
		//Arquivos Suporte
		arquivoConfig::configuracao();

		//Mensagem
		return "Hello World! \n\n";
	}

    Custumer catchForm() {

        cout << "Nome: \n";
        getline(cin, nome);

        cout << "Email: \n";
        getline(cin, email);

        string idadeS = to_string(idade);
        cout << "Idade: \n";
        getline(cin, idadeS);

        if (nome=="" || email=="" || idadeS==""){
            Custumer custumer = Custumer();
            custumer.mensagem = "H� Campos em Branco!";
            custumer.isValid = false;
            return custumer;
        } else {
            int idade = stoi(idadeS);
            Custumer custumer = Custumer(nome, email, idade);
            custumer.isValid = true;
            return custumer;
        }

    };

}


