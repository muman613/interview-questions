#!/usr/bin/perl
###############################################################################
#   Sort hash of by length of last name, then by first name.
#   By Michael Uman 12/4/2018
###############################################################################

# ./q2.pl
# Mary Li
# Elizabeth Davis
# James O'Day
# Thomas Miller
# William Garcia

# Construct the hash/dictionary
$last_name{"Mary"} = "Li";
$last_name{"James"} = "O'Day";
$last_name{"Thomas"} = "Miller";
$last_name{"William"} = "Garcia";
$last_name{"Elizabeth"} = "Davis";

foreach my $name (sort { (length($last_name{$a}) cmp length($last_name{$b})) or ($a cmp $b) } keys %last_name) {
    my $ln = $last_name{$name};

    print "$name $ln\n";
}