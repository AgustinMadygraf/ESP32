<?php
// Rui Santos
// Complete project details at https://RandomNerdTutorials.com/esp32-cam-post-image-photo-server/
// Code Based on this example: w3schools.com/php/php_file_upload.asp

$target_dir = "uploads/";
$current_time = mktime(date('H')+0, date('i'), date('s'), date('m'), date('d'), date('y'));
$targetFilePath = $target_dir . date('Y.m.d_H:i:s_', $current_time) . basename($_FILES["imageFile"]["name"]);
$isUploadSuccessful = 1;
$imageFileExtension = strtolower(pathinfo($targetFilePath,PATHINFO_EXTENSION));

// Check if image file is a actual image or fake image
if(isset($_POST["submit"])) {
  $check = getimagesize($_FILES["imageFile"]["tmp_name"]);
  if($check !== false) {
    echo "File is an image - " . $check["mime"] . ".";
    $isUploadSuccessful = 1;
  }
  else {
    echo "File is not an image.";
    $isUploadSuccessful = 0;
  }
}

// Check if file already exists
if (file_exists($targetFilePath)) {
  echo "Sorry, file already exists.";
  $isUploadSuccessful = 0;
}

// Check file size
if ($_FILES["imageFile"]["size"] > 500000) {
  echo "Sorry, your file is too large.";
  $isUploadSuccessful = 0;
}

// Allow certain file formats
if($imageFileExtension != "jpg" && $imageFileExtension != "png" && $imageFileExtension != "jpeg"
&& $imageFileExtension != "gif" ) {
  echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
  $isUploadSuccessful = 0;
}

// Check if $isUploadSuccessful is set to 0 by an error
if ($isUploadSuccessful == 0) {
  echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
}
else {
  if (move_uploaded_file($_FILES["imageFile"]["tmp_name"], $targetFilePath)) {
    echo "The file ". basename( $_FILES["imageFile"]["name"]). " has been uploaded.";
  }
  else {
    echo "Sorry, there was an error uploading your file.";
  }
}
?>