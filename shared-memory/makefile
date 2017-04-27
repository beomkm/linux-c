all : shm_pro.elf shm_con.elf

CC = clang

shm_pro.elf : shm_pro.c
	$(CC) shm_pro.c -o shm_pro.elf -std=gnu99 -lpthread

shm_con.elf : shm_con.c
	$(CC) shm_con.c -o shm_con.elf -std=gnu99 -lpthread
