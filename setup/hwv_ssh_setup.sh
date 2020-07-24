# /bin/bash
function nl_error {
  echo "hwv_ssh_setup: $*" >&2
  exit 1
}

username=$1
shift 1
[ -n "$username" ] || nl_error "Must specify your QNX/OpenBSD username"
hosts=$*
[ -n "$hosts" ] || hosts="x40gse hwvgse"

sshdir=~/.ssh
if [ ! -d $sshdir ]; then
  mkdir $sshdir
fi

cd $sshdir
if [ ! -f id_rsa ]; then
  echo "Creating an SSH key in your .ssh directory"
  echo "Please specify a passphrase to secure the key"
  echo
  ssh-keygen -t rsa -b 4096
fi
if [ ! -f config ]; then
  echo "Create .ssh/config for user $username"
  for short in $hosts; do
    cat >>config <<EOF
host $short $short.arp.harvard.edu
hostname $short.arp.harvard.edu
user $username
ForwardAgent yes
ProxyJump ishi.arp.harvard.edu

host $short.direct
hostname $short.arp.harvard.edu
user $username
ForwardAgent yes

EOF
  done
fi

for short in ishi ishi2; do
cat >>config <<EOF
host $short $short.arp.harvard.edu
hostname $short.arp.harvard.edu
user $username
ForwardAgent yes

EOF
done

for host in ishi $hosts; do
  ssh-copy-id $host.arp.harvard.edu
  # cat $sshdir/id_rsa.pub | ssh $host.arp.harvard.edu /usr/local/sbin/add_auth_key.sh
done
