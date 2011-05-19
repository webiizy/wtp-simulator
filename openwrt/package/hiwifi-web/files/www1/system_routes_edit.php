<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">系统: 静态路由: 编辑</p>
            <form action="system_routes_edit.php" method="post" name="iform" id="iform">
              <table width="100%" border="0" cellpadding="6" cellspacing="0">
                <tr> 
                  <td width="22%" valign="top" class="vncellreq">接口</td>
                  <td width="78%" class="vtable">
<select name="interface" class="formfld">
                                            <option value="lan" > 
                      LAN                      </option>
                                            <option value="wan" > 
                      WAN                      </option>
                                            <option value="pptp" > 
                      PPTP                      </option>
                                          </select> <br>
                    <span class="vexpl">Choose which interface this route applies to.</span></td>
                </tr>
                <tr>
                  <td width="22%" valign="top" class="vncellreq">目标网络(或主机)</td>
                  <td width="78%" class="vtable"> 
                    <input name="network" type="text" class="formfld" id="network" size="20" value=""> 
				  / 
                    <select name="network_subnet" class="formfld" id="network_subnet">
						<?php
							for($i = 32; $i >= 8; $i--) {
								echo '<option value="' . $i . '">' . $i . '</option>';
							}
						?>
                                          </select>
                    <br> <span class="vexpl">此静态路由的目标网络</span></td>
                </tr>
				<tr>
                  <td width="22%" valign="top" class="vncellreq">网关</td>
                  <td width="78%" class="vtable"> 
                    <input name="gateway" type="text" class="formfld" id="gateway" size="40" value="">
                    <br> <span class="vexpl">可通向目标网络的网关</span></td>
                </tr>
				<tr>
                  <td width="22%" valign="top" class="vncell">描述</td>
                  <td width="78%" class="vtable"> 
                    <input name="descr" type="text" class="formfld" id="descr" size="40" value="">
                    <br> <span class="vexpl">本条路由的一些描述.</span></td>
                </tr>
                <tr>
                  <td width="22%" valign="top">&nbsp;</td>
                  <td width="78%"> 
                    <input name="Submit" type="submit" class="formbtn" value="确定"> 
					<input type="button" value="取消" class="formbtn"  onclick="history.back()">
                                      </td>
                </tr>
              </table>
</form>
<?php
	include("fend.inc");
?>
<script language="JavaScript">
	enable_change();
</script>
</body>
</html>
