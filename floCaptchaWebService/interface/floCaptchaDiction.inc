<?php
interface floCaptchaDiction{
	public function __construct($texte);
	public function getDiction();
	public function writeDiction();
}
?>