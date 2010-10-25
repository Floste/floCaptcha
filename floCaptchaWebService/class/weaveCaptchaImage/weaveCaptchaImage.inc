<?php
class weaveCaptchaImage implements floCaptchaImage{
	
	//Texte du captcha
	private $texte;
	
	//hauteur et largeur de l'image
	private $imageLargeur = 125;
	private $imageHauteur = 60;
	
	//image créé
	private $image;
	
	//style, taille et angle de la police
	private $font_style = "class/weaveCaptchaImage/After_Shok.ttf";
	private $font_size = 25;
	private $font_angle = 15;
	
	public function __construct($texte){
		$this->texte = $texte;
		$this->createImage();
	}
	
	public function __destroy(){
		imagedestroy ($this->image);
	}

	public function getImage(){
		return $this->image;
	}

	public function writeImage(){
		header("Content-type: image/png");
		imagepng($this->getImage());
	}
	
	private function createImage(){
		$this->image = imagecreatetruecolor($this->imageLargeur, $this->imageHauteur);
		imagefilledrectangle($this->image, 0, 0, 125, 60, imagecolorallocate($this->image, 125,125,125));
		
		for($j=0; $j<200; $j++){
			$ellipse_col = imagecolorallocate($this->image, rand(150,250), rand(150,250), rand(150,250));
			imagefilledellipse($this->image, rand(1,63), rand(1,58), rand(3,15), rand(3,15), $ellipse_col);
		}

		for($j=0; $j<200; $j++){
			$ellipse_col = imagecolorallocate($this->image, rand(25,125), rand(25,125), rand(25,125));
			imagefilledellipse($this->image, rand(63,124), rand(1,58), rand(3,15), rand(3,15), $ellipse_col);
		}

		$line_col = imagecolorexactalpha($this->image, 255,255,255,75);
		
		for($l=0;$l<60+125;$l=$l+3){
			imageline($this->image, 0, $l, 125, $l-125, $line_col);
		}
		for($l=-125;$l<60;$l=$l+3){
			imageline($this->image, 0, $l, 125, $l+125, $line_col);
		}

		$text_col = imagecolorallocate($this->image, 0,0,0);
		$x = 5;
		$y = 50;
		imagettftext($this->image, $this->font_size, $this->font_angle, $x, $y, $text_col, $this->font_style, substr($this->texte,0,2));

		$text_col = imagecolorallocate($this->image, 255,255,255);
		$x = 65;
		$y = 50;
		imagettftext($this->image, $this->font_size, $this->font_angle, $x, $y, $text_col, $this->font_style, substr($this->texte,2,2));

		$this->wave_region($this->image,0,0,imagesx($this->image),imagesy($this->image));

	}
	
	private function wave_region($img, $x, $y, $width, $height,$amplitude = 10,$period = 40)
    {
        // Make a copy of the image twice the size
        $mult = 2;
        $img2 = imagecreatetruecolor($width * $mult, $height * $mult);
        imagecopyresampled ($img2,$img,0,0,$x,$y,$width * $mult,$height * $mult,$width, $height);

        // Wave it
        for ($i = 0;$i < ($width * $mult);$i += 2)
        {
           imagecopy($img2,$img2,
               $x + $i - 2,$y + sin($i / $period) * $amplitude,    // dest
               $x + $i,$y,            // src
               2,($height * $mult));
        }
       
        // Resample it down again
        imagecopyresampled ($img,$img2,$x,$y,0,0,$width, $height,$width * $mult,$height * $mult);
        imagedestroy($img2);
    }
	
}
?>