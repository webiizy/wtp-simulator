<?php
	include("head.inc");
?>
<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">服务: DHCP: 编辑静态地址</p>
            <form action="services_dhcp_edit.php" method="post" name="iform" id="iform">
              <table width="100%" border="0" cellpadding="6" cellspacing="0">
                <tr> 
                  <td width="22%" valign="top" class="vncellreq">MAC地址</td>
                  <td width="78%" class="vtable"> 
                    <input name="mac" type="text" class="formfld" id="mac" size="30" value="">
		    		    <a OnClick="document.forms[0].mac.value='00:50:56:c0:00:08';" href="services_dhcp_edit.php#">复制本机地址</a>   		    
                    <br>
                    <span class="vexpl">MAC地址格式:
                    xx:xx:xx:xx:xx:xx</span></td>
                </tr>
                <tr> 
                  <td width="22%" valign="top" class="vncell">IP地址</td>
                  <td width="78%" class="vtable"> 
                    <input name="ipaddr" type="text" class="formfld" id="ipaddr" size="20" value="">
                    <br>
                   </td>
                </tr>
                <tr> 
                  <td width="22%" valign="top" class="vncell">主机名</td>
                  <td width="78%" class="vtable"> 
                    <input name="hostname" type="text" class="formfld" id="hostname" size="20" value="">
                    <br> <span class="vexpl">不包括域名部分.</span></td>
                </tr>				
                <tr> 
                  <td width="22%" valign="top" class="vncell">描述</td>
                  <td width="78%" class="vtable"> 
                    <input name="descr" type="text" class="formfld" id="descr" size="40" value=""> 
                    <br> <span class="vexpl">此设备的部分描述.</span></td>
                </tr>
                <tr> 
                  <td width="22%" valign="top">&nbsp;</td>
                  <td width="78%"> 
                    <input name="Submit" type="submit" class="formbtn" value="确定"> 
					<input class="formbtn" type="button" value="取消" onclick="history.back()">
					<input name="if" type="hidden" value="lan"> 
                  </td>
                </tr>
              </table>
</form>
<?php
	include("fend.inc");
?>
</body>
</html>
