package LucyX::Analysis::WhitespaceTokenizer;

use 5.008003;

use Lucy;

# We can't use XSLoader here, because it doesn't find the dynamic library
# during testing. This makes it fall back to DynaLoader by calling
# DynaLoader::bootstrap_inherit. bootstrap_inherit then localizes @ISA, so the
# XS bootstrap code adding the Clownfish parent class to @ISA will have no
# effect.

BEGIN {
    our $VERSION = '0.1.0';
    $VERSION = eval $VERSION;

    require DynaLoader;
    our @ISA = qw(DynaLoader);
    bootstrap LucyX::Analysis::WhitespaceTokenizer;
}

1;

__END__


