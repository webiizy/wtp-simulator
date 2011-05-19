<?php
	include("head.inc");
?>
<script language="JavaScript">
<!--
function enable_change(enable_over) {
	if (document.iform.enable.checked || enable_over) {
		document.iform.remoteserver.disabled = 0;
		document.iform.filter.disabled = 0;
		document.iform.dhcp.disabled = 0;
		document.iform.portalauth.disabled = 0;
		document.iform.vpn.disabled = 0;
		document.iform.system.disabled = 0;
	} else {
		document.iform.remoteserver.disabled = 1;
		document.iform.filter.disabled = 1;
		document.iform.dhcp.disabled = 1;
		document.iform.portalauth.disabled = 1;
		document.iform.vpn.disabled = 1;
		document.iform.system.disabled = 1;
	}
}
// -->
</script>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">Diagnostics: System logs: Settings</p>
<form action="diag_logs_settings.php" method="post" name="iform" id="iform">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr><td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><div id='tabdeactive0'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><div id='tabdeactive2'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><div id='tabdeactive3'></div></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
</tr>
<tr>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs.php'><font color='white'>System</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_dhcp.php'><font color='white'>DHCP</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_auth.php'><font color='white'>Portal Auth</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;Settings&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
</tr>
<tr height='5px'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"></td>
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
	  <table class="tabcont" width="100%" border="0" cellpadding="6" cellspacing="0">
                      <tr>
                        <td width="22%" valign="top" class="vtable">&nbsp;</td>
                        <td width="78%" class="vtable"> <input name="reverse" type="checkbox" id="reverse" value="yes" >
                          <strong>Show log entries in reverse order (newest entries
                          on top)</strong></td>
                      </tr>
                      <tr>
                        <td width="22%" valign="top" class="vtable">&nbsp;</td>
                        <td width="78%" class="vtable">Number of log entries to
                          show:
                          <input name="nentries" id="nentries" type="text" class="formfld" size="4" value="50"></td>
                      </tr>
                      <tr>
                        <td valign="top" class="vtable">&nbsp;</td>
                        <td class="vtable"> <input name="logdefaultblock" type="checkbox" id="logdefaultblock" value="yes" checked>
                          <strong>Log packets blocked by the default rule</strong><br>
                          Hint: packets that are blocked by the
                          implicit default block rule will not be logged anymore
                          if you uncheck this option. Per-rule logging options are not affected.</td>
                      </tr>
                      <tr>
                        <td valign="top" class="vtable">&nbsp;</td>
                        <td class="vtable"> <input name="rawfilter" type="checkbox" id="rawfilter" value="yes" >
                          <strong>Show raw filter logs</strong><br>
                          Hint: If this is checked, filter logs are shown as generated by the packet filter, without any formatting. This will reveal more detailed information. </td>
                      </tr>
                      <tr>
                        <td width="22%" valign="top" class="vtable">&nbsp;</td>
                        <td width="78%" class="vtable"> <input name="enable" type="checkbox" id="enable" value="yes"  onClick="enable_change(false)">
                          <strong>Enable syslog'ing to remote syslog server</strong></td>
                      </tr>
                      <tr>
                        <td width="22%" valign="top" class="vtable">&nbsp;</td>
                        <td width="78%" class="vtable"> <input name="disablelocallogging" type="checkbox" id="disablelocallogging" value="yes"  onClick="enable_change(false)">
                          <strong>Disable writing log files to the local ram disk</strong></td>
                       </tr>
                      <tr>
                        <td width="22%" valign="top" class="vncell">Remote syslog
                          server</td>
                        <td width="78%" class="vtable"> <input name="remoteserver" id="remoteserver" type="text" class="formfld" size="20" value="">
                          <br>
                          IP address of remote syslog server<br> <br> <input name="system" id="system" type="checkbox" value="yes" onclick="enable_change(false)" >
                          system events <br> <input name="filter" id="filter" type="checkbox" value="yes" >
                          firewall events<br> <input name="dhcp" id="dhcp" type="checkbox" value="yes" >
                          DHCP service events<br> <input name="portalauth" id="portalauth" type="checkbox" value="yes" >
                          Portal Auth<br> <input name="vpn" id="vpn" type="checkbox" value="yes" >
                          VPN events
			<br> <input name="logall" id="logall" type="checkbox" value="yes" >
                          Everything</td>
                      </tr>
                      <tr>
                        <td width="22%" valign="top">&nbsp;</td>
                        <td width="78%"> <input name="Submit" type="submit" class="formbtn" value="Save" onclick="enable_change(true)">
                        </td>
                      </tr>
                      <tr>
                        <td width="22%" height="53" valign="top">&nbsp;</td>
                        <td width="78%"><strong><span class="red">Note:</span></strong><br>
                          syslog sends UDP datagrams to port 514 on the specified
                          remote syslog server. Be sure to set syslogd on the
                          remote server to accept syslog messages from pfSense.
                        </td>
                      </tr>
                    </table>
	</div>
    </td>
  </tr>
</table>
</form>
<script language="JavaScript">
<!--
enable_change(false);
//-->
</script>
<?php
	include("fend.inc");
?>
</body>
</html>
