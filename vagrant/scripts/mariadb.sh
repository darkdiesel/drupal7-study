#!/usr/bin/env bash

. /lib/lsb/init-functions

source /vagrant/configs/global.conf

log_begin_msg "Installing MariaDB"
sudo apt-get install software-properties-common -y

# Import repo key
sudo apt-key adv --recv-keys --keyserver hkp://keyserver.ubuntu.com:80 0xcbcb082a1bb943db

# Add repo for MariaDB
sudo add-apt-repository "deb [arch=amd64,i386,ppc64el] http://mirrors.dotsrc.org/mariadb/repo/${MARIADB_VERSION}/ubuntu trusty main"

# Update
sudo apt-get update

# Install MariaDB without password prompt
# Set username to 'root' and password to 'mariadb_root_password' (see Vagrantfile)
sudo debconf-set-selections <<< "maria-db-${MARIADB_VERSION} mysql-server/root_password password ${DBPASSWORD}"
sudo debconf-set-selections <<< "maria-db-${MARIADB_VERSION} mysql-server/root_password_again password ${DBPASSWORD}"
#sudo debconf-set-selections <<< "mariadb-server mysql-server/root_password password ${DBPASSWORD}"
#sudo debconf-set-selections <<< "mariadb-server mysql-server/root_password_again password ${DBPASSWORD}"

sudo apt-get install -y mariadb-server php5-mysql > /dev/null 2>&1

sudo mysql -u${DBUSER} -p${DBPASSWORD} -e "CREATE DATABASE ${DBNAME} CHARACTER SET utf8 COLLATE utf8_general_ci;"
log_end_msg 0