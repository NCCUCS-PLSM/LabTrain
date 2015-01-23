#makefile start!!!

# 最終要讀取的檔案名稱，若找不到會往下找。
# 先設CC的用意是為了以後的習慣？！
# -g: 將除錯資訊加入（for gdb?）
# -Wall: 顯示所有警告資訊
# -ansi: 使用ansi c 編碼

all: hello_PLSM
CC = gcc
CFLAGS = -g -Wall -ansi

hello_PLSM: dennis_hello.o
	$(CC) -o hello_PLSM dennis_hello.o
clean:
	rm -f dennis_hello.o hello_PLSM
