## Dynamic libraries   
Dynamic libraries (shared object files) are not part of the executable itsef. Instead, 
they should be loaded and brought in while loading a process for execution.  
Dynamic libraries may have undefined symbols that are not resolved at linking 
time. These symbols are searched for when the executable product is about to be 
loaded to begin its execution.  

A *dynamic linker*, or simply the *loader*, usually does the linking while loading 
an exectuble file and preparing it to be run as a process. 

Dynamic library files are sister files to static library files. These shared object 
files have the `.so` extension in most Unix-like systems. On execution, the dynamic 
library shared object files will be loaded and mapped to a memory region accessible 
by the process. This procedure is done by a dynamic linker (or loader), which loads 
and executes an executable file.  Some segments used for loading in a standard ELF 
executable object file are not present in shared object files, this means that the 
dynamic library shared object files cannot be 
executed stand-alone.   

Both ELF executable and shared object files have segments in their ELF structure. Each 
segment has zero or more sections in them.  The symbols in ELF shared object files have 
relative absolute addresses. The dynamic library relocatable object files are *position independent*, 
this means that while the address of each instruction is different in any process, 
the distance between two instructions remains fixed, that is, the addresses are fixed 
relative to an offset.  Position independent simply means that the instructions
within it don't have fixed addresses. They have relative addresses; hence they can
obtain different addresses in different processes. 


## How to create a dynamic library   
The **PIC** option (**position independent code**) used when compiling relocatable 
object files is *mandatory* to create a dynamic library.  
 
The `-shared` option asks gcc to create a shared object file from the relocatable
object files. 
The program loader does not know how to find the provided custom path to the shared
object. Update the environment variable `LD_LIBRARY_PATH` to point to the custom
directory.    

```c
gcc -c <source-code-1.c> -fPIC -o <object-code-1.o>   
gcc -c <source-code-2.c> -fPIC -o <object-code-2.o>    
gcc -c <source-code-3.c> -fPIC -o <object-code-3.o>
gcc -shared <object-code-1.o> <object-code-2.o> <object-code-3.o> -o <lib<project-name.so>>   
mkdir -p /<path>/<to>/<shared-object-directory>
mv <lib<project-name.so>> /<path>/<to>/<shared-object-directory>    
gcc -c <source-code-main.c> -o main.o
export LD_LIBRARY_PATH=/<path>/<to>/<shared-object-directory>
gcc main.o -L/<path>/<to>/<shared-object-directory> -lm -o a.out 
```  

## How to lazily load a dynamic library functions  
The difference with lazily loading dynamic libraries is that dependencies must be handled
by the linker on the command line:   

`gcc -shared <object-code-1.o> <object-code-2.o> <object-code-3.o> -lm -o <lib<project-name.so>>`    

The options `-lm`, tells the linker to link the shared object agains the standard math 
library which is a dependency to the dynamic library. 

The function `dlopen` will load the shared object library and `dlsym` will obtain the object 
symbol using a function pointer.  

```c
...
int main(int argc), char** argv) {
    void* handle = dlopen ("/<path>/<to>/<lib<project-name.so>>", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    func_ptr = dlsym(handle, "<object-symbol>");
    if (!func_ptr) {
        ...
}

When compiling the program is not linked to the shared object library:  
`gcc <source-code-main.c> -ldl -o a.out`  


#### Examples and comments from "Extreme C" by Kamran Amini
