#!/usr/bin/perl
use warnings;
use strict;

use CGI;
use C4::Auth;
use C4::Output;
use C4::Visitas;
my $query = new CGI;
my $cantidad = $query->param('cantidad');
my $salida = "";

for(my $i=1;$i<=$cantidad;$i++){
    #$salida .= $query->param("dni$i");
    my $dni = $query->param("dni$i");
    my $localidad = $query->param("localidad$i");
    my $direccion = $query->param("direccion$i");
    #PutGrupalDetallada($dni,$localidad,$direccion);
}
#die $salida;

#my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
#     {
#         template_name   => "visitas/visitas-nueva2.tt",
#         query           => $query,
#         type            => "intranet",
#         authnotrequired => 0,
#         debug           => 1,
#     }
# );


#output_html_with_http_headers $query, $cookie, $template->output;

##############################################################


