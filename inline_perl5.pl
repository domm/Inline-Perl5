#!/usr/bin/env perl6

use v6;
use lib '.';
use Inline::Perl5;

my $i = p5_init_perl();
say $i.run('
use 5.10.0;

sub test {
    say time;
}

print "Hello world from Perl ";
5');
print 'It is now ';
$i.call('test');

$i.DESTROY;

# vim: ft=perl6
