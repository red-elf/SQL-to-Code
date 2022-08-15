# SQL to Code

Tool for generating source code from the raw sql data.

CURRENTLY IN THE PHASE OF DEVELOPMENT.

## Code dependencies

The sql2code codebase dependencies are defined under the [Dependencies](./Dependencies) directory.

## How to use

The following example shows the conversion from the SQL file into the Dart source code:

`sql2code -i data.sql -o cpp`

Where the parameters are the following:

- Path to the sql file
- Programming language for which source code will be generated.

Supported programming languages (parameters) are:

- C++ (cpp)
- Java (java)
- Dart (dart)
- More to come ...
