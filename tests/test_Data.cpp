#include "../third_party/doctest.h"
#include "utils/ArquivosUteis.hpp"  

TEST_CASE("1 - Teste data em formato válido") {
    CHECK(ArquivosUteis::checaData("2023-08-03") == "03/08/2023");
    CHECK(ArquivosUteis::checaData("1999/12/31") == "31/12/1999");
    CHECK(ArquivosUteis::checaData("1895-01-01") == "01/01/1895");
}

TEST_CASE("2 - Teste data em formato inválido lança exceção") {
    CHECK_THROWS_AS(ArquivosUteis::checaData("20230803"), ArquivosUteis::Data_invalida);
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-8-3"), ArquivosUteis::Data_invalida); 
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023_08_03"), ArquivosUteis::Data_invalida);
    CHECK_THROWS_AS(ArquivosUteis::checaData(""), ArquivosUteis::Data_invalida);
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-0803"), ArquivosUteis::Data_invalida);
}

TEST_CASE("3 Teste data com caracteres extras ou tamanho incorreto") {
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-08-031"), ArquivosUteis::Data_invalida);
    CHECK_THROWS_AS(ArquivosUteis::checaData(" 2023-08-03 "), ArquivosUteis::Data_invalida);
}

TEST_CASE("4 - Teste datas com mês ou dia inválidos") {
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-00-10"), ArquivosUteis::Data_invalida); 
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-13-10"), ArquivosUteis::Data_invalida); 
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-04-31"), ArquivosUteis::Data_invalida); 
    CHECK_THROWS_AS(ArquivosUteis::checaData("2023-02-29"), ArquivosUteis::Data_invalida); 
    CHECK(ArquivosUteis::checaData("2024-02-29") == "29/02/2024"); 
}

TEST_CASE("5 - Teste ano abaixo do limite do primeiro filme") {
    CHECK_THROWS_AS(ArquivosUteis::checaData("1800-01-01"), ArquivosUteis::Data_invalida);
}

TEST_CASE("6 - Teste data futura deve lançar exceção") {
    CHECK_THROWS_AS(ArquivosUteis::checaData("2100-01-01"), ArquivosUteis::Data_invalida);
}
