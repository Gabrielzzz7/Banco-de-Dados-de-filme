#pragma once

#ifndef GERENCIADOR_DE_FILMES_HPP
#define GERENCIADOR_DE_FILMES_HPP

#include "Filme.hpp"
#include "Sqlite/sqlite3.h"

#include <string>
#include <vector>

class Erro_ao_inserir_no_banco {};
class Erro_ao_buscar_no_banco {};
class Erro_ao_listar_no_banco {};
class Erro_ao_atualizar_no_banco {};
class Erro_ao_deletar_no_banco {};

class GerenciadorDeFilmes {
public:
  static bool inserir(sqlite3* db, const Filme& filme);
  static Filme buscarPorId(sqlite3* db, int id);
  static std::vector<Filme> listarTodos(sqlite3* db);
  static bool atualizar(sqlite3* db, const Filme& filme);
  static bool deletar(sqlite3* db, int id);
};

#endif