<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include 'conexion.php';

if ($con) {
    echo "Conexión con base de datos exitosa! ";
    
    // Mostrar todos los datos POST recibidos
    echo "<pre>";
    print_r($_POST);
    echo "</pre>";

    if (isset($_POST['temperatura']) && isset($_POST['humedad'])) {
        $temperatura = mysqli_real_escape_string($con, $_POST['temperatura']);
        $humedad = mysqli_real_escape_string($con, $_POST['humedad']);
        
        echo "Estación meteorológica";
        echo " Temperatura: " . htmlspecialchars($temperatura);
        echo " Humedad: " . htmlspecialchars($humedad);
        
        date_default_timezone_set('America/Costa_Rica');
        $fecha_actual = date("Y-m-d H:i:s");

        $consulta = "INSERT INTO Tb_DHT11 (Temperatura, Humedad, fecha_actual) VALUES (?, ?, ?)";
        
        if ($stmt = mysqli_prepare($con, $consulta)) {
            mysqli_stmt_bind_param($stmt, "dds", $temperatura, $humedad, $fecha_actual);
            
            if (mysqli_stmt_execute($stmt)) {
                echo " Registro en base de datos OK! ";
            } else {
                echo " Falla! Registro BD. Error: " . mysqli_error($con);
            }

            mysqli_stmt_close($stmt);
        } else {
            echo " Error al preparar la consulta. Error: " . mysqli_error($con);
        }
    } else {
        echo "No se recibieron datos POST.";
    }
} else {
    echo "Falla! Conexión con base de datos. Error: " . mysqli_connect_error();
}

mysqli_close($con);
?>
