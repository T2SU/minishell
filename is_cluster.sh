#!/bin/zsh
if [ $(hostname | grep -Eo "c\d{1,2}r\d{1,2}s\d{1,2}.42seoul.kr") ]
then
	# echo "You are in 42 Seoul Cluster!"
	return 1
	else
	# echo "You are not in 42 Seoul Cluster."
	return 0
fi
