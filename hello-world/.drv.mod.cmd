cmd_/home/fuck/study/hello-world/drv.mod := printf '%s\n'   drv.o | awk '!x[$$0]++ { print("/home/fuck/study/hello-world/"$$0) }' > /home/fuck/study/hello-world/drv.mod
