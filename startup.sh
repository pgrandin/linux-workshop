apt-get install puppet-common
apt-get install -y git fluxbox xterm wireshark vnc4server
[ -d /etc/puppet/modules/ ] || mkdir /etc/puppet/modules/
git clone https://github.com/pgrandin/linux-workshop.git /etc/puppet/modules/
puppet module install puppetlabs/firewall
puppet apply /etc/puppet/modules/linux-workshop/nodes.pp
