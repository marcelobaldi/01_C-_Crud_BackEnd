//Configuração Inicial
#pragma once					//Impedir 2x Carregar
#include <iostream>				//Lib Linguacem C++
#include <mysql.h>				//Lib MySQL
#include "custumer.h"			//Arquivo Classe
using namespace std;			//Omitir Classe Std

///////////////////////////////////////////////////////////////

class DatabaseModel {
	
	//Variáveis e Constantes - Banco Dados
	public:
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	int qstate = 0;

	//Variáveis e Constantes - Diversos
	int id, idade = 0;
	string nome, email = "";

///////////////////////////////////////////////////////////////

	//Construtores e Destrutor
	public:
	DatabaseModel() {
		this->conexao();
	}

	~DatabaseModel() {
		//Objeto Apagado;
	}

///////////////////////////////////////////////////////////////

	//Método - Conexão
	void conexao() {
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "", "teste", 3306, NULL, 0);
	}

///////////////////////////////////////////////////////////////

	//Métodos - Auxiliares
	Custumer findById(string id) {

		string queryfindById;
		queryfindById = "SELECT * FROM clientes WHERE id = '" + id + "'";
		mysql_query(conn, queryfindById.c_str());

		res = mysql_store_result(conn);
		if (mysql_fetch_row(res)) {

			queryfindById = "SELECT * FROM clientes WHERE id = '" + id + "'";
			mysql_query(conn, queryfindById.c_str());

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				int id = stoi(row[0]);	//forçar cast	
				nome = row[1];
				email = row[2];
				idade = stoi(row[3]);

				Custumer custumer = Custumer(id, nome, email, idade);
				custumer.isExist = true;
				return custumer;
			}

		}
		else {
			Custumer custumer = Custumer();
			custumer.mensagem = "Id Não Encontrado!";
			custumer.isExist = false;
			return custumer;
		}
	}


	Custumer findByEmail(string email) {
		
		string queryfindByEmail;
		queryfindByEmail = "SELECT * FROM clientes WHERE email = '" + email + "'";
		mysql_query(conn, queryfindByEmail.c_str());

		res = mysql_store_result(conn);
		if (mysql_fetch_row(res)) {
		
			queryfindByEmail = "SELECT * FROM clientes WHERE email = '" + email + "'";
			mysql_query(conn, queryfindByEmail.c_str());

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				id = stoi(row[0]);		
				nome = row[1];
				email = row[2];
				idade = stoi(row[3]);	

				Custumer custumer = Custumer(id, nome, email, idade);
				custumer.isExist = true;
				return custumer; 
			}

		} else {
			Custumer custumer = Custumer();
			custumer.mensagem = "Email Não Encontrado!";
			custumer.isExist = false;
			return custumer;
		}
	}

///////////////////////////////////////////////////////////////

	//Métodos - Principais (CRUD)
	void create(Custumer custumer) {
		
		string nome = custumer.nome;
		string email = custumer.email;

		int idade = custumer.idade;
		string idadeS = to_string(idade);

		Custumer custumerEmail = findByEmail(email);
		if (custumerEmail.isExist) {
			cout << "\n" << "Este Email Ja Existe! \n\n";
			return;
		}

		string queryCreate;
		queryCreate = "INSERT INTO clientes (nome, email, idade) VALUES('"+nome+"','"+email+"', '"+idadeS+"')";
		mysql_query(conn, queryCreate.c_str());
		cout << "\n" << "Cadastrado Com Sucesso! \n\n";
	}


	void findByAll() {

		//Buscar Todos (Indexando Decrescente Por ID e Trazer 10 Registros)
		string comandoSQL = "SELECT * FROM clientes ORDER BY iD DESC LIMIT 10";
		qstate = mysql_query(conn, comandoSQL.c_str());

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			cout << "ID: " << row[0] << " - ";
			cout << "Nome: " << row[1] << " - ";
			cout << "Email: " << row[2] << " - ";
			cout << "Idade: " << row[3] << "\n";
		}

		//Quantidade Total de Registros
		string quantidadeSQL = "SELECT COUNT(*) FROM clientes";
		qstate = mysql_query(conn, quantidadeSQL.c_str());

		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		cout << "Qt Registros: " << row[0] << "\n";

		//Último ID Registrado (Não Consegui com o Last Insert Id)
		string ultimoID = "SELECT * FROM clientes ORDER BY iD DESC LIMIT 1";
		qstate = mysql_query(conn, ultimoID.c_str());

		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		cout << "Ultimo Id: " << row[0] << "\n";
	}


	void findByName(string nome) {

		string queryfindByName;
		queryfindByName = "Select * from clientes where nome LIKE '%" + nome + "%'";
		mysql_query(conn, queryfindByName.c_str());

		res = mysql_store_result(conn);
		if (mysql_fetch_row(res)) {
			cout << "\n" << "Nome(s) Encontrado(s): \n\n";

			string queryfindByName;
			queryfindByName = "Select * from clientes where nome LIKE '%" + nome + "%'";
			mysql_query(conn, queryfindByName.c_str());

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				cout << "Id: " << row[0] << " - ";
				cout << "Nome: " << row[1] << " - ";
				cout << "Email: " << row[2] << " - ";
				cout << "Idade: " << row[3] << "\n";
			}
		}
		else {
			cout << "\n" << "Nome Nao Encontrado! \n\n";
		}
		
	}


	void update(Custumer custumer) {
		
		int id = custumer.id;
		string idS = to_string(id);

		string nome = custumer.nome;
		string email = custumer.email;

		int idade = custumer.idade;
		string idadeS = to_string(idade);
		
		string queryUpdate;
		queryUpdate = "UPDATE clientes SET nome='"+nome+"', email='"+email+"', idade='"+idadeS+"' WHERE id='"+idS+"'";
		mysql_query(conn, queryUpdate.c_str());
		cout << "\n" << "Atualizado Com Sucesso! \n\n";
	}


	void remove(string id) {
		
		string queryRemove;
		queryRemove = "Select * from clientes where id = '" + id + "'";
		mysql_query(conn, queryRemove.c_str());

		res = mysql_store_result(conn);
		if (mysql_fetch_row(res)) {
			string queryDeletar;
			queryDeletar = "DELETE from clientes WHERE id='" + id + "'";
			mysql_query(conn, queryDeletar.c_str());
			cout << "\n" << "Deletado Com Sucesso! \n\n";
		} else {
			cout << "\n" << "Id Nao Encontrado! \n\n"; 
		}
	}
	
};

