#!/usr/bin/perl
use strict;
use warnings;

use C4::Auth;
use Koha::AuthUtils;
use C4::Output;
use C4::Context;
use C4::Members;
use C4::Branch;
use C4::Circulation;
use CGI qw ( -utf8 );
use C4::Members::Attributes qw(GetBorrowerAttributes);

use Digest::MD5 qw(md5_base64);

my $input = new CGI;
my ( $template, $loggedinuser, $cookie, $staffflags ) = get_template_and_user(
    {
        template_name   => "members/mostrarImagen.tt",
	#template_name   => "members/member-password.tt",        
	query           => $input,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => { borrowers => 1 },
        debug           => 1,
    }
);
my $borrowernumber = $input->param('borrowernumber');
$template->param(borrowernumber => $borrowernumber);
output_html_with_http_headers $input, $cookie, $template->output;

