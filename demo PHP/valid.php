<?php

require("../floCaptchaLib/floCaptchaVerif.inc");

if(floCaptchaVerif($_REQUEST)){
	echo $_REQUEST["testVal"];
}else{
	echo "Erreur dans le code de controle";
}

?>