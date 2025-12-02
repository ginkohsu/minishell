# minishell

[example](https://i.imgur.com/YTyL1eg.gif)

## what is this

42 project. minimal bash implementation. 

handles pipes, redirections, builtins, signals, environment variables.  two person project.

## implementation

- parse to AST, execute recursively
- max 2 concurrent pipes open at any time
- builtins: cd, echo, pwd, export, unset, env, exit
- proper signal handling and quote parsing

parser builds an abstract syntax tree, execution traverses it recursively. keeps pipe management simple and efficient.

## usage

```bash
make
./minishell
```

learned about process management, file descriptors, and recursive execution patterns. parsing turned out clean. 
