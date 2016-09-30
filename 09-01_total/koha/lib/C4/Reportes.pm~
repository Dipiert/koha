package C4::Reportes;

use strict;
use C4::Context;
use C4::Members;

use C4::Dates qw(format_date_in_iso);
use Digest::MD5 qw(md5_base64);
use Date::Calc qw/Today Add_Delta_YM/;
use DBI;
use Data::Dumper; 
use C4::Log; # logaction
use C4::Overdues;
use C4::Reserves;
use C4::Accounts;
use C4::Biblio;

our ($VERSION,@ISA,@EXPORT,@EXPORT_OK,$debug);
BEGIN {
	$VERSION = 3.02;
	$debug = $ENV{DEBUG} || 0;
	require Exporter;
	@ISA = qw(Exporter);
	#Get data
    push @EXPORT, qw(GetUsuariosStaff);
    push @EXPORT, qw(GetReportes);
    push @EXPORT, qw(GetUsuariosReportes);
    push @EXPORT, qw(PutUsuarioReporte);
    push @EXPORT, qw(RemoveUsuarioReporte);
    push @EXPORT, qw(CrearReporte);
    push @EXPORT, qw(GetCarnets);    
}
sub CrearReporte {
	my $dbh   = C4::Context->dbh;
    my ($nombre,$archivo) = @_;
    my $query = "";
    my $count;
    my @data;	
    
    $query = "INSERT into reportes (nombrereporte,label) VALUES (?,?)";
    my $sth = $dbh->prepare($query);
	$sth->execute($nombre,$archivo);
	$sth->finish;
	return 1;
	
}


sub GetUsuariosStaff {
    my $dbh   = C4::Context->dbh;
    my $query = "";
    my $count;
    my @data;
    my @bind = ();
	 $query = "SELECT borrowernumber,cardnumber,concat(surname,' ',firstname) as nombre FROM `borrowers` where categorycode = 'S' order by surname";
	 my $sth = $dbh->prepare($query);
	 $sth->execute();
	my $data = $sth->fetchall_arrayref({});
    if (@$data){
        return ( scalar(@$data), $data );
    }
    $sth->finish;
}

sub GetReportes {
    my $dbh   = C4::Context->dbh;
    my $query = "";
    my $count;
    my @data;
    my @bind = ();
	 $query = "SELECT idreporte,label,nombrereporte FROM `reportes` ORDER BY label";
	 my $sth = $dbh->prepare($query);
	 $sth->execute();
	my $data = $sth->fetchall_arrayref({});
    if (@$data){
        return ( scalar(@$data), $data );
    }
    $sth->finish;
}

sub GetUsuariosReportes {
	my $dbh   = C4::Context->dbh;
    my ($idusuario) = @_;
    my $query = "";
    my $count;
    my @data;
    my @bind = ();
	$query = "SELECT idreporte FROM `borrowersxreporte` where borrowernumber = ?";

	my $sth = $dbh->prepare($query);
	$sth->execute($idusuario);
	my $data = $sth->fetchall_arrayref({});
    if (@$data){
        return ( scalar(@$data), $data );
    }
    

    $sth->finish;

   
}

sub PutUsuarioReporte {
	my $dbh   = C4::Context->dbh;
	my ( $idusuario, $idreporte ) = @_;
	my $query = "";
	my $cantidad = 0;
	 $query = "select count(*) as cantidad from borrowersxreporte where borrowernumber = $idusuario and idreporte = $idreporte";
	 my $sth = $dbh->prepare($query);
	 $sth->execute();
	 my $data = $sth->fetchall_arrayref({});
	 if (@$data){
        $cantidad =  $data->[0]->{'cantidad'};
        if ($cantidad < 1)
        {
        	$query = "insert into borrowersxreporte values (?,?)";
        	my $sth2 = $dbh->prepare($query);
	 		$sth2->execute($idusuario,$idreporte);
	 		$sth2->finish;
        	
        	
        }
    }
    
	return 1;
    $sth->finish;

}


sub RemoveUsuarioReporte{
	my $dbh   = C4::Context->dbh;
	my ( $idusuario, $idreporte ) = @_;
	my $query = "";
	
	 $query = "DELETE FROM  `borrowersxreporte` WHERE borrowernumber = ? and idreporte = ? ";
	 my $sth = $dbh->prepare($query);
	 $sth->execute($idusuario,$idreporte);
	 
	 $sth->finish;
	 
	 return 1;
} 

#Damian, 29/02/16 GetCarnets

sub GetCarnets{
#No recibe ningun paramétro
my $dbh   = C4::Context->dbh;
my $query = "";
$query = "SELECT borrowernumber, cardnumber, nombre, cantidadcarnet FROM `borrowers`";
my $sth = $dbh->prepare($query);
$sth->execute();
$sth->finish;
return 1;
}

return 1;
