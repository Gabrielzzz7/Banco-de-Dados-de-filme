#include <iostream>
#include <limits>
#include <string>

#include "Interface.hpp"
#include "utils/ArquivosUteis.hpp"

Interface::Interface(sqlite3* db) : _db(db) {}

void Interface::cadastrarNovoFilme() {
  std::string titulo, diretor, genero, dataLancamento;
  int duracaoMinutos;

  std::cout << "\n--- CADASTRO DE NOVO FILME ---\n";
  std::cout << "Titulo: ";
  titulo = ArquivosUteis::GerenciadorDeEntradas::lerString();
  std::cout << "Diretor: ";
  diretor = ArquivosUteis::GerenciadorDeEntradas::lerString();
  std::cout << "Data de Lancamento (DD-MM-AAAA): ";
  dataLancamento = ArquivosUteis::GerenciadorDeEntradas::lerData();
  std::cout << "Genero: ";
  genero = ArquivosUteis::GerenciadorDeEntradas::lerString(false, true);
  std::cout << "Duracao (minutos): ";
  duracaoMinutos = ArquivosUteis::GerenciadorDeEntradas::lerInt(true);

  Filme novoFilme(titulo, diretor, dataLancamento, genero, duracaoMinutos);

  try {
    GerenciadorDeFilmes::inserir(_db, novoFilme);
    std::cout << "\nFilme cadastrado com sucesso!\n";
    geradorRelatorio.registrarOperacao("Cadastrar novo filme", novoFilme.toString());
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de cadastro. Por favor, tente novamente." << std::endl;
    geradorRelatorio.registrarOperacao("Cadastrar novo filme");
    return;
  }
  catch (const Erro_ao_inserir_no_banco&) {
    std::cerr << "Erro: Não foi possível salvar o filme no banco de dados. Verifique os dados e tente novamente." << std::endl;
    geradorRelatorio.registrarOperacao("Cadastrar novo filme");
    return;
  }


}

void Interface::listarTodosOsFilmes() {
  std::cout << "\n--- LISTA DE TODOS OS FILMES ---\n";
  try {
    std::vector<Filme> filmes = GerenciadorDeFilmes::listarTodos(_db);
    if (filmes.empty()) {
      std::cout << "Nenhum filme encontrado.\n";
    }
    else {
      for (const auto& filme : filmes) {
        filme.exibir();
      }
      std::string lista = std::to_string(filmes.size()) + " filmes.";
      geradorRelatorio.registrarOperacao("Listar todos", lista);
    }
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de listagem. Por favor, tente novamente." << std::endl;
    return;
  }
  catch (const Erro_ao_listar_no_banco&) {
    std::cerr << "Erro: Falha ao listar os filmes do banco de dados. Por favor, tente novamente." << std::endl;
    return;
  }
}

void Interface::buscarFilmePorId() {
  int id;
  std::cout << "\n--- BUSCAR FILME POR ID ---\n";
  std::cout << "Digite o ID do filme: ";
  id = ArquivosUteis::GerenciadorDeEntradas::lerInt();

  try {
    Filme filme = GerenciadorDeFilmes::buscarPorId(_db, id);
    if (filme.getId() != 0) {
      std::cout << "\nFilme encontrado:\n";
      filme.exibir();
      geradorRelatorio.registrarOperacao("Buscar filme por ID", filme.toString());
    }
    else {
      std::cout << "\nNenhum filme encontrado com o ID " << id << ".\n";
    }
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de busca. Por favor, tente novamente." << std::endl;
    return;
  }
  catch (const Erro_ao_buscar_no_banco&) {
    std::cerr << "Erro: Não foi possível buscar o filme no banco de dados. Por favor, verifique o ID e tente novamente." << std::endl;
    return;
  }
}

