use 5.008003;
use strict;
use warnings;
use Clownfish::CFC::Perl::Build;
use File::Spec::Functions qw( catdir );

my @cf_base_path    = Clownfish::CFC::Perl::Build->cf_base_path;
my @cf_linker_flags = Clownfish::CFC::Perl::Build->cf_linker_flags('Lucy');

my $builder = Clownfish::CFC::Perl::Build->new(
    module_name        => 'LucyX::Analysis::WhitespaceTokenizer',
    dist_abstract      => 'Split input at whitespace',
    dist_author        => 'Nick Wellnhofer <wellnhofer@aevum.de>',
    dist_version       => '0.1.0',
    extra_linker_flags => [ @cf_linker_flags ],
    requires           => {
        'perl' => '5.8.3',
        'Lucy' => '0.3.0',
    },
    build_requires     => {
        'Clownfish::CFC::Perl::Build' => 0,
    },
    clownfish_params => {
        source  => [ catdir( @cf_base_path, 'core' ) ],
    },
);

$builder->create_build_script();

__END__
