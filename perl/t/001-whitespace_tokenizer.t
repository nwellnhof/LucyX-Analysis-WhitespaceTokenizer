use strict;
use warnings;

use Test::More tests => 3;
use Lucy::Test;

BEGIN { use_ok('LucyX::Analysis::WhitespaceTokenizer'); }

my $tokenizer = LucyX::Analysis::WhitespaceTokenizer->new;
my $other     = LucyX::Analysis::WhitespaceTokenizer->new;
ok( $other->equals($other), "Equals" );

my $tokens = $tokenizer->split("__  _this_\t_is_a_ \n _test__");
is_deeply( $tokens, [ qw(__ _this_ _is_a_ _test__) ], "split" );

