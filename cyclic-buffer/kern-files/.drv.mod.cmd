cmd_/home/fuck/study/cyclic-buffer/kern-files/drv.mod := printf '%s\n'   drv.o | awk '!x[$$0]++ { print("/home/fuck/study/cyclic-buffer/kern-files/"$$0) }' > /home/fuck/study/cyclic-buffer/kern-files/drv.mod
