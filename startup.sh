sudo apt-get install puppet-common
sudo puppet module install puppetlabs/firewall
sudo git clone https://github.com/pgrandin/linux-workshop.git /etc/puppet/modules/
sudo puppet apply /etc/puppet/modules/linux-workshop/nodes.pp
