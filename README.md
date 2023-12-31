# Proyecto de Detección de Movimiento con NodeMCU y LM386

## Descripción
Este proyecto utiliza un NodeMCU para detectar movimiento a través de un sensor PIR y, en respuesta, reproduce un archivo de audio almacenado en una tarjeta SD. La señal de audio se amplifica utilizando un circuito con un LM386.

## Creadores
- **MoonMakers**
- **Nada que hacer**


[![MoonMakers](https://yt3.googleusercontent.com/ytc/APkrFKaYfTydgBwDyVQie8Ydaq5RVH_9_k-87lEnMcHvAQ=s176-c-k-c0x00ffffff-no-rj-mo)](https://www.youtube.com/@NadaQueHacer)
[![MoonMakers](https://yt3.googleusercontent.com/7W7Ap3W9coRjVPdUCT2_C6HjXWZPdG7X7fq7T01SYlBFuq8G52CiA03x_4d2duYNLXkKKeTxKg=s176-c-k-c0x00ffffff-no-rj)](https://www.youtube.com/@MoonMakers)


## Esquemático de Conexiones del proyecto basico
![Esquemático](imgs/proyecto-basico.png)

## Esquemático de Conexiones del proyecto con la bocina
![Esquemático](imgs/protecto-pro.png)

## Componentes
- NodeMCU
- Sensor PIR
- LM386 Amplificador
- Tarjeta SD
- Bocina

## Código Fuente

### NodeMCU
- http://arduino.esp8266.com/stable/package_esp8266com_index.json
### Librerias
- [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio)
- [SD](https://github.com/arduino-libraries/SD)
