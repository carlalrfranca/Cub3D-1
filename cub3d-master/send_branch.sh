#!/bin/bash

#--validate vars--
if [[ !$1 || !$2 ]];then
	echo "Error: No arguments. Try this:'what to do' 'branch name'."
	exit 1
fi
#--verify args--
if [[ $1 == "send" ]]; then
	git push origin $1
	exit 0
else if [[ $1 != "remove" ]]
	echo "Error: You can either 'send' or 'remove'. Please try again."
	exit 1
fi
#--verif merge--
name_branch=$(git branch | grep "*" | awk '{print $2}')
main_branch="main"
#--verify branch--
if [[ $name_branch -eq $main_branch ]]; then
#--remove branch--
	git pull
	git branch -d $1
else
	git checkout main
	git pull
	git branch -d $1
fi