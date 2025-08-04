#pragma once

#ifndef GERADORRELATORIOATIVIDADE_HPP
#define GERADORRELATORIOATIVIDADE_HPP

#include <string>
#include <vector>
#include <ctime>

struct RegistroAtividade {
    std::string operacao;
    std::string resultado;
    std::string hora;
};

class GeradorRelatorioAtividade {
public:
    GeradorRelatorioAtividade();

    void registrarOperacao(const std::string& operacao, const std::string& resultado = "");
    void salvarRelatorio(const std::string& tipo);

private:
    std::string gerarRelatorioCurto() const;
    std::string gerarRelatorioCompleto() const;

    std::string obterHoraAtual() const;

    std::vector<RegistroAtividade> atividades;
    const std::string PASTA_RELATORIOS = "reports";
};

#endif 