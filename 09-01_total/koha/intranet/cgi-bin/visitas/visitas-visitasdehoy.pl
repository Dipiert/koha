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

my ($count,$data) = VisitasdeHoy();

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


for($i = 0; $i < $count; $i++) {
  my %row = (tipo => $data->[$i]->{'tipo'},
    cantidad => $data->[$i]->{'cantidad'});
  push(@resultsdata, \%row);
}

my ($count,$data) = VisitasdelMes();
for($i = 0; $i < $count; $i++) {
  my %row = (tipo => $data->[$i]->{'tipo'},
    cantidad => $data->[$i]->{'cantidad'});
  push(@resultsdata2, \%row);
}
my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
         template_name   => "visitas/visitas-visitasdehoy.tt",
         query           => $query,
         type            => "intranet",
         authnotrequired => 0,
         debug           => 1,
     }
 );
$template->param( 
        numresults      => $count,
        resultsloopdia     => \@resultsdata,
	resultsloopmes     => \@resultsdata2,
	fecha		=>  $fecha_actual,
            );
 output_html_with_http_headers $query, $cookie, $template->output;
