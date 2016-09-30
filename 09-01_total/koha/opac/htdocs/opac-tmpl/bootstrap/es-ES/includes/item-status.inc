[% USE AuthorisedValues %] [% SET itemavailable = 1 %] [%#- Esta inclusión toma dos parámetros: una estructura de ítem y una estructura opcional de préstamo (emisión). La estructura de préstamo se utiliza por las páginas de reservas para cursos, que no utilizan una API para obtener los ítems que llenan item.datedue. -%] [% IF ( item.itemlost ) %] [% SET itemavailable = 0 %] [% av_lib_include = AuthorisedValues.GetByCode( 'LOST', item.itemlost, 1 ) %] [% IF ( av_lib_include ) %] <span class="item-status lost">[% av_lib_include %]</span>
 [% ELSE %]
 <span class="item-status lost">Ítem dañado</span>
 [% END %]
[% END %]

[% IF ( item.datedue || issue.date_due ) %]
 [% SET itemavailable = 0 %]
 [% IF item.onsite_checkout %]
 [% IF ( OPACShowCheckoutName ) %]
 <span class="item-status checkedout">Actualmente en uso local por [% item.firstname %] [% item.surname %] [% IF ( item.cardnumber ) %]([% item.cardnumber %])[% END %]</span>
 [% ELSE %]
 <span class="item-status checkedout">Actualmente en uso local</span>
 [% END %]
 [% ELSE %]
 [% IF ( OPACShowCheckoutName ) %]
 <span class="item-status checkedout">Prestado a [% item.firstname %] [% item.surname %] [% IF ( item.cardnumber ) %]([% item.cardnumber %])[% END %]</span>
 [% ELSE %]
 <span class="item-status checkedout">Prestado</span>
 [% END %]
 [% END %]
[% END %]

[% IF ( item.transfertwhen ) %]
 [% SET itemavailable = 0 %]
 <span class="item-status intransit">En tránsito de [% item.transfertfrom %] a [% item.transfertto %] desde [% item.transfertwhen | $KohaDates %]</span>
[% END %]

[% IF ( item.waiting ) %]
 [% SET itemavailable = 0 %]
 <span class="item-status onhold">Reservado</span>
[% END %]

[% IF ( item.withdrawn ) %]
 [% SET itemavailable = 0 %]
 <span class="item-status withdrawn">Ítem retirado</span>
[% END %]

[% IF ( item.itemnotforloan ) %]
 [% SET itemavailable = 0 %]
 [% IF ( item.notforloanvalueopac ) %]
 <span class="item-status notforloan">[% item.notforloanvalueopac %] [% IF ( item.restrictedopac ) %]<span class="restricted">([% item.restrictedopac %])</span>[% END %]</span>
 [% ELSE %]
 <span class="item-status notforloan">No para préstamo [% IF ( item.restrictedopac ) %]<span class="restricted">([% item.restrictedopac %])</span>[% END %]</span>
 [% END %]
[% ELSIF ( item.notforloan_per_itemtype ) %]
 [% SET itemavailable = 0 %]
 <span class="item-status notforloan">No para préstamo [% IF ( item.restrictedopac ) %]<span class="restricted">([% item.restrictedopac %])</span>[% END %]</span>
[% END %]

[% IF ( item.damaged ) %]
 [% SET itemavailable = 0 %]
 [% av_lib_include = AuthorisedValues.GetByCode( 'DAMAGED', item.damaged, 1 ) %]
 [% IF av_lib_include %]
 <span class="item-status damaged">[% av_lib_include %]</span>
 [% ELSE %]
 <span class="item-status damaged">Ítem dañado</span>
 [% END %]
[% END %]

[% IF item.on_order %]
 [% SET itemavailable = 0 %]
 <span class="item-status onorder">Pedido</span>
[% END %]

[% IF ( itemavailable ) %]
 <span class="item-status available">Disponible [% IF ( item.restrictedopac ) %]<span class="restricted">([% item.restrictedopac %])</span>[% END %]</span>
[% END %]
