#!/usr/bin/perl

use warnings;
use strict;

use CGI;
use C4::Auth;
use C4::Output;
use C4::Visitas;


my $fechavenc;
my $tipo;
my $afiliado; 
my $idvisita = 0;
my $query = new CGI;

#Parametros
#my $salida="";
#my @names = $query->param;
#foreach my $name(@names){
#    $salida .= $name."\n";
#}
#die $salida;

my $dni = "";
my $nombre = "";
my $apellido = "";
my $cp = "";
my $email = "";
my $direccion = "";
my $barrio = "";
my $tipovisita = "";
my $cantpersonas = "";
my $borrowernumber = "";
my $localidad = "";
my $responsable = "";
my $input = new CGI;
my @arrtemp;

$dni = $query->param('cardnumber');
$nombre = $query->param('firstname');
$apellido = $query->param('surname');
$cp = $query->param('zipcode');
$email = $query->param('email');
$direccion = $query->param('address');
$barrio = $query->param('barrio');
$tipovisita = $query->param('tipovisita');
$cantpersonas = $query->param('cantpersonas');
$borrowernumber = $query->param('borrowernumber');
$responsable = $query->param('responsable');


my $nombreestablecimiento = " ";
my $grado = " ";
my $telefono = " ";
my $correoelectronico = " ";
my $id_tgrupo = 0;
my $direcc = " ";

$nombreestablecimiento = $query->param('nombreestablecimiento');
$grado = $query->param('grado');
$telefono = $query->param('telefono');
$localidad = $query->param('cp');
$correoelectronico = $query->param('correoelectronico');

$direcc = $query->param('direcc');
$id_tgrupo = $query->param('grupos');

my $obs = $query->param('obs');

#agregar los inputs param

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
         template_name   => "visitas/visitas-agregar.tt",
         query           => $query,
         type            => "intranet",
         authnotrequired => 0,
         debug           => 1,
     }
 );

# $borrowernumber = "362";
 if ($borrowernumber eq "0"){
  $borrowernumber = PutUsuario($dni,$nombre,$apellido,$cp,$email,$barrio,$direccion);
 }
  $idvisita = PutVisita($borrowernumber,$tipovisita,$cantpersonas,$obs,$nombreestablecimiento,$telefono,$localidad,$correoelectronico,$grado, $id_tgrupo, $direcc,$responsable);
if ($tipovisita=="GD"){
    my @dnigd = $query->param('dnigd[]');
    my @localidadgd = $query->param("localidadgd[]");
    my @direcciongd = $query->param("direcciongd[]"); 
    for (my $i=0;$i<$cantpersonas;$i++){
        PutGrupalDetallada($idvisita,$dnigd[$i],$localidadgd[$i],$direcciongd[$i]);
    }
}
my $i;
$i = 0;
	my @perms = $input->param('act');
        foreach my $perm (@perms) {
    		my ($idactividad, $sub_perm) = split /:/, $perm, 2;
            my $consulta = PutActividad($idvisita,$idactividad);
            @arrtemp[$i] = $idactividad;
            $i++;
    }


$template->param("id"=> $idvisita);

 output_html_with_http_headers $query, $cookie, $template->output;


