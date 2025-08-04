#include "../include/Filme.hpp"
#include "../third_party/doctest.h"

#include <sstream>
#include <iostream>

TEST_CASE("1 - Testar construtores e getters") {
    Filme f1;
    CHECK(f1.getId() == 0);
    CHECK(f1.getTitulo() == "");
    CHECK(f1.getDiretor() == "");
    CHECK(f1.getDataLancamento() == "");
    CHECK(f1.getGenero() == "");
    CHECK(f1.getDuracaoMinutos() == 0);

    Filme f2("Matrix", "Wachowski", "1999-03-31", "Ficção", 136);
    CHECK(f2.getId() == 0);
    CHECK(f2.getTitulo() == "Matrix");
    CHECK(f2.getDiretor() == "Wachowski");
    CHECK(f2.getDataLancamento() == "1999-03-31");
    CHECK(f2.getGenero() == "Ficção");
    CHECK(f2.getDuracaoMinutos() == 136);

    Filme f3(42, "Inception", "Nolan", "2010-07-16", "Ação", 148);
    CHECK(f3.getId() == 42);
    CHECK(f3.getTitulo() == "Inception");
    CHECK(f3.getDiretor() == "Nolan");
    CHECK(f3.getDataLancamento() == "2010-07-16");
    CHECK(f3.getGenero() == "Ação");
    CHECK(f3.getDuracaoMinutos() == 148);
}

TEST_CASE("2 - Testar setters") {
    Filme f;
    f.setId(7);
    f.setTitulo("Avatar");
    f.setDiretor("Cameron");
    f.setDataLancamento("2009-12-18");
    f.setGenero("Fantasia");
    f.setDuracaoMinutos(162);

    CHECK(f.getId() == 7);
    CHECK(f.getTitulo() == "Avatar");
    CHECK(f.getDiretor() == "Cameron");
    CHECK(f.getDataLancamento() == "2009-12-18");
    CHECK(f.getGenero() == "Fantasia");
    CHECK(f.getDuracaoMinutos() == 162);
}

TEST_CASE("3 - Testar método exibir") {
    Filme f(10, "Titanic", "Cameron", "1997-12-19", "Drama", 195);

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    f.exibir();

    std::cout.rdbuf(oldCout); 

    std::string output = buffer.str();

    CHECK(output.find("ID: 10") != std::string::npos);
    CHECK(output.find("Título: Titanic") != std::string::npos);
    CHECK(output.find("Diretor: Cameron") != std::string::npos);
    CHECK(output.find("Data de Lançamento: 1997-12-19") != std::string::npos);
    CHECK(output.find("Gênero: Drama") != std::string::npos);
    CHECK(output.find("Duração: 195 minutos") != std::string::npos);
}
