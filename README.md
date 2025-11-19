<!--Big dependency problem explanation, by l0c

    l0c says:
        the movement demands knowledge of 
        the mpu during movement. Then we'll
        pass the mpu as a dependency on movement
        AND on the blasted main. 

        Main's job is initializaing the mpu. 
        Meanwhile, movement's job is taking a
        look at the giroscope when executing and 
        correcting till gyroY <= .01

        Thats that. 

        then
            accsensor -> main
            accsensor -> movement
-->
# Projeto Integrador I
## Grupo 02, Professor Ajax


