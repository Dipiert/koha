[% UNLESS ( is_popup ) %]
 [% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
 [% IF ( opaccredits ) %]
 <div class="container-fluid">
 <div class="row-fluid">
 <div class="span12">
 <div id="opaccredits" class="noprint">
 [% opaccredits %]
 </div>
 </div>
 </div>
 </div>
 [% END #/ opaccredits %]

 [% IF ( OpacKohaUrl ) %]
 <div class="container-fluid">
 <div class="row-fluid">
 <div class="span12">
 <div id="koha_url" class="clearfix noprint">
 <p>Con tecnología [% IF template.name.match('opac-main.tt') %] <a class="koha_url" href="http://koha-community.org">Koha</a>
 [% ELSE %]
 <a class="koha_url" rel="nofollow" href="http://koha-community.org">Koha</a>
 [% END %]</p>
 </div>
 </div> <!-- /.span12 -->
 </div> <!-- /.row-fluid -->
 </div> <!-- /.container-fluid -->
 [% END # / OpacKohaUrl %]

</div> <!-- / #wrap in masthead.inc -->
[% IF OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer' %]
 [% IF ( opaclanguagesdisplay ) %]
 [% IF ( languages_loop && opaclanguagesdisplay ) %]
 [% UNLESS ( one_language_enabled ) %]
 <div id="changelanguage" class="navbar navbar-fixed-bottom navbar-static-bottom noprint">
 <div class="navbar-inner">
 <ul id="i18nMenu" class="nav">
 <li><p class="lang navbar-text"><strong>Idiomas:&nbsp;</strong></p></li>
 [% FOREACH languages_loo IN languages_loop.sort('rfc4646_subtag') %]
 [% IF ( languages_loo.group_enabled ) %]
 [% IF ( languages_loo.plural ) %]
 <li class="dropdown">
 <a data-toggle="dropdown" class="dropdown-toggle sublangs" id="show[% languages_loo.rfc4646_subtag %]" href="#">[% IF ( languages_loo.native_description ) %][% languages_loo.native_description %][% ELSE %][% languages_loo.rfc4646_subtag %][% END %] <b class="caret"></b></a>
 <ul id="sub[% languages_loo.rfc4646_subtag %]" class="dropdown-menu">
 [% FOREACH sublanguages_loo IN languages_loo.sublanguages_loop %]
 [% IF ( sublanguages_loo.enabled ) %]
 [% IF ( sublanguages_loo.sublanguage_current ) %]
 <li> <p>[% sublanguages_loo.native_description %] [% sublanguages_loo.script_description %] [% sublanguages_loo.region_description %] [% sublanguages_loo.variant_description %] ([% sublanguages_loo.rfc4646_subtag %])</p></li>
 [% ELSE %]
 <li><a href="/cgi-bin/koha/opac-changelanguage.pl?language=[% sublanguages_loo.rfc4646_subtag %]"> [% sublanguages_loo.native_description %] [% sublanguages_loo.script_description %] [% sublanguages_loo.region_description %] [% sublanguages_loo.variant_description %] ([% sublanguages_loo.rfc4646_subtag %])</a></li>
 [% END %]
 [% END # / IF sublanguages_loo.enabled %]
 [% END # / FOREACH sublanguages_loo %]
 </ul>
 </li> <!-- / .more -->
 [% ELSE %]
 [% IF ( languages_loo.group_enabled ) %]
 [% IF ( languages_loo.current ) %]
 <li class="active"><p class="navbar-text">[% IF ( languages_loo.native_description ) %][% languages_loo.native_description %][% ELSE %][% languages_loo.rfc4646_subtag %][% END %]</p></li>
 [% ELSE %]
 <li><a href="/cgi-bin/koha/opac-changelanguage.pl?language=[% languages_loo.rfc4646_subtag %]">[% IF ( languages_loo.native_description ) %][% languages_loo.native_description %][% ELSE %][% languages_loo.rfc4646_subtag %][% END %]</a></li>
 [% END %]
 [% END # / IF languages_loo.current %]
 [% END # / IF ( languages_loo.plural ) %]
 [% END # / IF ( languages_loo.group_enabled ) %]
 [% END # / FOREACH languages_loo IN languages_loop %]
 </ul> <!-- / #i18menu -->
 </div> <!-- / .navbar-inner -->
 </div> <!-- / #changelanguage -->
 [% END # / UNLESS ( one_language_enabled ) %]
 [% END # / IF ( languages_loop && opaclanguagesdisplay ) %]
 [% END # / IF opaclanguagesdisplay %]
[% END %]
[% END # / UNLESS is_popup %]


<!-- JavaScript includes -->
<script type="text/javascript" src="[% interface %]/[% theme %]/lib/jquery/jquery.js"></script>
<script type="text/javascript" src="[% interface %]/[% theme %]/lib/jquery/jquery-ui.js"></script>
<script type="text/javascript">
// Resolve name collision between jQuery UI and Twitter Bootstrap
$.widget.bridge('uitooltip', $.ui.tooltip);
</script>
<script type="text/javascript" src="[% interface %]/[% theme %]/lib/bootstrap/js/bootstrap.min.js"></script>
<script type="text/javascript" src="[% interface %]/[% theme %]/js/global.js"></script>
<script type="text/javascript">
    Modernizr.load([
        // Test need for polyfill
        {
            test: window.matchMedia,
            nope: "[% interface %]/[% theme %]/lib/media.match.min.js"
        },
        // and then load enquire
        "[% interface %]/[% theme %]/lib/enquire.min.js",
        "[% interface %]/[% theme %]/js/script.js"
    ]);

    // Fix for datepicker in a modal
    $.fn.modal.Constructor.prototype.enforceFocus = function () {};
</script>
[% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
<script type="text/javascript">//<![CDATA[
        var NO_AMAZON_IMAGE = _("No hay imagen de cubierta disponible");
    //]]>
</script>
<script type="text/javascript" src="[% interface %]/[% theme %]/js/amazonimages.js"></script>
[% END %]

<script type="text/javascript">
    //<![CDATA[
    var MSG_CONFIRM_AGAIN = _("Advertencia: No puede deshacerse. Por favor confirmar nuevamente")
    var MSG_DELETE_SEARCH_HISTORY = _("¿Está seguro que desea eliminar su historial de búsqueda?");
    var MSG_NO_SUGGESTION_SELECTED = _("No se seleccionó ninguna sugerencia");
    [% IF Koha.Preference( 'opacbookbag' ) == 1 or Koha.Preference( 'virtualshelves' ) == 1 %]
        var MSG_BASKET_EMPTY = _("Su carrito está vacío");
        var MSG_RECORD_IN_BASKET = _("Este ejemplar ya se encuentra en su carrito");
        var MSG_RECORD_ADDED = _("Este ejemplar ha sido agregado a su carrito");
        var MSG_RECORD_REMOVED = _("Este ejemplar ha sido eliminado de su carrito");
        var MSG_NRECORDS_ADDED = _(" ejemplar(es) agregado(s) a su carrito");
        var MSG_NRECORDS_IN_BASKET = _("ya está en su carrito");
        var MSG_NO_RECORD_SELECTED = _("Ningún ítem fue seleccionado");
        var MSG_NO_RECORD_ADDED = _("No se agregaron ítems a su carrito");
        var MSG_CONFIRM_DEL_BASKET = _("¿Está seguro de querer vaciar su carrito?");
        var MSG_CONFIRM_DEL_RECORDS = _("¿Está seguro de querer eliminar los ítems seleccionados?");
        var MSG_ITEM_IN_CART = _("En su carrito");
        var MSG_IN_YOUR_CART = _("Ítems en su carrito: ");
        var MSG_ITEM_NOT_IN_CART = _("Agregar a su carrito");
    [% END %]
    [% IF ( Koha.Preference( 'opacuserlogin' ) == 1 ) && ( Koha.Preference( 'TagsEnabled' ) == 1 ) %]
        var MSG_TAGS_DISABLED = _("Lo sentimos, las etiquetas no están habilitadas en este sistema.");
        var MSG_TAG_ALL_BAD = _("Error! Su etiqueta tenía código ilegal. NO ha sido agregada. Intente nuevamente con texto plano.");
        var MSG_ILLEGAL_PARAMETER = _("¡Error! Parámetro ilegal");
        var MSG_TAG_SCRUBBED = _("Nota: su etiqueta contenía código que fue removido. La etiqueta fue agregada como ");
        var MSG_ADD_TAG_FAILED = _("¡Error! La adición de etiquetas falló en");
        var MSG_ADD_TAG_FAILED_NOTE = _("Nota: solo puede etiquetar un ítem con determinado término una vez. Vea 'Mis Etiquetas' para ver sus etiquetas actuales.");
        var MSG_DELETE_TAG_FAILED = _("¡Error! No puede eliminar la etiqueta");
        var MSG_DELETE_TAG_FAILED_NOTE = _("Nota: sólo puede eliminar sus propias etiquetas.")
        var MSG_LOGIN_REQUIRED = _("Debe ingresar a su cuenta para agregar etiquetas.");
        var MSG_TAGS_ADDED = _("Etiquetas agregadas: ");
        var MSG_TAGS_DELETED = _("Etiquetas agregadas: ");
        var MSG_TAGS_ERRORS = _("Errores: ");
        var MSG_MULTI_ADD_TAG_FAILED = _("No se pudo agregar una o más etiquetas.");
        var MSG_NO_TAG_SPECIFIED = _("No se especificó etiqueta.");
    [% END %]
    [% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
        $(window).load(function() {
            verify_images();
         });
    [% END %]

    $(".print-large").on("click",function(){
        window.print();
        return false;
    });
    $(".addtoshelf").on("click",function(){
        Dopop('opac-addbybiblionumber.pl?biblionumber=[% biblionumber %]');
        return false;
    });
    $(".addrecord").on("click",function(){
        addRecord('[% biblionumber %]');
        return false;
    });
    $(".cartRemove").on("click",function(){
        delSingleRecord('[% biblionumber %]');
        return false;
    });
    //]]>
</script>

[% IF Koha.Preference( 'opacbookbag' ) == 1 %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/basket.js"></script>
[% ELSIF ( Koha.Preference( 'virtualshelves' ) == 1 ) %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/basket.js"></script>
[% ELSE %]
 <script type="text/javascript">var readCookie;</script>
[% END %]

[% IF Koha.Preference( 'opacuserlogin' ) == 1 %][% IF Koha.Preference( 'TagsEnabled' ) == 1 %]<script type="text/javascript" src="[% interface %]/[% theme %]/js/tags.js"></script>[% END %][% ELSE %][% END %]
[% IF ( GoogleJackets ) %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/google-jackets.js"></script>
 <script type="text/javascript">
        //<![CDATA[
        var NO_GOOGLE_JACKET = _("No hay imagen de cubierta disponible");
        //]]>
    </script>
[% END %]
[% IF ( Koha.Preference('Coce') && Koha.Preference('CoceProviders') ) %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/coce.js"></script>
 <script type="text/javascript">
        //<![CDATA[
        var NO_COCE_JACKET = _("No hay imagen de cubierta disponible");
        //]]>
    </script>
[% END %]

[% IF OpenLibraryCovers || OpenLibrarySearch %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/openlibrary.js"></script>
 <script type="text/javascript">
    //<![CDATA[
    var NO_OL_JACKET = _("No hay imagen de cubierta disponible");
    var OL_PREVIEW = _("Vista previa");
    //]]>
    </script>
[% END %]

[% IF OPACLocalCoverImages %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/localcovers.js"></script>
 <script type="text/javascript">
    //<![CDATA[
    var NO_LOCAL_JACKET = _("No hay imagen de cubierta disponible");
    //]]>
    </script>
[% END %]

[% IF ( BakerTaylorEnabled ) %]
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/bakertaylorimages.js"></script>
 <script type="text/javascript">
        //<![CDATA[
        var NO_BAKERTAYLOR_IMAGE = _("No hay imagen de cubierta disponible");
        $(window).load(function(){
            bt_verify_images();
        });
        //]]>
    </script>
[% END %]
[% IF ( GoogleIndicTransliteration ) %]
 <script type="text/javascript" src="https://www.google.com/jsapi"></script>
 <script type="text/javascript" src="[% interface %]/[% theme %]/js/googleindictransliteration.js"></script>
[% END %]
[% IF persona %]
 <script src="https://login.persona.org/include.js"></script>
 <script type="text/javascript">

    navigator.id.watch({
        loggedInUser: [% IF emailaddress && loggedinpersona %]'[% emailaddress %]'[% ELSE %]null[% END %],
        onlogin: function (assertion) {
            $.post('/cgi-bin/koha/svc/login',
                { assertion: assertion },
                function (data) {
                    window.location = '/cgi-bin/koha/opac-user.pl';
                }
            )
            .fail(function() { var errstr = _("No pudo ingresar, quizás su email de Persona no coincide con el de Koha");
                alert(errstr);
            });
        },
        onlogout: function () {
            window.location = '/cgi-bin/koha/opac-main.pl?logout.x=1';
        }
    });

    var signinLink = document.getElementById('browserid');

    if (signinLink) {
        signinLink.onclick = function(evt) {
            // Requests a signed identity assertion from the user.
            navigator.id.request({
                siteName: "[% LibraryName | html %]",
                returnTo: '/cgi-bin/koha/opac-user.pl',
                oncancel: function() { alert('user refuses to share identity.'); }
                });
            };
    }

    </script>
[% END #  / IF persona %]

<script type="text/javascript" src="[% interface %]/[% theme %]/lib/jquery/plugins/jquery.cookie.min.js"></script>
<script type="text/javascript">
$(document).ready(function() {
    if($('#searchsubmit').length) {
        $(document).on("click", '#searchsubmit', function(e) {
            jQuery.removeCookie("form_serialized", { path: '/'});
            jQuery.removeCookie("form_serialized_itype", { path: '/'});
            jQuery.removeCookie("form_serialized_limits", { path: '/'});
            jQuery.removeCookie("num_paragraph", { path: '/'});
            jQuery.removeCookie("search_path_code", { path: '/'});
        });
    }
});
</script>
[% PROCESS jsinclude %]
[% IF ( OPACUserJS ) %]
 <script type="text/javascript">
        //<![CDATA[
        [% OPACUserJS %]
        //]]>
    </script>
[% END %]
[% IF SCO_login %]
 [% SET SCOUserJS = Koha.Preference('SCOUserJS') %]
 [% IF ( SCOUserJS ) %]
 <script type="text/javascript">
            //<![CDATA[
            [% SCOUserJS %]
            //]]>
        </script>
 [% END %]
[% END %]
</body>
</html>
