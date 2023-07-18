cmd_/home/fuck/study/pci-driver/drv.mod := printf '%s\n'   drv.o | awk '!x[$$0]++ { print("/home/fuck/study/pci-driver/"$$0) }' > /home/fuck/study/pci-driver/drv.mod
