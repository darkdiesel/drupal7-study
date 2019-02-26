#!/usr/bin/env bash

. /lib/lsb/init-functions

source /vagrant/configs/global.conf

echo "Updating packages list"
apt-get update > /dev/null 2>&1

sudo apt-get install -y build-essential > /dev/null 2>&1

log_begin_msg "Install dos2unix and fix sh files"
sudo apt-get install dos2unix > /dev/null 2>&1

sudo dos2unix /vagrant/scripts/*.sh  > /dev/null 2>&1
log_end_msg 0

chmod +x /vagrant/scripts/*.sh

chmod 777 /etc/default/locale
echo 'LANGUAGE=en_US.UTF-8' > /etc/default/locale
echo 'LC_ALL=en_US.UTF-8' >> /etc/default/locale
echo 'LANG=en_US.UTF-8' >> /etc/default/locale
echo 'LC_TYPE=en_US.UTF-8' >> /etc/default/locale
locale-gen en_US.UTF-8

/vagrant/scripts/apache2.sh
/vagrant/scripts/php5.sh
/vagrant/scripts/mysql.sh

if [ -d "/home/vagrant/data" ]; then
    if [ -f "/home/vagrant/data/db-backups/db.sql" ]; then
        sudo mysql -u${DBUSER} -p${DBPASSWORD} ${DBNAME} < /home/vagrant/data/db-backups/db.sql
    fi
fi

#if ! [ -L /var/www ]; then
#  rm -rf /var/www
#  sudo ln -fs /vagrant/project /var/www/vrbangers
#fi

sudo cp -R /vagrant/etc / > /dev/null 2>&1

/vagrant/scripts/composer.sh
/vagrant/scripts/mailcatcher.sh
/vagrant/scripts/phpmyadmin.sh

log_begin_msg "Configuring web servers"
sudo service apache2 stop > /dev/null 2>&1

sudo a2enconf server.conf > /dev/null 2>&1

sudo rm -rf /etc/apache2/sites-enabled/* > /dev/null 2>&1
sudo a2ensite masalskiandrei.conf > /dev/null 2>&1
sudo a2ensite pma.conf > /dev/null 2>&1
sudo a2ensite mailcatcher.conf > /dev/null 2>&1


sudo a2enmod rewrite > /dev/null 2>&1
sudo a2enmod expires > /dev/null 2>&1
sudo a2enmod headers > /dev/null 2>&1
sudo a2enmod ssl > /dev/null 2>&1
sudo a2enmod proxy > /dev/null 2>&1
sudo a2enmod proxy_http > /dev/null 2>&1

sudo a2enmod proxy_ajp > /dev/null 2>&1
sudo a2enmod proxy_balancer > /dev/null 2>&1
sudo a2enmod proxy_connect > /dev/null 2>&1
sudo a2enmod proxy_html > /dev/null 2>&1

sudo service apache2 start > /dev/null 2>&1
sudo service mysql restart > /dev/null 2>&1
sudo chmod 777 -R /var/log/apache2/ > /dev/null 2>&1
log_end_msg 0

log_success_msg "Project server has been installed"