#!/bin/bash
trap "/bin/rm -f /home/PhD/michael61112/TA/lab3_add/.clean_up.sh" 0
sleep 5
exec $COWAREHOME/common/bin/process_cleanup 16598 16598 > /dev/null 2>&1
