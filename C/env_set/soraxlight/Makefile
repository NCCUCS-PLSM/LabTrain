
CC = gcc
CFLAGS = -ansi -pedantic -Wall
hello.exe : 
	$(CC) $(CFLAGS) -o hello.exe soraxlight_hello.c
clean :
	rm hello.exe

# make 會去執行編譯的動作，如果用 gcc 編譯，應該寫成：
# 	gcc [CFLAG] -o 產生可執行檔名 要編譯檔名
# 所以原本最後面寫 .o 不對，.o 是編譯過程的檔案
# 另外，第四行 hello.exe 建議寫成 all: 比較通用
# 還有 hello.exe，因為 exe 是 Windows 的執行檔名，在其他平台未必可執行
# 所以建議就寫成 hello.out 或 hello
