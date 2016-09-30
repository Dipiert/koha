#!/usr/bin/perl

use warnings;
use strict;

use CGI;
use C4::Auth;
use C4::Output;
use C4::Visitas;
use C4::Context;
use Data::Dumper; 


my $templatename;
my $query = new CGI;
my $i;
my @codigos_postales;
my @grupos;
my @actividades;


 #Busco el nro de usuario
my $dni = $query->param('dni');
my $borrowernumber = Getvisitante($dni);

my ($nombre,$apellido) =datosvisitante($borrowernumber);
 if ($borrowernumber == 0){
   $templatename = "visitas-nueva2.tt";
 }else{
   $templatename = "visitas-buscar.tt";
 }
 
my ($cnt,$dt) = actividades(); 
 for($i = 0; $i < $cnt; $i++) {
   my %row = (id => $dt->[$i]->{'id'},
     descripcion => $dt->[$i]->{'descripcion'});
   push(@actividades, \%row);
 }

 
 my ($count,$data) = CodigosPostales();
 my %p1 = (cp => 104,
     localidad => "..Otra Ubicación",
	 codigo => 0);
  push(@codigos_postales, \%p1);


 
 #agrega como primer localidad Posadas..pedido personal de Informes...
 my %p2 = (cp => 20,
     localidad => "Posadas",
	 codigo => 3300);
 push(@codigos_postales, \%p2);
	
 for($i = 0; $i < $count; $i++) {
   my %row = (cp => $data->[$i]->{'id'},
     localidad => $data->[$i]->{'descripcion'},
	 codigo => $data->[$i]->{'cp'});
   push(@codigos_postales, \%row);
 }


my ($count2,$data2) = Grupos();
 for($i = 0; $i < $count2; $i++) {
   my %row = (gp => $data2->[$i]->{'id'},
     tipo_grupo => $data2->[$i]->{'tipo_grupo'});
   push(@grupos, \%row);
 }

 my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
         template_name   => "visitas/".$templatename,
         query           => $query,
         type            => "intranet",
         authnotrequired => 0,
         debug           => 1,
     }
 );
my $check_BorrowerMandatoryField=C4::Context->preference("BorrowerMandatoryField");
my @field_check=split(/\|/,$check_BorrowerMandatoryField);
foreach (@field_check) {
	$template->param( "mandatory$_" => 1);    
}

if (foto($dni) > 0){
$template->param("picture"=> 1);
} 
$template->param(resultsloopcodigospostales     => \@codigos_postales);
$template->param(resultsgrupos     => \@grupos);
$template->param(resultsactividades     => \@actividades);
$template->param("borrowernumber"=> $borrowernumber);
$template->param("BorrowerMandatoryField"=> $check_BorrowerMandatoryField);
$template->param("check_member"=> 1);
$template->param("dni"=> $dni);
$template->param("nombre"=> $nombre);
$template->param("apellido"=> $apellido);
 output_html_with_http_headers $query, $cookie, $template->output;
