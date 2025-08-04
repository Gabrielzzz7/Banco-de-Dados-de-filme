FROM debian:bookworm-slim

RUN apt update && apt install -y \
    g++ \
    make \
    libsqlite3-dev \
    sqlite3 \
    dos2unix

WORKDIR /app

COPY . .

RUN find entradas/ -type f -exec dos2unix {} \;

RUN make

RUN sqlite3 filmes.db < sql/create_table.sql

CMD ["./bin/main"]
