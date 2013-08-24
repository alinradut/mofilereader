mofilereader
============

This API lets you read .mo-Files and use their content just as you would do with GNUs gettext. It is implemented in C++ with a very liberal license, allowing the programmer to use it in modern programs, without the need of linking against gettext and libiconv.

You will need cmake to build it as a seperate application or library, or just include the few files into your project. Any C++ Compiler should suffice. 

Optionally, you can also build an executable that is able to dump any .mo file to .html to peek into the contents of this file. 

Please report any issues you encounter, I can't fix them if I don't know about them!