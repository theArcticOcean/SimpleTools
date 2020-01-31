<?php  
$conn = mysql_connect("localhost","root","19941212") or die("无法连接数据库，请重试");
mysql_select_db("GIS") or die(mysql_error());

$addr = $_SERVER['HTTP_REFERER'];
if (strpos($addr, '?username=') !== false) {
		$name = $_GET['username'];
}
else {
	
$name = $_POST["username"];
$password = $_POST["password"];
$query = "SELECT * FROM `user` WHERE email=\"$name\" and passwd=\"$password\""; 

$result = mysql_query($query); 
$numrows = mysql_num_rows($result);
if($numrows == 0){ 
?>	
	<script>
	alert("非法用户,请注册. \n 关闭提示窗口，返回登陆界面");
	var url = window.location.href;  
	var folder = url.substring(0,url.lastIndexOf('/'));
	location.href = folder+"/main.html";
	</script>	
	
<?php
}
}
?>  
<table width=90% border="0" align="center" cellpadding="5" cellspacing="1" bgcolor="#add3ef">  
<?php  
$sql="select * from text where email = \"$name\" order by time desc ";  
$result = mysql_query($sql);  
while($row = mysql_fetch_array($result)){  
?>  
  <tr bgcolor="#eff3ff">  
  <td>  
  <font color="red"><?php echo $row['title']; ?></font> &nbsp &nbsp    
  <a href="<?php echo "delete.php?username=".$name."&title=".$row['title'] ?>">删除</a>  
  <a href="<?php echo "edit.php?username=".$name."&title=".$row['title'] ?>">编辑</a>  
  </td>  
  </tr>  
  <tr bgColor="#ffffff">  
  <td>
  <span style="font-family:微软雅黑;font-size:17px;color:#7f7f7f;font-style: normal;   
  font-variant: normal; font-weight: normal; letter-spacing: normal; line-height: 21px;   
  orphans: auto; text-align: left; text-indent: 0px; text-transform: none; white-space:   
  normal; widows: auto; word-spacing: 0px; -webkit-text-stroke-width: 0px; background-color:   
  rgb(255, 255, 255); display: inline !important; float: none;">  
  内容：<br>
  <?php echo $row['context']; ?>
  </span>  
  </td>  
  </tr>  
<?php  
}  
?>  
</table>  
<table width=90% border="0" align="center" cellpadding="5" cellspacing="1" bgcolor="#add3ef">  
<tr><td>
<form method="post" action="new.php?username=<?php echo $name; ?>">
<input type="submit" name="submit" value="新建"/>
</form>
</td></tr>
</table>

<?php
 mysql_close();  
?> 
