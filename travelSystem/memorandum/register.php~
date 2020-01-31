<?php
$name = $_POST["username"];
$password1 = $_POST["password1"];
$password2 = $_POST["password2"];
if($password1 != $password2){
 ?>
	 <script> 	
	   alert("输入密码不一致");
		var url = window.location.href;  
		var folder = url.substring(0,url.lastIndexOf('/'));
		//var loc = url.substring(url.lastIndexOf('/')+1, url.length);   	
		location.href = folder+"/register.html";
   </script>
<?php
}
else {
	$conn = mysql_connect("localhost","root","19941212") or die("无法连接数据库，请重试");
	mysql_select_db("GIS") or die(mysql_error());
	$query = "insert into `user` values (\"$name\",\"$password1\");"; 
	//echo $query;
		
	mysql_query($query);	
	if(mysql_affected_rows() <= 0){
		die('Could not register: ' . mysql_error());
	}
	else {	
		printf("Records affected: %d\n", mysql_affected_rows());
?>
	 <script> 	
	   alert("注册成功! 关闭提示窗口，返回登陆界面");
		var url = window.location.href;  
		var folder = url.substring(0,url.lastIndexOf('/'));
		location.href = folder+"/main.html";
   </script>
<?php		
	}
	mysql_close();
}
?>