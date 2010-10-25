<?php

function floCaptchaVerif($requestCollection){
	$ret = false;

	$param = "action=controle";
	$param .= "&idCaptcha=" . $requestCollection["floCaptcha_id"];
	$param .= "&testTexte=" . $requestCollection["floCaptcha_testTexte"];
	
	$url_manager = $requestCollection["floCaptcha_urlWebService"];
	
	$url_to_get = $url_manager . "?" . $param;
	
	$f = fopen($url_to_get, "r");
	$content='';
	while(!feof($f))
	    $content.=fread($f,8);
	fclose($f);
	if($content=="ok"){
        $ret = true;
    }
	return $ret;
}

?>