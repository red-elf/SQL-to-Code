# DDL to Code

Tool for generating source code from the DDL sql data.

CURRENTLY IN THE PHASE OF DEVELOPMENT.

## Code dependencies

The ddl2code codebase dependencies are defined under the [Dependencies](./Dependencies) directory.

## How to use

The following example shows the conversion from the SQL ddl file into the Dart source code:

`ddl2code -i ddl.sql -o dart`

Where the parameters are the following:

- Path to the DDL sql file
- Programming language for which source code will be generated.

Supported programming languages (parameters) are:

- C++ (cpp)
- Java (java)
- Dart (dart)
- More to come ...
