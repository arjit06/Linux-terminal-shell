maincode_execute: date mkdir ls rm cat 
	gcc -pthread -o maincode maincode.c
	./maincode

date: mkdir
	gcc -o date date.c

mkdir: ls
	gcc -o mkdir mkdir.c

ls: rm
	gcc -o ls ls.c

rm: cat
	gcc -o rm rm.c

cat:
	gcc -o cat.c

