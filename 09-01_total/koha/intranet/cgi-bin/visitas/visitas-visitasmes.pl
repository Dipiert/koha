#!/usr/bin/perl

use warnings;
use strict;

use CGI;
use Data::Dumper; 
use C4::Auth;
use C4::Output;
use C4::Visitas;

my $query = new CGI;
my @resultsdata;
my @resultsdata2;
my $i;
my $total;

	my $seg;
	my $min;
	my $hora;
	my $dia;
	my $mes;
	my $anho;

	($seg, $min, $hora, $dia, $mes, $anho) = localtime(time);
	$mes++;
	$anho+=1900;
	my $fecha_actual= "$dia/$mes/$anho";
my $m = $query->param('m');
if ($m == ''){
  if ($mes < 10 ){
	$m = "0".$mes;
  }else{
	$m = $mes;
  }

	
}
my ($count,$data) = VisitasMes($m);
for($i = 0; $i < $count; $i++) {
  my %row = (tipo => $data->[$i]->{'tipo'},
    cantidad => $data->[$i]->{'cantidad'});
    $total = $total + $data->[$i]->{'cantidad'};
  push(@resultsdata2, \%row);
}

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
         template_name   => "visitas/visitas-visitasmes.tt",
         query           => $query,
         type            => "intranet",
         authnotrequired => 0,
         debug           => 1,
     }
 );

$template->param( 
        numresults      => $total,
	resultsloopmes     => \@resultsdata2,
	fecha		=>  $fecha_actual,
	mes		=>  Mes($m),
            );
 output_html_with_http_headers $query, $cookie, $template->output;
