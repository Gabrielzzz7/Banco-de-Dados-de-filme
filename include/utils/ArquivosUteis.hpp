#pragma once
#include <string>

namespace ArquivosUteis {

    class Erro_ao_ler_query {};

    class Data_invalida {};

    std::string lerQueriesDoArquivo(const std::string& nomeArquivo);
    std::string checaData(const std::string& data);
    void imprimeFalhaDeTipoNumerico(std::string tipoEsperado);
    void imprimeFalhaString();
    bool stringVazia(const std::string& str);
    void imprimeFalhaData();

    class GerenciadorDeEntradas {
    public:
        static int lerInt(bool opicional = true);
        static float lerFloat();
        static double lerDouble();
        static std::string lerString(bool atualizar = false, bool opicional = false);
        static std::string lerData(bool atualizar = false, bool opicional = false);
        static std::string lerEntradaRelatorio();
    };

}
