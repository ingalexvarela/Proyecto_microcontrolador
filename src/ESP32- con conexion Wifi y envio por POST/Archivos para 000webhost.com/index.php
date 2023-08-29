<!DOCTYPE html>
<!– Inicio de pagina con esta etiqueta –>
    <html>


    <!– Agrega titulos, idioma, tiempo de Refrescar pág, estilo, declaración, escalado de contenido–>

        <head>
            <meta name="viewport" content="width=device-width, user-scalable=no">
            <meta http-equiv="refresh" content="45" charset="UTF-8">

            <title>
                Estación Meteorológica con IoT
            </title>

            <style>
                body {
                    font-family: monospace;
                    background-color: rgb(4, 2, 7);
                    text-align: center; /* Centra el contenido en el cuerpo */
                }

                h1 {
                    color: white;
                    margin: 5px;
                    text-align: center;
                    margin: 50px;
                    font-size: 30px;
                }
                
                h2 {
                    color: orange;
                    margin: 5px;
                    text-align: center;
                    margin: 50px;
                    font-size: 18px;
                }
                
                h3 {
                    color: skyblue;
                    margin: 5px;
                    text-align: center;
                    margin: 50px;
                    font-size: 18px;
                }
                
                h4 {
                    color: purple;
                    margin: 5px;
                    text-align: center;
                    margin: 50px;
                    font-size: 24px;
                }

                .barraTemp {
                    height: 200px;
                    width: 190px;
                    background-color: rgba(0, 0, 0, 0.795);
                    margin: auto;
                    border-radius: 50%;
                    overflow: hidden;
                }

                .cont {
                    height: 100px;
                    width: 200px;
                }

                .CirculoCentro {
                    height: 150px;
                    width: 150px;
                    background-color: rgb(4, 2, 7);
                    border-radius: 50%;
                    margin: auto;
                    position: relative;
                    margin: -175px auto 50px;
                }

                .Rectangulo {
                    height: 100px;
                    width: 200px;
                    background-color: rgb(4, 2, 7);
                    position: relative;
                    margin: -125px auto 50px;
                }
            </style>
        </head>

        <!– Contenido de pagina, h1 son las escrituras, div figuras y sub figuras –>

            <Body>
                <h1>
                    Laboratorio de telecomunicaciones - 201
                </h1>
                  
                
                <h1> 
                <?php
            	include'conexion.php';       
                // Crea la conexión
                $conn = mysqli_connect($server, $user, $pass, $db);
            	// Verifica la conexión
            	if (!$conn) {
            	    die("Conexión fallida: " . mysqli_connect_error());
            	}
            	// Selecciona la base de datos
            	mysqli_select_db($conn, $db);
            	// Selecciona la última fila de la tabla TB_DHT11
            	$sql = "SELECT * FROM TB_DHT11 ORDER BY fecha_actual DESC LIMIT 1";
            	$result = mysqli_query($conn, $sql);
            	
                // Obtener el valor de la temperatura desde la base de datos
                if (mysqli_num_rows($result) > 0) {
                $row = mysqli_fetch_assoc($result);
                $temperatura = $row["Temperatura"];
                $humedad = $row["Humedad"];
                $fecha = $row["fecha_actual"];
                } 
                // Calcular el ángulo correspondiente a la temperatura
                $angulo = $temperatura * 1.8; // Multiplica por 1.8 para convertir de Celsius a grados
                $angulo1 = $humedad * 1.8; // Multiplica por 1.8 para convertir de Celsius a grados
                mysqli_close($conn);
                ?>
                </h1>

                <!-- Agregar el estilo CSS con el ángulo calculado -->
                <div class='barraTemp' style='transform: rotate(<?php echo $angulo; ?>deg);'>
                <div class="cont" style="background-color: rgb(143, 136, 136);"> </div>
                <div class="cont" style="background-color: rgba(253, 114, 0, 0.986);"> </div>
                </div>
                <div class="CirculoCentro"></div>
                <div class="Rectangulo"></div>
                <h2 style="font-size: 22px; position: relative; margin: -125px auto 50px;"> 
                <?php echo "Temperatura: " . $temperatura . " &deg;C<br>";  ?> </h2>                
                

                <!--  Medición de la humedad relativa -->
                <!-- Agregar el estilo CSS con el ángulo calculado -->
                <div class='barraTemp' style='transform: rotate(<?php echo $angulo1; ?>deg);'>
                <div class="cont" style="background-color: rgb(143, 136, 136);"> </div>
                <div class="cont" style="background-color: rgb(23, 218, 224);"> </div>
                </div>
                <div class="CirculoCentro"></div>
                <div class="Rectangulo"></div>
                <h3 style="font-size: 22px; position: relative; margin: -125px auto 50px;"> 
                <?php echo "Humedad relativa: " . $humedad . " %<br>";  ?> </h3>
                
                <h4 style="font-size: 22px; position: relative; margin: -0px auto 50px;"> 
                <?php echo "Fecha del registro: " .$fecha;  ?> </h4>
                
                
                
                <img src="https://i.postimg.cc/hvtdRL0p/iconopeque.jpg" alt="Descripción de la imagen">
            

            </Body>
    
    </html>
    <!– Fin de pagina con esta etiqueta –>
    




