#include "../third_party/doctest.h"
#include "Utils/ArquivosUteis.hpp" 

#include <fstream>
#include <cstdio> 

TEST_CASE("1 - Testa Query Válida") {
    const char* nomeArquivo = "arquivo_teste.sql";
    {
        std::ofstream arq(nomeArquivo);
        arq << "SELECT * FROM filmes;";
    }
    std::string conteudo = ArquivosUteis::lerQueriesDoArquivo(nomeArquivo);
    CHECK(conteudo == "SELECT * FROM filmes;");
    
    std::remove(nomeArquivo);
}

TEST_CASE("2 - Testa Query Inválida") {
    const char* nomeArquivo = "arquivo_inexistente.sql";
    CHECK_THROWS_AS(ArquivosUteis::lerQueriesDoArquivo(nomeArquivo), ArquivosUteis::Erro_ao_ler_query);
}

TEST_CASE("3 - Testa Arquivo Vazio") {
    const char* nomeArquivo = "arquivo_vazio.sql";
    {
        std::ofstream arq(nomeArquivo);
    }
    std::string conteudo = ArquivosUteis::lerQueriesDoArquivo(nomeArquivo);
    CHECK(conteudo.empty());

    std::remove(nomeArquivo);
}
