cmd_/home/fuck/study/pci-driver/modules.order := {   echo /home/fuck/study/pci-driver/drv.ko; :; } | awk '!x[$$0]++' - > /home/fuck/study/pci-driver/modules.order
