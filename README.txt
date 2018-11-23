Welcome to Ruvim's example of how to display a picture in a C program on Windows! 

Here are the steps to follow to make it show *your* picture: 
1. Save your picture as a .bmp (Windows Bitmap) file, in the same folder as this program. 
2. Open picture.c with a notepad, and on line 12, where it says my_picture = ..., replace the "IMG_6788.bmp" with *your* bitmap filename (keep the quotes in there, please). 
3. Compile picture.c into picture.exe, and as long as your picture file is there when the program runs, it'll display your picture! 

To compile the code: 
1. Make sure you have a C compiler. 
2. For Digital Mars C Compiler, the command line to compile picture.c into picture.exe is: dmc picture gdi32.lib 
The gdi32.lib is just the Win32 GDI library; you need it to display the picture. 

To download the free Digital Mars C Compiler, go to: https://www.digitalmars.com/download/freecompiler.html
Don't get the Development System; rather, go to the next link on that page, where it says: 
"Digital Mars C/C++ Compiler Version 8.57" 

1. Download that ZIP file. You don't need the second STL download, which pertains to C++; just the compiler will suffice for this C program. 
2. Extract (unzip) the contents of the ZIP file somewhere. 
3. Open the extracted folder, go into "dm" folder, then go into "bin" folder. 
4. At the top of the explorer window, where it says what folder you're in, right-click and select "Copy Address". On your clipboard you should have something like "C:\Users\...\Downloads\dm857c(1).zip\dm\bin" 
5. Open a command prompt, and "cd" into the folder where you have picture.c saved, along with your bitmap file. 
6. Paste the address of the folder into the command line, enclosing it in quotes, and include a "\dmc" at the end. Then add the "picture gdi32.lib" arguments. For example, you might type this command: 
"C:\Users\...\Downloads\dm857c(1)\dm\bin\dmc" picture gdi32.lib

In the above command, please keep the quotes around C:\Users\..., and please do include \dmc at the end, or else it won't work. 

Alternatively, if you have administrator access to the computer, you may right-click on "My Computer", go to "Properties", go to "Advanced System Settings", go to "Environment Variables", click on "System Variables", find "Path", and pase the address from step 4 as a new address for the PATH variable. 
After restarting command prompt, simply typing "dmc picture gdi32.lib" should compile your program without having to paste addresses or put things in quotes. 
