<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, user-scalable=no">
    <meta http-equiv="refresh" content="5" charset="UTF-8">
    <title>Automata-Estación</title>
    <style>

        body {
        font-family: monospace;
        //background-color: rgb(20, 21, 38); /* Color de fondo de respaldo, por si la imagen no se carga */
        background-image: url('imagen.jpeg'); /* Ruta de la imagen de fondo */
        background-size: cover; /* Ajusta la imagen para que cubra todo el área del contenedor */
        background-position: center; /* Centra la imagen de fondo */
        background-repeat: no-repeat; /* Evita que la imagen se repita */
        margin: 0;
        padding: 0;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
        overflow: hidden;
        position: relative;
    }


        h1 {
            color: white;
            text-align: center;
            top: 30%;
            left: 50%;
            font-size: 15px;
            z-index: 100;
        }

         h9 {
            color: white;
            text-align: center;
            margin: 20px 0;
            font-size: 24px;
            z-index: 100;
        }

        .barraTemp {
            height: 200px;
            width: 200px;
            border-radius: 50%;
            overflow: hidden;
            position: relative;
        }

        .cont {
            height: 100px;
            width: 200px;
        }

        .circulo_centro, .circulo_centro1 {
            width: 150px;
            height: 150px;
            background-color: black;
            border-radius: 50%;
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
        }

        .rectangulo, .rectangulo1 {
            width: 210px;
            height: 110px;
            background-color: black;
            position: absolute;
            left: 50%;
            transform: translateX(-50%);
            top: 45%;
            margin-top: 10px;
        }
    
         .rectanguloG {
            width: 600px;
            height: 390px;
            background-color: black;
            position: absolute;
            left: 50%;
            transform: translateX(-50%);
            top: 20%;
            margin-top: 10px;
            z-index: -1;
        }

        .container {
            display: flex;
            justify-content: center;
            align-items: center;
            gap: 30px;
            position: relative;
        }

        h4 {
            color: white;
            text-align: center;
            margin: 40px;
            font-size: 22px;
        }

        .container > div {
            text-align: center;
            position: relative;
        }

        .custom-label {
            position: absolute;
            width: 100%;
            text-align: center;
            font-size: 22px;
            color: white;
            z-index: 10; /* Asegura que esté por encima de otros elementos */
        }

        .temp-label {
            color: white;
            top: 30%;
            left: 50%;
            transform: translateX(-50%);
        }

        .humidity-label {
            color: white;
            top: 30%;
            left: 50%;
            transform: translateX(-50%);
        }

         .fecha-label {
            color: green;
            top: 72%;
            left: 50%;
            transform: translateX(-50%);
        }

        .custom-label1 {
            position: absolute;
            font-size: 22px;
            color: white;
            font-style: italic;
            z-index: 10; /* Asegura que esté por encima de otros elementos */
        }

        .label1 {
            top: 62%; /* Ajusta este valor si es necesario */
            left: 35%;
             color: orange;
        }

        .label2 {
            top: 62%; /* Ajusta este valor si es necesario */
            left: 55%;
             color: blue;
        }
        
</style>




</head>

<body>
    <h9>Estación meteorológica con IOT</h9>

    <?php
    include 'conexion.php'; // Incluye el archivo de conexión

    // Verifica la conexión
    if ($con->connect_error) {
        $conexion_status = "dB= OFF";
    } else {
        $conexion_status = "dB= ON";

        // Realiza la consulta para obtener los últimos datos de la tabla
        $sql = "SELECT * FROM Tb_DHT11 ORDER BY fecha_actual DESC LIMIT 1";
        $result = $con->query($sql);

        if ($result->num_rows > 0) {
            // Obtiene la última fila
            $row = $result->fetch_assoc();
            $temperatura = $row['Temperatura'];
            $humedad = $row['Humedad'];
            $fecha = $row['fecha_actual'];
        } else {
            $temperatura = "No disponible";
            $humedad = "No disponible";
            $fecha = "No disponible";
        }

        $con->close();
    }
    ?>

    <h1><?php echo $conexion_status; ?></h1>

    <?php if ($conexion_status === "dB= ON") { ?>
        <div class="container">
            <div>
                <div class="barraTemp" style="transform: rotate(<?php echo $temperatura * 1.8; ?>deg);">
                    <div class="cont" style="background-color: rgb(143, 136, 136);"></div>
                    <div class="cont" style="background-color: orange;"></div>
                </div>
                <div class="circulo_centro"></div>
                <div class="rectangulo"></div>
                <div class="custom-label temp-label"><?php echo $temperatura; ?> °C</div>
            </div>

            <div>
                <div class="barraTemp" style="transform: rotate(<?php echo $humedad * 1.8; ?>deg);">
                    <div class="cont" style="background-color: rgb(143, 136, 136);"></div>
                    <div class="cont" style="background-color: rgb(0, 0, 253);"></div>
                </div>
                <div class="circulo_centro1"></div>
                <div class="rectangulo1"></div>
                <div class="custom-label humidity-label"><?php echo $humedad; ?> %</div>
            </div>
        </div>
        <div class="custom-label1 label1">Temperatura</div>
        <div class="custom-label1 label2">Humedad</div>
        <div class="custom-label fecha-label"><?php echo "Fecha del registro: " . $fecha; ?> </div>
        <div class="rectanguloG"></div>
    <?php } ?>

</body>

</html>