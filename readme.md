# C Compiler

## Basics

### Hello, Assembly!

```bash
$ gcc -S -O -fno-asynchronous-unwind-tables -fcf-protection=none return_2.c
```

- **-S** Don’t run the assembler or linker. This makes the compiler emit
  assembly instead of a binary file.

- **-O** Optimize the code. This eliminates some instructions we aren’t
  concerned with right now

- **-fno-asynchronous-unwind-tables** Don’t generate the unwind table, which is
  used for debugging. We don’t need it.

- **-fcf-protection=none** Disable control-flow protection, a security feature
  that adds extra instructions we aren’t concerned with. Control-flow pro-
  tection might already be disabled by default on your system, in which case
  this option won’t do anything. Skip this option if you’re using an old version
  of GCC or Clang that doesn’t support it.

```bash
$ gcc return_2.s -o return_2
$ ./return_2
$ echo $?
```

---

### The compiler Driver

You’ll write a compiler driver before starting on the compiler itself. It should
convert a source file to an executable in three steps:

1. Run this command to preprocess the source file:

```bash
$ gcc -E -P INPUT_FILE -o PREPROCESSED_FILE
```

- This command preprocesses **INPUT_FILE** and then writes the result to
  **PREPROCESSED_FILE**.

- The **-E** option tells GCC to run only the preprocessor, not the later steps
  of the compilation process.

- The **-P** option tells the preprocessor not to emit linemarkers; our lexer
  and parser won’t be able to process them.

2. Compile the preprocessed source file and output an assembly file with a .s
   extension. You’ll have to stub out this step, since you haven’t writ- ten
   your compiler yet. Delete the preprocessed file when you’re done with it.

3. Assemble and link the assembly file to produce an executable, using this
   command:

```bash
$ gcc ASSEMBLY_FILE -o OUTPUT_FILE
```

4. Delete the assembly file when you’re done with it

```
Your compiler driver must have a specific command line interface so this book’s
test script, test_compiler, can run it. It must be a command line program that
accepts a path to a C source file as its only argument. If this command
succeeds, it must produce an executable in the same directory as the input file,
with the same name (minus the file extension).
```

compiler driver should support the following options, which test_compiler uses
to test intermediate stages:

- **--lex** Directs it to run the lexer, but stop before parsing
- **--parse** Directs it to run the lexer and parser, but stop before assem- bly
  generation
- **--codegen** Directs it to perform lexing, parsing, and assembly genera-
  tion, but stop before code emission

None of these options should produce any output files, and all should terminate
with an exit code of 0 if they don’t hit any errors.

---

### The Lexer

The lexer should read in a source file and produce a list of tokens. Before you
can start writing the lexer, you need to know what tokens you might encounter.

- **int** A keyword
- **main** An identifier, whose value is “main”
- **(** An open parenthesis
- **void** A keyword
- **)** A close parenthesis
- **{** An open brace
- **return** A keyword
- **2** A constant, whose value is “2”
- **;** A semicolon
- **}** A close brace

**Tokens and Their Regular Expressions**

| Token             | Regular expression |
| ----------------- | ------------------ |
| Identifier        | [a-zA-Z_]\w*\b     |
| Constant          | [0-9]+\b           |
| int keyword       | int\b              |
| void keyword      | void\b             |
| return keyword    | return\b           |
| Open parenthesis  | \(                 |
| Close parenthesis | \)                 |
| Open brace        | {                  |
| Close brace       | }                  |
| Semicolon         | ;                  |

```
The process of tokenizing a program looks roughly like
```

```bash
while input isn't empty:
    if input starts with whitespace:
        trim whitespace from start of input
    else:
        find longest match at start of input for any regex in Table 1-1
        if no match is found, raise an error
        convert matching substring into a token
        remove matching substring from start of input
```

Rules:

- **Treat keywords like other identifiers.** The regex for identifiers also
  matches keywords. Don’t try to simultane- ously find the end of the next token
  and figure out whether it’s a key- word. First, find the end of the token.
  Then, if it looks like an identifier, check whether it matches any keywords.
- **Don’t split on whitespace.** It isn’t a good idea to start by splitting the
  string on whitespace, since whitespace isn’t the only boundary between tokens.
  For example, main(void) has four tokens and no whitespace.
- **You only need to support ASCII characters.** The test programs for this book
  contain only ASCII characters. The C standard provides a mechanism called
  universal character names to include non-ASCII characters in identifiers, but
  we won’t implement them. Many C implementations let you use Unicode characters
  directly, but you don’t need to support that either.

---

## Flex & Bison

### Basics

En la carpeta flex_bison

```bash
$ flex fb1-1.l
$ gcc lex.yy.c -lfl
$ ./a.out
$ <Escribe tu palabra u oracion y luego presionas ctrl + D >
```

Generation via Makefile and its execution

```bash
<Inside the directory of the working project>
$ make
```

For Chapter 2 fb2-1.fl, fb2-2.fl

```bash
$ flex fb2-1.l
$ gcc lex.yy.c -lfl
$ ./a.out
```

For Chapter 2 fb2-3.fl

```bash
$ flex fb2-1.l
$ gcc lex.yy.c -lfl
$ ./a.out test.c
```
