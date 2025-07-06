# MyShell - A Simple Unix Shell Implementation

A lightweight, modular Unix shell implementation written in C that supports basic command execution, built-in commands, and optional readline support for enhanced user experience.[![Open in Codespaces](https://github.com/codespaces/badge.svg)](https://github.com/codespaces/new?template_repository=antiquark007/myshell)


## Features

- **Command Execution**: Execute external programs and system commands
- **Built-in Commands**: Support for `cd`, `exit`, and other internal commands
- **Input Parsing**: Parse command-line input with argument handling
- **Modular Design**: Clean separation of concerns across multiple modules
- **Readline Support**: Enhanced input with history and line editing (optional)
- **History Management**: Command history functionality when readline is available

## Project Structure

```
my_shell/
├── Makefile              # Build configuration
├── main.c                # Entry point and main loop
├── parser.c / parser.h   # Input parsing, redirection, pipes
├── builtins.c / builtins.h # Built-in commands (cd, exit, etc.)
├── executor.c / executor.h # Process execution and pipeline handling
├── prompt.c / prompt.h   # User prompt and readline integration
├── history.c / history.h # Command history management
└── README.md             # This file
```

## Prerequisites

- GCC compiler
- Make utility
- libreadline-dev (optional, for enhanced input features)

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

**CentOS/RHEL/Fedora:**
```bash
sudo yum install gcc make readline-devel
# or for newer versions:
sudo dnf install gcc make readline-devel
```

**macOS:**
```bash
# Install Xcode command line tools
xcode-select --install
# Install readline via Homebrew
brew install readline
```

## Building

1. Clone or download the project files
2. Navigate to the project directory
3. Compile the shell:

```bash
make
```

To clean build artifacts:
```bash
make clean
```

## Usage

### Starting the Shell

```bash
./myshell
```

### Supported Commands

#### Built-in Commands

- **exit**: Quit the shell
  ```bash
  exit
  ```

- **cd**: Change directory
  ```bash
  cd /path/to/directory
  cd ..
  cd ~
  ```

#### External Commands

Execute any system command available in your PATH:

```bash
ls -la
ps aux
grep "pattern" file.txt
cat file.txt
```

### Example Session

```bash
$ ./myshell
myshell> pwd
/home/user/project/myshell
myshell> ls
Makefile  README.md  builtins.c  builtins.h  executor.c  executor.h  history.c  history.h  main.c  myshell  parser.c  parser.h  prompt.c  prompt.h
myshell> cd ..
myshell> pwd
/home/user/project
myshell> exit
$
```

## Development

### Adding New Built-in Commands

1. Add the command logic to `builtins.c`
2. Add the function declaration to `builtins.h`
3. Update the main loop in `main.c` to handle the new command

### Extending Functionality

The modular design makes it easy to extend:

- **Parser**: Modify `parser.c` to support new syntax features
- **Executor**: Update `executor.c` to handle new execution modes
- **Built-ins**: Add new commands in `builtins.c`

## Compilation Notes

- The project automatically detects readline availability
- If readline is not available, basic functionality continues to work
- Use `make install-readline` for installation instructions

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is for educational purposes. Feel free to modify and distribute.

## Troubleshooting

### Common Issues

**Readline errors during compilation:**
- Install libreadline-dev package
- Or modify Makefile to disable readline support

**Permission denied errors:**
- Ensure the executable has proper permissions: `chmod +x myshell`

**Command not found:**
- Check that external commands are in your PATH
- Use absolute paths for custom executables

## Future Enhancements

- [ ] Pipe support (`|`)
- [ ] Input/Output redirection (`>`, `<`, `>>`)
- [ ] Background process execution (`&`)
- [ ] Environment variable support
- [ ] Tab completion
- [ ] Signal handling (Ctrl+C, Ctrl+Z)
- [ ] Job control
- [ ] Scripting support

## Author

Created as part of a systems programming project.

