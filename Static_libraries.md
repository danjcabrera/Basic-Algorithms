### Static Library  
- A static library is simply a Unix archive made from relocatable object files. Such
a library is usually linked together with other object files to form an executable
object file.    
- A static library is not an object file, ELF file, but it is a archived file that 
has been created by the Unix `ar` utility.  
- When a linker is about to use a static library in the linking step, it first tries 
to extract the relocatable object files from it, then it starts to look up and 
resolve the undefined symbols that may be found in some of them.  
- Static libraries are usually named according to convention. The name starts with
`lib` and ends with the `.a` extension. 
- Without a `main()` function, the relocatable files cannot be linked to create an
executable file, but we can archive them to form a static library.  
- Executable files produced produced from the linkage of many static libraries usually
have huge sizes.  

### Header files   
When using a C library, we need to have access to the declarations that are exposed
by the library together with its static library file. 
The declarations are considered as the *public interface* of the library, the *API*.  
Header files provide declarations, types, function signatures, etc., to the compiler. 
Details, such as type sizes and function addresses are needed at the later stages of 
linking and loading.

#### Use of Unix Archiver
The `ar` command does not necessarily create a *compressed* archive file. It is 
only used to put files together to form a single file that is an archive.   

### How to create a static library    
1. Compile all of the source files in a C/C++ project.
`gcc -c <source-file1.c> -o <relocatable-file1.o>`   
`gcc -c <source-file2.c> -o <relocatable-file2.o>`   
2. Use the Unix archiving tool `ar` to create the static library's archive file:   
`ar crs <lib-name.a> <relocatable-file1.o> ... <relocatable-fileN.o>`    
3. After executing the command, `lib-name.a` is created, which contains all of 
the preceding relocatable object files as a single archive.  
4. Create a directory to contain the static library and move the static library file to this directory.
5. Show the contents of the archived file:   
`ar t /<path>/<to>/<file-folder>/<lib-name.a>`   

### How to use a static library   
1. The new source file will include the library's API (the header file) and make use of its functions. 
` gcc -c <source-code.c> -o main.o`    
2. Link the new relocatable object file to the static library:  
` gcc main.o -L/<path>/<to>/<file-folder> -l<file-folder> -lm -o a.out`   
    * `-L/<path>/<to>/<file-folder>`:  points gcc to the library. If you do not specify, the linker will
    only search its default pasts.  
    * `-lgeometry`:  tells gcc to find a library with the name geometry prepended with `lib` and 
    ending with a `.a` or `.so` file extension. so `-lgeometry` will be `libgeometry.a` or `libgeometry.so`.       
    * `-lm`:  tells gcc to look for a math library named `libm.a` or `libm.so`.   

##### Examples and comments from "Extreme C" by Kamran Amini






