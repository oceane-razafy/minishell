# Minishell

This Minishell project was completed by @alselnet and me. It is a group project at 42 school that involves creating a basic Unix shell, providing a command-line interface for users to interact with the operating system. The project aims to implement key functionalities of a shell (using bash as a reference), such as executing basic commands, handling input/output redirection, implementing built-in commands, supporting environment variables and more.

I implemented the execution part (except the heredoc part), creating a command structure that stores essential information such as the presence of pipe, redirections, input/output files, etc. Additionally, I contributed to the completion of the built-in commands, signals management, and environment structure initialization.

## Table of Contents

- [Project Description](#project-description)
- [Installation](#installation)
- [Usage](#usage)

## Project Description

The "Minishell" project focuses on building a simple Unix shell (using bash as reference) with the following objectives:

1. Implementing a command-line interface that reads user input and interprets commands.

2. Parsing user input to identify the command to execute and its arguments.

3. Executing programs and managing their execution, including handling some built-in commands:  
◦ echo with option -n  
◦ cd with only a relative or absolute path  
◦ pwd with no options  
◦ export with no options  
◦ unset with no options  
◦ env with no options or arguments  
◦ exit with no options  

4. Handling signals management: ctrl-C, ctrl-D and ctrl-\

5. Managing environment variables and expanding those variables in command arguments.

6. Handling $? which should expand to the exit status of the most recently executed foreground pipeline.

For more detailed information on the specific requirements and considerations for the Minishell project, please refer to the `minishell.pdf` file provided in this repository. The document contains comprehensive guidelines and explanations on the functionalities to be implemented.

_Please note that the disclaimer regarding the usage of global variables for signal number is specific to the English subject and does not apply to the French subject of the Minishell project. However, we did use a global variable for signals._

## Installation

To use the "Minishell" program, follow these steps:

1. Clone the repository to your local machine:

```
git clone <repo url> minishell
```

2. Navigate to the project directory:

```
cd minishell
```

3. Compile the program using the provided Makefile:

```
make
```

## Usage

To run the "Minishell" program, use the following commands:

```
cd bin
./minishell
```

The program will start, and you can enter commands to be executed.


