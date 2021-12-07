# ~/.bashrc: executed by bash(1) for non-login shells.

# Note: PS1 and umask are already set in /etc/profile. You should not
# need this unless you want different defaults for root.
# PS1='${debian_chroot:+($debian_chroot)}\h:\w\$ '
# umask 022

# You may uncomment the following lines if you want `ls' to be colorized:
# export LS_OPTIONS='--color=auto'
# eval "`dircolors`"
# alias ls='ls $LS_OPTIONS'
# alias ll='ls $LS_OPTIONS -l'
# alias l='ls $LS_OPTIONS -lA'
#
# Some more alias to avoid making mistakes:
# alias rm='rm -i'
# alias cp='cp -i'
# alias mv='mv -i'

ifdown eth0
ifconfig eth0 down
ifconfig eth0 hw ether 00:0a:35:00:01:28
ifconfig eth0 up
ifup eth0

#dhclient eth0
export http_proxy=http://ftn.proxy:8080
export https_proxy=https://ftn.proxy:8080
alias ll='ls -lah'
/init_drivers.sh
