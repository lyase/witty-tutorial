<?php
class WebTest extends PHPUnit_Extensions_Selenium2TestCase
{
protected function setUp()
{
$this->a=True;
$this->setBrowser('iceweasel');
$this->setBrowserUrl('http://www.google.fr/');
}
             
public function testsetup()
{
$this->url('http://www.google.fr/');
$this->assertEquals($this->a, true);
}
public function testTitle()
{
$this->url('http://www.google.fr/');
$this->assertEquals(true, true);
}
                                        
}
?>
