<?
        if(Connection_Aborted()) {
                exit;
        }
	require_once("auth.inc");
	
	require("../includes/sajax.class.php");
	require("../includes/functions.inc.php");

	$oSajax = new sajax();
	$oSajax->sajax_export("get_stats");
	$oSajax->sajax_handle_client_request();
?>
