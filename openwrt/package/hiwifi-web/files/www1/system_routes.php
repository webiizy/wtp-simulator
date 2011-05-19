<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">系统: 静态路由</p>
<form action="system_routes.php" method="post">
<input type="hidden" name="y1" value="1">

	     
              <table width="100%" border="0" cellpadding="0" cellspacing="0">
                <tr>
                  <td width="15%" class="listhdrr">Interface</td>
                  <td width="25%" class="listhdrr">Network</td>
                  <td width="20%" class="listhdrr">Gateway</td>
                  <td width="30%" class="listhdr">Description</td>
                  <td width="10%" class="list">
			<table border="0" cellspacing="0" cellpadding="1">
			   <tr>
				<td width="17"></td>
				<td><a href="system_routes_edit.php"><img src="themes/nervecenter/images/icons/icon_plus.gif" width="17" height="17" border="0"></a></td>
			   </tr>
			</table>
		  </td>
		</tr>
			                  <tr>
                  <td class="list" colspan="4"></td>
                  <td class="list">
			<table border="0" cellspacing="0" cellpadding="1">
			   <tr>
				<td width="17"></td>
				<td><a href="system_routes_edit.php"><img src="themes/nervecenter/images/icons/icon_plus.gif" width="17" height="17" border="0"></a></td>
			   </tr>
			</table>
		  </td>
		</tr>
              </table>
            </form>
			<!--
			<p><b>注意:</b></p>
			-->

<?php
	include("fend.inc");
?>
</body>
</html>

