<?php
	include("head.inc");
?>

<body link="#0000CC" vlink="#0000CC" alink="#0000CC">
<?php
	include("fbegin.inc");
?>
<p class="pgtitle">诊断: 重启系统</p>
<div id="canvas1" style="display:none">
	<p><strong>当前设备将会在<span id="sec"></span>秒钟内重启</strong></p>
    <p> 
		<input type="button" class="formbtn" value=" 立即重启 " onclick="send_reboot()">
		<input type="button" class="formbtn" value=" 取消重启 " onclick="window.location='index.php'">
    </p>
		
</div>
<div id="canvas2" style="display:none">
	<p><strong>设备正在重启, 请等待</strong></p>
</div>
<div id="canvas">
      
        <p><strong>你确认想重新启动当前设备吗?</strong></p>
        <p> 
		<input name="Submit" type="button" class="formbtn" value=" 确定 " onclick="do_step1()">
		<input type="button" class="formbtn" value=" 取消 " onclick="history.back(-1)">
        </p>
      </form>
</div>

<?php
	include("fend.inc");
?>
<script language="javascript">

o1 = document.getElementById("canvas1");
o2 = document.getElementById("canvas2");
o0 = document.getElementById("canvas");
osec = document.getElementById("sec");

var sec = 10;
var oT = null;
function wait10()
{
	osec.innerHTML = --sec;
	if(sec == 0) {send_reboot();return;}
	oT = setTimeout("wait10()", 1000);
}

function send_reboot()
{
	o1.style.display = "none";
	o2.style.display = "";
}

function do_step1()
{
	o0.style.display = "none";
	o1.style.display = "";
	
	sec = 10;wait10();
}

function do_reboot()
{


}

</script>

</body>
</html>
