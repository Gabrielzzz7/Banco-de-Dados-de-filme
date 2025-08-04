#include "GeradorRelatorioAtividade.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

GeradorRelatorioAtividade::GeradorRelatorioAtividade() {}

std::string GeradorRelatorioAtividade::obterHoraAtual() const {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void GeradorRelatorioAtividade::registrarOperacao(const std::string& operacao, const std::string& resultado) {
    RegistroAtividade registro;
    registro.operacao = operacao;
    registro.resultado = resultado;
    registro.hora = obterHoraAtual();
    atividades.push_back(registro);
}

std::string GeradorRelatorioAtividade::gerarRelatorioCurto() const {
    std::string relatorio = "--- Relatorio de Atividade (Curto) ---\n";
    for (const auto& atividade : atividades) {
        relatorio += "[" + atividade.hora + "] Operacao: " + atividade.operacao + "\n";
    }
    return relatorio;
}

std::string GeradorRelatorioAtividade::gerarRelatorioCompleto() const {
    std::string relatorio = "--- Relatorio de Atividade (Completo) ---\n";
    for (const auto& atividade : atividades) {
        std::string resultado_str = atividade.resultado.empty() ? "Resultado: N/A" : "Resultado: " + atividade.resultado;
        relatorio += "[" + atividade.hora + "] Operacao: " + atividade.operacao + ":\n" + resultado_str + "\n";
    }
    return relatorio;
}

void GeradorRelatorioAtividade::salvarRelatorio(const std::string& tipo) {
    if (!fs::exists(PASTA_RELATORIOS)) {
        fs::create_directory(PASTA_RELATORIOS);
    }

    std::string relatorio_texto;
    std::string nome_arquivo;

    std::string timestamp = obterHoraAtual();
    std::replace(timestamp.begin(), timestamp.end(), ':', '_'); 
    std::replace(timestamp.begin(), timestamp.end(), ' ', '_');

    if (tipo == "curto") {
        relatorio_texto = gerarRelatorioCurto();
        nome_arquivo = "relatorio_curto_" + timestamp + ".txt";
    } else if (tipo == "completo") {
        relatorio_texto = gerarRelatorioCompleto();
        nome_arquivo = "relatorio_completo_" + timestamp + ".txt";
    } else {
        std::cout << "Tipo de relatorio invalido. Salvamento cancelado." << std::endl;
        return;
    }

    std::string caminho_arquivo = PASTA_RELATORIOS + "/" + nome_arquivo;
    std::ofstream arquivo(caminho_arquivo);

    if (arquivo.is_open()) {
        arquivo << relatorio_texto;
        arquivo.close();
        std::cout << "Relatorio '" << nome_arquivo << "' salvo com sucesso em '" << PASTA_RELATORIOS << "/'." << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
    }
}