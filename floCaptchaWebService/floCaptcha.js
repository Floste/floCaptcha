var floCaptcha_urlManager = "http://.../";
var floCaptcha_idCaptcha = "";

/*
 * Fonction de configuration de l'url de webservice
 */
function floCaptcha_setUrlWebService(nouvelle_url){
	floCaptcha_urlManager = nouvelle_url;
}

/*
 * Fonction de génération du formulaire captcha
 */
function floCaptcha_makeForm(){
	document.write("<div id='floCaptcha'></div>");
	floCaptcha_attachFunctionOnLoad(function(){
		floCaptcha_changeCode();
	});
}

function floCaptcha_makeContentHtml(idCaptcha){
	chemin_image = floCaptcha_urlManager + "floCaptcha.php?action=getImage&idCaptcha=" + idCaptcha;
	chemin_audio = floCaptcha_urlManager + "floCaptcha.php?action=getDiction&idCaptcha=" + floCaptcha_idCaptcha + "'";
	chemin_audio = encodeURIComponent(chemin_audio);
	ret = "";
	ret += "<img src='" + chemin_image + "' />";
	ret += "<div class='floCaptcha-link-changeCode'><a href='#' onclick='floCaptcha_changeCode();'>changer le code</a></div>";
	ret += "<div class='floCaptcha-link-getAudio'><a href='" + floCaptcha_urlManager + "floCaptcha.php?action=getDiction&idCaptcha=" + floCaptcha_idCaptcha + "'>Code audio</a></div>";
	ret += "<object type='application/x-shockwave-flash'";
		ret += "data='" + floCaptcha_urlManager + "audio-player/musicplayer.swf?&song_url=" +  chemin_audio + "' ";
		ret += "width='17' height='17'>";
		ret += "<param name='movie'" ;
		ret += "value='" + floCaptcha_urlManager + "audio-player/musicplayer.swf?&song_url=" + chemin_audio + "' />";
	ret += "</object>";
	ret += "<br />";
	ret += "<label for='elt_floCaptcha_testTexte'>Code de controle : </label>";
	ret += "<input type='text' id='elt_floCaptcha_testTexte' name='floCaptcha_testTexte'/>";
	ret += "<input type='hidden' id='elt_floCaptcha_idCaptcha' name='floCaptcha_id' value='" + idCaptcha + "' />";
	ret += "<input type='hidden' id='elt_floCaptcha_urlWebService' name='floCaptcha_urlWebService' value='" + floCaptcha_urlManager + "' />";
	return ret;
}

function floCaptcha_changeCode(){
	floCaptcha_createHTTPRequest(floCaptcha_urlManager + "floCaptcha.php?action=create","",function(xhr_object){
		if(xhr_object.readyState==4){
			floCaptcha_idCaptcha = xhr_object.responseText;
			(document.getElementById("floCaptcha")).innerHTML = floCaptcha_makeContentHtml(floCaptcha_idCaptcha);
		}
	},"post");
}

/*
* La fonction attachFunctionOnLoad permet d'ajouter une fonction a éxécuter au chargement de la page
*
* paramêtres : 
*	- theFunction : Fonction à ajouter
*
*/
function floCaptcha_attachFunctionOnLoad(theFunction){
	if(typeof window.addEventListener != 'undefined'){
		//.. gecko, safari, konqueror and standard
		window.addEventListener('load', theFunction, false);
	}else if(typeof document.addEventListener != 'undefined'){
		//.. opera 7
		document.addEventListener('load', theFunction, false);
	}else if(typeof window.attachEvent != 'undefined'){
		//.. win/ie
		window.attachEvent('onload', theFunction);
	}
}

/*
* La fonction createHTTPRequest permet de créer et d'éxécuter une requete http
*
* paramêtres : 
*	- urlToCall : adresse du script à appeler (chaine de caractères)
*	- params : paramêtres à envoyer au script. Doivent être sous la forme d'une query (chaine de caractères)
*   - fonction_at_return : fonction a éxécuter au retour de la requète (doit avoir un parametre, qui sera l'objet xhr)
*   - method : optionnel, par défaut : GET
*
* Element utile à connaitre sur un objet xhr : 
* - xhr_object.readyState : indique l'état de la requette ( 4 indique que tout s'est bien passé)
* - xhr_object.responseText : contenu du retour
*/
function floCaptcha_createHTTPRequest(urlToCall, params, fonction_at_return, method){
	if(!method){method = "GET";}
	//Création de l'objet XMLHTTPREQUEST
	var xhr_object = null;

	if(window.XMLHttpRequest) // Firefox
		xhr_object = new XMLHttpRequest();
	else if(window.ActiveXObject) // Internet Explorer
		xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
	else { // XMLHttpRequest non supporté par le navigateur
		alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest...");
		return;
	}

	xhr_object.open(method, urlToCall, true);

	xhr_object.onreadystatechange = function(){
		fonction_at_return(xhr_object);
	}

	xhr_object.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	xhr_object.setRequestHeader("Content-Transfer-Encoding", "iso-8859-1");
	xhr_object.send(params);
}