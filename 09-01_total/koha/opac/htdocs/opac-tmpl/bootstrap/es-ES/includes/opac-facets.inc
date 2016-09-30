[% IF ( opacfacets && facets_loop && total ) %]
 <div id="search-facets">
 <h4><a href="#" class="menu-collapse-toggle">Refinar su búsqueda</a></h4>
 <ul class="menu-collapse">
 <li id="availability_facet">Disponibilidad: <ul>
 <li>
 [% IF ( available ) %]
 <strong>Mostrar ítems actualmente disponibles</strong></li><li><a href="/cgi-bin/koha/opac-search.pl?[% query_cgi %][% limit_cgi_not_availablity %][% IF ( sort_by ) %]&amp;sort_by=[% sort_by |url %][% END %]">Mostrar todos los ítems:</a>
 [% ELSE %]
 <a href="/cgi-bin/koha/opac-search.pl?[% query_cgi %][% limit_cgi |url %][% IF ( sort_by ) %]&amp;sort_by=[% sort_by |url %][% END %]&amp;limit=available">Limitar a ítems actualmente disponibles.</a>
 [% END %]
 </li>
 </ul>
 [% IF ( related ) %] <li>(búsquedas relacionadas: [% FOREACH relate IN related %][% relate.related_search %][% END %])</li>[% END %]
 </li>

 [% FOREACH facets_loo IN facets_loop %]
 [% IF facets_loo.facets.size > 0 %]
 <li id="[% facets_loo.type_id %]">
 [% IF facets_loo.type_label_Authors %]<h5 id="facet-authors">Autores</h5>[% END %]
 [% IF facets_loo.type_label_Titles %]<h5 id="facet-titles">Títulos</h5>[% END %]
 [% IF facets_loo.type_label_Topics %]<h5 id="facet-topics">Tópicos</h5>[% END %]
 [% IF facets_loo.type_label_Places %]<h5 id="facet-places">Lugares</h5>[% END %]
 [% IF facets_loo.type_label_Series %]<h5 id="facet-series">Series</h5>[% END %]
 [% IF facets_loo.type_label_ItemTypes %]<h5 id="facet-itemtypes">Tipos de ítem</h5>[% END %]
 [% UNLESS singleBranchMode %]
 [% IF ( facets_loo.type_label_HomeLibrary ) %]<span id="facet-home-libraries">Bibliotecas de origen</span>[% END %]
 [% IF ( facets_loo.type_label_HoldingLibrary ) %]<span id="facet-holding-libraries">Bibliotecas depositarias</span>[% END %]
 [% END %]
 [% IF facets_loo.type_label_Location %]<h5 id="facet-locations">Ubicaciones</h5>[% END %]
 <ul>
 [% SET url = "/cgi-bin/koha/opac-search.pl?" _ query_cgi _ limit_cgi %]
 [% IF ( sort_by ) %]
 [% url = BLOCK %][% url %][% "&amp;sort_by=" _ sort_by |url %][% END %]
 [% END %]
 [% FOREACH facet IN facets_loo.facets %]
 <li>
 [% IF facet.active %]
 [% SET local_url = url _ "&amp;nolimit=" _ facet.type_link_value _ ":" _ facet.facet_link_value %]
 <span class="facet-label">[% facet.facet_label_value %]</span>
 [<a href="[% local_url %]" title="Eliminar faceta [% facet.facet_link_value | html %]">x</a>]
 [% ELSE %]
 [% SET local_url = url _ "&amp;limit=" _ facet.type_link_value _ ":" _ facet.facet_link_value %]
 <span class="facet-label"><a href="[% local_url %]" title="[% facet.facet_title_value |html %]">[% facet.facet_label_value %]</a></span>
 [% IF ( displayFacetCount ) %]
 <span class="facet-count"> ([% facet.facet_count %])</span>
 [% END %]
 [% END %]
 </li>
 [% END %]
 [% IF ( facets_loo.expandable ) %]
 <li class="showmore">
 <a href="[% url %][% IF offset %]&amp;offset=[% offset |url %][% END %]&amp;expand=[% facets_loo.expand |url %]#[% facets_loo.type_id |url %]">Mostar más</a>
 </li>
 [% END %]
 </ul>
 </li>
 [% END # / IF facets_loo.facets.size > 0 %]
 [% END # / FOREACH facets_loo  %]
 </ul>
 </div> <!-- / #search-facets -->

 [% IF ( OPACResultsSidebar ) %]
 <div id="opacresultssidebar">
 [% OPACResultsSidebar %]
 </div>
 [% END %]
[% END # / IF opacfacets && facets_loop %]
