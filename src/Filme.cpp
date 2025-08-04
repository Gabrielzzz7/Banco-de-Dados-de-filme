#include "Filme.hpp"
#include <iostream>

Filme::Filme() : _id(0), _duracaoMinutos(0) {}

Filme::Filme(const std::string& titulo, const std::string& diretor, const std::string& dataLancamento,
  const std::string& genero, int duracaoMinutos)
  : _id(0), _titulo(titulo), _diretor(diretor), _dataLancamento(dataLancamento),
  _genero(genero), _duracaoMinutos(duracaoMinutos) {
}

Filme::Filme(int id, const std::string& titulo, const std::string& diretor,
  const std::string& dataLancamento, const std::string& genero, int duracaoMinutos)
  : _id(id), _titulo(titulo), _diretor(diretor), _dataLancamento(dataLancamento),
  _genero(genero), _duracaoMinutos(duracaoMinutos) {
}

int Filme::getId() const {
  return _id;
}

std::string Filme::getTitulo() const {
  return _titulo;
}

std::string Filme::getDiretor() const {
  return _diretor;
}

std::string Filme::getDataLancamento() const {
  return _dataLancamento;
}

std::string Filme::getGenero() const {
  return _genero;
}

int Filme::getDuracaoMinutos() const {
  return _duracaoMinutos;
}

void Filme::setId(int id) {
  _id = id;
}

void Filme::setTitulo(const std::string& titulo) {
  _titulo = titulo;
}

void Filme::setDiretor(const std::string& diretor) {
  _diretor = diretor;
}

void Filme::setDataLancamento(const std::string& dataLancamento) {
  _dataLancamento = dataLancamento;
}

void Filme::setGenero(const std::string& genero) {
  _genero = genero;
}

void Filme::setDuracaoMinutos(int duracaoMinutos) {
  _duracaoMinutos = duracaoMinutos;
}

std::string Filme::toString() const {
  std::ostringstream oss;
  oss << "ID: " << _id << ", "
    << "Título: " << _titulo << ", "
    << "Diretor: " << _diretor << ", "
    << "Data de Lançamento: " << _dataLancamento << ", "
    << "Gênero: " << _genero << ", "
    << "Duração: " << _duracaoMinutos << " minutos";
  return oss.str();
}

void Filme::exibir() const {
  std::cout << "--------------------------------\n";
  std::cout << "ID: " << _id << "\n";
  std::cout << "Título: " << _titulo << "\n";
  std::cout << "Diretor: " << _diretor << "\n";
  std::cout << "Data de Lançamento: " << _dataLancamento << "\n";
  std::cout << "Gênero: " << _genero << "\n";
  std::cout << "Duração: " << _duracaoMinutos << " minutos\n";
  std::cout << "--------------------------------\n";
}