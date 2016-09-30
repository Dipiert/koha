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

 my $tipo = $query->param('tipo');
 my $nro = $query->param('nro');
 my $action = $query->param('action');

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
	 template_name   => "cataloguing/buscar.tt",
	 query           => $query,
	 type            => "intranet",
	 authnotrequired => 0,
	 debug           => 1,
     }
);


if ($tipo eq '0') {
   my $mfn = GetMFN($nro);	 
   $template->param("biblionumber"=> $mfn);
   my $dat = GetBiblioData($mfn);
   $template->param("title"=> $dat->{title});
}else{
   $template->param("biblionumber"=> $nro);
   my $dat = GetBiblioData($nro);
   $template->param("title"=> $dat->{title});

}
output_html_with_http_headers $query, $cookie, $template->output;

