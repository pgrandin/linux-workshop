class linux-workshop {
    resources { "firewall":
        purge => true
    }
    Firewall {
        before  => Class['linux-workshop::post'],
        require => Class['linux-workshop::pre'],
    }
    class { ['linux-workshop::pre', 'linux-workshop::post']: }
    class { 'firewall': }
}
