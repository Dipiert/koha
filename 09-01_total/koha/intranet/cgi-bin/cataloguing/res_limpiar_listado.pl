#!/usr/bin/perl


# 
#
# 
#
use warnings;
use strict;

use CGI;
use C4::Auth;
use C4::Output;
#use C4::Visitas;
use C4::Context;
use C4::Biblio;
use C4::Items;


 my $query = new CGI;
 my $i;
 my $action = $query->param('action');
 my @listado;

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
	 template_name   => "cataloguing/listado.tt",
	 query           => $query,
	 type            => "intranet",
	 authnotrequired => 0,
	 debug           => 1,
     }
);


    my $userenv = C4::Context->userenv();
    my $usernumber = (ref($userenv) eq 'HASH') ? $userenv->{'number'} : 0;
    my $nro_usuario = PutLimpiarListado($usernumber);	


output_html_with_http_headers $query, $cookie, $template->output;

