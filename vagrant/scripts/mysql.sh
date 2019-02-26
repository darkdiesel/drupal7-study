#!/usr/bin/env bash

. /lib/lsb/init-functions

source /vagrant/configs/global.conf

log_begin_msg "Installing MySql"
sudo debconf-set-selections <<< "mysql-server mysql-server/root_password password ${DBPASSWORD}"
sudo debconf-set-selections <<< "mysql-server mysql-server/root_password_again password ${DBPASSWORD}"
sudo apt-get install -y mysql-server-5.6 php5-mysql > /dev/null 2>&1
sudo mysql -u${DBUSER} -p${DBPASSWORD} -e "CREATE DATABASE ${DBNAME} CHARACTER SET utf8 COLLATE utf8_general_ci;"



log_end_msg 0