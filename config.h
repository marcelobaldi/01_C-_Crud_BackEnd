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


//Configura��es Diversas
namespace arquivoConfig {
	
	void configuracao() {
		setlocale(LC_ALL, "Portuguese");

		UINT CPAGE_UTF8 = 65001;
		UINT CPAGE_DEFAULT = GetConsoleOutputCP();
		SetConsoleOutputCP(CPAGE_UTF8);
	}

}





