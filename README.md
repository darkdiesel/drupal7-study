# Drupal 7 CMS Study

Site to study and testing drupal 7 CMS

Contains the files and information for the masalskiandrei.com website. 

### Vagrant installation ###
* [Check](#db-backups) db backup files before location  
* Install VirtualBox on you machine from. See [virtualbox.org](https://www.virtualbox.org/) for installation package.
* Vagrant Box init wih ubuntu/trusty64 box. Before start vagrant check for box last version `vagrant box update`
* Install plugin vagrant-vbguest `vagrant plugin install vagrant-vbguest`
* Run vagrant `vagrant up`
* Add to hosts `192.168.56.126  drupal7-study.loc www.drupal7-study.loc pma.drupal7-study.loc www.pma.drupal7-study.loc mailcatcher.drupal7-study.loc www.mailcatcher.drupal7-study.loc`
* Note! After installation complete [update](#update-db-links) db links.

#### Config
* Create copy of sites/default/default.settings.php with name settings.php
* Set db name, user, password, table prefix and other settings for db connections.

#### Db backups
* db backup files ignored by git 
* Create database backup and put it to `data/db-backups/` folder
* Rename db backup file to `db.sql`

#### Update db links
* Use searchreplacedb2.php for updating urls in db. Run this file in browser.
