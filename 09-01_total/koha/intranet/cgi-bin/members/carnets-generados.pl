#!/usr/bin/perl

# This file is part of Koha.
#
# Koha is free software; you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# Koha is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# Koha; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
# Suite 330, Boston, MA  02111-1307 USA
#!/usr/bin/perl

use warnings;
use strict;
use CGI;
use C4::Context;
use C4::Auth;
use C4::Output;
use C4::Members;
use C4::Members::Attributes;
use C4::Dates;
use C4::Reserves;
use C4::Circulation;
use C4::Koha;
use C4::Letters;
use C4::Biblio;
use C4::Reserves;
use C4::Branch; # GetBranchName
use C4::Transaccion;

my $dbh = C4::Context->dbh;
my $input = new CGI;
my $query = new CGI;

my $i;
$i = 0;

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
     {
         template_name   => "members/carnets-generados.tt",
         query           => $query,
         type            => "intranet",
         authnotrequired => 0,
         debug           => 1,
     }
 );


	my @perms = $input->param('bor');
        foreach my $perm (@perms) {
    	    my ($borrowernumber, $sub_perm) = split /:/, $perm, 2;
            #my $consulta = SumarCarnet($borrowernumber);
            #my $consulta = CarnetCreado($borrowernumber);
            SumarCarnet($borrowernumber);
	    CarnetCreado($borrowernumber);
	    $i++;
    }



 output_html_with_http_headers $query, $cookie, $template->output;