void Interface::atualizarFilme() {
  int id;
  std::cout << "\n--- ATUALIZAR FILME ---\n";
  std::cout << "Digite o ID do filme que deseja atualizar: ";
  id = ArquivosUteis::GerenciadorDeEntradas::lerInt();

  Filme filmeAtual;
  try {
    filmeAtual = GerenciadorDeFilmes::buscarPorId(_db, id);
    if (filmeAtual.getId() == 0) {
      std::cout << "\nNenhum filme encontrado com o ID " << id << ".\n";
      return;
    }
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de atualização. Por favor, tente novamente." << std::endl;
    return;
  }
  catch (const Erro_ao_buscar_no_banco&) {
    std::cerr << "Erro: Não foi possível buscar o filme para atualização. Por favor, verifique o ID e tente novamente." << std::endl;
    return;
  }

  std::cout << "\nFilme atual:\n";
  filmeAtual.exibir();

  std::string novoTitulo, novoDiretor, novoGenero, novaDataLancamento;
  int novaDuracao = 0;

  std::cout << "\nDigite os novos dados (deixe em branco para nao alterar):\n";
  std::cout << "Novo Titulo: ";
  novoTitulo = ArquivosUteis::GerenciadorDeEntradas::lerString(true);
  if (!novoTitulo.empty()) filmeAtual.setTitulo(novoTitulo);

  std::cout << "Novo Diretor: ";
  novoDiretor = ArquivosUteis::GerenciadorDeEntradas::lerString(true);
  if (!novoDiretor.empty()) filmeAtual.setDiretor(novoDiretor);

  std::cout << "Nova Data de Lancamento (DD-MM-AAAA): ";
  novaDataLancamento = ArquivosUteis::GerenciadorDeEntradas::lerData(true);
  if (!novaDataLancamento.empty()) filmeAtual.setDataLancamento(novaDataLancamento);

  std::cout << "Novo Genero: ";
  novoGenero = ArquivosUteis::GerenciadorDeEntradas::lerString(true);
  if (!novoGenero.empty()) filmeAtual.setGenero(novoGenero);

  std::cout << "Nova Duracao (minutos): ";
  novaDuracao = ArquivosUteis::GerenciadorDeEntradas::lerInt();
  if (novaDuracao != 0) filmeAtual.setDuracaoMinutos(novaDuracao);

  try {
    if (GerenciadorDeFilmes::atualizar(_db, filmeAtual)) {
      geradorRelatorio.registrarOperacao("Atualizar filme", filmeAtual.toString());
      std::cout << "\nFilme atualizado com sucesso!\n";
    }
    else {
      std::cout << "\nErro ao atualizar filme.\n";
    }
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de atualização. Por favor, tente novamente." << std::endl;
    return;
  }
  catch (const Erro_ao_atualizar_no_banco&) {
    std::cerr << "Erro: Não foi possível atualizar o filme no banco de dados. Por favor, verifique os dados e tente novamente." << std::endl;
    return;
  }
}

void Interface::deletarFilme() {
  int id;
  std::cout << "\n--- DELETAR FILME ---\n";
  std::cout << "Digite o ID do filme que deseja deletar: ";
  id = ArquivosUteis::GerenciadorDeEntradas::lerInt();

  try {
    if (GerenciadorDeFilmes::deletar(_db, id)) {
      geradorRelatorio.registrarOperacao("Deletar filme", std::to_string(id));
      std::cout << "\nFilme com ID " << id << " deletado com sucesso!\n";
    }
    else {
      std::cout << "\nErro ao deletar filme ou ID nao encontrado.\n";
    }
  }
  catch (const ArquivosUteis::Erro_ao_ler_query&) {
    std::cerr << "Ocorreu um erro interno ao preparar a operação de deleção. Por favor, tente novamente." << std::endl;
    return;
  }
  catch (const Erro_ao_deletar_no_banco&) {
    std::cerr << "Erro: Não foi possível deletar o filme do banco de dados. Por favor, verifique o ID e tente novamente." << std::endl;
    return;
  }
}

void Interface::ExibirMenu() {
  int escolha;
  do {
    std::cout << "\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Cadastrar novo filme\n";
    std::cout << "2. Listar todos os filmes\n";
    std::cout << "3. Buscar filme por ID\n";
    std::cout << "4. Atualizar filme\n";
    std::cout << "5. Deletar filme\n";
    std::cout << "6. Sair\n";
    std::cout << "Escolha uma opcao: ";
    escolha = ArquivosUteis::GerenciadorDeEntradas::lerInt();

    switch (escolha) {
    case 1:
      cadastrarNovoFilme();
      break;
    case 2:
      listarTodosOsFilmes();
      break;
    case 3:
      buscarFilmePorId();
      break;
    case 4:
      atualizarFilme();
      break;
    case 5:
      deletarFilme();
      break;
    case 6:
      std::cout << "\nEncerrando o programa.\n";

      char opcaoSalvar;
      std::cout << "Voce deseja guardar um registro com as operacoes feitas? (s/n): ";
      std::cin >> opcaoSalvar;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (opcaoSalvar == 's' || opcaoSalvar == 'S') {
        std::string tipo;
        std::cout << "Deseja relatorio (curto) ou (completo)? ";
        std::getline(std::cin, tipo);
        geradorRelatorio.salvarRelatorio(tipo);
      }
      else {
        std::cout << "Relatorio nao sera salvo." << std::endl;
      }
      break;
      break;
    default:
      std::cout << "\nOpcao invalida. Tente novamente.\n";
    }
  } while (escolha != 6);
}