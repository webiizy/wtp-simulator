<?php
	include("head.inc");
?>
<body link="#000000" vlink="#000000" alink="#000000">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: Ping</p>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
        <tr>
                <td>
			<form action="diag_ping.php" method="post" name="iform" id="iform">
			  <table width="100%" border="0" cellpadding="6" cellspacing="0">
                <tr>
				  <td width="22%" valign="top" class="vncellreq">主机名或者IP地址</td>
				  <td width="78%" class="vtable"> 
                    <input name="host" type="text" class="formfld" id="host" size="20" value=""></td>
				</tr>
				<tr>
				  <td width="22%" valign="top" class="vncellreq">次数</td>
				  <td width="78%" class="vtable">
					<select name="count" class="formfld" id="count">
						<option value="1" >1</option>
						<option value="2" >2</option>
						<option value="3" selected>3</option>
						<option value="4" >4</option>
						<option value="5" >5</option>
						<option value="6" >6</option>
						<option value="7" >7</option>
						<option value="8" >8</option>
						<option value="9" >9</option>
						<option value="10" >10</option>
					</select></td>
				</tr>
				<tr>
				  <td width="22%" valign="top">&nbsp;</td>
				  <td width="78%"> 
                    <input name="Submit" type="submit" class="formbtn" value="Ping">
				</td>
				</tr>
				<tr>
					<td valign="top" colspan="2">
					</td>
				</tr>		
			</table>
</form>
</td></tr></table>
<?php
	include("fend.inc");
?>
</body>
</html>
