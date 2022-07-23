# DDL to Code

Tool for generating source code from the DDL sql data.

CURRENTLY IN THE PHASE OF DEVELOPMENT.

## Code dependencies

The ddl2code codebase depends on the following libraries:

- RedElf's [Logger](https://github.com/red-elf/Logger)
- RedElf's [Tester](https://github.com/red-elf/Tester)

## How to use

The following example shows the conversion from the SQL ddl file into the Dart source code:

`ddl2code ddl.sql dart`

Where the parameters are the following:

- Path to the DDL sql file
- Programming language for which source code will be generated.

Suported programming languages (parameters) are:

- Java (java)
- Dart (dart).
