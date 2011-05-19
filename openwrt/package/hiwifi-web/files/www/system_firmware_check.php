<?php
	include("head.inc");
?>
<script src="javascript/scriptaculous/prototype.js" type="text/javascript"></script>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">系统: 固件升级: (网络)</p>

<form action="system_firmware_auto.php" method="post">
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td>
<table cellpadding='0' cellspacing='0'>
 <tr height='1'>
  <td bgcolor='#777777' onClick="document.location='system_firmware.php'" style="cursor: pointer;"><div id='tabdeactive0'></div></td>
  <td bgcolor='#EEEEEE' onClick="document.location='system_firmware_check.php'" style="cursor: pointer;"><div id='tabactive'></div></td>
</tr>
<tr>
  <td bgcolor='#777777' onClick="document.location='system_firmware.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;<a href='system_firmware.php'><font color='white'>本地升级</a>&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  <td bgcolor='#EEEEEE' onClick="document.location='system_firmware_check.php'" style="cursor: pointer;"><B>&nbsp;&nbsp;&nbsp;网络升级&nbsp;&nbsp;&nbsp;<font size='-12'>&nbsp;</td>
  </tr>
</table>
<script type="text/javascript">NiftyCheck();
Rounded("div#tabactive","top","#FFF","#EEEEEE","smooth");
Rounded("div#tabdeactive0","top","#FFF","#777777","smooth");
</script>		</td>
	</tr>
	<tr>
	  <td class="tabcont">
	      <table width="100%" border="0" cellpadding="6" cellspacing="0">
		<tr>
		  <td>
		      <!-- progress bar -->
		      <center>
							<table height='15' width='420' border='0' colspacing='0' cellpadding='0' cellspacing='0'>

							<tr>
								<td background="themes/pfsense/images/misc/bar_left.gif" height='15' width='5'>
								</td>
								<td>
								<table id="progholder" name="progholder" height='15' width='410' border='0' colspacing='0' cellpadding='0' cellspacing='0'>
									<td background="themes/pfsense/images/misc/bar_gray.gif" valign="top" align="left">
										<img src='themes/pfsense/images/misc/bar_blue.gif' width='0' height='15' name='progressbar' id='progressbar'>
									</td>
								</table>
							</td>
							<td background="themes/pfsense/images/misc/bar_right.gif" height='15' width='5'>
							</td>
						</tr>
					</table>
		      <br>                      
		      <!-- command output box -->
		      即将完成                    
		      </center>
 			<p>
			<center><input id='invokeupgrade' style='visibility:hidden' type="submit" value="Invoke Auto Upgrade">
		  </td>
		</tr>
	      </table>
	  </td>
	</tr>
</table>

<p>

</form>
<?php
	include("fend.inc");
?>
</body>
</html>
