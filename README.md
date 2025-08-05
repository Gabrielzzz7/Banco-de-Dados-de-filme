
# 🎬 Banco de Dados de Filmes

Este projeto é um **sistema de gerenciamento de banco de dados de filmes** desenvolvido em **C++** com persistência em **SQLite** e interface via **linha de comando (CLI)**. Ele oferece funcionalidades completas de **CRUD**, geração de relatórios, testes automatizados e suporte à conteinerização com **Docker**.

---

## 📚 Índice

- [🚀 Clonando o Repositório](#-clonando-o-repositório)
- [🧩 Funcionalidades](#-funcionalidades)
- [🛠️ Requisitos](#️-requisitos)
- [⚙️ Execução Local](#️-execução-local)
- [🧪 Execução dos Testes](#-execução-dos-testes)
- [📊 Cobertura de Código](#-cobertura-de-código)
- [🐳 Execução com Docker](#-execução-com-docker)
- [📁 Estrutura do Projeto](#-estrutura-do-projeto)
- [📄 Relatório Técnico](#-relatório-técnico)
- [👨‍💻 Autor](#-autor)
- [📜 Licença](#-licença)

---

## 🚀 Clonando o Repositório

Clone o repositório com o comando:

```bash
git clone https://github.com/Gabrielzzz7/Banco-de-Dados-de-filme.git
cd Banco-de-Dados-de-filme
```

---

## 🧩 Funcionalidades

- 📥 Cadastro de filmes
- 📄 Listagem de filmes
- 🔍 Busca por ID
- ✏️ Atualização de dados
- ❌ Exclusão de registros
- 🧪 Testes unitários e de integração
- 📊 Geração de relatórios (curto ou completo)
- 🐳 Suporte a Docker
- 🛠️ Arquitetura limpa e modular

---

## 🛠️ Requisitos

### 📌 Linux (execução local)

- `g++` (C++17)
- `make`
- `libsqlite3-dev`
- `sqlite3`
- (Opcional) `gcov` para cobertura de testes

Instalação no Ubuntu/Debian:

```bash
sudo apt update
sudo apt install g++ make libsqlite3-dev sqlite3
```

---

## ⚙️ Execução Local

### 1. Criar o banco de dados:

```bash
sqlite3 filmes.db < sql/create_table.sql
```

### 2. Compilar e executar o programa:

```bash
make run
```

Ou, diretamente:

```bash
./bin/main
```

---

## 🧪 Execução dos Testes

### Rodar todos os testes:

```bash
make tests
```

### Rodar teste específico:

```bash
make run-test TEST_FILE=tests/teste_nome.cpp VERBOSITY=2
```

---

## 📊 Cobertura de Código

Para gerar relatório de cobertura de testes:

```bash
make cov
```

---

## 🧹 Limpeza do Projeto

Remover binários e arquivos temporários:

```bash
make clean
```

---

## 🐳 Execução com Docker

### 1. Build da imagem Docker:

```bash
docker build -t filmes-app .
```

### 2. Executar container interativo:

```bash
docker run -it --rm -v $(pwd):/app -w /app filmes-app
```

### 3. Comandos dentro do container:

```bash
make run           # Executa o programa principal
make tests         # Executa todos os testes
make run-test TEST_FILE=tests/teste_nome.cpp VERBOSITY=2
```

### 4. Execução direta sem terminal interativo:

```bash
docker run -it --rm -v $(pwd):/app -w /app filmes-app make run
```

---

## 📁 Estrutura do Projeto

```
📁 include/              # Headers (.hpp)
📁 src/                  # Código-fonte (.cpp)
📁 tests/                # Testes unitários e de integração
📁 sql/                  # Scripts SQL
📁 entradas/             # Simulações de entrada
📁 reports/              # Relatórios gerados
📁 third_party/          # Framework de testes (Doctest)
📁 build/                # Objetos compilados
📁 bin/                  # Executáveis
```

---

## 📄 Relatório Técnico

O repositório inclui um arquivo `Relatório_Técnico.pdf` com a documentação completa do sistema, contendo:

- Arquitetura do sistema
- Estrutura de classes
- Estratégias de validação e tratamento de erros
- Detalhamento dos testes
- Instruções detalhadas de uso

---

## 👨‍💻 Autor

Gabriel Campos Prudente  
📧 gabrielcamposprudente19@gmail.com

---

## 📜 Licença

Este projeto é de uso acadêmico e educacional. Para uso comercial, entre em contato com o autor.
