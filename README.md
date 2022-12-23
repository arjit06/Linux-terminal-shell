# Linux-terminal-shell 

Gives a simulation of the actual linux terminal shell. Supports 5 external 
commands - cat, mkdir, date, ls, rm and 4 internal commands - cd ,pwd ,echo ,exit.
For more info pls refer to the documentation.txt file.



EXTERNAL COMMANDS :
a)ls command: 
        1) ls             : lists all components of current directory except hidden.
        2) ls -a          : lists all components of curr directory inlcuding hidden.
        3) ls -1          : lists all components of curr directory in different lines. 

b)mkdir command: 
        1) mkdir          : creates a new directory (mkdir e/b/c wont work if e not there).
        2) mkdir -v       : aknowledges that directory is created on creating a new one. 
        3) mkdir -p       : creates successive directories like e/b/c even if e not there.
        
c)rm command 
        1) rm             : removes any files given.
        2) rm -d          : removes empty directories.
        3) rm -v          : acknowledges that files have been removed after removing them.
        
d)cat command:
        1) cat [filenames]  : concatenates the contents of files and prints on the terminal  
        2) cat -E           : works similar to cat but adds a $ sign in beginng of each line
        3) cat -n           : works similar to cat but prints the line no. sign in beginng of each line
        
e)date command
        1) date           : prints date and time.
        2) date -u        : prints date time according to UTC time format.
        3) date -R        : prints info about time differnce between utc and current zone.   
        
        
        
        

INTERNAL COMMANDS:
a)echo command
        1) echo           : prints as a string.
        2) echo -n        : doesn't terminate string with a newline.
        3) echo --help    : prints help of echo.
        
b)pwd command
        1) pwd            : prints current working directory 
        2) pwd -L         : works exactly same as pwd 
        
c)cd command 
        1) cd dir_name    : changes current directory to the one mentioned
        2) cd ~           : changes to home directory
        3) cd -           : goes back to previous directory.
        
        
