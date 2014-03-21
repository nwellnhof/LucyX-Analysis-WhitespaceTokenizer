package Binding;
use strict;
use warnings;

our $VERSION = '0.01';
$VERSION = eval $VERSION;

sub bind_all {
    my $class = shift;

    my $xs_code = <<'END_XS_CODE';
MODULE = LucyX::Analysis::WhitespaceTokenizer    PACKAGE = LucyX::Analysis::WhitespaceTokenizer

BOOT:
    cfish_LucyX__Analysis__WhitespaceTokenizer_bootstrap();
END_XS_CODE

    my $pod_spec = Clownfish::CFC::Binding::Perl::Pod->new;
    my $synopsis = <<'END_SYNOPSIS';
    my $tokenizer = LucyX::Analysis::WhitespaceTokenizer->new;

    # Then... once you have a tokenizer, put it into a PolyAnalyzer:
    my $polyanalyzer = Lucy::Analysis::PolyAnalyzer->new(
        analyzers => [ $tokenizer, $normalizer, $stemmer ], );
END_SYNOPSIS
    my $constructor = <<'END_CONSTRUCTOR';
    my $tokenizer = LucyX::Analysis::WhitespaceTokenizer->new;
END_CONSTRUCTOR
    $pod_spec->set_synopsis($synopsis);
    $pod_spec->add_constructor( alias => 'new', sample => $constructor );

    my $binding = Clownfish::CFC::Binding::Perl::Class->new(
        parcel     => 'WhitespaceTokenizer',
        class_name => 'LucyX::Analysis::WhitespaceTokenizer',
    );
    $binding->append_xs($xs_code);
    $binding->set_pod_spec($pod_spec);

    Clownfish::CFC::Binding::Perl::Class->register($binding);
}


