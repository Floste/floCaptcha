<?php
/*
 * Class de gestion du captcha.
 * Elle permet de créer un captcha et de l'enregistrer en base de donnée jusqu'à son controle
 */
class floCaptcha{
	
	private $captchaTexte;
	private $idCaptcha;
	
	function __construct($unIdCaptcha=""){
		if($unIdCaptcha===""){
			//creation d'un captcha en base de donnée
			try{
				$dbh = new PDO(BDDDSN,BDDUSER,BDDPWD);
				$dbh->exec("SET NAMES 'utf8'");
			}catch(Exception $e){
				echo($e->getFile() . " - " . $e->getLine() . "<br />" . $e->getMessage());
			}
			
			$this->idCaptcha = $this->createIdCaptcha();
			$this->captchaTexte = $this->createCaptchaTexte();
			
			$sql_new = "insert into captcha (idCaptcha,texte,date_creation) ";
			$sql_new .= " values('" . $this->idCaptcha . "','" . $this->captchaTexte . "',now())";
			$sth = $dbh->exec($sql_new);
			$id = $dbh->lastInsertId();
			$this->idCaptcha .= $id;
			$sql_update = "update captcha set idCaptcha = '" . $this->idCaptcha . "' where id = " . $id;
			$sth = $dbh->exec($sql_update);
		}else{
			//récupération d'un captcha en base de donnée
			try{
				$dbh = new PDO(BDDDSN,BDDUSER,BDDPWD);
				$dbh->exec("SET NAMES 'utf8'");
			}catch(Exception $e){
				echo($e->getFile() . " - " . $e->getLine() . "<br />" . $e->getMessage());
			}
			
			$sql_get = "select * from captcha where idCaptcha = '" . $unIdCaptcha . "' ";
			$sth = $dbh->query($sql_get);
			if($sth->rowCount()>0){
				$row = $sth->fetch(PDO::FETCH_ASSOC);
				$this->captchaTexte = $row['texte'];			
				$this->idCaptcha = $row['idCaptcha'];
			}else{
				$this->__construct();
			}
			$sth->closeCursor();
		}
	}
	
	function destructCaptcha(){
		//destruction du captcha
		try{
			$dbh = new PDO(BDDDSN,BDDUSER,BDDPWD);
			$dbh->exec("SET NAMES 'utf8'");
		}catch(Exception $e){
			echo($e->getFile() . " - " . $e->getLine() . "<br />" . $e->getMessage());
		}
		
		$sql_delete = "delete from captcha where idCaptcha = '" . $this->idCaptcha . "' ";
		$sth = $dbh->exec($sql_delete);
		$this->idCaptcha = null;
		$this->captchaTexte = null;
	}
	
	public function getCaptchaTexte(){
		return $this->captchaTexte;
	}
	
	public function getIdCaptcha(){
		return $this->idCaptcha;
	}

	public function controleCaptcha($testTexte){
		$ret = false;
		if($testTexte==$this->captchaTexte){
			$ret = true;
		}
		$this->destructCaptcha();
		return $ret;
	}
	
	/*
	 * Retourne une chaine de 4 caractères généré aléatoirement
	 */
	private function createCaptchaTexte(){
		$ret = "";
		
		for($i=0; $i < CAPTCHA_NB_CAR; $i++){
			$ascii_lettre = intval(rand(97,122));
			$lettre = chr($ascii_lettre);
			$ret .= $lettre;
		}
		return $ret;
	}
	
	/*
	 * Retourne une chaine de 15 caractères généré à partir d'un time stamp
	 * et de 5 caratères aléatoire inséré pseudo aléatoirement
	 */
	private function createIdCaptcha(){
		$dateTime = (new DateTime());
		$stamp = $dateTime->getTimestamp();
		$ret = "";
		
		for($i=0; $i < 5; $i++){
			$pos_init = $i * 2;
			$tmp_str = "";
			$pos_lettre = rand(0,3);
			$ascii_lettre = intval(rand(97,122));
			$lettre = chr($ascii_lettre);
			if($pos_lettre<1){
				$tmp_str .= $lettre;
				$tmp_str .= substr($stamp,$pos_init,2); 
			}elseif($pos_lettre<2){
				$tmp_str .= substr($stamp,$pos_init,1); 
				$tmp_str .= $lettre;
				$tmp_str .= substr($stamp,$pos_init+1,1); 
			}else{
				$tmp_str .= substr($stamp,$pos_init,2); 
				$tmp_str .= $lettre;
			}
			$ret .= $tmp_str;
		}
		return $ret;
	}
}
?>