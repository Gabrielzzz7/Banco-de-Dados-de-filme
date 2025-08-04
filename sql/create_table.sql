CREATE TABLE IF NOT EXISTS filmes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    titulo TEXT NOT NULL,
    diretor TEXT NOT NULL,
    data_lancamento DATE NOT NULL,
    genero TEXT,
    duracao_minutos INT DEFAULT 0
);