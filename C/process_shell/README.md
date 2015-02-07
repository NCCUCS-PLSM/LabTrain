#C Practice III - Process & Shell
This practice has following objective:
* To be familiar with file operations in UNIX-like environment.
* To understand how a shell is implemented.

	Shell 指的就是命令提示字元、終端機的那個程式，電腦啟動以後，經過一連串的開機與系統載入過程(可以參考<鳥哥的LINUX私房菜 基礎學習篇>)，最終進入作業系統可用的 user interface 就是 Shell，早期的電腦其實是沒有 GUI，只有靠輸入命令來與電腦做互動，接收輸入命令的程式就是 Shell，Shell 其實也是一支程式，也就是一個 shell.c 這樣的檔案，編譯後產生 shell 這個程式，作業系統啟動最後就去執行 shell，shell 中至少有個這樣的演算法:
	
	```
	 while(1){ 
	 	puts("$"); 
	 	command = getchar();
	 }
	```
	如此就是你啟動命令提示字元或終端機後看到一直停在那邊等你輸入指令的畫面了。
	
* To understand how APIs are implemented.

	在作業系統中，不論是 UNIX、Linux、Windows 或 OS X 等作業系統，都有內建一些由組合語言或 C 語言(或這個作業系統客製的程式語言，如 Objective-C) 的函式庫，你可以試著在 UNIX/Linux 或 OS X 的終端機輸入 `man getc`：
	```	
	GETC(3)            BSD Library Functions Manual             GETC(3)

	NAME
     fgetc, getc, getc_unlocked, getchar, getchar_unlocked, getw -- get next
     character or word from input stream

	LIBRARY
     Standard C Library (libc, -lc)

	SYNOPSIS
     #include <stdio.h>

     int
     fgetc(FILE *stream);

     int
     getc(FILE *stream);

     int
     getc_unlocked(FILE *stream);

	   ...	
	```
	這個訊息就是說這個版本的 Linux 上有實作標準 C 語言函式庫的 stdio.h 這個標頭檔的 getc() 這個函式，因此你可以安裝 C compiler 後直接使用 stdio.h 並且呼叫 getc() 這個函式，這其實就是我們在作業系統課程中學到，作業系統提供應用程式開發者進行系統呼叫 System Call 的應用程式開發介面(Application Programming Interface, API)。
	
	然而其實程式就是一個 function，shell 的命令其實也是一個 function 或 program，例如我們在命令提示字元或終端機輸入的 ls 或 clear 指令，都是一個函式或程式，Shell 程式接收 user 輸入的指令後，會去判斷是要執行哪個函式或程式。
	
	Shell 的指令分成 builtin command 和 external command：
	
	* Builtin command: 又稱為 internal command，顧名思義，就是和 shell 主程式寫在一起的命令(寫在 shell.c 或在 shell.c 中 include 一起編譯)，exit 和 cd 就是兩個典型的 builtin command，exit 就跟程式碼中呼叫 exit(1) 一樣，會把 process 自己砍掉，cd 等等會說會什麼是。
	* 後者則是利用 exec*() (標準 C 定義了 6 種不同執行外部程式的 exec 函式)，來執行外部程式，ls 就是一個外部程式，shell 會呼叫 ls 這個程式，ls 中大概就是用到了標準 C 中 dirent.h 的 opendir()、readdir() 和 closedir()。
		
	當 shell 接收到使用者輸入，判斷是要執行外部指令時，shell 就會呼叫 fork() 產生一個新的 process 去呼叫 exec\*() 來執行外部指令，為什麼要用到 fork() 呢？因為當程式呼叫了 exec\*() 成功後，這個程式的記憶體空間就會被新的(你用 exec\*() 執行的程式的) process 給取代了，如果是由 shell 自己的 process 呼叫 exec*()，那一執行完外部指令你就沒辦法再做其他事情了，這在 UNIX 或 server 版本的 Linux 而言可是只能重開機的悲劇。

	為什麼要分成內建指令和外部指令牽涉到了 Process 的管理，簡單來說就是每個程式執行以後的 process 會有自己的記憶體空間，這個記憶體空間記錄的程式執行的基本資訊，例如『所在目錄』(例如你在 Desktop 執行一個 phonebook 的程式，執行以後 OS 會在 phonebook 的記憶體空間記錄他的位置在 `\User\<name>\Desktop`)，試想如果 cd 指令做成外部命令，那麼 shell 執行 cd 以後，因為會進行所在位置改寫的程式是 cd 不是 shell，因此 OS 改變的只是 cd 的位置，你用 pwd 看就會發現怎麼還是在同一個目錄下，還有就是像 exit 這個指令是用來終結 process，如果呼叫一個外部程式叫做 exit，exit 會呼叫 exit()，那就只是把 exit 這個程式的 process 砍掉，shell 還在。
	
	至於 ls 這個指令好像可以也做成 builtin command，此時就要思考『盡可能做成外部指令』的問題了，因為如果『好像做成內外部指令都可以』的指令都做成內部指令，則一來 shell 程式碼可能會很長(如果你試著寫 ls 的完整功能，會發現其實要考慮的 case 很多很複雜)，另一方面是如果你正在用 shell，但是你修改了 ls 的程式碼，就必須將整個 shell.c 重新編譯過一遍，浪費不必要的時間，因此在決定哪些指令要做成內建指令時，是採取『盡可能做成外部指令』的思考方向。
	
	Reference:<br>
	1. Wikipedia: [Shell Builtin Command](https://zh.wikipedia.org/wiki/%E6%AE%BC%E5%B1%A4%E5%85%A7%E5%BB%BA%E6%8C%87%E4%BB%A4)<br>
	2.  推薦買一本的讀物：[\<Advanced Programming in UNIX>](http://www.apuebook.com/)<br>
	3. [Bash builtin command](https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html)
	

#Assignments and Requirements
1. 請實作一個簡單的 shell 和兩個內建指令 (不能使用 system() 去執行這兩個指令)
	* find - 在指定的檔案或資料夾中所有的檔案尋找關鍵字

	```
	find keyword target
		keyword : the word you want to find
		target : the target file or directory
	```

	例如在現行目錄下的 hello.txt 第 7 行的第 11~15 個字母分別是 w, o, r, l, d，則：
	```
	find world .
		In hello.txt Line 7 : Char  11~15
	```

2.  除了上述兩個指令外，你個程式要能夠執行其他原本 shell 可以執行的命令或功能，請另外寫一個 hello_world.c，並確認你的 shell 可以執行它，請使用以下兩個函式實作，不可以直接使用 system() 去呼叫
    * fork()
    * exec() – 6 variations, you can use any one.

3. 編譯出來以後的執行檔請命名為 <你英文名字的第一個字母>sh，例如 Veck 的 shell 應為 vsh，執行以後只顯示 『(O-O)』等待使用者輸入命令：
```
~$ ./vsh
(O-O) find world .
In hello.txt Line 7 : Char  11~15
(O-O) ./hello
hello world!!!
(O-O) exit
~$
```

* NOTICE: 請確保你的程式可以在 Linux 上執行。

Deadline: 2015/02/21