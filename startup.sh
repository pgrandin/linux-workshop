apt-get install puppet-common
apt-get install -y git fluxbox xterm wireshark vnc4server gcc
wget https://raw.githubusercontent.com/pgrandin/linux-workshop/master/demo.c -O /usr/src/
gcc -o /usr/local/bin/workshop-server /usr/src/demo.c
rm /usr/src/demo.c
wget https://raw.githubusercontent.com/pgrandin/linux-workshop/master/loader.c -O /usr/src/
gcc -o /usr/local/bin/devcon02 /usr/src/test2.c -lm
rm /usr/src/test2.c
[ -d /etc/puppet/modules/ ] || mkdir /etc/puppet/modules/
git clone https://github.com/pgrandin/linux-workshop.git /etc/puppet/modules/
puppet module install puppetlabs/firewall
puppet apply /etc/puppet/modules/linux-workshop/nodes.pp
