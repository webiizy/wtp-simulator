<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">Diagnostics: System logs: System</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><div id='tabdeactive1'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><div id='tabdeactive2'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><div id='tabdeactive3'></div></td>
</tr>
<tr>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;System&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_dhcp.php'><font color='white'>DHCP</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_auth.php'><font color='white'>Portal Auth</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_settings.php'><font color='white'>Settings</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
</tr>
<tr height='5px'>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"></td>
 </tr>
</table>
<script type="text/javascript">NiftyCheck();
Rounded("div#tabactive","top","#FFF","#EEEEEE","smooth");
Rounded("div#tabdeactive0","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive1","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive2","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive3","top","#FFF","#777777","smooth");
</script>		</td>
	</tr>
	<tr>
		<td>
			<div id="mainarea">
			<table class="tabcont" width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td colspan="2" class="listtopic">最新的50条系统日志</td>
				</tr>
				<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[273]: connection closed</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[273]: exiting.</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[273]: exiting.</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[1606]: DHCPREQUEST on em0 to 255.255.255.255 port 67</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[1606]: DHCPACK from 192.168.154.254</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:42</td>
<td class="listr">dhclient[1606]: bound to 192.168.154.131 -- renewal in 900 seconds.</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:45</td>
<td class="listr">dnsmasq[1547]: exiting on receipt of SIGTERM</td>
</tr>

				<tr>
					<td align="left" valign="top">
						<form id="filterform" name="filterform" action="diag_logs.php" method="post" style="margin-top: 14px;">
              				<input id="submit" name="clear" type="submit" class="formbtn" value="Clear log" />
						</form>
					</td>
					<td align="right" valign="top" >
						<form id="clearform" name="clearform" action="diag_logs.php" method="post" style="margin-top: 14px;">
              				<input id="filtertext" name="filtertext" value="" />
              				<input id="filtersubmit" name="filtersubmit" type="submit" class="formbtn" value="Filter" />
						</form>
					</td>
				</tr>
			</table>
	    	</div>
		</td>
	</tr>
</table>
<?php
	include("fend.inc");
?>
</body>
</html>
