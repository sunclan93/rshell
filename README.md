#rshell
This is a command shell. Programmed in C++ and makes use of the system calls.

##Introduction

This project is built to act as a terminal. It has the same functionality as a regular terminal, it is able to perform all the execvp functions and gives proper feedback on whether the functions have worked or failed.

##Install Instructions
<pre class="brush:shell;gutter:true;">
$ clone  https://github.com/sunclan93/rshell.git
$ cd rshell
$ git checkout hw3
$ make
$ bin/rshell
</pre>
##Bugs/Limitations for signaling

1. Cannot recognize \.

1. Cannot recognize the command if the command has pipe(>> or <<).

