CREATE TABLE documents
(

    id          TEXT    NOT NULL PRIMARY KEY UNIQUE,
    title       TEXT    NOT NULL,
    project_id  TEXT    NOT NULL,
    document_id TEXT,
    created     INTEGER NOT NULL,
    modified    INTEGER NOT NULL,
    deleted     BOOLEAN NOT NULL CHECK (deleted IN (0, 1)) DEFAULT 0
);