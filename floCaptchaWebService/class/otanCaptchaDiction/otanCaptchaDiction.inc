<?php
class otanCaptchaDiction implements floCaptchaDiction{
	
	//Texte du captcha
	private $texte;
	
	//diction sonore créé
	private $diction;
	
	public function __construct($texte){
		$this->texte = $texte;
		$this->createDiction();
	}
	
	public function __destroy(){
	}

	public function getDiction(){
		return $this->diction;
	}

	public function writeDiction(){
		// Spit out the audio file!
		$this->diction->output("captcha.mp3");
	}
	
	private function createDiction(){
		$this->diction = new mp3("");
		$this->diction->striptags();
		
		for($i=0;$i<strlen($this->texte);$i++){
			$car = substr($this->texte,$i,1);
			$cas_curMp3 = new mp3(getcwd() . "\\class\\otanCaptchaDiction\\alphabetOtan\\" . $car . ".mp3");
			$this->diction->mergeBehind($cas_curMp3);
			$this->diction->striptags();
		}
	}
		
}
?>