#include "doctest.h"
#include "GerenciadorDeFilmes.hpp"
#include "Filme.hpp"
#include "Sqlite/sqlite3.h"
#include "utils/ArquivosUteis.hpp"

#include <stdexcept>
#include <vector>

const char* DB_FILENAME = "testes_filme.bd";

sqlite3* abrirBancoDeTeste() {
  sqlite3* db;
  int rc = sqlite3_open(DB_FILENAME, &db);
  if (rc != SQLITE_OK) {
    throw std::runtime_error("Erro ao abrir banco de dados");
  }

  const char* sqlCreate = R"(
    CREATE TABLE IF NOT EXISTS filmes (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      titulo TEXT NOT NULL,
      diretor TEXT NOT NULL,
      data_lancamento DATE,
      genero TEXT NOT NULL,
      duracao_minutos INTEGER
    );
  )";

  char* errMsg = nullptr;
  rc = sqlite3_exec(db, sqlCreate, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::string err = errMsg ? errMsg : "Erro desconhecido ao criar tabela";
    sqlite3_free(errMsg);
    sqlite3_close(db);
    throw std::runtime_error(err);
  }

  return db;
}

void apagarBancoDeTeste() {
  std::remove(DB_FILENAME);
}


TEST_CASE("1 - Teste sucesso Abrir Banco SQLite em Arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  CHECK(db != nullptr);

  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("2 - Teste sucesso de Inserção de Filme em arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme("Matrix", "Wachowski", "31-03-1999", "Ficção", 136);

  CHECK(gerenciador.inserir(db, filme) == true);

  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("3 - Teste sucesso de Busca de Filme por ID em arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme("Inception", "Nolan", "16-07-2010", "Ação", 148);
  gerenciador.inserir(db, filme);

  Filme resultado = gerenciador.buscarPorId(db, 1);
  CHECK(resultado.getId() == 1);
  CHECK(resultado.getTitulo() == "Inception");
  CHECK(resultado.getDiretor() == "Nolan");
  CHECK(resultado.getDataLancamento() == "16-07-2010");
  CHECK(resultado.getGenero() == "Ação");
  CHECK(resultado.getDuracaoMinutos() == 148);


  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("4 - Teste sucesso de Listagem de Todos os Filmes em arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme1("Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  Filme filme2("Inception", "Nolan", "16-07-2010", "Ação", 148);
  gerenciador.inserir(db, filme1);
  gerenciador.inserir(db, filme2);
  std::vector<Filme> filmes = gerenciador.listarTodos(db);
  CHECK(filmes.size() == 2);
  CHECK(filmes[0].getTitulo() == "Matrix");
  CHECK(filmes[1].getTitulo() == "Inception");
  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("5 - Teste sucesso de Atualização de Filme em arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  gerenciador.inserir(db, filme);

  filme.setTitulo("Matrix Reloaded");
  filme.setDuracaoMinutos(138);
  CHECK(gerenciador.atualizar(db, filme) == true);
  Filme atualizado = gerenciador.buscarPorId(db, 1);
  CHECK(atualizado.getTitulo() == "Matrix Reloaded");
  CHECK(atualizado.getDuracaoMinutos() == 138);

  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("6 - Teste sucesso de Deleção de Filme em arquivo") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme1(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  Filme filme2(2, "Inception", "Nolan", "16-07-2010", "Ação", 148);
  gerenciador.inserir(db, filme1);
  gerenciador.inserir(db, filme2);

  CHECK(gerenciador.deletar(db, 1) == true);
  std::vector<Filme> filmes = gerenciador.listarTodos(db);
  CHECK(filmes.size() == 1);
  CHECK(filmes[0].getTitulo() == "Inception");

  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("7 - Teste atualização de Filme com ID inexistente") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  gerenciador.inserir(db, filme);
  filme.setId(999);
  CHECK_THROWS_AS(gerenciador.atualizar(db, filme), Erro_ao_atualizar_no_banco);

  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("8 - Teste deleção de Filme com ID inexistente") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  gerenciador.inserir(db, filme);

  CHECK(gerenciador.deletar(db, 999) == false);
  sqlite3_close(db);
  apagarBancoDeTeste();
}

TEST_CASE("10 - Teste atualização com todos os campos vazios") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  gerenciador.inserir(db, filme);

  filme.setTitulo("");
  filme.setDiretor("");
  filme.setDataLancamento("");
  filme.setGenero("");
  filme.setDuracaoMinutos(0);

  CHECK(gerenciador.atualizar(db, filme) == true);
  Filme atualizado = gerenciador.buscarPorId(db, 1);
  CHECK(atualizado.getTitulo() == "");
  CHECK(atualizado.getDiretor() == "");
  CHECK(atualizado.getDataLancamento() == "");
  CHECK(atualizado.getGenero() == "");
  CHECK(atualizado.getDuracaoMinutos() == 0);
}

TEST_CASE("11 - Teste atualização de todos os campos") {
  sqlite3* db = abrirBancoDeTeste();
  GerenciadorDeFilmes gerenciador;
  Filme filme(1, "Matrix", "Wachowski", "31-03-1999", "Ficção", 136);
  gerenciador.inserir(db, filme);

  filme.setTitulo("Matrix Reloaded");
  filme.setDiretor("Wachowski Brothers");
  filme.setDataLancamento("10-05-2003");
  filme.setGenero("Acao");
  filme.setDuracaoMinutos(135);

  CHECK(gerenciador.atualizar(db, filme) == true);
  Filme atualizado = gerenciador.buscarPorId(db, 1);
  CHECK(atualizado.getTitulo() == "Matrix Reloaded");
  CHECK(atualizado.getDiretor() == "Wachowski Brothers");
  CHECK(atualizado.getDataLancamento() == "10-05-2003");
  CHECK(atualizado.getGenero() == "Acao");
  CHECK(atualizado.getDuracaoMinutos() == 135);
}

