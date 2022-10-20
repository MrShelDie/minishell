# Minishell
 [![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/) ![](https://img.shields.io/badge/Education%20Project-%F0%9F%93%96-orange)
 [![GitHub commits](https://badgen.net/github/commits/MrShelDie/minishell)](https://GitHub.com/MrShelDie/minishell/commit/) [![GitHub latest commit](https://badgen.net/github/last-commit/MrShelDie/minishell)](https://GitHub.com/MrShelDie/minishell/commit/)
 [![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg) [![macOS](https://svgshare.com/i/ZjP.svg)](https://svgshare.com/i/ZjP.svg)

![](https://github.com/MrShelDie/minishell/blob/master/demo.gif?raw=true)

Minishell is a simplified version of bash. Nevertheless, this shell remains quite functional.
The minishell works like a bash in interactive mode and supports the following functionality:
- Command input prompt
- Command history
- Search for executable files based on the PATH variable, local or global path
- Single `'` and double `"` quotes are handled the same way they are handled in bash
- Environment variables `$var_name`
- Exit codes `$?`
- Redirects `<`, `<<`, `>`, `>>`
- Pipelines `|`
- Keyboard shortcuts `ctrl-C`, `ctrl-D` and `ctrl-\`
- Builds:
	- `echo` with option -n
	- `cd` with only a relative or absolute path
	- `pwd` with no options
	- `export` with no options
	- `unset` with no options
	- `env` with no options or arguments
	- `exit` with no options
- Operators `&&` and `||` and parentheses `()` to prioritize and run commands in a subshell
- Wildcards `*` for the current directory.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make
- GCC
- readline library:
	- libreadline-dev (Ubuntu)
	- readline-devel (Fedora)

### Building the program

1. Download/Clone this repo
        ```git clone git@github.com:MrShelDie/minishell.git```
        
2. `cd` into the root directory and run `make`
	```
	cd minishell
   make
	```
### Running the program

After building the source, run `./minishell` from the project root.

## Authors

* **Nikolay Ivchenko** 
	* email:  [mrsheldie@mail.ru](mailto:mrsheldie@mail.ru)
	* github: https://github.com/MrShelDie
* **Mihail Gubanov**
	* email: [gubanov26@list.ru](mailto:gubanov26@list.ru)
	* github: https://github.com/Magnificent-Edric 

## Notes

- This is an educational project of school 21 (ecole 42).
- The project is written in accordance with the school code style (<a ref="https://github.com/MrShelDie/minishell/blob/master/en.norm.pdf">norm</a>).
- You can find the project instructions by <a ref="https://github.com/MrShelDie/minishell/blob/master/en.subject.pdf">here</a>.
