#pragma once

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "GerenciadorDeFilmes.hpp"
#include "GeradorRelatorioAtividade.hpp"
#include "utils/ArquivosUteis.hpp"
#include "Sqlite/sqlite3.h"

#include <iostream>

class Interface
{
private:
  GeradorRelatorioAtividade geradorRelatorio;

  sqlite3* _db;

  void cadastrarNovoFilme();
  void listarTodosOsFilmes();
  void buscarFilmePorId();
  void atualizarFilme();
  void deletarFilme();

public:
  Interface(sqlite3* db);
  ~Interface() = default;

  void ExibirMenu();
};

#endif