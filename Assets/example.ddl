create table documents
(
    id          TEXT    not null
        primary key
        unique,
    title       TEXT    not null,
    project_id  TEXT    not null,
    document_id TEXT,
    created     INTEGER not null,
    modified    INTEGER not null,
    deleted     BOOLEAN default 0 not null
        check (deleted IN (0, 1))
);

create index get_by_created
    on documents (created);

create index get_by_created_and_modified
    on documents (created, modified);

create index get_by_deleted
    on documents (deleted);

create index get_by_document_id
    on documents (document_id);

create index get_by_modified
    on documents (modified);

create index get_by_project_id
    on documents (project_id);

create index get_by_title
    on documents (title);

