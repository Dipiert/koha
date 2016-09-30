<ul id="action">
 [% UNLESS ( norequests ) %]
 [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
 [% IF Koha.Preference( 'RequestOnOpac' ) == 1 %]
 [% IF ( AllowOnShelfHolds OR ItemsIssued ) %]
 <li><a class="reserve" href="/cgi-bin/koha/opac-reserve.pl?biblionumber=[% biblionumber %]">Hacer reserva</a></li>
 [% END %]
 [% END %]
 [% END %]
 [% END %]
 <li><a class="print-large" href="#">Imprimir</a></li>
 [% IF Koha.Preference( 'virtualshelves' ) == 1 %]
 [% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && loggedinusername ) %]
 <li><a class="addtoshelf" href="/cgi-bin/koha/opac-addbybiblionumber.pl?biblionumber=[% biblionumber %]">Guardar en sus listas</a></li>
 [% END %]
 [% END %]
 [% IF Koha.Preference( 'opacbookbag' ) == 1 %]
 [% IF ( incart ) %]
 <li><a class="incart cart[% biblionumber %] addrecord" href="#">En su carrito</a> <a class="cartRemove cartR[% biblionumber %]" href="#">(remover)</a></li>
 [% ELSE %]
 <li><a class="addtocart cart[% biblionumber %] addrecord" href="#">Agregar a su carrito</a> <a style="display:none;" class="cartRemove cartR[% biblionumber %]" href="#">(remover)</a></li>
 [% END %]
 [% END %]
 [% IF ( OpacHighlightedWords && query_desc ) %]
 <li>
 <a href="#" class="highlight_toggle" id="highlight_toggle_off">De-resaltar</a>
 <a href="#" class="highlight_toggle" id="highlight_toggle_on">Resaltar</a>
 </li>
 [% END %]

 [% SET export_options = Koha.Preference('OpacExportOptions').split(',') %]
 [% IF export_options.size %]
 <li>
 <div id="export">
 <div class="dropdown">
 <a id="format" class="dropdown-toggle" data-toggle="dropdown" href="#">Guardar registro <b class="caret"></b></a>
 <ul class="dropdown-menu pull-right" role="menu" aria-labelledby="format">
 [% FOREACH option IN export_options %]
 [% IF option == 'dc' %]
 <li><a role="menuitem" href="#" data-toggle="modal" data-target="#exportModal_">Dublin Core</a></li>
 [% ELSE %]
 <li>
 <a role="menuitem" href="/cgi-bin/koha/opac-export.pl?op=export&amp;bib=[% biblionumber %]&amp;format=[% option %]">
 [% SWITCH option %] [% CASE 'bibtex' %]BIBTEX [% CASE 'endnote' %]EndNote [% CASE 'marcxml' %]MARCXML [% CASE 'marc8' %]MARC (no-Unicode/MARC-8) [% CASE 'utf8' %]MARC (Unicode/UTF-8) [% CASE 'marcstd' %]MARC (Unicode/UTF-8, estándar) [% CASE 'mods' %]MODS (XML) [% CASE 'ris' %]RIS [% CASE 'isbd' %]ISBD [% END %] </a>
 </li>
 [% END %]
 [% END %]
 </ul>
 </div>
 </div>
 </li>
 [% END %]

 [% IF ( OPACSearchForTitleIn ) %]
 <li>
 <div id="moresearches_menu">
 <div class="dropdown">
 <a id="furthersearches" class="dropdown-toggle" data-toggle="dropdown" href="#">Más búsquedas <b class="caret"></b></a>
 <ul class="dropdown-menu pull-right" role="menu" aria-labelledby="furthersearches">
 <li><a href="#" class="menu-inactive">Buscar para este título en:</a></li>
 [% OPACSearchForTitleIn %]
 </ul>
 </div>
 </div>
 </li>
 [% END %]
</ul>

<!-- Dublin Core Modal Form -->
<div class="modal hide" id="exportModal_" tabindex="-1" role="dialog" aria-labelledby="exportLabelexportModal_" aria-hidden="true">
 <div class="modal-header">
 <button type="button" class="closebtn" data-dismiss="modal" aria-hidden="true">&times;</button>
 <h3 class="modal-title" id="exportModalLabel">Exportando a Dublin Core...</h3>
 </div>
 <form method="get" action="/cgi-bin/koha/opac-export.pl">
 <div class="modal-body">
 <fieldset id="dc_fieldset">
 <input id="input-simple" type="radio" name="format" value="rdfdc">
 <label class="label_dc" for="input-simple">DC-RDF simple</label>
 <br>
 <input id="input-oai" type="radio" name="format" value="oaidc" checked>
 <label class="label_dc" for="input-oai">OAI-DC</label>
 <br>
 <input id="input-srw" type="radio" name="format" value="srwdc">
 <label class="label_dc" for="input-srw">SRW-DC</label>
 <br>
 <input type="hidden" name="op" value="export">
 <input type="hidden" name="bib" value="[% biblionumber %]">
 </fieldset>
 </div>
 <div class="modal-footer">
 <button type="submit" class="btn">Exportar</button>
 <button class="btn btn-link" data-dismiss="modal" aria-hidden="true">Cancelar</button>
 </div>
 </form>
</div>
