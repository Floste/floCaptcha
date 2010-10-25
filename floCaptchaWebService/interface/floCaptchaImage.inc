<?php
interface floCaptchaImage{
	public function __construct($texte);
	public function getImage();
	public function writeImage();
}
?>