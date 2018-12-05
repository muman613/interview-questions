#!/usr/bin/perl
###############################################################################
#   Generate Histogram of letter frequency
#   By Michael Uman 12/4/2018
###############################################################################

# ./q1.pl "Mississippi borders Tennessee." 
# s        #######
# e        #####
# i        ####
# n        ##
#          ##
# r        ##
# p        ##
# d        #
# T        #
# .        #
# b        #
# M        #
# o        #

# Make sure user passed correct # of arguments
my $argcnt = $#ARGV+1;
if ($argcnt != 1) {
    print "Invalid arguments\n";
    exit;
}

my $sentence = $ARGV[0];

# Iterate through sentence accumulating count of letters.
foreach $char (split('', $sentence)) {
  $accum{$char}++;
}

# Display histogram
foreach my $name (sort { $accum{$b} <=> $accum{$a} } keys %accum) {
    my $cnt = $accum{$name};
    my $bar = "";

    for (my $i = 0 ; $i < $cnt ; $i++) {
        $bar = $bar . "#";
    }
    printf "%-8s %s\n", $name, $bar;
}