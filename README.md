
# Custom Shell Project

**Manan Chichra**

## 1. echo

### Description:
The `echo` command outputs the given arguments. It supports:
- Quoted strings.
- Multiple spaces between words.

### Features:
- Handles whitespace and quotations correctly (e.g.,<pre> `echo "hello     world"` </pre> 
outputs `"hello world"` without collapsing spaces).



### Example:
```bash
~$ echo "hello      world"
hello      world
~$ echo hello world
hello world 
```


## 2. cd
### Description:

The cd command changes the current working directory. 

<!-- **It supports:** -->
#### Features:

- Navigation to the home directory using ~.

- Navigation to the previous directory using -.

- cd ~  : Changes to the user's home directory.
- cd    : Changes to the user's home directory.
- cd -  : Changes to the last visited directory.
- cd `<directory>` : Changes to a specified directory.
- cd ..  : Changes to the directory `one level above`
- Tracks directory history for the ` cd - ` functionality.
- Taken care of whitespaces 
    
    eg. `both give same output`

    <pre>  cd --  
    cd     --</pre>
            

**Error Handling**:

- Displays error messages for invalid paths.

<!-- Example: -->

## 3. pwd

### Description:
The pwd command prints the current working directory.

#### Features:
- Outputs the absolute path of the current directory.

        Example:
        ~$ pwd
        /home/mananchichra/


## 4. history


### Description:
The history command shows the command history, listing all the previous commands executed in the session or across sessions. Commands are saved and loaded from a history file (.shell_history).

#### Features:
- Stores command history across shell sessions.
- Avoids adding duplicate commands in sequence.
- Limits the history to 20 entries (configurable).
- Commands stored in .shell_history are saved without duplicate or empty lines.
- Handles commands containing quotes and whitespace.



## 5. Whitespace Handling
Description:

The shell correctly handles commands with extra spaces, preserving spaces when necessary (e.g., echo), and trimming when appropriate.


## 6. Shell Prompt
Description:
The shell prompt is displayed using:

    Username@SystemName:Current Directory (e.g., user@system:~$).
    The home directory is replaced with ~ in the prompt.
    Example:
    bash
    Copy code
    user@system:~$ 
    user@system:/path/to/directory$ 




***Used Makefile for code compilation**
