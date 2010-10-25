<?php
?>
<html>
	<head>
		<script type="text/javascript" src="http://localhost/floCaptcha/floCaptchaWebService/floCaptcha.js"></script>
	</head>
	<body>
		<form action="valid.php" method="post">
			valeur de test : <input type="text" name="testVal" /><br />
			<div id="captcha">
				<script type="text/javascript">
					floCaptcha_setUrlWebService('http://localhost/floCaptcha/floCaptchaWebService/');
					floCaptcha_makeForm();
				</script>
			</div>
			<input type="submit" value="Valider" />
		</form>
	</body>
</html>