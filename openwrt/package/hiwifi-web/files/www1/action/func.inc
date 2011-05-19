<?php
function config_get($name)
{
	$fp = popen('uci show ' . $name, 'r');
	if(!$fp)
		return '';
	
	$line = fgets($fp);
	$line = substr($line, strlen($name) + 1);
	$line = str_replace("\n", "", $line);
	pclose($fp);
	return $line;

}

function config_get_array($name)
{
	$arr = array();
	
	$fp = popen('uci show ' . $name, 'r');
				
	if(!$fp) 
		return $arr;
								
	$len = strlen($name) + 1;
	while(!feof($fp)) {
		$line = fgets($fp);
		$line = substr($line, $len);
		
		$split = strpos($line, '=');
		if($split < 1)
			continue;
				
		$key = substr($line, 0, $split);
		$val = substr($line, $split+1);
		//substr($val, 0, -1);
		$val = str_replace("\n", "", $val);
		$arr[$key] = $val;		
	}
	pclose($fp);
	
	return $arr;
}
	
function config_set($name, $value)
{
	$cmd = 'uci set ' . $name . '=' . $value;
	
	$fp = popen($cmd, 'r');
	pclose($fp);
}

function config_set_array($root, $hash)
{
	while($key = key($hash)) {
		$cmd = 'uci set ' . $root . '.' . $key . '=' . current($hash);
		$fp = popen($cmd, 'r');
		pclose($fp);
		next($hash);
	}
}

function config_commit($root)
{
	$cmd = 'uci commit';
	if(isset($root)) {
		$cmd = 'uci commit ' . $root;
	}
	$fp = popen($cmd, 'r');
	pclose($fp);
}

function config_get_rootname($name2)
{
	$fp = popen('uci show ' . $name2, 'r');
	$line = fgets($fp);
	pclose($fp);
		
	$split = strpos($line, '=');
	return substr($line, 0, $split);
}

function module_restart($module)
{
	$cmd = '/etc/init.d/' . $module;
	$fp = popen($cmd, 'r');
	pclose($fp);
}

