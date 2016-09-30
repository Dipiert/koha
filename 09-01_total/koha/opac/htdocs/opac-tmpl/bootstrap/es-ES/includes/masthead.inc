[% USE Koha %]
[% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
<div id="wrap">
 <div id="header-region" class="noprint">
 <div class="navbar navbar-inverse navbar-static-top">
 <div class="navbar-inner">
 <div class="container-fluid">
 <h1 id="logo">
 <a class="brand" href="/cgi-bin/koha/opac-main.pl">
 [% IF ( LibraryNameTitle ) %] [% LibraryNameTitle %] [% ELSE %] Catálogo en línea [% END %] </a>
 </h1>
 [% IF ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
 <div id="cartDetails" class="cart-message">Su carrito está vacío</div>
 [% END %]
 <ul class="nav">
 [% IF ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
 <li class="dropdown">
 <a id="cartmenulink" href="#" role="button" data-toggle="dropdown" title="Reunir ítems en los que esta interesado" class="dropdown-toggle">
 <i id="carticon" class="icon-shopping-cart icon-white"></i> <span class="cartlabel">Carrito</span> <span id="basketcount"></span> <b class="caret"></b>
 </a>
 <ul aria-labelledby="cartmenulink" role="menu" class="dropdown-menu">
 <li role="presentation">
 <a href="#" id="cartmenuitem" class="cart-message" tabindex="-1" role="menuitem">Su carrito está vacío</a>
 </li>
 </ul>
 </li>
 [% END %]
 [% IF ( Koha.Preference( 'virtualshelves' ) == 1 ) && ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
 <li class="divider-vertical"></li>
 [% END %]
 [% IF ( Koha.Preference( 'virtualshelves' ) == 1 ) %]
 <li class="dropdown">
 <a title="Mostrar listas" class="dropdown-toggle" data-toggle="dropdown" role="button" id="listsmenu" href="#"><i class="icon-list icon-white"></i> <span class="listslabel">Listas</span> <b class="caret"></b></a>
 <ul aria-labelledby="listsmenu" role="menu" class="dropdown-menu">
 [% IF some_public_shelves.count %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=2" tabindex="-1" role="menuitem"><strong>Listas públicas</strong></a></li>
 [% SET number_of_public_shelves = 0 %]
 [% FOREACH s IN some_public_shelves %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=view&amp;shelfnumber=[% s.shelfnumber %]&amp;sortfield=[% s.sortfield %]" tabindex="-1" role="menuitem">[% s.shelfname |html %]</a></li>
 [% SET number_of_public_shelves = number_of_public_shelves + 1 %]
 [% IF number_of_public_shelves >= 10 %][% LAST %][% END %]
 [% END %]
 [% IF some_public_shelves > 10 %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=2" tabindex="-1" role="menuitem" class="listmenulink">Ver todo</a></li>
 [% END %]
 [% ELSE %]
 <li role="presentation"><a href="#" tabindex="-1" class="menu-inactive" role="menuitem">No hay listas públicas</a></li>
 [% END %]
 <li class="divider" role="presentation"></li>
 [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=1" tabindex="-1" role="menuitem"><strong>Sus listas</strong></a></li>
 [% IF loggedinusername %]
 [% IF some_private_shelves.count %]
 [% SET number_of_private_shelves = 0 %]
 [% FOREACH s IN some_private_shelves %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=view&amp;shelfnumber=[% s.shelfnumber %]&amp;sortfield=[% s.sortfield %]" tabindex="-1" role="menuitem">[% s.shelfname |html %]</a></li>
 [% SET number_of_private_shelves = number_of_private_shelves + 1 %]
 [% IF number_of_private_shelves >= 10 %][% LAST %][% END %]
 [% END %]
 [% IF some_private_shelves > 10 %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=1" tabindex="-1" role="menuitem" class="listmenulink">Ver todo</a></li>
 [% END %]
 [% ELSE %]
 <li role="presentation"><a href="#" tabindex="-1" class="menu-inactive" role="menuitem">No hay listas privadas</a></li>
 <li role="presentation"><a href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;category=1" tabindex="-1" role="menuitem" class="listmenulink">Nueva lista</a></li>
 [% END %]
 [% ELSE %]
 <li role="presentation"><a href="/cgi-bin/koha/opac-user.pl" tabindex="-1" class="menu-inactive loginModal-trigger" role="menuitem">Ingrese para crear sus propias listas</a></li>
 [% END # / IF loggedinusername %]
 [% END # / IF opacuserlogin %]
 </ul> <!-- / .dropdown-menu -->
 </li> <!-- / .dropdown -->
 [% END # / IF virtualshelves %]
 </ul> <!-- / .nav -->
 [% IF Koha.Preference( 'virtualshelves' ) == 1 %]<div id="listsDetails"></div>[% END %]
 [% IF Koha.Preference( 'opacuserlogin' ) == 1 || opaclanguagesdisplay || EnableOpacSearchHistory %]
 <a id="user-menu-trigger" class="pull-right" href="#"><i class="icon-user"></i> <span class="caret"></span></a>
 <div id="members">
 <ul class="nav pull-right">

 [% INCLUDE 'masthead-langmenu.inc' %]

 [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
 [% UNLESS ( loggedinusername ) %]
 [% IF Koha.Preference('casAuthentication') %]
 [%# CAS authentication is too complicated for modal window %]
 <li><a href="/cgi-bin/koha/opac-user.pl">Ingresar a su cuenta</a></li>
 [% ELSIF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
 <li><a href="/cgi-bin/koha/svc/auth/googleopenidconnect" role="button" data-toggle="modal">Ingresar a su cuenta</a></li>
 [% ELSE %]
 <li><a href="/cgi-bin/koha/opac-user.pl" class="loginModal-trigger" role="button" data-toggle="modal">Ingresar a su cuenta</a></li>
 [% END %]
 [% END %]
 [% IF ( loggedinusername ) %]
 <li><p class="members navbar-text">Bienvenido, <a href="/cgi-bin/koha/opac-user.pl"><span class="loggedinusername">[% USER_INFO.title %] [% USER_INFO.firstname %] [% USER_INFO.surname %]</span></a></p></li>
 <li class="divider-vertical"></li>
 [% END %]
 [% END %]
 [% IF EnableOpacSearchHistory %]
 <li><p class="navbar-text"><a title="Ver su historial de búsqueda" href="/cgi-bin/koha/opac-search-history.pl">Historial de búsqueda</a> [<a class="logout" title="Eliminar historial de búsqueda" href="/cgi-bin/koha/opac-search-history.pl?action=delete" onclick="return confirm(MSG_DELETE_SEARCH_HISTORY);">x</a>]</p></li>
 <li class="divider-vertical"></li>
 [% END %]
 [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
 [% IF ( loggedinusername ) %]
 <li><p class="navbar-text">
 [% IF persona %]
 <a class="logout" id="logout" href="/cgi-bin/koha/opac-main.pl?logout.x=1" onclick='navigator.id.logout();'>
 [% ELSE %]
 <a class="logout" id="logout" href="/cgi-bin/koha/opac-main.pl?logout.x=1">
 [% END %] Salir</a></p></li>
 [% END %]
 [% END %]
 </ul>
 </div> <!-- /members -->
 [% END # IF opacuserlogin %]
 </div> <!-- /container-fluid -->
 </div> <!-- /navbar-inner -->
 </div> <!-- /navbar -->

 [% IF ( opacheader ) %]
 <div class="container-fluid">
 <div class="row-fluid">
 <div id="opacheader">
 [% opacheader %]
 </div>
 </div>
 </div>
 [% END %]
 </div> <!-- / header-region -->

 <div class="container-fluid">
 <div class="row-fluid">
 <div id="opac-main-search">
 <!-- <div class="span2">
 [% IF ( opacsmallimage ) %]
 <h1 id="libraryname" style="background-image: url('[% opacsmallimage %]');">
 [% ELSE %]
 <h1 id="libraryname">
 [% END %]
 <a href="/cgi-bin/koha/opac-main.pl">[% IF ( LibraryName ) %][% LibraryName %][% ELSE %]Koha Online Catalog[% END %]</a></h1>
 </div> /.span2 -->
 <div class="span12">
 [% IF ( OpacPublic ) %]
 [% UNLESS ( advsearch ) %]
 [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
 <div class="mastheadsearch librarypulldown">
 [% ELSE %]
 <div class="mastheadsearch">
 [% END %]
 [% IF Koha.Preference('OpacCustomSearch') == '' %]
 <form name="searchform" method="get" action="/cgi-bin/koha/opac-search.pl" id="searchform" class="form-inline">
 <label for="masthead_search"> Buscar [% UNLESS ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %] [% IF ( mylibraryfirst ) %] (en [% mylibraryfirst %] solamente) [% END %] [% END %] </label>

 <select name="idx" id="masthead_search">
 [% IF ( ms_kw ) %]
 <option selected="selected" value="">Catálogo de biblioteca</option>
 [% ELSE %]
 <option value="">Catálogo de biblioteca</option>
 [% END # /ms_kw %]
 [% IF ( ms_ti ) %]
 <option selected="selected" value="ti">Título</option>
 [% ELSE %]
 <option value="ti">Título</option>
 [% END # /ms_ti %]
 [% IF ( ms_au ) %]
 <option selected="selected" value="au">Autor</option>
 [% ELSE %]
 <option value="au">Autor</option>
 [% END # /ms_au%]
 [% IF ( ms_su ) %]
 <option selected="selected" value="su">Materia</option>
 [% ELSE %]
 <option value="su">Materia</option>
 [% END # /ms_su %]
 [% IF ( ms_nb ) %]
 <option selected="selected" value="nb">ISBN</option>
 [% ELSE %]
 <option value="nb">ISBN</option>
 [% END # /ms_nb%]
 [% IF ( ms_se ) %]
 <option selected="selected" value="se">Series</option>
 [% ELSE %]
 <option value="se">Series</option>
 [% END # /ms_se %]
 [% IF ( numbersphr ) %]
 [% IF ( ms_callnum ) %]
 <option selected="selected" value="callnum,phr">Signatura</option>
 [% ELSE %]
 <option value="callnum,phr">Signatura</option>
 [% END #/ms_callnum %]
 [% ELSE %]
 [% IF ( ms_callnum ) %]
 <option selected="selected" value="callnum">Signatura</option>
 [% ELSE %]
 <option value="callnum">Signatura</option>
 [% END # /ms_callnum %]
 [% END # /numbersphr %]
 </select>

 [% UNLESS ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
 <div class="input-append nolibrarypulldown">
 [% END %]
 [% IF ( ms_value ) %]
 <input value="[% ms_value |html %]" name="q" id="translControl1" type="text" title="Escriba el término de búsqueda" class="transl1" /><span id="translControl"></span>
 [% ELSE %]
 <input id="translControl1" name="q" class="transl1" title="Escriba el término de búsqueda" type="text" /><span id="translControl"></span>
 [% END # /ms_value %]

 [% UNLESS ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
 <button type="submit" id="searchsubmit" class="btn btn-primary">Ir</button>
 </div>
 [% END %]

 [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
 <div class="input-append">
 <select name="branch_group_limit" id="select_library">
 <option value="">Todas las bibliotecas</option>
 [% IF BranchCategoriesLoop %]<optgroup label="Bibliotecas">[% END %]
 [% FOREACH BranchesLoo IN BranchesLoop %]
 [% IF ( BranchesLoo.selected ) %]<option selected="selected" value="branch:[% BranchesLoo.value %]">[% BranchesLoo.branchname %]</option>
 [% ELSE %]<option value="branch:[% BranchesLoo.value %]">[% BranchesLoo.branchname %]</option>[% END %]
 [% END %]
 [% IF BranchCategoriesLoop %]
 </optgroup>
 <optgroup label="Grupos">
 [% FOREACH bc IN BranchCategoriesLoop %]
 [% IF bc.categorycode == opac_name %]
 <option selected="selected" value="multibranchlimit-[% bc.categorycode %]">[% bc.categoryname %]</option>
 [% ELSE %]
 <option value="multibranchlimit-[% bc.categorycode %]">[% bc.categoryname %]</option>
 [% END # / bc.selected %]
 [% END %]
 </optgroup>
 [% END # / BranchCategoriesLoop %]
 </select>
 <button type="submit" id="searchsubmit" class="btn btn-primary">Ir</button>
 </div>
 [% ELSE %]
 [% IF ( opac_limit_override ) %]
 [% IF ( opac_search_limit ) %]
 <input name="limit" value="[% opac_search_limit %]" type="hidden" />
 [% END %]
 [% ELSE %]
 [% IF ( mylibraryfirst ) %]
 <input name="limit" value="branch:[% mylibraryfirst %]" type="hidden" />
 [% END %]
 [% END # / opac_limit_override %]
 [% END # / OpacAddMastheadLibraryPulldown %]

 </form>
 [% ELSE # / Koha.Preference('OpacCustomSearch') == '' %]
 [% Koha.Preference('OpacCustomSearch') %]
 [% END # / Koha.Preference('OpacCustomSearch') == '' %]
 </div> <!-- / .mastheadsearch -->
 [% END # / UNLESS advsearch %]

 <div class="row-fluid">
 <div id="moresearches">
 <ul>
 <li><a href="/cgi-bin/koha/opac-search.pl">Búsqueda avanzada</a></li>
 [% IF ( Koha.Preference( 'UseCourseReserves' ) == 1 ) %]<li><a href="/cgi-bin/koha/opac-course-reserves.pl">Reservas para cursos</a></li>[% END %]
 [% IF Koha.Preference( 'OpacBrowser' ) == 1 %]<li><a href="/cgi-bin/koha/opac-browser.pl">Explorar por jerarquía</a></li>[% END %]
 [% IF Koha.Preference( 'OpacAuthorities' ) == 1 %]<li><a href="/cgi-bin/koha/opac-authorities-home.pl">Búsqueda de autoridad</a></li>[% END %]
 [% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && ( Koha.Preference( 'reviewson' ) == 1 ) && ( Koha.Preference( 'OpacShowRecentComments' ) == 1 ) ) %]<li><a href="/cgi-bin/koha/opac-showreviews.pl">Comentarios recientes</a></li>[% END %]
 [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]<li><a href="/cgi-bin/koha/opac-tags.pl">Nube de etiquetas</a></li>[% END %]
 [% IF Koha.Preference( 'OpacCloud' ) == 1 %]<li><a href="/cgi-bin/koha/opac-tags_subject.pl">Nube de temas</a></li>[% END %]
 [% IF Koha.Preference( 'OpacTopissue' ) == 1 %]<li><a href="/cgi-bin/koha/opac-topissues.pl">Más populares</a></li>[% END %]
 [% IF Koha.Preference( 'suggestion' ) == 1 %]
 [% IF Koha.Preference( 'AnonSuggestions' ) == 1 %]
 <li><a href="/cgi-bin/koha/opac-suggestions.pl">Sugerencias de compra</a></li>
 [% ELSIF ( ( Koha.Preference( 'OPACViewOthersSuggestions' ) == 1 ) ) %]
 <li><a href="/cgi-bin/koha/opac-suggestions.pl">Sugerencias de compra</a></li>
 [% END %]
 [% END %]
 </ul>
 </div> <!-- /#moresearches -->
 </div> <!-- /.row-fluid -->

 [% END # / OpacPublic %]
 </div> <!-- /.span10 -->
 </div> <!-- /.opac-main-search -->
 </div> <!-- / .row-fluid -->
 </div> <!-- /.container-fluid -->

 <!-- Login form hidden by default, used for modal window -->
 <div id="loginModal" class="modal hide" tabindex="-1" role="dialog" aria-labelledby="modalLoginLabel" aria-hidden="true">
 <div class="modal-header">
 <button type="button" class="closebtn" data-dismiss="modal" aria-hidden="true">×</button>
 <h3 id="modalLoginLabel">Ingresar a su cuenta</h3>
 </div>
 <form action="/cgi-bin/koha/opac-user.pl" method="post" name="auth" id="modalAuth">
 <div class="modal-body">
 [% IF ( shibbolethAuthentication ) %]
 [% IF ( invalidShibLogin ) %]
 <!-- This is what is displayed if shibboleth login has failed to match a koha user -->
 <div class="alert alert-info">
 <p>Lo sentimos, tu identidad Shibboleth no coincide con una identidad válida de la biblioteca. Si usted tiene una cuenta local, puede utilizar esa a continuación.</p>
 </div>
 [% ELSE %]
 <h4>Iniciar sesión Shibboleth</h4>
 <p>Si tiene una cuenta Shibboleth, por favor, <a href="[% shibbolethLoginUrl %]">haga clic aquí para ingresar</a>.</p>
 <h4>Iniciar sesión local</h4>
 [% END %]
 [% END %]
 <input type="hidden" name="koha_login_context" value="opac" />
 <fieldset class="brief">
 <label for="muserid">Usuario:</label><input type="text" id="muserid" name="userid" />
 <label for="mpassword">Contraseña:</label><input type="password" id="mpassword" name="password" />
 [% IF Koha.Preference('OpacPasswordChange') && Koha.Preference('OpacResetPassword') %]
 <div id="forgotpassword-modal">
 <a href="/cgi-bin/koha/opac-password-recovery.pl">¿Olvidó su contraseña?</a>
 </div>
 [% END %]
 [% IF Koha.Preference( 'NoLoginInstructions' ) %]
 <div id="nologininstructions-modal">
 [% Koha.Preference( 'NoLoginInstructions' ) %]
 </div>
 [% END %]
 [% IF PatronSelfRegistration && PatronSelfRegistrationDefaultCategory %]<div id="mpatronregistration"><p>¿No tiene una cuenta? <a href="/cgi-bin/koha/opac-memberentry.pl">Registrarse aquí.</a></p></div>[% END %]
 </fieldset>
 </div>
 <div class="modal-footer">
 <input type="submit" class="btn btn-primary" value="Ingresar" />
 <a href="#" data-dismiss="modal" aria-hidden="true" class="cancel">Cancelar</a>
 </div>
 </form> <!-- /#auth -->
 </div> <!-- /#modalAuth -->
