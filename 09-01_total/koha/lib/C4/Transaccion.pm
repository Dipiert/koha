package C4::Transaccion;

use strict;
use C4::Context;
use C4::Members;

use C4::Dates qw(format_date_in_iso);
use Digest::MD5 qw(md5_base64);
use Date::Calc qw/Today Add_Delta_YM/;
use DBI;
use Data::Dumper; 
use C4::Log; # logaction
use C4::Accounts;
use C4::Biblio;

our ($VERSION,@ISA,@EXPORT,@EXPORT_OK,$debug);
BEGIN {
	$VERSION = 3.02;
	$debug = $ENV{DEBUG} || 0;
	require Exporter;
	@ISA = qw(Exporter);
	#Get data
    push @EXPORT, qw(GenerarTransaccion);
	push @EXPORT, qw(ObtenerIdTrans);
	push @EXPORT, qw(GetIdTemporalTransaccion);
	push @EXPORT, qw(ActualizarTemporalTransacciones);
 
}

#La idea es guardar en la bd la transaccion que se genera
#a partir de un prestamo en la tabla: tickets_circulacion


sub GenerarTransaccion {
	#parametros: operacion, borrowernumber, barcode
	my ( $operacion, $borrowernumber,$barcode ) = @_;

	my $dbh = C4::Context->dbh;
	my $query;
	my $query2;
	my $sth;
	my $row;
	my $id_trans = 0;
	
	my ($seg, $min, $hora, $dia, $mes, $anho) = localtime(time);
	$mes++;
	$anho+=1900;
	my $fecha_actual= "$anho-$mes-$dia";

	#devuelve el id de transaccion del usuario, 
	#si ya esta realizando prestamos
	$id_trans = GetIdTemporalTransaccion($borrowernumber);
	if( $id_trans == 0 ){
		$id_trans = ObtenerIdTrans();#idtransaccion = obtiene el numero para una nueva transaccion
	}
	
	if($id_trans > 0){
	#preparo los datos para insertar una nueva transaccion en tickets_circulacion
	$query = "INSERT INTO tickets_circulacion (idtransaccion, operacion, borrowernumber, barcode, fecha) 
		   VALUES (
			". $dbh->quote($id_trans).",
		    ". $dbh->quote($operacion).",
			". $dbh->quote($borrowernumber).",
			". $dbh->quote($barcode).",
			". $dbh->quote($fecha_actual)."
			) ";
	$query2 = "INSERT INTO temporal_tickets_circulacion (idtransaccion, borrowernumber, barcode) 
		   VALUES (
			". $dbh->quote($id_trans).",
			". $dbh->quote($borrowernumber).",
			". $dbh->quote($barcode)."
			) ";
			
			my $sth = $dbh->prepare($query);
			#guarda en la bd tickets_circulacion
			$sth->execute();
			$sth->finish;
			
			my $sth2 = $dbh->prepare($query2);
			#guarda en la bd temporal_tickets_circulacion
			$sth2->execute();
			$sth2->finish;
			
	}#en otro caso: no recupero el valor de id
	
	return $id_trans;

}

#devuelve el id de la transaccion actual que corresponde 
#a los prestamos realizados a un usuario. Si no encuentra el id
#significa que el usuario no tiene prestamos
sub GetIdTemporalTransaccion{ 
	my ( $borrowernumber ) = @_;
	my $dbh = C4::Context->dbh;
	my $query;
	my $sth;
	my $row;
	my $id_trans = 0;
	
	$sth = $dbh->prepare("SELECT idtransaccion FROM temporal_tickets_circulacion WHERE borrowernumber = ?");
	$sth->execute($borrowernumber);
	if($row = $sth->fetchrow_hashref){
		$id_trans = $row->{'idtransaccion'};
	}
	return $id_trans;
}

sub ObtenerIdTrans{

	my $dbh = C4::Context->dbh;
	my $sth;
	my $row;
	my $id_actual = 0;
	
	$sth = $dbh->prepare("SELECT id_transaccion FROM parametros_transaccion");
    $sth->execute();
	$row = $sth->fetchrow_hashref;
	$id_actual = $row->{'id_transaccion'};
	if($id_actual > 0){
			$id_actual = $id_actual + 1;
			$sth = $dbh->prepare("UPDATE parametros_transaccion SET id_transaccion = ? ");
			$sth->execute($id_actual);
	}
	return $id_actual;
}

#Agrega en tickets_circulacion la devolucion correspondiente 
#a un prestamo realizado por un usuario. Luego elimina el prestamo
#en temporal_tickets_circulacion
sub ActualizarTemporalTransacciones{
	my ( $barcode ) = @_;
	
	my $dbh = C4::Context->dbh;
	my $sth;
	my $sth_ins;
	my $sth_del;
	my $row;
	my $query;
	
	my ($seg, $min, $hora, $dia, $mes, $anho) = localtime(time);
	$mes++;
	$anho+=1900;
	my $fecha_actual= "$anho-$mes-$dia";
	
	if($barcode){
		#agrega la devolucion de un libro en tickets_circulacion correspondiente a un prestamo
		$sth = $dbh->prepare("SELECT * FROM temporal_tickets_circulacion WHERE barcode = ?");
		$sth->execute($barcode);
		$row = $sth->fetchrow_hashref;
		my $id_trans = $row->{'idtransaccion'};
		my $borrowernumber = $row->{'borrowernumber'};
		my $barcode = $row->{'barcode'};
		my $operacion = "devolucion";
		
		$query = "INSERT INTO tickets_circulacion (idtransaccion, operacion, borrowernumber, barcode, fecha) 
		   VALUES (
			". $dbh->quote($id_trans).",
		    ". $dbh->quote($operacion).",
			". $dbh->quote($borrowernumber).",
			". $dbh->quote($barcode).",
			". $dbh->quote($fecha_actual)."
			) ";
		$sth_ins = $dbh->prepare($query);
		$sth_ins->execute();
		$sth_ins->finish;
		
		#elimina de temporal_tickets_circulacion los prestamos realizados en el dia
		$sth_del = $dbh->prepare("DELETE FROM temporal_tickets_circulacion WHERE barcode = ?");
		$sth_del->execute($barcode);
	}
	
}

return 1;



