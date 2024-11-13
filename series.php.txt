<?php
//Series.php ver 1.0.1
//written in php5.2 by Tom Veile 1/5/2011
//Calculation of the partial sum of the reciprocals of the squares of the integers
//using OOP programming techniques
//for the not just tiny-c Programming Group
//Facebook
//Updated 1/13/2011 ver 1.0.1
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>Partial sum of the reciprocals of the squares of the integers - Seeking Objectivity</title>
<style type="text/css">
	body {
		margin: 0;
		padding: 0;
		font-family: Verdana, sans-serif;
		font-size: small;
		background: #fff;
	}
	h1, h2, h3 {
		display: block;
		text-align: center;
	}

	p {
		display: block;
		text-align: center;
		font-weight: bold;
	}
</style>
</head>
<body>
<h1>Partial sum of the reciprocals of the squares of the integers<br />Seeking Objectivity</h1>

<?php
//instantiate the Series class
$series = new Series();
//set parameters for the methods
$series->set_params();
//get the values
list($total,$num,$pi26,$diff,$exclamation) = $series->get_values();
//display the values
echo "<br />";
echo "<h3>The ".$num."'th partial sum = " . $total."</h3>";
echo "<br />";
echo "<h3>&pi;^2/6 = " . $pi26."</h3>";
echo "<br />";
echo "<h3>The difference is = ".$diff."</h3>";
echo "<br />";
echo "<h2>The evidence is ".$exclamation."!</h2>";
echo "<br />";
echo "<p>by Tom Veile</p>";
echo "<p>for the</p>";
echo "<p>Facebook</p>"; 
echo "<p>not just tiny-c Programming Group</p>";
echo "<p>Revised: January 13, 2011</p>";
echo "<p>Revised: October 13, 2017</p>";

class Series {
	public $harms = 0;
	public $total = 0;
	public $pi26  = 0;
	public $diff  = 0;
	public $reit  = 0;
	public $exclamation = array();
	public $selection = '';
	
	public function set_params($h = 1, $t = 0, $p = 0, $d = 0, $r = 0){
		$this->harms = $h;
		$this->total = $t;
		$this->pi26  = $p;
		$this->diff  = $d;
		$this->reit  = $r;
		$this->exclamation = array(
                  'up to Hardhacker standards','tiny-c compliant','8-bit awesome'
                  );
		}

	public function get_values(){
		$data = array();
		for ($this->harms; $this->harms <= 1000000; $this->harms++){
			$this->total += 1/(pow($this->harms,2));}
			$this->total = round($this->total,7);
			$this->reit = $this->harms - 1;
			$this->pi26 = round(pow(pi(),2)/6,7);
			$this->diff = $this->total - $this->pi26;
			shuffle($this->exclamation);
			$this->selection = $this->exclamation[0];
			array_push($data, $this->total, $this->reit, $this->pi26, $this->diff, $this->selection);
		
			return($data); 
	}
}
?>
</body>
</html>

