set path="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin"

echo "Flashing new bootloader"
avrdude -P com6 -c stk500hvsp -p t85 -U flash:w:bootloader/main.hex:i -B 20

echo "Press enter to configure fuses and disable reset pin"
pause
avrdude -P com6 -c stk500hvsp -p t85 -U lfuse:w:0xe1:m -U efuse:w:0xfe:m -U hfuse:w:0x5d:m


