# UVTimer - device that created for flare(polymerization) of photoresist
## Features:   
* 1-100 sec timer
* Attiny2313 and tm1637( display).
* Matrix of UV Led in led strip, voltage 12 V, current draw of matrix ~1 A, Power 12W. Ppolymerization of standart photoresist takes only **55 seconds**. Work zone 10x15 cm
* Matrix power by usb step-up board 5V->12V. USB current draw ~2.5A,so all system can be powered up from powerbank or the computer. **WARNING** The limit of stanart usb 2A so if you want to power system from weak powerbanks, then power matrix lower voltage, something about 11V
* Matrix controlled with MOSFET IRF530, 1A for that transistor is easy to controll.
## Known limitations:
* Timer accuracy 2 sec on 100 sec. Use extrenetal quarz to achieve maximum accuracy.
* Chinense chip led strip **BAD**. It heats from 20C up to 80C in 100 seconds. Use beeter strip in your project)
## Photo of system
![Img](/1.jpg)
![Img](/2.jpg)
![Img](/3.jpg)
![Img](/4.jpg)