cmd_/home/fuck/study/cyclic-buffer/kern-files/Module.symvers := sed 's/ko$$/o/' /home/fuck/study/cyclic-buffer/kern-files/modules.order | scripts/mod/modpost -m -a  -o /home/fuck/study/cyclic-buffer/kern-files/Module.symvers -e -i Module.symvers   -T -
