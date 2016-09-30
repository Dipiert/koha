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
 my $tipo = $query->param('tipo');
 my $nro = $query->param('nro');
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


   my $mfn = GetMFN($nro);	 
   my $dat = GetBiblioData($mfn);

    my $userenv = C4::Context->userenv();
    my $usernumber = (ref($userenv) eq 'HASH') ? $userenv->{'number'} : 0;
    my $ss =  $usernumber;
    my $nro_usuario = PutListado($usernumber,$mfn,$nro,$dat->{title});	

my ($cnt,$dt) = GetListado($usernumber); 
 for($i = 0; $i < $cnt; $i++) {
   my %row = (biblionumber => $dt->[$i]->{'mfn'},
     title => $dt->[$i]->{'title'},
     autor => $dt->[$i]->{'author'},
     ubicacion => $dt->[$i]->{'lib'},
     notas => $dt->[$i]->{'itemnotes'},
     barcode => $dt->[$i]->{'barcode'});
   push(@listado, \%row);
 }

   $template->param(resultslistado     => \@listado);

output_html_with_http_headers $query, $cookie, $template->output;

