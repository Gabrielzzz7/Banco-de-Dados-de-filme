#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <ctime>
#include <regex>
#include <iomanip>  

#include "utils/ArquivosUteis.hpp"

namespace ArquivosUteis {

    std::string lerQueriesDoArquivo(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            throw Erro_ao_ler_query();
        }

        std::stringstream buffer;
        buffer << arquivo.rdbuf();
        arquivo.close();
        return buffer.str();
    }

    std::string checaData(const std::string& data) {
        if (data.size() != 10 || (data[2] != '-' && data[2] != '/') || (data[5] != '-' && data[5] != '/')) {
            throw Data_invalida();
        }

        int dia = std::stoi(data.substr(0, 2));
        int mes = std::stoi(data.substr(3, 2));
        int ano = std::stoi(data.substr(6, 4));

        if (mes < 1 || mes > 12) {
            throw Data_invalida();
        }

        int dias_mes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (bissexto) dias_mes[1] = 29;

        if (dia < 1 || dia > dias_mes[mes - 1]) {
            throw Data_invalida();
        }

        const int ANO_MINIMO = 1895;
        if (ano < ANO_MINIMO) {
            throw Data_invalida();
        }

        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);

        if (ano > (now->tm_year + 1900) ||
            (ano == (now->tm_year + 1900) && mes > (now->tm_mon + 1)) ||
            (ano == (now->tm_year + 1900) && mes == (now->tm_mon + 1) && dia > now->tm_mday)) {
            throw Data_invalida();
        }

        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << dia << "/"
            << std::setw(2) << mes << "/"
            << std::setw(4) << ano;

        return oss.str();
    }

    void imprimeFalhaDeTipoNumerico(std::string tipoEsperado) {
        std::cout << "\nVocê não digitou um " << tipoEsperado << "." << std::endl;
        std::cout << "Informe novamente um " << tipoEsperado << "." << std::endl;
        std::cout << "Nova entrada: ";
    }

    void imprimeFalhaString() {
        std::cout << "\nA entrada informada não possui texto." << std::endl;
        std::cout << "Informe novamente uma entrada válida." << std::endl;
        std::cout << "Nova entrada: ";
    }

    bool stringVazia(const std::string& str) {
        for (char c : str) {
            if (!std::isspace(c)) {
                return false;
            }
        }
        return true;
    }

    void imprimeFalhaData() {
        std::cout << "\nA data informada não está no formato correto ou está fora do limite." << std::endl;
        std::cout << "Por favor, informe uma data no formato DD-MM-AAAA." << std::endl;
        std::cout << "Nova entrada: ";
    }

    int GerenciadorDeEntradas::lerInt(bool atualizar, bool opicional) {
        int inteiro;

        bool leitura_com_sucesso = false;
        while (!leitura_com_sucesso)
        {
            try
            {
                std::string input;
                std::getline(std::cin, input);

                if ((opicional && input.empty()) || (atualizar && input.empty())) break;

                size_t pos;
                inteiro = std::stoi(input, &pos);

                if (pos != input.size())
                    throw std::invalid_argument("Formato inválido.");

                if (inteiro < std::numeric_limits<int>::min() || inteiro > std::numeric_limits<int>::max())
                    throw std::out_of_range("Fora dos limites do tipo int.");

                leitura_com_sucesso = true;

            }
            catch (const std::exception& e)
            {
                imprimeFalhaDeTipoNumerico("inteiro");
            }
        }

        return inteiro;
    }

    float GerenciadorDeEntradas::lerFloat() {
        float decimal;

        bool leitura_com_sucesso = false;
        while (!leitura_com_sucesso)
        {
            try
            {
                std::string input;
                std::getline(std::cin, input);

                size_t pos;
                decimal = std::stof(input, &pos);

                if (pos != input.size())
                    throw std::invalid_argument("Formato inválido.");

                if (decimal < std::numeric_limits<float>::lowest() || decimal > std::numeric_limits<float>::max())
                    throw std::out_of_range("Fora dos limites do tipo float.");

                leitura_com_sucesso = true;
            }
            catch (const std::exception& e)
            {
                imprimeFalhaDeTipoNumerico("float");
            }
        }

        return decimal;
    }

    double GerenciadorDeEntradas::lerDouble() {
        double decimal;

        bool leitura_com_sucesso = false;
        while (!leitura_com_sucesso)
        {
            try
            {
                std::string input;
                std::getline(std::cin, input);

                size_t pos;
                decimal = std::stod(input, &pos);

                if (pos != input.size())
                    throw std::invalid_argument("Formato inválido.");

                if (decimal < std::numeric_limits<double>::lowest() || decimal > std::numeric_limits<double>::max())
                    throw std::out_of_range("Fora dos limites do tipo double.");

                leitura_com_sucesso = true;
            }
            catch (const std::exception& e)
            {
                imprimeFalhaDeTipoNumerico("double");
            }
        }

        return decimal;
    }

    std::string GerenciadorDeEntradas::lerString(bool atualizar, bool opicional ) {
        std::string texto;

        bool leitura_com_sucesso = false;
        while (!leitura_com_sucesso) {
            if (opicional) break;
            try {
                std::getline(std::cin, texto);

                if (stringVazia(texto) && !atualizar)
                    throw std::exception();

                if (texto.size() == 1 && !std::isalpha(static_cast<unsigned char>(texto[0])))
                    throw std::exception();

                leitura_com_sucesso = true;
            }
            catch (const std::exception& e)
            {
                imprimeFalhaString();
            }
        }

        return texto;
    }

    std::string GerenciadorDeEntradas::lerData(bool atualizar, bool opicional) {
        std::string data;
        bool leitura_com_sucesso = false;
        while (!leitura_com_sucesso) {
            try {
                std::getline(std::cin, data);
                if ((opicional && data.empty()) || (atualizar && data.empty())) break;
                checaData(data);
                leitura_com_sucesso = true;
            }
            catch (const Data_invalida&) {
                imprimeFalhaData();
            }
        }
        return data;
    }

    std::string GerenciadorDeEntradas::lerEntradaRelatorio() {
        std::string entrada;
        bool leitura_com_sucesso = false;

        while (!leitura_com_sucesso) {
            std::getline(std::cin, entrada);

            if (entrada == "curto" || entrada == "completo") {
                leitura_com_sucesso = true;
            }
            else {
                std::cout << "Entrada invalida. Digite 'curto' ou 'completo': ";
            }
        }

        return entrada;
    }
}