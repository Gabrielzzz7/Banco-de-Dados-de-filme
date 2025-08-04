#pragma once

#ifndef FILME_HPP
#define FILME_HPP

#include <string>
#include <sstream>

class Filme {
private:
  int _id;
  std::string _titulo;
  std::string _diretor;
  std::string _dataLancamento;
  std::string _genero;
  int _duracaoMinutos;

public:
  Filme();
  Filme(const std::string& titulo, const std::string& diretor, const std::string& dataLancamento,
        const std::string& genero, int duracaoMinutos);
  Filme(int id, const std::string& titulo, const std::string& diretor,
        const std::string& dataLancamento, const std::string& genero, int duracaoMinutos);

  int getId() const;
  std::string getTitulo() const;
  std::string getDiretor() const;
  std::string getDataLancamento() const;
  std::string getGenero() const;
  int getDuracaoMinutos() const;

  void setId(int id);
  void setTitulo(const std::string& titulo);
  void setDiretor(const std::string& diretor);
  void setDataLancamento(const std::string& dataLancamento);
  void setGenero(const std::string& genero);
  void setDuracaoMinutos(int duracaoMinutos);

  std::string toString() const;

  void exibir() const;
};

#endif