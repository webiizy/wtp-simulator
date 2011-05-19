<?php

	unset($input_errors);
	$pconfig = $_POST;
	
	$wifi['']['network'] = '';
	
	require("func.inc");

	/* input validation */
	//$reqdfields = split(" ", "hostname domain username");
	//$reqdfieldsn = split(",", "Hostname,Domain,Username");

	//do_input_validation($_POST, $reqdfields, $reqdfieldsn, &$input_errors);
		//$input_errors[] = "The hostname may only contain the characters a-z, 0-9 and '-'.";

		
	if ($_POST['hostname'] && !is_hostname($_POST['hostname'])) {
		$input_errors[] = "The hostname may only contain the characters a-z, 0-9 and '-'.";
	}
	if ($_POST['domain'] && !is_domain($_POST['domain'])) {
		$input_errors[] = "The domain may only contain the characters a-z, 0-9, '-' and '.'.";
	}
	if (($_POST['dns1'] && !is_ipaddr($_POST['dns1'])) || ($_POST['dns2'] && !is_ipaddr($_POST['dns2']))) {
		$input_errors[] = "A valid IP address must be specified for the primary/secondary DNS server.";
	}
	if ($_POST['username'] && !preg_match("/^[a-zA-Z0-9]*$/", $_POST['username'])) {
		$input_errors[] = "The username may only contain the characters a-z, A-Z and 0-9.";
	}
	
	if (($_POST['password']) && ($_POST['password'] != $_POST['password2'])) {
		$input_errors[] = "The passwords do not match.";
	}

	foreach (explode(' ', $_POST['timeservers']) as $ts) {
		if (!is_domain($ts)) {
			$input_errors[] = "A NTP Time Server name may only contain the characters a-z, 0-9, '-' and '.'.";
		}
	}

	if (!$input_errors) {
	/*
		update_if_changed("hostname", $config['system']['hostname'], strtolower($_POST['hostname']));
		update_if_changed("domain", $config['system']['domain'], strtolower($_POST['domain']));
		update_if_changed("username", $config['system']['username'], $_POST['username']);

		update_if_changed("timezone", $config['system']['timezone'], $_POST['timezone']);
		update_if_changed("NTP servers", $config['system']['timeservers'], strtolower($_POST['timeservers']));
		update_if_changed("NTP update interval", $config['system']['time-update-interval'], $_POST['timeupdateinterval']);
*/
		/* XXX - billm: these still need updating after figuring out how to check if they actually changed */
		/*
		unset($config['system']['dnsserver']);
		if ($_POST['dns1'])
			$config['system']['dnsserver'][] = $_POST['dns1'];
		if ($_POST['dns2'])
			$config['system']['dnsserver'][] = $_POST['dns2'];

		if ($changecount > 0)
			write_config($changedesc);

			$retval = 0; 
		config_lock();
		$retval = system_hostname_configure();
		$retval |= system_hosts_generate();
		$retval |= system_resolvconf_generate();
		$retval |= system_password_configure();
		$retval |= services_dnsmasq_configure();
		$retval |= system_timezone_configure();
		$retval |= system_ntp_configure();

		if ($olddnsallowoverride != $config['system']['dnsallowoverride'])
			$retval |= interfaces_wan_configure();

		config_unlock();

		// Reload filter -- plugins might need to run
		filter_configure();*/
	}
?>
