<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">Diagnostics: System logs: DHCP</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
  <tr><td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><div id='tabdeactive1'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><div id='tabdeactive2'></div></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><div id='tabdeactive3'></div></td>
</tr>
<tr>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<font color='white'>System</font>&nbsp;&nbsp;&nbsp;&nbsp;</td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_dhcp.php'><font size='-12'>DHCP</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_auth.php'><font color='white'>Portal Auth</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='diag_logs_settings.php'><font color='white'>Settings</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
</tr>
<tr height='5px'>
  <td bgcolor='#777777' onClick="document.location='diag_logs.php'" style="cursor: pointer;"></td>
  <td bgcolor='#EEEEEE' onClick="document.location='diag_logs_dhcp.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_auth.php'" style="cursor: pointer;"></td>
  <td bgcolor='#777777' onClick="document.location='diag_logs_settings.php'" style="cursor: pointer;"></td>
 </tr>
</table>
<script type="text/javascript">NiftyCheck();
Rounded("div#tabactive","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive1","top","#FFF","#EEEEEE","smooth");
Rounded("div#tabdeactive2","top","#FFF","#777777","smooth");
Rounded("div#tabdeactive3","top","#FFF","#777777","smooth");
</script>  </td></tr>
  <tr>
    <td>
	<div id="mainarea">
		<table class="tabcont" width="100%" border="0" cellspacing="0" cellpadding="0">
		  <tr>
			<td colspan="2" class="listtopic">
			  最新的50条DHCP服务日志</td>
		  </tr>
		  <tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:47</td>
<td class="listr">dhcpd: Sending on   BPF/em1/00:0c:29:5e:e6:9b/192.168.1/24</td>
</tr>
<tr valign="top">
<td class="listlr" nowrap>Feb 21 15:15:47</td>
<td class="listr">dhcpd: Sending on   Socket/fallback/fallback-net</td>
</tr>

		<tr><td><br><form action="diag_logs_dhcp.php" method="post">
<input name="clear" type="submit" class="formbtn" value="Clear log"></td></tr>
		</table>
	</div>
</form>
	</td>
  </tr>
</table>
                </div> <!-- Right DIV -->
        </div> <!-- Content DIV -->
        <div id="footer">
			<a target="_blank" href="http://www.pfsense.org/?gui12" class="redlnk">pfSense</a> is &copy;
			 2004 - 2009 by <a href="http://www.bsdperimeter.com" class="tblnk">BSD Perimeter LLC</a>. All Rights Reserved.
			[<a href="license.php" class="tblnk">view license</a>] 
			<br/>
			[<a target="_blank" href="https://portal.pfsense.org/?guilead=true" class="tblnk">Commercial Support Available</a>]
		</div> <!-- Footer DIV -->
</div> <!-- Wrapper Div -->
<script type="text/javascript" src="themes/nervecenter/bottom-loader.js"></script>

</body>
</html>
