#! /usr/bin/perl -w
use strict;
use Text::Wrap;

my $base = $ARGV[0] || 'dacsmread';
open(IF, "<", "$base.txt") ||
  die "Cannot locate input file '$base.txt'\n";
my @list = <IF>;
close(IF);
my %addr;
my %suffix;
my %rate;
my $line = 0;
for my $chan (@list) {
  ++$line;
  next if $chan =~ m,^\s*(?:/\*.*)$,; #Ignore comments, blanks
  if ( $chan =~ m,^\s* TM \s+ (\d+(?:/\d+)?) \s* Hz
              \s+ \S+ \s+ (\S+) \s*;\s*
              Address \s+ (\S+) \s+ (0x[A-F0-9]+) \s*;,x) {
    my $rate = $1;
    my $var = $2;
    my $var2 = $3;
    my $addr = $4;
    die "$line: Addressee ($var2) does not match definition ($var)\n"
      if $var ne $var2;
    die "$line: Address $addr already in use\n" if $addr{$addr};
    $rate{$rate} ||= [];
    $addr{$addr} = $var;
    push(@{$rate{$rate}}, $addr);
    if ($chan =~ m,#\s+(.*) #,) {
      $suffix{$addr} = " $1";
    } else {
      $suffix{$addr} = '';
    }
  } else {
    warn "$line: Invalid syntax: $chan";
  }
}

my @rates = sort keys %rate;
my @group;
my $group_idx = 0;
for my $rate (@rates) {
  my @coladdr = sort(@{$rate{$rate}});

  while (@coladdr) {
    ++$group_idx;
    my $group = "dacsmread_$group_idx";
    my @addrs = (@coladdr > 50) ?
      splice(@coladdr, 0, 50) : splice(@coladdr, 0);
    push(@group, { rate => $rate, group => $group, addrs => [ @addrs ] });
  }
}

open(OF, ">", "${base}_col.tmc") ||
  die "Unable to write to output file '${base}_col.tmc'\n";

print OF <<EOF;
%{
  #include "subbus.h"
  uint16_t dacsmread_buf[50];

EOF
for my $groupp (@group) {
  next if @{$groupp->{addrs}} == 1;
  my $group = $groupp->{group};
  print OF "  subbus_mread_req *$group;\n";
}
print OF "%}\n";

for my $groupp (@group) {
  next if @{$groupp->{addrs}} == 1;
  my $group = $groupp->{group};
  print OF wrap("TM INITFUNC $group = pack_mread_requests(", "    ",
    join ", ", map "$addr{$_}.address", @{$groupp->{addrs}}),
      ");\n";
}
close(OF) || warn "Error closing ${base}_col.tmc\n";

open(OF, ">", "${base}.tmc");
for my $groupp (@group) {
  next if @{$groupp->{addrs}} == 1;
  my $group = $groupp->{group};
  my @vars = map $addr{$_}, @{$groupp->{addrs}};
  my @sfx = map $suffix{$_}, @{$groupp->{addrs}};
  print OF "\n",
    wrap("Group $group (", "      ",
      join ", ", @vars),
    ") {\n",
    "  mread_subbus($group, dacsmread_buf);\n",
    map( "  $vars[$_] = dacsmread_buf[$_]$sfx[$_];\n",
      (0 .. $#vars)),
    "}\n";
}

close(OF) || warn "Error closing ${base}.tmc\n";
