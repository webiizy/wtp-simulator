<?php
	include("head.inc");
?>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">Diagnostics: System logs: Portal Auth</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr><td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><div id='tabdeactive0'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><div id='tabdeactive2'></div></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><div id='tabdeactive9'></div></td>
</tr>
<tr>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs.php'><font color='white'>System</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_dhcp.php'><font color='white'>DHCP</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;Portal Auth&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_settings.php'><font color='white'>Settings</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
</tr>
<tr height='5px'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"></td>
 </tr>
</table>
<script type="text/javascript">NiftyCheck();
Rounded("div#tabactive","top","#FFF","#EEEEEE","smooth");
Rounded("div#tabdeactive0","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive1","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive2","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive3","top","#FFF","#777777","smooth");
</script>  </td></tr>
  <tr>
    <td>
	<div id="mainarea">
		<table class="tabcont" width="100%" border="0" cellspacing="0" cellpadding="0">
		  <tr>
			<td colspan="2" class="listtopic">
			  Last 50 Portal Auth log entries</td>
		  </tr>
		  		<tr><td><br><form action="diag_logs_auth.php" method="post">
<input name="clear" type="submit" class="formbtn" value="Clear log"></td></tr>
		</table>
	</div>
</form>
	</td>
  </tr>
</table>
<?php
	include("fend.inc");
?>
</body>
</html>
