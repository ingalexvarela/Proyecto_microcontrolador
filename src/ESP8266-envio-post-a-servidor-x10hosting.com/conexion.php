<?php
$server = "localhost";
$user = "tbztwdzc_esp328266";
$pass = "CCr74Drx4wS9fxYXPacv";
$db = "tbztwdzc_esp328266";  // Corregido el nombre de la base de datos

// Crea la conexión
$con = new mysqli($server, $user, $pass, $db);

// Verifica la conexión
if ($con->connect_error) {
    die("Error al conectar con la base de datos: " . $con->connect_error);
}
?>
