#!/usr/bin/perl

# file: fnsOutputChecker.pl
# last name: Erle
# first name: Mark
# LU email: mae5@lehigh.edu

# $ARGV[0] is file to be scanned
# $ARGV[1] is number of children

use strict;
use warnings;

if ($#ARGV < 1) {
  print "\nUsage example: $0 output 8\n";
  print "\n  where 8 is value of NUMCHILDREN and output is file produced as follows:\n";
  print "\n    fns 2>&1 | tee output\n\n";
  exit(0);
}

my $score = 0;
my $numChildren = $ARGV[1];
my $installing = 0;
my $sending = 0;
my $caught = 0;
my $normally = 0;
my $abnormally = 0;

open(IN, "<$ARGV[0]") || die("Can't open $ARGV[0] for reading - $!");
while (<IN>) {
  if      (/Parent process installing signal handlers/i) {
    $installing++;
  } elsif (/Child process \d+ sending SIG\w+ to parent/i) {
    $sending++;
  } elsif (/Parent process caught SIG\w+/i) {
    $caught++;
  } elsif (/Child process \d+ terminated normally with exit status \d+/i) {
    $normally++;
  } elsif (/Child process \d+ terminated abnormally/i) {
    $abnormally++;
  }
}
close(IN);

print "installing = $installing\n";
print "sending    = $sending\n";
print "caught     = $caught\n";
print "normally   = $normally\n";
print "abnormally = $abnormally\n";

if ($installing == 1) {
  $score += 5;
} elsif ($installing > 1) {
  $score += 2.5;
}
if ($sending == $numChildren) {
  $score += 5;
} elsif ($sending > 0) {
  $score += 2.5;
}
if ($caught == $numChildren) {
  $score += 5;
} elsif ($caught > 0) {
  $score += 2.5;
}
if ($normally == $numChildren) {
  $score += 5;
} elsif ($normally > 0) {
  $score += 2.5;
}
if ($abnormally == 0) {
  $score += 5;
}
print "---------------\n";
print "sub-score  = $score\n";

exit($score);
