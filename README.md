# SQL to Code

Tool for generating source code from the raw sql data.

## How to install

Follow the installation steps:

- Clone the project
- From the project root execute:

```shell
git submodule init && git submodule update && sh Installable/install.sh
```

## How to use

The following example shows the conversion from the SQL file into the Dart source code:

`sql2code -i Assets/documents.sql -t cpp -l -o ./Work`

Program arguments:

- -h --help, shows help message and exits [default: false]
- -v --version, prints version information and exits [default: false]
- -i --input, The path for the input SQL file(s) [required]
- -t --target, The target programming language [required]
- -o --output, The destination output directory [required]
- -l --logFull, Log with the full details [default: false]
- -d --debug, Additional information related to the parsing and code generating [default: false]

## Multiple inputs

We can feed program with the multiple inputs:

`sql2code -i Assets/documents.sql Assets/chats.sql Assets/times.sql Assets/main.sql -t cpp -l -o ./Work`

## Supported targets

This is the list of the supported targets in the current version:

- C++ (cpp)

*Note:* More programming language recipes and features will come in upcoming development iterations.

## Code dependencies

The sql2code codebase dependencies are defined under the [Dependencies](./Dependencies) directory.