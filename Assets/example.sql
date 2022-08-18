/*
    Version: 1
*/

/*
    Notes:

    - The main project board: https://github.com/orgs/red-elf/projects/2/views/1
    - Identifiers in the system are UUID strings.
    - Mapping tables are used for binding entities and defining relationships.
        Mapping tables are used as well to append properties to the entities.
    - Additional tables are defined to provide the meta-data to entities of the system.
    - To follow the order of entities definition in the system follow the 'DROP TABLE' directives.
*/

/*
    Documents.
    Users can create the project documentation.
    Each document (the root) belongs to the project. It can also belong to the the parent document.
*/
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