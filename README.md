# FP
This utility is used to find/copy files related to specific predicat, passed as CL argument.<br>
Also you can exlude all thing you don't need in ```WhatToInclude.h```<br>
Let's see, how to do that:<br>
```cpp
//some code
#define COPY 1
#define FIND 1
//some code
```
If you don't need Copy module or Find module you should set 0 value.<br>
Yes, if there is no module, programm won't do anything, but you will see message<br>
and so you can understand copy of programm is just "empty" executable file.<br>

### The main idea
It doesn't follow the Unix-philosophy in classic way, but it modifies it!<br>
Programm is combination of independent modules, which can be included in different versions<br>
and every module has only one goal and reason to exist.<br>

### How to use
There is global Arguments:<br>
```F``` and ```C```<br>
Each global argument relates to specific module<br>

And so there is standart arguments, contained withing brackets<br>
```fp F[ -p=* -t=e:/books]```                  - example of Find module.<br>
```-p``` is predicat, * means anything.<br>
```-t``` is top directory to search.<br>


```fp C[ -p=*.txt -w=e:/books -f=txt_books]``` - example of Copy module.<br>
```-w``` is folder, where to copy files<br>
```-f``` is folder, where should be stored copies<br>
Also there is optional argument ```-c ```<br>
Remove files from ```-w``` after they are copied to ```-f```<br>
