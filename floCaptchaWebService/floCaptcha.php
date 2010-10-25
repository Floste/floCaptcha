<?php
	/*
	 * Script principal du floCaptcha
	 * Il faut l'appeler avec une de ces actions (param action): 
	 * - create : pour créer ou recréer un captcha.
	 * 		param supplémentaire : 
	 * 			- idCaptcha : (optionnel) préciser l'id si c'est pour recreer le captha
	 * 		retour : 
	 * 			- dans le retour se trouve l'identifiant captcha
	 * - getImage : pour obtenir l'image du captcha
	 * 		param supplémentaire : 
	 * 			- idCaptcha : l'identifiant retourné par la méthode create
	 * - getDiction : pour obtenir la diction orale du captcha
	 * 		param supplémentaire : 
	 * 			- idCaptcha : l'identifiant retourné par la méthode create
	 * - controle : pour effectuer le controle du captcha.
	 * 					Seul un controle par identifiant est possible.
	 * 					A la suite du controle, ce captcha est détruit
	 * 		param supplémentaire : 
	 * 			- idCaptcha : l'identifiant retourné par la méthode create
	 * 			- testTexte : code saisi dans le formulaire
	 * 
	 * 
	 */
require_once 'config.inc';

//Nettoyage des captcha périmé
nettoieCaptchaPerime();

$action = "";
$idCaptcha = "";
$testTexte = "";

if(isset($_REQUEST['action'])){
		$action = $_REQUEST['action'];
}
if(isset($_REQUEST['idCaptcha'])){
	$idCaptcha = $_REQUEST['idCaptcha'];
}

if(isset($_REQUEST['testTexte'])){
	$testTexte = $_REQUEST['testTexte'];
}

if($action == ""){
	$action = "";
}
if($idCaptcha=="" && $action!="create"){
	remonte_erreur("Il faut préciser le paramètre idCaptcha");
}elseif($idCaptcha=="" && $action=="create"){
	$myCaptcha = new floCaptcha();
}else{
	$myCaptcha = new floCaptcha($idCaptcha);
}


switch ($action){
	case "create":
		echo $myCaptcha->getIdCaptcha();
		break;
	case "getImage":
		$myCaptchaImage = new weaveCaptchaImage($myCaptcha->getCaptchaTexte());
		$myCaptchaImage->writeImage();
		break;
	case "getDiction":
		$myCaptchaDiction = new otanCaptchaDiction($myCaptcha->getCaptchaTexte());
		$myCaptchaDiction->writeDiction();
		break;
	case "controle":
		if($myCaptcha->controleCaptcha($testTexte)){
			echo "ok";
		}else{
			echo "no";
		}
		break;
	default:
		break;
}

function remonte_erreur($texte_error){
	echo $texte_error;
}

function nettoieCaptchaPerime(){
	try{
		$dbh = new PDO(BDDDSN,BDDUSER,BDDPWD);
		$dbh->exec("SET NAMES 'utf8'");
	}catch(Exception $e){
		echo($e->getFile() . " - " . $e->getLine() . "<br />" . $e->getMessage());
	}
	
	$sql_delete = "delete from captcha where date_add(date_creation,INTERVAL 6 HOUR) < now()";
	$sth = $dbh->exec($sql_delete);
}

function __autoload($class_name) {
	if(file_exists('class/' . $class_name . '.inc')){
    	require_once 'class/' . $class_name . '.inc';
    }elseif(file_exists('class/' . $class_name . '/' . $class_name . '.inc')){
		require_once 'class/' . $class_name . '/' . $class_name . '.inc';
    }elseif(file_exists('interface/' . $class_name . '.inc')){
		require_once 'interface/' . $class_name . '.inc';
    }
}
?>