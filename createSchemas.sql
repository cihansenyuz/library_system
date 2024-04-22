CREATE TABLE IF NOT EXISTS books (
    isbn INTEGER PRIMARY KEY,
    title TEXT,
    author TEXT,
    available INTEGER
);

CREATE TABLE IF NOT EXISTS persons (
    id INTEGER PRIMARY KEY,
    name TEXT,
    takenBookIsbn INTEGER,
    takenDate INTEGER
);

INSERT INTO books (isbn, title, author, available) VALUES (" ", " ", " ", " ");

INSERT INTO persons (id, name, takenBookIsbn, takenDate) VALUES (" ", " ", " ", " ");