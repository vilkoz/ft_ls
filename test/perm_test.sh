# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    perm_test.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 14:42:54 by vrybalko          #+#    #+#              #
#    Updated: 2017/03/10 15:30:13 by vrybalko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/zsh

rm -f file*;
touch file1 && chmod 0777 file1;
echo "ls";
ls -l file1;
echo "ft_ls";
../ft_ls -l file1;
echo "============="
touch file2 && chmod 1777 file2;
echo "ls";
ls -l file2;
echo "ft_ls";
../ft_ls -l file2;
echo "============="
touch file3 && chmod 2777 file3;
echo "ls";
ls -l file3;
echo "ft_ls";
../ft_ls -l file3;
echo "============="
touch file4 && chmod 3777 file4;
echo "ls";
ls -l file4;
echo "ft_ls";
../ft_ls -l file4;
echo "============="
touch file5 && chmod 4777 file5;
echo "ls";
ls -l file5;
echo "ft_ls";
../ft_ls -l file5;
echo "============="
touch file6 && chmod 5777 file6;
echo "ls";
ls -l file6;
echo "ft_ls";
../ft_ls -l file6;
echo "============="
touch file7 && chmod 6777 file7;
echo "ls";
ls -l file7;
echo "ft_ls";
../ft_ls -l file7;
echo "============="
touch file8 && chmod 7777 file8;
echo "ls";
ls -l file8;
echo "ft_ls";
../ft_ls -l file8;
echo "============="
touch file9 && chmod 0000 file9;
echo "ls";
ls -l file9;
echo "ft_ls";
../ft_ls -l file9;
echo "============="
touch file10 && chmod 1000 file10;
echo "ls";
ls -l file10;
echo "ft_ls";
../ft_ls -l file10;
echo "============="
touch file11 && chmod 2000 file11;
echo "ls";
ls -l file11;
echo "ft_ls";
../ft_ls -l file11;
echo "============="
touch file12 && chmod 3000 file12;
echo "ls";
ls -l file12;
echo "ft_ls";
../ft_ls -l file12;
echo "============="
touch file13 && chmod 4000 file13;
echo "ls";
ls -l file13;
echo "ft_ls";
../ft_ls -l file13;
echo "============="
touch file14 && chmod 5000 file14;
echo "ls";
ls -l file14;
echo "ft_ls";
../ft_ls -l file14;
echo "============="
touch file15 && chmod 6000 file15;
echo "ls";
ls -l file15;
echo "ft_ls";
../ft_ls -l file15;
echo "============="
touch file16 && chmod 7000 file16;
echo "ls";
ls -l file16;
echo "ft_ls";
../ft_ls -l file16;
echo "============="
rm -f file*;
