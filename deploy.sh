#! /bin/sh

IP= '192.168.0.103'

scp apollo/core/hello root@$IP:~
scp apollo/remote/remote root@$IP:~
scp apollo/control/control root@$IP:~
scp start_up.sh root@$IP:~
