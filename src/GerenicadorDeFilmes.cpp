#include <iostream>
#include <fstream>
#include <sstream>

#include "GerenciadorDeFilmes.hpp"
#include "utils/ArquivosUteis.hpp"

bool GerenciadorDeFilmes::inserir(sqlite3* db, const Filme& filme) {
  std::string sqlString = ArquivosUteis::lerQueriesDoArquivo("sql/insert_filme.sql");
  if (sqlString.empty()) {
    return false;
  }

  const char* sql = sqlString.c_str();
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    throw Erro_ao_inserir_no_banco();
  }

  sqlite3_bind_text(stmt, 1, filme.getTitulo().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, filme.getDiretor().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, filme.getDataLancamento().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, filme.getGenero().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 5, filme.getDuracaoMinutos());

  bool sucesso = sqlite3_step(stmt) == SQLITE_DONE;
  if (!sucesso) {
    throw Erro_ao_inserir_no_banco();
  }
  sqlite3_finalize(stmt);
  return sucesso;
}

Filme GerenciadorDeFilmes::buscarPorId(sqlite3* db, int id) {
  std::string sqlString = ArquivosUteis::lerQueriesDoArquivo("sql/select_filme_by_id.sql");
  if (sqlString.empty()) return Filme();
  const char* sql = sqlString.c_str();

  sqlite3_stmt* stmt;
  Filme filme;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
      filme.setId(sqlite3_column_int(stmt, 0));
      filme.setTitulo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
      filme.setDiretor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
      filme.setDataLancamento(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
      filme.setGenero(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
      filme.setDuracaoMinutos(sqlite3_column_int(stmt, 5));
    }
    sqlite3_finalize(stmt);
  }
  else {
    throw Erro_ao_buscar_no_banco();
  }

  return filme;
}

std::vector<Filme> GerenciadorDeFilmes::listarTodos(sqlite3* db) {
  std::vector<Filme> filmes;
  std::string sqlString = ArquivosUteis::lerQueriesDoArquivo("sql/select_all_filmes.sql");
  if (sqlString.empty()) return filmes;
  const char* sql = sqlString.c_str();

  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      Filme f;
      f.setId(sqlite3_column_int(stmt, 0));
      f.setTitulo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
      f.setDiretor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
      f.setDataLancamento(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
      f.setGenero(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
      f.setDuracaoMinutos(sqlite3_column_int(stmt, 5));
      filmes.push_back(f);
    }
    sqlite3_finalize(stmt);
  }
  else {
    throw Erro_ao_listar_no_banco();
  }

  return filmes;
}

bool GerenciadorDeFilmes::atualizar(sqlite3* db, const Filme& filme) {
  std::string sqlString = ArquivosUteis::lerQueriesDoArquivo("sql/update_filme.sql");
  if (sqlString.empty()) {
    return false;
  }
  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sqlString.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    throw Erro_ao_atualizar_no_banco();
  }

  sqlite3_bind_text(stmt, 1, filme.getTitulo().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, filme.getDiretor().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, filme.getDataLancamento().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, filme.getGenero().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 5, filme.getDuracaoMinutos());
  sqlite3_bind_int(stmt, 6, filme.getId());

  bool sucesso = sqlite3_step(stmt) == SQLITE_DONE;
  int linhasAfetadas = sqlite3_changes(db);
  sqlite3_finalize(stmt);

  if (!sucesso || linhasAfetadas == 0) {
    throw Erro_ao_atualizar_no_banco();
  }

  return true;
}


bool GerenciadorDeFilmes::deletar(sqlite3* db, int id) {
  std::string sqlString = ArquivosUteis::lerQueriesDoArquivo("sql/delete_filme.sql");
  if (sqlString.empty()) {
    return false;
  }

  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, sqlString.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    throw Erro_ao_deletar_no_banco();
  }

  sqlite3_bind_int(stmt, 1, id);

  bool sucesso = sqlite3_step(stmt) == SQLITE_DONE;
  int linhasAfetadas = sqlite3_changes(db);
  if (!sucesso) {
    throw Erro_ao_deletar_no_banco();
  }
  else if (linhasAfetadas == 0) {
    sucesso = false;
  }
  sqlite3_finalize(stmt);
  return sucesso;
}