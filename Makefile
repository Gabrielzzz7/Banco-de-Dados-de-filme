CC := g++
SRCDIR := src
TSTDIR := tests
OBJDIR := build
BINDIR := bin

MAIN := program/main.cpp
TESTER := program/tester.cpp

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TSTSOURCES := $(shell find $(TSTDIR) -type f -name *.$(SRCEXT))

CFLAGS := -Wall -std=c++17 -g --coverage
INC := -I include/ -I third_party/

# VERBOSITY padrão 0, pode ser sobrescrito na linha de comando
VERBOSITY ?= 0

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

main: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(MAIN) $^ -o $(BINDIR)/main -lsqlite3

run-test: $(OBJECTS)
	@if [ -z "$(TEST_FILE)" ]; then \
		echo "Uso: make run-test TEST_FILE=nome_do_arquivo.cpp [VERBOSITY=0|1|2]"; \
	else \
		mkdir -p $(BINDIR); \
		find . -name "*.gcda" -delete; \
		echo "Compilando e executando teste para: $(TEST_FILE)"; \
		$(CC) $(CFLAGS) $(INC) $(TESTER) $(TSTDIR)/$(TEST_FILE) $(OBJECTS) -o $(BINDIR)/tester -lsqlite3; \
		$(BINDIR)/tester --verbosity=$(VERBOSITY) --success; \
	fi


tests: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(TESTER) $(TSTSOURCES) $^ -o $(BINDIR)/tester -lsqlite3
	$(BINDIR)/tester --verbosity=$(VERBOSITY) --success

run: main
	$(BINDIR)/main

clean:
	$(RM) -r $(OBJDIR)/* $(BINDIR)/* coverage/* *.gcda *.gcno *.gcov *.info

cov: clean tests
	@mkdir -p coverage
	@echo "Gerando cobertura com gcov..."
	@find build -name "*.gcno" -exec sh -c 'gcov -o $$(dirname {}) {} > /dev/null' \;
	@mv *.gcov coverage/ 2>/dev/null || true
	@echo "Cobertura gerada em: coverage/"

.PHONY: clean run tests main cov run-test
