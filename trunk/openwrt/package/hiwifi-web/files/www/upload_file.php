<?php
if ($_FILES["firmware"]["error"] > 0) {
	echo "Error: " . $_FILES["firmware"]["error"] . "<br />";
}
else
{
	echo "Upload: " . $_FILES["firmware"]["name"] . "<br />";
	echo "Type: " . $_FILES["firmware"]["type"] . "<br />";
	echo "Size: " . ($_FILES["firmware"]["size"] / 1024) . " Kb<br />";
	echo "Stored in: " . $_FILES["firmware"]["tmp_name"];
  
	if (file_exists("/tmp/" . $_FILES["firmware"]["name"])) {
		echo $_FILES["firmware"]["name"] . " already exists. ";
	}
	else {
		move_uploaded_file($_FILES["firmware"]["tmp_name"],
							"/tmp/" . $_FILES["firmware"]["name"]);
		echo "Stored in: " . "/tmp/" . $_FILES["firmware"]["name"];
    }
}
?>
